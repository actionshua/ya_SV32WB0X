// Copyright 2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sys/param.h>
#include <string.h>
//#include "soc/soc.h"
#include "ssv_types.h"
//#include "ssv_attr.h"
#include "ssv_err.h"
#include "ssv_timer.h"
#include "ssv_task.h"
#include "ssv_log.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//#include "freertos/xtensa_api.h"
#include "sdkconfig.h"
#include <stdlib.h>
#include "ssv_private/ssv_timer_impl.h"
#include "soc_assert.h"
#include "osi/allocator.h"

#ifdef CONFIG_SSV_TIMER_PROFILING
#define WITH_PROFILING 1
#endif

#ifndef NDEBUG
// Enable built-in checks in queue.h in debug builds
#define INVARIANTS
#endif
#include "sys/queue.h"

#define EVENT_ID_DELETE_TIMER   0xF0DE1E1E

#define TIMER_EVENT_QUEUE_SIZE      1//16

struct ssv_timer {
    uint64_t alarm;
    uint64_t period;
    union {
        ssv_timer_cb_t callback;
        uint32_t event_id;
    };
    void* arg;
#if WITH_PROFILING
    const char* name;
    size_t times_triggered;
    size_t times_armed;
    uint64_t total_callback_run_time;
#endif // WITH_PROFILING
    LIST_ENTRY(ssv_timer) list_entry;
};

static bool is_initialized();
static ssv_err_t timer_insert(ssv_timer_handle_t timer);
static ssv_err_t timer_remove(ssv_timer_handle_t timer);
static bool timer_armed(ssv_timer_handle_t timer);
static void timer_list_lock();
static void timer_list_unlock();

#if WITH_PROFILING
static void timer_insert_inactive(ssv_timer_handle_t timer);
static void timer_remove_inactive(ssv_timer_handle_t timer);
#endif // WITH_PROFILING

static const char* TAG = "ssv_timer";

// list of currently armed timers
static LIST_HEAD(ssv_timer_list, ssv_timer) s_timers =
        LIST_HEAD_INITIALIZER(s_timers);
#if WITH_PROFILING
// list of unarmed timers, used only to be able to dump statistics about
// all the timers
static LIST_HEAD(ssv_inactive_timer_list, ssv_timer) s_inactive_timers =
        LIST_HEAD_INITIALIZER(s_timers);
#endif
// task used to dispatch timer callbacks
static TaskHandle_t s_timer_task;
// counting semaphore used to notify the timer task from ISR
#define USE_SSV_OS_SEMA_IN_SSVTIMER 1

#if USE_SSV_OS_SEMA_IN_SSVTIMER
static OsSemaphore s_timer_semaphore = NULL;
#else
static SemaphoreHandle_t s_timer_semaphore;
#endif

#if CONFIG_SPIRAM_USE_MALLOC
// memory for s_timer_semaphore
static StaticQueue_t s_timer_semaphore_memory;
#endif

// lock protecting s_timers, s_inactive_timers
//static portMUX_TYPE s_timer_lock = portMUX_INITIALIZER_UNLOCKED;



ssv_err_t ssv_timer_create(const ssv_timer_create_args_t* args,
                           ssv_timer_handle_t* out_handle)
{
    if (!is_initialized()) {
        return SSV_ERR_INVALID_STATE;
    }
    if (args->callback == NULL) {
        return SSV_ERR_INVALID_ARG;
    }
    ssv_timer_handle_t result = (ssv_timer_handle_t) calloc(1, sizeof(*result));
    if (result == NULL) {
        return SSV_ERR_NO_MEM;
    }
    result->callback = args->callback;
    result->arg = args->arg;
#if WITH_PROFILING
    result->name = args->name;
    timer_insert_inactive(result);
#endif
    *out_handle = result;
    return SSV_BM_OK;
}

ssv_err_t ssv_timer_start_once(ssv_timer_handle_t timer, uint64_t timeout_us)
{
    if (!is_initialized() || timer_armed(timer)) {
        return SSV_ERR_INVALID_STATE;
    }
    timer_list_lock();
    timer->alarm = ssv_timer_get_time() + timeout_us;
    //printf("set alarm time %llu, timeout_us %llu\n", timer->alarm, timeout_us);//werner dbg
    timer->period = 0;
#if WITH_PROFILING
    timer->times_armed++;
#endif
    ssv_err_t err = timer_insert(timer);
    timer_list_unlock();
    return err;
}

ssv_err_t ssv_timer_start_periodic(ssv_timer_handle_t timer, uint64_t period_us)
{
    if (!is_initialized() || timer_armed(timer)) {
        return SSV_ERR_INVALID_STATE;
    }
    timer_list_lock();
    period_us = MAX(period_us, ssv_timer_impl_get_min_period_us());
    timer->alarm = ssv_timer_get_time() + period_us;
    timer->period = period_us;
#if WITH_PROFILING
    timer->times_armed++;
#endif
    ssv_err_t err = timer_insert(timer);
    timer_list_unlock();
    return err;
}

ssv_err_t ssv_timer_stop(ssv_timer_handle_t timer)
{
    if (!is_initialized() || !timer_armed(timer)) {
        return SSV_ERR_INVALID_STATE;
    }
    return timer_remove(timer);
}

ssv_err_t ssv_timer_delete(ssv_timer_handle_t timer)
{
    if (timer == NULL) {
        return SSV_ERR_INVALID_ARG;
    }
    if (timer_armed(timer)) {
        return SSV_ERR_INVALID_STATE;
    }
    timer_list_lock();
    timer->event_id = EVENT_ID_DELETE_TIMER;
    timer->alarm = ssv_timer_get_time();
    timer->period = 0;
    timer_insert(timer);
    timer_list_unlock();
    return SSV_BM_OK;
}

static ssv_err_t timer_insert(ssv_timer_handle_t timer)
{
#if WITH_PROFILING
    timer_remove_inactive(timer);
#endif
    ssv_timer_handle_t it, last = NULL;
    if (LIST_FIRST(&s_timers) == NULL) {
        LIST_INSERT_HEAD(&s_timers, timer, list_entry);
    } else {
        LIST_FOREACH(it, &s_timers, list_entry) {
            if (timer->alarm < it->alarm) {
                LIST_INSERT_BEFORE(it, timer, list_entry);
                break;
            }
            last = it;
        }
        if (it == NULL) {
            assert(last);
            LIST_INSERT_AFTER(last, timer, list_entry);
        }
    }
    if (timer == LIST_FIRST(&s_timers)) {
        ssv_timer_impl_set_alarm(timer->alarm);
    }
    return SSV_BM_OK;
}

static ssv_err_t timer_remove(ssv_timer_handle_t timer)
{
    timer_list_lock();
    LIST_REMOVE(timer, list_entry);
    timer->alarm = 0;
    timer->period = 0;
#if WITH_PROFILING
    timer_insert_inactive(timer);
#endif
    timer_list_unlock();
    return SSV_BM_OK;
}

#if WITH_PROFILING

static void timer_insert_inactive(ssv_timer_handle_t timer)
{
    /* May be locked or not, depending on where this is called from.
     * Lock recursively.
     */
    timer_list_lock();
    ssv_timer_handle_t head = LIST_FIRST(&s_inactive_timers);
    if (head == NULL) {
        LIST_INSERT_HEAD(&s_inactive_timers, timer, list_entry);
    } else {
        /* Insert as head element as this is the fastest thing to do.
         * Removal is O(1) anyway.
         */
        LIST_INSERT_BEFORE(head, timer, list_entry);
    }
    timer_list_unlock();
}

static void timer_remove_inactive(ssv_timer_handle_t timer)
{
    timer_list_lock();
    LIST_REMOVE(timer, list_entry);
    timer_list_unlock();
}

#endif // WITH_PROFILING

static bool timer_armed(ssv_timer_handle_t timer)
{
    return timer->alarm > 0;
}

static void timer_list_lock()
{
    //portENTER_CRITICAL(&s_timer_lock);
    BM_EnterCritical();
}

static void timer_list_unlock()
{
    //portEXIT_CRITICAL(&s_timer_lock);
    BM_ExitCritical();
}

static void timer_process_alarm(ssv_timer_dispatch_t dispatch_method)
{
    /* unused, provision to allow running callbacks from ISR */
    (void) dispatch_method;
    //printf("tpa\n");//werner dbg
    OS_MsDelay(3);//delay for timer is not very correct when set timer us(faster than 1ms)
    timer_list_lock();
    uint64_t now = ssv_timer_impl_get_time();
    ssv_timer_handle_t it = LIST_FIRST(&s_timers);
    /*if (it != NULL)
        printf("alarm %llu %llu\n", it->alarm, now);//werner dbg
    else 
        printf("it is NULL\n");*/

    while (it != NULL &&
            it->alarm < now) {
        //printf("alarm < now \n");//werner dbg
        LIST_REMOVE(it, list_entry);
        if (it->event_id == EVENT_ID_DELETE_TIMER) {
            free(it);
            it = LIST_FIRST(&s_timers);
            continue;
        }
        if (it->period > 0) {
            it->alarm += it->period;
            timer_insert(it);
        } else {
            it->alarm = 0;
#if WITH_PROFILING
            timer_insert_inactive(it);
#endif
        }
#if WITH_PROFILING
        uint64_t callback_start = now;
#endif
        ssv_timer_cb_t callback = it->callback;
        void* arg = it->arg;
        timer_list_unlock();
        (*callback)(arg);
        timer_list_lock();
        now = ssv_timer_impl_get_time();
#if WITH_PROFILING
        it->times_triggered++;
        it->total_callback_run_time += now - callback_start;
#endif
        it = LIST_FIRST(&s_timers);
    }
    ssv_timer_handle_t first = LIST_FIRST(&s_timers);
    if (first) {
        ssv_timer_impl_set_alarm(first->alarm);
    }
    timer_list_unlock();
}

static void timer_task(void* arg)
{
#if USE_SSV_OS_SEMA_IN_SSVTIMER
    while (true){
        OS_STATUS res = OS_SemWait(s_timer_semaphore, portMAX_DELAY);
        assert(res == OS_SUCCESS);
        timer_process_alarm(SSV_TIMER_TASK);
    }
#else
    while (true){
        int res = xSemaphoreTake(s_timer_semaphore, portMAX_DELAY);
        assert(res == pdTRUE);
        timer_process_alarm(SSV_TIMER_TASK);
    }
#endif
}

static void timer_alarm_handler(void* arg)
{
    static uint32_t count = 0;
#if USE_SSV_OS_SEMA_IN_SSVTIMER
    OS_STATUS ret = OS_SemSignal(s_timer_semaphore);
    if (ret != OS_SUCCESS) {
        if (!(count%100))
            printf("tah %d\n", ret);

        count ++;
    }
    //ASSERT(ret == OS_SUCCESS)
#else
    //int need_yield;
    BaseType_t need_yield;
    if (gOsFromISR) {
        if (xSemaphoreGiveFromISR(s_timer_semaphore, &need_yield) != pdPASS) {    
            printf("timer queue overflow");
            return;
        }
    } else {
        if (xSemaphoreGive(s_timer_semaphore) != pdPASS) {
            printf("not isr timer queue overflow");
            //ASSERT(0);
        }
        return;
    }
    
    //printf("tse rel\n");//werner dbg
    if (need_yield == pdTRUE) {
        portYIELD_FROM_ISR();
    }
#endif
}

static bool is_initialized()
{
    return s_timer_task != NULL;
}


ssv_err_t ssv_timer_init(void)
{
    ssv_err_t err;
    if (is_initialized()) {
        return SSV_ERR_INVALID_STATE;
    }

#if CONFIG_SPIRAM_USE_MALLOC
    memset(&s_timer_semaphore_memory, 0, sizeof(StaticQueue_t));
    s_timer_semaphore = xSemaphoreCreateCountingStatic(TIMER_EVENT_QUEUE_SIZE, 0, &s_timer_semaphore_memory);
#else

    #if USE_SSV_OS_SEMA_IN_SSVTIMER
        OS_SemInit(&s_timer_semaphore, TIMER_EVENT_QUEUE_SIZE, 0);
    #else    
        s_timer_semaphore = xSemaphoreCreateCounting(TIMER_EVENT_QUEUE_SIZE, 0);
    #endif

#endif
    if (!s_timer_semaphore) {
        err = SSV_ERR_NO_MEM;
        goto out;
    }

    /*int ret = xTaskCreatePinnedToCore(&timer_task, "ssv_timer",
            SSV_TASK_TIMER_STACK, NULL, SSV_TASK_TIMER_PRIO, &s_timer_task, PRO_CPU_NUM);*/
    //printf("create timer_task %d\n", SSV_TASK_TIMER_STACK);
    u8 ret = OS_TaskCreate(&timer_task, "ssv_timer",
            SSV_TASK_TIMER_STACK, NULL, SSV_TASK_TIMER_PRIO, (OsTaskHandle *)&s_timer_task);

    if (ret != 1) {
        err = SSV_ERR_NO_MEM;
        goto out;
    }

    err = ssv_timer_impl_init(&timer_alarm_handler);
    if (err != SSV_BM_OK) {
        goto out;
    }

    return SSV_BM_OK;

out:
    if (s_timer_task) {
        OS_TaskDelete(s_timer_task);
        s_timer_task = NULL;
    }
    if (s_timer_semaphore) {
        //vSemaphoreDelete(s_timer_semaphore);
        OS_SemDelete(s_timer_semaphore);
        s_timer_semaphore = NULL;
    }
    return SSV_ERR_NO_MEM;
}

ssv_err_t ssv_timer_deinit(void)
{
    if (!is_initialized()) {
        return SSV_ERR_INVALID_STATE;
    }

    /* Check if there are any active timers */
    if (!LIST_EMPTY(&s_timers)) {
        return SSV_ERR_INVALID_STATE;
    }

    /* We can only check if there are any timers which are not deleted if
     * profiling is enabled.
     */
#if WITH_PROFILING
    if (!LIST_EMPTY(&s_inactive_timers)) {
        return SSV_ERR_INVALID_STATE;
    }
#endif

    ssv_timer_impl_deinit();

    OS_TaskDelete(s_timer_task);
    s_timer_task = NULL;
    //vSemaphoreDelete(s_timer_semaphore);
    OS_SemDelete(s_timer_semaphore);
    s_timer_semaphore = NULL;
    return SSV_BM_OK;
}

static void print_timer_info(ssv_timer_handle_t t, char** dst, size_t* dst_size)
{
    size_t cb = snprintf(*dst, *dst_size,
#if WITH_PROFILING
            "%-12s  %12lld  %12lld  %9d  %9d  %12lld\n",
            t->name, t->period, t->alarm,
            t->times_armed, t->times_triggered, t->total_callback_run_time);
    /* keep this in sync with the format string, used in ssv_timer_dump */
#define TIMER_INFO_LINE_LEN 78
#else
            "timer@%p  %12lld  %12lld\n", t, t->period, t->alarm);
#define TIMER_INFO_LINE_LEN 46
#endif
    *dst += cb;
    *dst_size -= cb;
}


ssv_err_t ssv_timer_dump(FILE* stream)
{
    /* Since timer lock is a critical section, we don't want to print directly
     * to stdout, since that may cause a deadlock if stdout is interrupt-driven
     * (via the UART driver). Allocate sufficiently large chunk of memory first,
     * print to it, then dump this memory to stdout.
     */

    ssv_timer_handle_t it;

    /* First count the number of timers */
    size_t timer_count = 0;
    timer_list_lock();
    LIST_FOREACH(it, &s_timers, list_entry) {
        ++timer_count;
    }
#if WITH_PROFILING
    LIST_FOREACH(it, &s_inactive_timers, list_entry) {
        ++timer_count;
    }
#endif
    timer_list_unlock();

    /* Allocate the memory for this number of timers. Since we have unlocked,
     * we may find that there are more timers. There's no bulletproof solution
     * for this (can't allocate from a critical section), but we allocate
     * slightly more and the output will be truncated if that is not enough.
     */
    size_t buf_size = TIMER_INFO_LINE_LEN * (timer_count + 3);
    char* print_buf = calloc(1, buf_size + 1);
    if (print_buf == NULL) {
        return SSV_ERR_NO_MEM;
    }

    /* Print to the buffer */
    timer_list_lock();
    char* pos = print_buf;
    LIST_FOREACH(it, &s_timers, list_entry) {
        print_timer_info(it, &pos, &buf_size);
    }
#if WITH_PROFILING
    LIST_FOREACH(it, &s_inactive_timers, list_entry) {
        print_timer_info(it, &pos, &buf_size);
    }
#endif
    timer_list_unlock();

    /* Print the buffer */
    fputs(print_buf, stream);

    free(print_buf);
    return SSV_BM_OK;
}

int64_t ssv_timer_get_next_alarm()
{
    int64_t next_alarm = INT64_MAX;
    timer_list_lock();
    ssv_timer_handle_t it = LIST_FIRST(&s_timers);
    if (it) {
        next_alarm = it->alarm;
    }
    timer_list_unlock();
    return next_alarm;
}

uint64_t ssv_timer_get_time()
{
    return ssv_timer_impl_get_time();
}
