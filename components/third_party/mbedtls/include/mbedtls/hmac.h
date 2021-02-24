#ifndef _HMAC_H_
#define _HMAC_H_

#include "mbedtls/md.h"

int ssv_hmac_common_vector(ssv_mbedtls_md_type_t type, const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], size_t *len, u8 *mac);
int ssv_hmac_common(ssv_mbedtls_md_type_t type, const u8 *key, size_t key_len, const u8 *data, size_t data_len, u8 *mac);

#ifdef MBEDTLS_EN
int hmac_common_vector(mbedtls_md_type_t type, const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], size_t *len, u8 *mac);
int hmac_common(mbedtls_md_type_t type, const u8 *key, size_t key_len, const u8 *data, size_t data_len, u8 *mac);
#endif


#endif
