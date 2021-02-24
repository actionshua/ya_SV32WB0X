/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include "nimble/nimble_npl.h"

#include <stdio.h>
#include <string.h>
#include <soc_assert.h>
#include "os/os.h"

extern volatile u8 gOsFromISR;
#if 0
static inline bool
in_isr(void)
{
    /* XXX hw specific! */
    return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
}
#endif
struct ble_npl_event *
npl_freertos_eventq_get(struct ble_npl_eventq *evq, ble_npl_time_t tmo)
{
#if 1
    OS_STATUS ret = 0;
    struct ble_npl_event *ev = NULL;
    ret = OS_BufQPop(evq->q, &ev, tmo);

    if (ret == OS_SUCCESS && ev) {
        ev->queued = false;
    }
    ASSERT(ret == OS_SUCCESS);

    if (ev) {
        ev->queued = false;
    }
    return ev;
#else
    struct ble_npl_event *ev = NULL;
    BaseType_t woken;
    BaseType_t ret;

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        ASSERT(tmo == 0);
        ret = xQueueReceiveFromISR(evq->q, &ev, &woken);
        //portYIELD_FROM_ISR(woken);//--werner
        if( woken == pdTRUE )//++werner
            portYIELD_FROM_ISR();//++werner
    } else {
        ret = xQueueReceive(evq->q, &ev, tmo);
    }
    ASSERT(ret == pdPASS || ret == errQUEUE_EMPTY);

    if (ev) {
        ev->queued = false;
    }

    return ev;
#endif
}

void
npl_freertos_eventq_put(struct ble_npl_eventq *evq, struct ble_npl_event *ev)
{
#if 1
    u32 count = 0;
    OS_STATUS ret = 0;
    if (ev->queued) {
            return;
    }

    CHECK_EVQMEM(ev);
    CHECK_EVQMEM_FN(ev->fn);

    ev->queued = true;

    ret = OS_BufQPush(evq->q, &ev);

    if (ret != OS_SUCCESS) {
        count = OS_BufQWaitingSize(evq->q);
        printf("WaitingSize %d\n", count);
    }

    ASSERT(ret == OS_SUCCESS);
#else
    BaseType_t woken;
    BaseType_t ret;

    if (ev->queued) {
        return;
    }

    CHECK_EVQMEM(ev);
    CHECK_EVQMEM_FN(ev->fn);

    ev->queued = true;

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        ret = xQueueSendToBackFromISR(evq->q, &ev, &woken);
        //portYIELD_FROM_ISR(woken);//--werner
        if( woken == pdTRUE )//++werner
        {
            portYIELD_FROM_ISR();//++werner
        }

    } else {
        ret = xQueueSendToBack(evq->q, &ev, portMAX_DELAY);
    }

    ASSERT(ret == pdPASS);
#endif
}

void
npl_freertos_eventq_remove(struct ble_npl_eventq *evq,
                      struct ble_npl_event *ev)
{
#if 1
    if (!ev->queued) {
        return;
    }

    OS_BufQDelete(evq->q);

    ev->queued = 0;
#else
    struct ble_npl_event *tmp_ev;
    BaseType_t ret;
    int i;
    int count;
    BaseType_t woken, woken2;

    if (!ev->queued) {
        return;
    }

    /*
     * XXX We cannot extract element from inside FreeRTOS queue so as a quick
     * workaround we'll just remove all elements and add them back except the
     * one we need to remove. This is silly, but works for now - we probably
     * better use counting semaphore with os_queue to handle this in future.
     */

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        woken = pdFALSE;

        count = uxQueueMessagesWaitingFromISR(evq->q);
        for (i = 0; i < count; i++) {
            ret = xQueueReceiveFromISR(evq->q, &tmp_ev, &woken2);

            ASSERT(ret == pdPASS);
            woken |= woken2;

            if (tmp_ev == ev) {
                continue;
            }

            ret = xQueueSendToBackFromISR(evq->q, &tmp_ev, &woken2);
            if (!(ret == pdPASS))
                    printf("%s b assert", __func__);

            ASSERT(ret == pdPASS);
            woken |= woken2;
        }

        //portYIELD_FROM_ISR(woken);//--werner

        if( woken )//++werner
            portYIELD_FROM_ISR();//++werner
    } else {
        taskENTER_CRITICAL();

        count = uxQueueMessagesWaiting(evq->q);
        for (i = 0; i < count; i++) {
            ret = xQueueReceive(evq->q, &tmp_ev, 0);

            ASSERT(ret == pdPASS);

            if (tmp_ev == ev) {
                continue;
            }

            ret = xQueueSendToBack(evq->q, &tmp_ev, 0);

            ASSERT(ret == pdPASS);
        }

        taskEXIT_CRITICAL();//no use
    }

    ev->queued = 0;
#endif
}

ble_npl_error_t
npl_freertos_mutex_init(struct ble_npl_mutex *mu)
{
#if 1
    OS_STATUS ret = 0;
    if (!mu) {
        return BLE_NPL_INVALID_PARAM;
    }
    ret = OS_MutexInit(&mu->handle);

    ASSERT(ret == OS_SUCCESS);
    return BLE_NPL_OK;
#else
    if (!mu) {
        return BLE_NPL_INVALID_PARAM;
    }

    mu->handle = xSemaphoreCreateRecursiveMutex();
    if (mu->handle == NULL)
        printf("%s assert", __func__);

    ASSERT(mu->handle);

    return BLE_NPL_OK;
#endif
}

ble_npl_error_t
npl_freertos_mutex_pend(struct ble_npl_mutex *mu, ble_npl_time_t timeout)
{
#if 1
    OS_STATUS ret = 0;
    if (!mu) {
        return BLE_NPL_INVALID_PARAM;
    }
    ASSERT(mu->handle);
    ret = OS_MutexLock(mu->handle);

    return ret == OS_SUCCESS ? BLE_NPL_OK : BLE_NPL_TIMEOUT;
#else
    BaseType_t ret;

    if (!mu) {
        return BLE_NPL_INVALID_PARAM;
    }

    ASSERT(mu->handle);

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        ret = pdFAIL;
        ASSERT(0);
    } else {
        ret = xSemaphoreTakeRecursive(mu->handle, timeout);
    }

    return ret == pdPASS ? BLE_NPL_OK : BLE_NPL_TIMEOUT;
#endif
}

ble_npl_error_t
npl_freertos_mutex_release(struct ble_npl_mutex *mu)
{
    if (!mu) {
        return BLE_NPL_INVALID_PARAM;
    }

    ASSERT(mu->handle);
#if 1
    if (OS_MutexUnLock(mu->handle) != OS_SUCCESS){
            return BLE_NPL_BAD_MUTEX;
    }

    return BLE_NPL_OK;
#else
    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        ASSERT(0);
    } else {
        if (xSemaphoreGiveRecursive(mu->handle) != pdPASS) {
            return BLE_NPL_BAD_MUTEX;
        }
    }

    return BLE_NPL_OK;
#endif
}

ble_npl_error_t
npl_freertos_sem_init(struct ble_npl_sem *sem, uint16_t tokens)
{
#if 1
    OS_STATUS ret = 0;
    if (!sem) {
        return BLE_NPL_INVALID_PARAM;
    }
    ret = OS_SemInit(&sem->handle, 1, 0);

    ASSERT(ret == OS_SUCCESS);
    return BLE_NPL_OK;
#else
    if (!sem) {
        return BLE_NPL_INVALID_PARAM;
    }

    sem->handle = xSemaphoreCreateCounting(128, tokens);

    ASSERT(sem->handle);

    return BLE_NPL_OK;
#endif
}

ble_npl_error_t
npl_freertos_sem_pend(struct ble_npl_sem *sem, ble_npl_time_t timeout)
{
#if 1
    OS_STATUS ret = 0;
    if (!sem) {
        return BLE_NPL_INVALID_PARAM;
    }
    ASSERT(sem->handle);
    ret = OS_SemWait(sem->handle, timeout);

    return ret == OS_SUCCESS ? BLE_NPL_OK : BLE_NPL_TIMEOUT;
#else
    BaseType_t woken;
    BaseType_t ret;

    if (!sem) {
        return BLE_NPL_INVALID_PARAM;
    }

    ASSERT(sem->handle);

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        ASSERT(timeout == 0);
        ret = xSemaphoreTakeFromISR(sem->handle, &woken);
        //portYIELD_FROM_ISR(woken);//--werner

        if( woken )//++werner
            portYIELD_FROM_ISR();//++werner
    } else {
        ret = xSemaphoreTake(sem->handle, timeout);
    }

    return ret == pdPASS ? BLE_NPL_OK : BLE_NPL_TIMEOUT;
#endif
}

ble_npl_error_t
npl_freertos_sem_release(struct ble_npl_sem *sem)
{
#if 1
    OS_STATUS ret = 0;
    ret = OS_SemSignal(sem->handle);
    ASSERT(ret == OS_SUCCESS);
    return BLE_NPL_OK;
#else
    BaseType_t ret;
    BaseType_t woken;

    if (!sem) {
        return BLE_NPL_INVALID_PARAM;
    }

    ASSERT(sem->handle);

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        ret = xSemaphoreGiveFromISR(sem->handle, &woken);
        //portYIELD_FROM_ISR(woken);//--werner

        if( woken )//++werner
            portYIELD_FROM_ISR();//++werner
    } else {
        ret = xSemaphoreGive(sem->handle);
    }

    ASSERT(ret == pdPASS);
    return BLE_NPL_OK;
 #endif
}

#if 1
static void
os_callout_timer_cb(OsTimer data)
{
    struct ble_npl_callout *co;

    co = OS_TimerGetData(data);
    ASSERT(co);

    if (co->evq) {
        ble_npl_eventq_put(co->evq, &co->ev);
    } else {
        co->ev.fn(&co->ev);
    }

}
#else
static void
os_callout_timer_cb(TimerHandle_t timer)
{
    struct ble_npl_callout *co;

    co = pvTimerGetTimerID(timer);
    ASSERT(co);

    if (co->evq) {
        ble_npl_eventq_put(co->evq, &co->ev);
    } else {
        co->ev.fn(&co->ev);
    }

}
#endif

void
npl_freertos_callout_init(struct ble_npl_callout *co, struct ble_npl_eventq *evq,
                     ble_npl_event_fn *ev_cb, void *ev_arg)
{
    OS_STATUS ret = 0;
    memset(co, 0, sizeof(*co));
#if 1
    ret = OS_TimerCreate(&co->handle, 1, pdFALSE, co, os_callout_timer_cb);    
#else
    co->handle = xTimerCreate("co", 1, pdFALSE, co, os_callout_timer_cb);
#endif
    co->evq = evq;
    ble_npl_event_init(&co->ev, ev_cb, ev_arg);

}

ble_npl_error_t
npl_freertos_callout_reset(struct ble_npl_callout *co, ble_npl_time_t ticks)
{
#if 1
    u8 ret = 0;

    if (ticks < 0) {
        return BLE_NPL_INVALID_PARAM;
    }

    if (ticks == 0) {
        ticks = 10;//1;werner change to 1000s
    }

    ret = OS_TimerReset(co->handle);
    ASSERT(ret);

    //ret = OS_TimerSet(co->handle, ticks, 0, co);
    //ASSERT(ret);
    return BLE_NPL_OK;
#else
    BaseType_t woken1, woken2, woken3;

    if (ticks < 0) {
        return BLE_NPL_INVALID_PARAM;
    }

    if (ticks == 0) {
        ticks = 10;//1;werner change to 1000s
    }

    //if (in_isr()) {//--werner
    if (gOsFromISR) {//++werner
        xTimerStopFromISR(co->handle, &woken1);
        xTimerChangePeriodFromISR(co->handle, ticks, &woken2);
        xTimerResetFromISR(co->handle, &woken3);

        //portYIELD_FROM_ISR(woken1 || woken2 || woken3);//--werner

        if( woken1 || woken2 || woken3 )//++werner
            portYIELD_FROM_ISR();//++werner
    } else {
        xTimerStop(co->handle, portMAX_DELAY);
        xTimerChangePeriod(co->handle, ticks, portMAX_DELAY);
        xTimerReset(co->handle, portMAX_DELAY);
    }

    return BLE_NPL_OK;
#endif
}

ble_npl_time_t
npl_freertos_callout_remaining_ticks(struct ble_npl_callout *co,
                                     ble_npl_time_t now)
{
    ble_npl_time_t rt;
    uint32_t exp;

    exp = OS_TimerGetExpiryTime(co->handle);//xTimerGetExpiryTime(co->handle);//werner, no api

    if (exp > now) {
        rt = exp - now;
    } else {
        rt = 0;
    }

    return rt;
}

ble_npl_error_t
npl_freertos_time_ms_to_ticks(uint32_t ms, ble_npl_time_t *out_ticks)
{
    uint64_t ticks;

    ticks = ((uint64_t)ms * configTICK_RATE_HZ) / 1000;
    if (ticks > UINT32_MAX) {
        return BLE_NPL_EINVAL;
    }

    *out_ticks = ticks;

    return 0;
}

ble_npl_error_t
npl_freertos_time_ticks_to_ms(ble_npl_time_t ticks, uint32_t *out_ms)
{
    uint64_t ms;

    ms = ((uint64_t)ticks * 1000) / configTICK_RATE_HZ;
    if (ms > UINT32_MAX) {
        return BLE_NPL_EINVAL;
     }

    *out_ms = ms;

    return 0;
}
