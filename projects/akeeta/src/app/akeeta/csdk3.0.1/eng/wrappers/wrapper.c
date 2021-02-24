/**
 * NOTE:
 *
 * HAL_TCP_xxx API reference implementation: wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "infra_types.h"
#include "infra_defs.h"
#include "infra_compat.h"
#include "wrappers_defs.h"

#include "ya_common.h"
#include "ya_cert_flash_api.h"

static char _product_key[IOTX_PRODUCT_KEY_LEN + 1] 	       = {0};
static char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1]   = {0};
static char _device_name[IOTX_DEVICE_NAME_LEN + 1] 	       = {0};
static char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]     = {0};


extern void HAL_Printf(const char *fmt, ...);
extern uint64_t HAL_UptimeMs(void);


static uint64_t freertos_get_time_ms(void)
{
	return HAL_UptimeMs();
}

static uint64_t freertos_time_left(uint64_t t_end, uint64_t t_now)
{
    uint64_t t_left;

    if (t_end > t_now) {
        t_left = t_end - t_now;
    } else {
        t_left = 0;
    }

    return t_left;
}


/**
?*
?* ���� HAL_Free() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_Free() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_Free(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_Free, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Deallocate memory block
 *
 * @param[in] ptr @n Pointer to a memory block previously allocated with platform_malloc.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Free(void *ptr)
{
	vPortFree(ptr);
}


int HAL_SetProductKey(char *product_key)
{
    int len = strlen(product_key);

    if (len > IOTX_PRODUCT_KEY_LEN) {
        return -1;
    }
    memset(_product_key, 0x0, IOTX_PRODUCT_KEY_LEN + 1);
    strncpy(_product_key, product_key, len);

    return len;
}


int HAL_SetDeviceName(char *device_name)
{
    int len = strlen(device_name);

    if (len > IOTX_DEVICE_NAME_LEN) {
        return -1;
    }
    memset(_device_name, 0x0, IOTX_DEVICE_NAME_LEN + 1);
    strncpy(_device_name, device_name, len);

    return len;
}

int HAL_SetProductSecret(char *product_secret)
{
    int len = strlen(product_secret);

    if (len > IOTX_PRODUCT_SECRET_LEN) {
        return -1;
    }
    memset(_product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN + 1);
    strncpy(_product_secret, product_secret, len);

    return len;
}

int HAL_SetDeviceSecret(char *device_secret)
{
    int len = strlen(device_secret);

    if (len > IOTX_DEVICE_SECRET_LEN) {
        return -1;
    }
    memset(_device_secret, 0x0, IOTX_DEVICE_SECRET_LEN + 1);
    strncpy(_device_secret, device_secret, len);

    return len;
}


/**
?*
?* ���� HAL_GetDeviceName() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_GetDeviceName() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_GetDeviceName(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_GetDeviceName, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Get device name from user's system persistent storage
 *
 * @param [ou] device_name: array to store device name, max length is IOTX_DEVICE_NAME_LEN
 * @return the actual length of device name
 */
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN + 1])
{
	return  ya_get_deviceID(device_name);
}



/**
?*
?* ���� HAL_GetDeviceSecret() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_GetDeviceSecret() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_GetDeviceSecret(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_GetDeviceSecret, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Get device secret from user's system persistent storage
 *
 * @param [ou] device_secret: array to store device secret, max length is IOTX_DEVICE_SECRET_LEN
 * @return the actual length of device secret
 */
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN + 1])
{
	return ya_get_deviceSecret(device_secret);
}



/**
?*
?* ���� HAL_GetFirmwareVersion() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_GetFirmwareVersion() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_GetFirmwareVersion(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_GetFirmwareVersion, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Get firmware version
 *
 * @param [ou] version: array to store firmware version, max length is IOTX_FIRMWARE_VER_LEN
 * @return the actual length of firmware version
 */
int HAL_GetFirmwareVersion(char *version)
{
    char *ver = "sdk-1.0.0-20200427.1000";
    int len = strlen(ver);

    memset(version, 0x0, IOTX_FIRMWARE_VER_LEN);
    strncpy(version, ver, IOTX_FIRMWARE_VER_LEN);
    version[len] = '\0';
	
    return strlen(version);
}


/**
?*
?* ���� HAL_GetProductKey() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_GetProductKey() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_GetProductKey(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_GetProductKey, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Get product key from user's system persistent storage
 *
 * @param [ou] product_key: array to store product key, max length is IOTX_PRODUCT_KEY_LEN
 * @return  the actual length of product key
 */
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN + 1])
{
    return ya_get_productKey(product_key);
}

int HAL_GetProductSecret(char product_secret[IOTX_PRODUCT_SECRET_LEN + 1])
{
    int len = strlen(_product_secret);
    memset(product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN + 1);

    strncpy(product_secret, _product_secret, len);
	
    return len;
}



/**
?*
?* ���� HAL_Malloc() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_Malloc() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_Malloc(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_Malloc, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *
 * @param [in] size @n specify block size in bytes.
 * @return A pointer to the beginning of the block.
 * @see None.
 * @note Block value is indeterminate.
 */
void *HAL_Malloc(uint32_t size)
{
    return pvPortMalloc(size);
}


/**
?*
?* ���� HAL_MutexCreate() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_MutexCreate() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_MutexCreate(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_MutexCreate, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
void *HAL_MutexCreate(void)
{
	QueueHandle_t sem;

	sem = xSemaphoreCreateMutex();
	if (0 == sem) {
		return NULL;
	}

	return sem;
}



/**
?*
?* ���� HAL_MutexDestroy() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_MutexDestroy() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_MutexDestroy(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_MutexDestroy, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexDestroy(void *mutex)
{
	QueueHandle_t sem;
	if (mutex == NULL) {
		return;
	}
	sem = (QueueHandle_t)mutex;
	vSemaphoreDelete(sem);
}



/**
?*
?* ���� HAL_MutexLock() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_MutexLock() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_MutexLock(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_MutexLock, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexLock(void *mutex)
{
	BaseType_t ret;
	QueueHandle_t sem;
	if (mutex == NULL) {
		return;
	}

	sem = (QueueHandle_t)mutex;
	ret = xSemaphoreTake(sem, 0xffffffff);
	while (pdPASS != ret) {
		ret = xSemaphoreTake(sem, 0xffffffff);
	}
}


/**
?*
?* ���� HAL_MutexUnlock() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_MutexUnlock() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_MutexUnlock(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_MutexUnlock, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexUnlock(void *mutex)
{
	QueueHandle_t sem;
	if (mutex == NULL) {
		return;
	}
	sem = (QueueHandle_t)mutex;
	(void)xSemaphoreGive(sem);
}



/**
?*
?* ���� HAL_Printf() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_Printf() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_Printf(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_Printf, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Writes formatted data to stream.
 *
 * @param [in] fmt: @n String that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return None.
 * @see None.
 * @note None.
 */
 
void HAL_Printf(const char *fmt, ...)
{
#if 0 
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
#else

	char buffer[512] = {0};
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, 512, fmt, args);
	va_end(args);
	printf("%s", buffer);
#endif	
}

int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap)
{
    return vsnprintf(str, len, format, ap);
}


/**
?*
?* ���� HAL_SleepMs() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_SleepMs() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_SleepMs(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_SleepMs, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Sleep thread itself.
 *
 * @param [in] ms @n the time interval for which execution is to be suspended, in milliseconds.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SleepMs(uint32_t ms)
{
	vTaskDelay(ms/portTICK_PERIOD_MS);
}


/**
?*
?* ���� HAL_Snprintf() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_Snprintf() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_Snprintf(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_Snprintf, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Writes formatted data to string.
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] len: @n Maximum length of character will be written
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int rc;

    va_start(args, fmt);
    rc = vsnprintf(str, len, fmt, args);
    va_end(args);
    return rc;
}


/**
?*
?* ���� HAL_TCP_Destroy() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_TCP_Destroy() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_TCP_Destroy(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_TCP_Destroy, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Destroy the specific TCP connection.
 *
 * @param [in] fd: @n Specify the TCP connection by handle.
 *
 * @return The result of destroy TCP connection.
 * @retval < 0 : Fail.
 * @retval   0 : Success.
 */
int HAL_TCP_Destroy(uintptr_t fd)
{
	int rc;

	/* Shutdown both send and receive operations. */
	rc = shutdown((int) fd, 2);
	if (0 != rc) 
	{
		printf("shutdown error");
		return -1;
	}

	rc = close((int) fd);
	if (0 != rc)
	{
		printf("closesocket error");
		return -1;
	}

	return 0;
}


/**
?*
?* ���� HAL_TCP_Establish() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_TCP_Establish() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_TCP_Establish(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_TCP_Establish, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Establish a TCP connection.
 *
 * @param [in] host: @n Specify the hostname(IP) of the TCP server
 * @param [in] port: @n Specify the TCP port of TCP server
 *
 * @return The handle of TCP connection.
   @retval (uintptr_t)(-1): Fail.
   @retval All other values(0 included): Success, the value is handle of this TCP connection.
 */
uintptr_t HAL_TCP_Establish(const char *host, uint16_t port)
{
	int32_t ret = -1;
	int32_t fd = -1;
	struct sockaddr_in sock_addr;
	struct hostent* entry = NULL;

	printf("host: %s port: %d", host, port);

	do 
	{
		entry = gethostbyname(host);
		vTaskDelay(500 / portTICK_RATE_MS);
	} while (entry == NULL);

	printf("create socket...");
	
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0) 
	{
		printf("Creat socket failed...");
		return -1;
	}

	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	sock_addr.sin_addr.s_addr = ((struct in_addr*)(entry->h_addr))->s_addr;

	printf("tcp client connect ip:%s port:%d", inet_ntoa(sock_addr.sin_addr.s_addr), port);
	ret = connect(fd, (struct sockaddr*) &sock_addr, sizeof(sock_addr));

	if (ret < 0)
	{
		printf("connect is failed...");
		close(fd);
		return -1;
	}
	else
	{
		printf("connect is success ...");
	}

	return fd;
}


/**
?*
?* ���� HAL_TCP_Read() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_TCP_Read() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_TCP_Read(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_TCP_Read, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Read data from the specific TCP connection with timeout parameter.
 *        The API will return immediately if 'len' be received from the specific TCP connection.
 *
 * @param [in] fd @n A descriptor identifying a TCP connection.
 * @param [out] buf @n A pointer to a buffer to receive incoming data.
 * @param [out] len @n The length, in bytes, of the data pointed to by the 'buf' parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block 'timeout_ms' millisecond maximumly.
 *
 * @retval       -2 : TCP connection error occur.
 * @retval       -1 : TCP connection be closed by remote server.
 * @retval        0 : No any data be received in 'timeout_ms' timeout period.
 * @retval (0, len] : The total number of bytes be received in 'timeout_ms' timeout period.

 * @see None.
 */
int32_t HAL_TCP_Read(uintptr_t fd, char *buf, uint32_t len, uint32_t timeout_ms)
{
	int ret, err_code, tcp_fd;
	uint32_t len_recv;
	uint64_t t_end, t_left;
	fd_set sets;
	struct timeval timeout;

	t_end = freertos_get_time_ms() + timeout_ms;
	len_recv = 0;
	err_code = 0;

	if (fd >= FD_SETSIZE) {
		return -1;
	}
	tcp_fd = (int)fd;

	do {
		t_left = freertos_time_left(t_end, freertos_get_time_ms());
		if (0 == t_left) {
			break;
		}
		FD_ZERO(&sets);
		FD_SET(tcp_fd, &sets);

		timeout.tv_sec = t_left / 1000;
		timeout.tv_usec = (t_left % 1000) * 1000;

		ret = select(tcp_fd + 1, &sets, NULL, NULL, &timeout);
		if (ret > 0) {
			ret = recv(tcp_fd, buf + len_recv, len - len_recv, 0);
			if (ret > 0) {
				len_recv += ret;
			} else if (0 == ret) {
				printf("connection is closed\n");
				err_code = -1;
				break;
			} else {
				if (EINTR == errno) {
					continue;
				}
				printf("recv fail\n");
				err_code = -2;
				break;
			}
		} else if (0 == ret) {
			break;
		} else {
			if (EINTR == errno) {
				continue;
			}
			printf("select-recv fail\n");
			err_code = -2;
			break;
		}
	} while ((len_recv < len));

	/* priority to return data bytes if any data be received from TCP connection. */
	/* It will get error code on next calling */
	return (0 != len_recv) ? len_recv : err_code;
}


/**
?*
?* ���� HAL_TCP_Write() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_TCP_Write() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_TCP_Write(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_TCP_Write, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Write data into the specific TCP connection.
 *        The API will return immediately if 'len' be written into the specific TCP connection.
 *
 * @param [in] fd @n A descriptor identifying a connection.
 * @param [in] buf @n A pointer to a buffer containing the data to be transmitted.
 * @param [in] len @n The length, in bytes, of the data pointed to by the 'buf' parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block 'timeout_ms' millisecond maximumly.
 *
 * @retval      < 0 : TCP connection error occur..
 * @retval        0 : No any data be write into the TCP connection in 'timeout_ms' timeout period.
 * @retval (0, len] : The total number of bytes be written in 'timeout_ms' timeout period.

 * @see None.
 */
int32_t HAL_TCP_Write(uintptr_t fd, const char *buf, uint32_t len, uint32_t timeout_ms)
{
	int ret,tcp_fd;
	uint32_t len_sent;
	uint64_t t_end, t_left;
	fd_set sets;
	int net_err = 0;

	t_end = freertos_get_time_ms() + timeout_ms;
	len_sent = 0;
	ret = 1; /* send one time if timeout_ms is value 0 */

	if (fd >= FD_SETSIZE) {
		return -1;
	}
	tcp_fd = (int)fd;

	do {
		t_left = freertos_time_left(t_end, freertos_get_time_ms());

		if (0 != t_left) {
			struct timeval timeout;

			FD_ZERO(&sets);
			FD_SET(tcp_fd, &sets);

			timeout.tv_sec = t_left / 1000;
			timeout.tv_usec = (t_left % 1000) * 1000;

			ret = select(tcp_fd + 1, NULL, &sets, NULL, &timeout);
			if (ret > 0) {
				if (0 == FD_ISSET(tcp_fd, &sets)) {
					printf("Should NOT arrive\n");
					/* If timeout in next loop, it will not sent any data */
					ret = 0;
					continue;
				}
			} else if (0 == ret) {
				printf("select-write timeout %d\n", tcp_fd);
				break;
			} else {
				if (EINTR == errno) {
					printf("EINTR be caught\n");
					continue;
				}

				printf("select-write fail, ret = select() = %d\n", ret);
				net_err = 1;
				break;
			}
		}

		if (ret > 0) {
			ret = send(tcp_fd, buf + len_sent, len - len_sent, 0);
			if (ret > 0) {
				len_sent += ret;
			} else if (0 == ret) {
				printf("No data be sent\n");
			} else {
				if (EINTR == errno) {
					printf("EINTR be caught\n");
					continue;
				}

				printf("send fail, ret = send() = %d\n", ret);
				net_err = 1;
				break;
			}
		}
	} while (!net_err && (len_sent < len) && (freertos_time_left(t_end, freertos_get_time_ms()) > 0));

	if (net_err) {
		return -1;
	} else {
		return len_sent;
	}
}



/**
?*
?* ���� HAL_UptimeMs() ��ҪSDK��ʹ�������SDK�����е�Ӳ��ƽ̨���ʵ��, ��SDK����
?* ---
?* Interface of HAL_UptimeMs() requires to be implemented by user of SDK, according to target device platform
?*
?* �����Ҫ�ο����ʵ�ֺ��� HAL_UptimeMs(), ���Բ���SDK��ֲ�� Ubuntu Linux ��ʱ��ʾ������
?* ---
?* If you need guidance about how to implement HAL_UptimeMs, you can check its reference implementation for Ubuntu platform
?*
?* https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
?*
?*
?* ע��! HAL_XXX() ϵ�еĺ�����Ȼ�а����ṩ�Ķ�Ӧ�ο�ʵ��, ���������������κ��޸�/���ӵ�Ӧ�������������豸!
?*?
?* ע��! �ο�ʾ��ʵ�ֽ����ڽ��͸��� HAL_XXX() ϵ�к���������!
?*?
?*/
/**
 * @brief Retrieves the number of milliseconds that have elapsed since the system was boot.
 *
 * @return the number of milliseconds.
 * @see None.
 * @note None.
 */
uint64_t HAL_UptimeMs(void)
{
	uint64_t msRet;
	msRet = xTaskGetTickCount() * portTICK_PERIOD_MS;
	
	return msRet;
}



