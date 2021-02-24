/*
 * Copyright(c) 2018 - 2020 Yaguan Technology Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ya_common.h"
#include <wdt/drv_wdt.h>

//==============================thread============================================
void ya_printf_remain_heap(void)
{
	ya_printf(C_LOG_INFO, "remain heap: %d\r\n", xPortGetFreeHeapSize());
}


uint32_t ya_get_remain_heap(void)
{
	return xPortGetFreeHeapSize();
}

void ya_hal_sys_reboot()
{
	drv_wdt_init();
	drv_wdt_enable(SYS_WDT, 1);
}

int32_t ya_hal_os_thread_create(ya_hal_os_thread_t *thandle, 
											const char *name,
											void(*main_func)(void *arg),
											void *arg,
											int32_t stack_depth,
											int32_t priority)
{
	if(pdPASS == xTaskCreate(main_func, name, stack_depth/sizeof(portSTACK_TYPE), arg, (UBaseType_t)priority, (TaskHandle_t * const)thandle))
		return 0;

	return -1;
}

int32_t ya_hal_os_thread_delete(ya_hal_os_thread_t *thandle)
{
	if(thandle == NULL)
		vTaskDelete(NULL);
	else
		vTaskDelete( (TaskHandle_t) *thandle);

	return 0;
}

void ya_hal_os_thread_sleep(int32_t mses)
{
	vTaskDelay(mses * portTICK_PERIOD_MS);
	return;
}

void ya_hal_os_thread_suspend(ya_hal_os_thread_t *thandle)
{
	vTaskSuspend((TaskHandle_t) *thandle);
	return;
}

void ya_hal_os_thread_resume(ya_hal_os_thread_t *thandle)
{
	vTaskResume((TaskHandle_t) *thandle);
	return;
}
											
//==============================Queue============================================
int32_t ya_hal_os_queue_create(ya_hal_os_queue_t *qhandle, const char *name, int32_t msgsize, int32_t queue_length)
{
	int32_t ret = -1;
	*qhandle = xQueueCreate(queue_length, msgsize);

	if( *qhandle != NULL)
	{
		vQueueAddToRegistry(*qhandle, name);
		ret = 0;
	}

	return ret;
}

int32_t ya_hal_os_queue_send(ya_hal_os_queue_t *qhandle, const void *msg, uint32_t msecs)
{
	if(xQueueSendToBack(*qhandle, msg, (TickType_t)(msecs/portTICK_PERIOD_MS)) == pdPASS)
		return 0;
		
	return -1;
}

int32_t ya_hal_os_queue_recv(ya_hal_os_queue_t *qhandle, void *msg, uint32_t msecs)
{
	if(xQueueReceive(*qhandle, msg, (TickType_t)(msecs/portTICK_PERIOD_MS)) == pdPASS)
		return 0;

	return -1;
}

int32_t ya_hal_queue_get_msg_waiting(ya_hal_os_queue_t *qhandle)
{
	if(uxQueueMessagesWaiting(*qhandle) == pdPASS)
		return 0;

	return -1;
}

int32_t ya_hal_os_queue_delete(ya_hal_os_queue_t *qhandle)
{
	vQueueDelete(*qhandle);
	return 0;
}

//==============================mutex============================================
int32_t ya_hal_os_mutex_create(ya_hal_os_mutex_t *mhandle, const char *name)
{
	*mhandle = xSemaphoreCreateMutex();
	if(*mhandle != NULL)
	{
		vQueueAddToRegistry((*mhandle ), name);
		return 0;
	}
	return -1;
}

int32_t ya_hal_os_mutex_get(ya_hal_os_mutex_t *mhandle, uint32_t mses)
{
	if(xSemaphoreTake(*mhandle , (TickType_t)(mses/portTICK_PERIOD_MS) == pdPASS))
		return 0;

	return -1;
}

int32_t ya_hal_os_mutex_put(ya_hal_os_mutex_t *mhandle)
{
	if(xSemaphoreGive(*mhandle) == pdPASS)
		return 0;

	return -1;
}

void ya_hal_os_mutex_delete(ya_hal_os_mutex_t *mhandle)
{
	vSemaphoreDelete(*mhandle);
}

int ya_os_get_random(unsigned char *output, size_t output_len)
{
	size_t i;
    for(i=0; i<output_len; i++)
    {
        output[i] = OS_Random();
    }
	return 0;
}

//===================================tick===============================================

uint32_t ya_hal_os_tickcount_get(void)
{
	uint32_t mRet;
	mRet = (uint32_t) xTaskGetTickCount();
	return mRet;
}

uint32_t ya_hal_os_msec_to_ticks(uint32_t msecs)
{
	uint32_t msRet;
	msRet = msecs/portTICK_PERIOD_MS;
	return msRet;
}

uint32_t ya_hal_os_ticks_to_msec(void)
{
	uint32_t msRet;
	msRet = xTaskGetTickCount()*portTICK_PERIOD_MS;
	return msRet;
}

//==================Memory==============================
void *ya_hal_os_memory_alloc(uint32_t size)
{
	return OS_MemAlloc(size);
}

void ya_hal_os_memory_free(void *pmem)
{
	OS_MemFree(pmem);
}

void* ya_hal_os_memory_calloc(uint32_t nelements, uint32_t elementSize)
{
	uint32_t size;
	void *ptr = NULL;

	size = nelements * elementSize;
	ptr = ya_hal_os_memory_alloc(size);

	if(ptr)
		memset(ptr, 0, size);

	return ptr;
}
//===================================================

