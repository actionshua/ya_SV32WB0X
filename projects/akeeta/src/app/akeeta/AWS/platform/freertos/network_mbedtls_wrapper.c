/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ya_config_platform.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ya_config.h"
#include <timer_platform.h>
#include <network_interface.h>
#include "aws_iot_error.h"
#include "aws_iot_log.h"
#include "network_platform.h"
#include "timer_interface.h"
#include "ya_common.h"

#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"

const char *TAG = "aws_iot";

/* This is the value used for ssl read timeout */
#define IOT_SSL_READ_TIMEOUT 10

/*
 * This is a function to do further verification if needed on the cert received
 */
static int _iot_tls_verify_cert(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags) {

	char* buf_ptr = NULL;
	((void) data);

    buf_ptr =(char *)pvPortMalloc(1024);
    if (buf_ptr == NULL) {        
        IOT_DEBUG("_iot_tls_verify_cert memory calloc fail\r\n");
        return -1;
    }
    
    memset(buf_ptr, 0, 1024);

	printf("Verify requested for (Depth %d):\r\n", depth);
	mbedtls_x509_crt_info(buf_ptr, sizeof(buf_ptr) - 1, "", crt);
	printf("%s\r\n", buf_ptr);

	if ((*flags) == 0) {
		printf(" This certificate has no flags\r\n");
	} else {
		mbedtls_x509_crt_verify_info( buf_ptr, 1024, "  ! ", *flags );
	}

    vPortFree(buf_ptr);

	return 0;
}

void _iot_tls_set_connect_params(Network *pNetwork, char *pRootCALocation,
                                 char *pDeviceCertLocation, char *pDevicePrivateKeyLocation,
                                 char *pDestinationURL, uint16_t destinationPort,
                                 uint32_t timeout_ms, bool ServerVerificationFlag) {
	pNetwork->tlsConnectParams.DestinationPort = destinationPort;
	pNetwork->tlsConnectParams.pDestinationURL = pDestinationURL;
	pNetwork->tlsConnectParams.pDeviceCertLocation = pDeviceCertLocation;
	pNetwork->tlsConnectParams.pDevicePrivateKeyLocation = pDevicePrivateKeyLocation;
	pNetwork->tlsConnectParams.pRootCALocation = pRootCALocation;
	pNetwork->tlsConnectParams.timeout_ms = timeout_ms;
	pNetwork->tlsConnectParams.ServerVerificationFlag = ServerVerificationFlag;
}

IoT_Error_t iot_tls_init(Network *pNetwork, char *pRootCALocation, char *pDeviceCertLocation,
						 char *pDevicePrivateKeyLocation, char *pDestinationURL,
						 uint16_t destinationPort, uint32_t timeout_ms, bool ServerVerificationFlag) {
	_iot_tls_set_connect_params(pNetwork, pRootCALocation, pDeviceCertLocation, pDevicePrivateKeyLocation,
								pDestinationURL, destinationPort, timeout_ms, ServerVerificationFlag);

	pNetwork->connect = iot_tls_connect;
	pNetwork->read = iot_tls_read;
	pNetwork->write = iot_tls_write;
	pNetwork->disconnect = iot_tls_disconnect;
	pNetwork->isConnected = iot_tls_is_connected;
	pNetwork->destroy = iot_tls_destroy;

	pNetwork->tlsDataParams.flags = 0;

	return SUCCESS;
}

IoT_Error_t iot_tls_is_connected(Network *pNetwork) {
	/* Use this to add implementation which can check for physical layer disconnect */
	return NETWORK_PHYSICAL_LAYER_CONNECTED;
}

static void aws_my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
	ya_printf(C_LOG_INFO, "%s:%d: %s\r\n", file, line, str);
}

IoT_Error_t iot_tls_connect(Network *pNetwork, TLSConnectParams *params) {
	int ret = 0;
	TLSDataParams *tlsDataParams = NULL;
	char portBuffer[6];

	//weishan
	const char *alpnProtocols[] = { "x-amzn-mqtt-ca", NULL };

	if(NULL == pNetwork) {
		return NULL_VALUE_ERROR;
	}

	if(NULL != params) {
		_iot_tls_set_connect_params(pNetwork, params->pRootCALocation, params->pDeviceCertLocation,
									params->pDevicePrivateKeyLocation, params->pDestinationURL,
									params->DestinationPort, params->timeout_ms, params->ServerVerificationFlag);
	}

	//mbedtls_platform_set_calloc_free(aws_my_calloc, vPortFree);

	tlsDataParams = &(pNetwork->tlsDataParams);

	mbedtls_net_init(&(tlsDataParams->server_fd));
	mbedtls_ssl_init(&(tlsDataParams->ssl));
	mbedtls_ssl_config_init(&(tlsDataParams->conf));

	mbedtls_ctr_drbg_init(&(tlsDataParams->ctr_drbg));
	mbedtls_x509_crt_init(&(tlsDataParams->cacert));
	mbedtls_x509_crt_init(&(tlsDataParams->clicert));
	mbedtls_pk_init(&(tlsDataParams->pkey));

    mbedtls_entropy_init(&(tlsDataParams->entropy));
    if ((ret = mbedtls_ctr_drbg_seed(&(tlsDataParams->ctr_drbg), mbedtls_entropy_func, &(tlsDataParams->entropy), (const unsigned char *) TAG, strlen(TAG))) != 0) {
        IOT_DEBUG("failed! mbedtls_ctr_drbg_seed returned -0x%x\r\n", -ret);
        return NETWORK_MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED;
    }

    ret = mbedtls_x509_crt_parse(&(tlsDataParams->cacert),
                                    (const unsigned char *)pNetwork->tlsConnectParams.pRootCALocation,
                                    strlen(pNetwork->tlsConnectParams.pRootCALocation) + 1);
                                 //(const unsigned char *)AWS_IOT_ROOT_CA_CERT,
                                 //AWS_IOT_ROOT_CA_CERT_LEN);
	if (ret < 0) {
		IOT_ERROR(" failed  !  mbedtls_x509_crt_parse returned -0x%x while parsing root cert\n\n", -ret);
		return NETWORK_X509_ROOT_CRT_PARSE_ERROR;
	}

    ret = mbedtls_x509_crt_parse(&(tlsDataParams->clicert),
                                    (const unsigned char *)pNetwork->tlsConnectParams.pDeviceCertLocation,
                                    strlen(pNetwork->tlsConnectParams.pDeviceCertLocation) + 1);
                                  //(const unsigned char *)AWS_IOT_DEVICE_CERT,
                                  //AWS_IOT_DEVICE_CERT_LEN);
	if (ret != 0) {
		IOT_ERROR(" failed  !  mbedtls_x509_crt_parse returned -0x%x while parsing device cert\n\n", -ret);
		return NETWORK_X509_DEVICE_CRT_PARSE_ERROR;
	}
    
    ret = mbedtls_pk_parse_key(&(tlsDataParams->pkey),
                                    (const unsigned char *)pNetwork->tlsConnectParams.pDevicePrivateKeyLocation,
                                    strlen(pNetwork->tlsConnectParams.pDevicePrivateKeyLocation) + 1,
                                    (const unsigned char *)"", strlen(""));
                                //(const unsigned char *)AWS_IOT_PRIVATE_KEY,
                                //AWS_IOT_PRIVATE_KEY_LEN, (const unsigned char *)"", strlen(""));
	if (ret != 0) {
		IOT_ERROR(" failed  !  mbedtls_pk_parse_key returned -0x%x while parsing private key\n\n", -ret);
        if (ret == -0x1180) {
            IOT_DEBUG("\r\n***************************\r\nCurrent Free Heap Size : %d\r\n***************************\r\n", xPortGetFreeHeapSize());
        }
		return NETWORK_PK_PRIVATE_KEY_PARSE_ERROR;
	}
    printf("ssl init success\r\n");
    
	snprintf(portBuffer, 6, "%d", pNetwork->tlsConnectParams.DestinationPort);
	printf("Connecting to %s:%s...\r\n", pNetwork->tlsConnectParams.pDestinationURL, portBuffer);
	if ((ret = mbedtls_net_connect(&(tlsDataParams->server_fd), pNetwork->tlsConnectParams.pDestinationURL,
								   portBuffer, MBEDTLS_NET_PROTO_TCP)) != 0) {
		IOT_ERROR(" failed  ! mbedtls_net_connect returned -0x%x\r\n", -ret);
		switch(ret) {
			case MBEDTLS_ERR_NET_SOCKET_FAILED:
				return NETWORK_ERR_NET_SOCKET_FAILED;
			case MBEDTLS_ERR_NET_UNKNOWN_HOST:
				return NETWORK_ERR_NET_UNKNOWN_HOST;
			case MBEDTLS_ERR_NET_CONNECT_FAILED:
			default:
				return NETWORK_ERR_NET_CONNECT_FAILED;
		};
	}
    printf("connect server success\r\n");
	#if 0							   
    ret = mbedtls_net_set_block(&(tlsDataParams->server_fd));
	if (ret != 0) {
		IOT_ERROR(" set block failed  ! net_set_(non)block() returned -0x%x\n\n", -ret);
		return SSL_CONNECTION_ERROR;
	}
	#endif
	printf("Configuring the SSL/TLS Defaults...");
	if ((ret = mbedtls_ssl_config_defaults(&(tlsDataParams->conf), MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM,
			MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
		IOT_ERROR(" failed ! mbedtls_ssl_config_defaults returned -0x%x\n\n", -ret);
		return SSL_CONNECTION_ERROR;
	}
    printf("Configuring SSL/TLS Defaults Succeed\r\n");
			
	mbedtls_ssl_conf_verify(&(tlsDataParams->conf), _iot_tls_verify_cert, NULL);
	if (pNetwork->tlsConnectParams.ServerVerificationFlag == true) {
		mbedtls_ssl_conf_authmode(&(tlsDataParams->conf), MBEDTLS_SSL_VERIFY_REQUIRED);
	} else {
		mbedtls_ssl_conf_authmode(&(tlsDataParams->conf), MBEDTLS_SSL_VERIFY_OPTIONAL);
	}
	
    mbedtls_ssl_conf_rng(&(tlsDataParams->conf), mbedtls_ctr_drbg_random, &(tlsDataParams->ctr_drbg));
	//#ifdef MBEDTLS_DEBUG_C
		//mbedtls_debug_set_threshold(5);
	//#endif

	//mbedtls_ssl_conf_dbg(&(tlsDataParams->conf), aws_my_debug, NULL);

	mbedtls_ssl_conf_ca_chain(&(tlsDataParams->conf), &(tlsDataParams->cacert), NULL);
	if ((ret = mbedtls_ssl_conf_own_cert(&(tlsDataParams->conf), &(tlsDataParams->clicert), &(tlsDataParams->pkey))) != 0) {
		IOT_ERROR(" failed  ! mbedtls_ssl_conf_own_cert returned %d\n\n", ret);
		return SSL_CONNECTION_ERROR;
	}

	mbedtls_ssl_conf_read_timeout(&(tlsDataParams->conf), pNetwork->tlsConnectParams.timeout_ms);

	//weishan
	if(443 == pNetwork->tlsConnectParams.DestinationPort) {
		if((ret = mbedtls_ssl_conf_alpn_protocols(&(tlsDataParams->conf), alpnProtocols)) != 0) {
			IOT_ERROR(" failed\n  ! mbedtls_ssl_conf_alpn_protocols returned -0x%x\n\n", -ret);
			return SSL_CONNECTION_ERROR;
		}
	}

    printf("Setting up mbedtls ssl...\r\n");

	if ((ret = mbedtls_ssl_setup(&(tlsDataParams->ssl), &(tlsDataParams->conf))) != 0) {
		IOT_ERROR("   failed  ! mbedtls_ssl_setup returned -0x%x\n\n", -ret);
		return SSL_CONNECTION_ERROR;
	}
	if ((ret = mbedtls_ssl_set_hostname(&(tlsDataParams->ssl), pNetwork->tlsConnectParams.pDestinationURL)) != 0) {
		IOT_ERROR(" failed  ! mbedtls_ssl_set_hostname returned %d\n\n", ret);
		return SSL_CONNECTION_ERROR;
	}
	
	printf("SSL state connect : %d \r\n", tlsDataParams->ssl.state);
	mbedtls_ssl_set_bio(&(tlsDataParams->ssl), &(tlsDataParams->server_fd), mbedtls_net_send, NULL, mbedtls_net_recv_timeout);

	printf("ok\r\n");
	printf("SSL state connect : %d\r\n", tlsDataParams->ssl.state);
	printf("Performing the SSL/TLS handshake...\r\n");
	
	while ((ret = mbedtls_ssl_handshake(&(tlsDataParams->ssl))) != 0) {
		
		if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
			IOT_ERROR(" failed  ! mbedtls_ssl_handshake returned -0x%x\r\n", -ret);
			if (ret == MBEDTLS_ERR_X509_CERT_VERIFY_FAILED) {
				IOT_ERROR("\r\n    Unable to verify the server's certificate. "
						"Either it is invalid,\n"
						"    or you didn't set ca_file or ca_path "
						"to an appropriate value.\n"
						"    Alternatively, you may want to use "
						"auth_mode=optional for testing purposes.\r\n");
			}
			return SSL_CONNECTION_ERROR;
		}
	}

	printf("\r\n [ Protocol is %s ]\r\n [ Ciphersuite is %s ]\r\n", mbedtls_ssl_get_version(&(tlsDataParams->ssl)), mbedtls_ssl_get_ciphersuite(&(tlsDataParams->ssl)));
	if ((ret = mbedtls_ssl_get_record_expansion(&(tlsDataParams->ssl))) >= 0) {
		IOT_DEBUG("    [ Record expansion is %d ]\r\n", ret);
	} else {
		IOT_DEBUG("    [ Record expansion is unknown (compression) ]\r\n");
	}

	printf("Verifying peer X.509 certificate...\r\n");

	if(pNetwork->tlsConnectParams.ServerVerificationFlag == true) {
		if((tlsDataParams->flags = mbedtls_ssl_get_verify_result(&(tlsDataParams->ssl))) != 0) {
			
			IOT_DEBUG("Verify X.509 Certificate failed\r\n");
			ret = SSL_CONNECTION_ERROR;
		} else {
			printf("Verify X.509 Certificate Succeed\r\n");
			ret = SUCCESS;
		}
	} else {
		IOT_DEBUG(" Server Verification skipped\r\n");
		ret = SUCCESS;
	}

	mbedtls_ssl_conf_read_timeout(&(tlsDataParams->conf), IOT_SSL_READ_TIMEOUT);

	return (IoT_Error_t) ret;
}

IoT_Error_t iot_tls_write(Network *pNetwork, unsigned char *pMsg, size_t len, Timer *timer, size_t *written_len) {
	size_t written_so_far = 0;
	bool isErrorFlag = false;
	int frags, ret = 0;
	TLSDataParams *tlsDataParams = &(pNetwork->tlsDataParams);

	for(written_so_far = 0, frags = 0; written_so_far < len && !has_timer_expired(timer); written_so_far += ret, frags++) {
		while(!has_timer_expired(timer) && (ret = mbedtls_ssl_write(&(tlsDataParams->ssl), pMsg + written_so_far, len - written_so_far)) <= 0) {
			if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
				IOT_ERROR(" failed  ! mbedtls_ssl_write returned -0x%x\r\n", -ret);
				/* All other negative return values indicate connection needs to be reset.
		 		* Will be caught in ping request so ignored here */
				isErrorFlag = true;
				break;
			}
		}
		if(isErrorFlag) {
			break;
		}
	}

	*written_len = written_so_far;

	if(isErrorFlag) {
		return NETWORK_SSL_WRITE_ERROR;
	} else if(has_timer_expired(timer) && written_so_far != len) {
		return NETWORK_SSL_WRITE_TIMEOUT_ERROR;
	}

	return SUCCESS;
}

IoT_Error_t iot_tls_read(Network *pNetwork, unsigned char *pMsg, size_t len, Timer *timer, size_t *read_len) {
	mbedtls_ssl_context *ssl = &(pNetwork->tlsDataParams.ssl);
	size_t rxLen = 0;
	int ret;

	while (len > 0) {
		// This read will timeout after IOT_SSL_READ_TIMEOUT if there's no data to be read
		ret = mbedtls_ssl_read(ssl, pMsg, len);
		if (ret > 0) {
			rxLen += ret;
			pMsg += ret;
			len -= ret;
		} else if (ret == 0 || (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE && ret != MBEDTLS_ERR_SSL_TIMEOUT)) {
			return NETWORK_SSL_READ_ERROR;
		}

		// Evaluate timeout after the read to make sure read is done at least once
		if (has_timer_expired(timer)) {
			break;
		}
	}

	if (len == 0) {
		*read_len = rxLen;
		return SUCCESS;
	}

	if (rxLen == 0) {
		return NETWORK_SSL_NOTHING_TO_READ;
	} else {
		return NETWORK_SSL_READ_TIMEOUT_ERROR;
	}
}

IoT_Error_t iot_tls_disconnect(Network *pNetwork) {
	mbedtls_ssl_context *ssl = &(pNetwork->tlsDataParams.ssl);
	int ret = 0;
	do {
		ret = mbedtls_ssl_close_notify(ssl);
	} while (ret == MBEDTLS_ERR_SSL_WANT_WRITE);

	/* All other negative return values indicate connection needs to be reset.
	 * No further action required since this is disconnect call */

	return SUCCESS;
}

IoT_Error_t iot_tls_destroy(Network *pNetwork) {
	TLSDataParams *tlsDataParams = &(pNetwork->tlsDataParams);

	mbedtls_net_free(&(tlsDataParams->server_fd));
	mbedtls_x509_crt_free(&(tlsDataParams->clicert));
	mbedtls_x509_crt_free(&(tlsDataParams->cacert));
	mbedtls_pk_free(&(tlsDataParams->pkey));
	mbedtls_ssl_free(&(tlsDataParams->ssl));
	mbedtls_ssl_config_free(&(tlsDataParams->conf));
    mbedtls_ctr_drbg_free(&(tlsDataParams->ctr_drbg));
    mbedtls_entropy_free(&(tlsDataParams->entropy));

	return SUCCESS;
}

#ifdef __cplusplus
}
#endif
