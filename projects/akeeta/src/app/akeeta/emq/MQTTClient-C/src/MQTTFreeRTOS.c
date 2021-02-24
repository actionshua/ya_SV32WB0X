/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *    Ian Craggs - convert to FreeRTOS
 *******************************************************************************/

#include "MQTTFreeRTOS.h"

#ifdef LWIP_IPV6
#undef LWIP_IPV6
#endif
#ifdef inet_ntop
#undef inet_ntop
#endif
#ifdef inet_pton
#undef inet_pton
#endif
#define LWIP_IPV6 0
#if LWIP_IPV6
#define inet_ntop(af,src,dst,size) \
    (((af) == AF_INET6) ? ip6addr_ntoa_r((src),(dst),(size)) \
     : (((af) == AF_INET) ? ipaddr_ntoa_r((src),(dst),(size)) : NULL))
#define inet_pton(af,src,dst) \
    (((af) == AF_INET6) ? inet6_aton((src),(dst)) \
     : (((af) == AF_INET) ? inet_aton((src),(dst)) : 0))
#else /* LWIP_IPV6 */
#define inet_ntop(af,src,dst,size) \
    (((af) == AF_INET) ? ipaddr_ntoa_r((src),(dst),(size)) : NULL)
#define inet_pton(af,src,dst) \
    (((af) == AF_INET) ? inet_aton((src),(dst)) : 0)
#endif /* LWIP_IPV6 */

int ThreadStart(Thread* thread, void (*fn)(void*), void* arg)
{
	int rc = 0;
	uint16_t usTaskStackSize = (configMINIMAL_STACK_SIZE * 5);
	UBaseType_t uxTaskPriority = uxTaskPriorityGet(NULL); /* set the priority as the same as the calling task*/

	rc = xTaskCreate(fn,	/* The function that implements the task. */
		"MQTTTask",			/* Just a text name for the task to aid debugging. */
		usTaskStackSize,	/* The stack size is defined in FreeRTOSIPConfig.h. */
		arg,				/* The task parameter, not used in this case. */
		uxTaskPriority,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
		&thread->task);		/* The task handle is not used. */

	return rc;
}


void MutexInit(Mutex* mutex)
{
	mutex->sem = xSemaphoreCreateMutex();
}

int MutexLock(Mutex* mutex)
{
	return xSemaphoreTake(mutex->sem, portMAX_DELAY);
}

int MutexUnlock(Mutex* mutex)
{
	return xSemaphoreGive(mutex->sem);
}


void TimerCountdownMS(Timer* timer, unsigned int timeout_ms)
{
	timer->xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
	vTaskSetTimeOutState(&timer->xTimeOut); /* Record the time at which this function was entered. */
}


void TimerCountdown(Timer* timer, unsigned int timeout) 
{
	TimerCountdownMS(timer, timeout * 1000);
}


int TimerLeftMS(Timer* timer) 
{
	xTaskCheckForTimeOut(&timer->xTimeOut, &timer->xTicksToWait); /* updates xTicksToWait to the number left */
	return (timer->xTicksToWait * portTICK_PERIOD_MS);
}


char TimerIsExpired(Timer* timer)
{
	return xTaskCheckForTimeOut(&timer->xTimeOut, &timer->xTicksToWait) == pdTRUE;
}


void TimerInit(Timer* timer)
{
	timer->xTicksToWait = 0;
	memset(&timer->xTimeOut, '\0', sizeof(timer->xTimeOut));
}

int FreeRTOS_read(Network* n, unsigned char* buffer, int len, int timeout_ms)         
{
    int ret;
    struct timeval tv;
    fd_set read_fds;
    int fd = n->my_socket;

    if( fd < 0 )
        return( -1 );

    FD_ZERO( &read_fds );
    FD_SET( fd, &read_fds );

    tv.tv_sec  = timeout_ms / 1000;
    tv.tv_usec = ( timeout_ms % 1000 ) * 1000;

    ret = select( fd + 1, &read_fds, NULL, NULL, timeout_ms == 0 ? NULL : &tv );

    /* Zero fds ready means we timed out */
    if( ret == 0 )
        return 0;

    if( ret < 0 )
		return -1;

	ret = (int) read( fd, buffer, len );

	if( ret < 0 )
		return -1;

	return ret;
}

int FreeRTOS_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    int rc = 0;
    int ret = -1;
    fd_set fdset;
    struct timeval tv;

    FD_ZERO(&fdset);
    FD_SET(n->my_socket, &fdset);

    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    ret = select(n->my_socket + 1, NULL, &fdset, NULL, &tv);

    if (ret <= 0) {
       ya_printf(C_LOG_ERROR, "mqtt write fail\r\n");
        return -1;
    } else {
        rc = write(n->my_socket, buffer, len);
		ya_printf(C_LOG_INFO, "mqtt write: %d\r\n", rc);
    }
    return rc;

}


void FreeRTOS_disconnect(Network* n)
{
	shutdown(n->my_socket, SHUT_RDWR);
	close(n->my_socket);
	n->my_socket = -1;
}

void NetworkInit(Network* n)
{
	n->my_socket = -1;
	n->mqttread = FreeRTOS_read;
	n->mqttwrite = FreeRTOS_write;
	n->disconnect = FreeRTOS_disconnect;
}

int NetworkConnect(Network* n, char* addr, int port)
{
	struct sockaddr_in sAddr;
	int retVal = -1;
	struct hostent *hptr;
	char   **pptr;
	char   str[32];
	
	if(n->my_socket >= 0){
		n->disconnect(n);
	}
	if ((hptr = gethostbyname(addr)) == 0)
	{
		ya_printf(C_LOG_ERROR, "gethostbyname failed!\r\n");
		goto exit;
	}
	pptr = hptr->h_addr_list;

	for(; *pptr!=NULL; pptr++)
	{
		inet_ntop(hptr->h_addrtype, (const ip_addr_t *)*pptr, str, sizeof(str));
	}
	inet_ntop(hptr->h_addrtype, (const ip_addr_t *)hptr->h_addr, str, sizeof(str));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);
	sAddr.sin_addr.s_addr = inet_addr(str);
	ya_printf(C_LOG_INFO, "addr = %s\r\n", str);

	if ((n->my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		goto exit;
	}
	
	if ((retVal = connect(n->my_socket, (struct sockaddr*)&sAddr, sizeof(sAddr))) < 0)
	{
		close(n->my_socket);
		ya_printf(C_LOG_INFO, "Connect failed!!\r\n");
		goto exit;
	}
	
exit:
	return retVal;
}

#if 0
int NetworkConnectTLS(Network *n, char* addr, int port, SlSockSecureFiles_t* certificates, unsigned char sec_method, unsigned int cipher, char server_verify)
{
	SlSockAddrIn_t sAddr;
	int addrSize;
	int retVal;
	unsigned long ipAddress;

	retVal = sl_NetAppDnsGetHostByName(addr, strlen(addr), &ipAddress, AF_INET);
	if (retVal < 0) {
		return -1;
	}

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = sl_Htons((unsigned short)port);
	sAddr.sin_addr.s_addr = sl_Htonl(ipAddress);

	addrSize = sizeof(SlSockAddrIn_t);

	n->my_socket = sl_Socket(SL_AF_INET, SL_SOCK_STREAM, SL_SEC_SOCKET);
	if (n->my_socket < 0) {
		return -1;
	}

	SlSockSecureMethod method;
	method.secureMethod = sec_method;
	retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECMETHOD, &method, sizeof(method));
	if (retVal < 0) {
		return retVal;
	}

	SlSockSecureMask mask;
	mask.secureMask = cipher;
	retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECURE_MASK, &mask, sizeof(mask));
	if (retVal < 0) {
		return retVal;
	}

	if (certificates != NULL) {
		retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECURE_FILES, certificates->secureFiles, sizeof(SlSockSecureFiles_t));
		if (retVal < 0)
		{
			return retVal;
		}
	}

	retVal = sl_Connect(n->my_socket, (SlSockAddr_t *)&sAddr, addrSize);
	if (retVal < 0) {
		if (server_verify || retVal != -453) {
			sl_Close(n->my_socket);
			return retVal;
		}
	}

	SysTickIntRegister(SysTickIntHandler);
	SysTickPeriodSet(80000);
	SysTickEnable();

	return retVal;
}
#endif

