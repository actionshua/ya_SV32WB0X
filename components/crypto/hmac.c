#include "soc_types.h"
#include "mbedtls/md.h"

int ssv_hmac_common_vector(ssv_mbedtls_md_type_t type, const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], size_t *len, u8 *mac)

{
    int ret, i;
    ssv_mbedtls_md_context_t ctx;
    const ssv_mbedtls_md_info_t *info_md;

    info_md = ssv_mbedtls_md_info_from_type(type);
    if( info_md == NULL )
    {
        ret = -1;
        goto exit;
        
    }

    ssv_mbedtls_md_init( &ctx );

    if( ( ret = ssv_mbedtls_md_setup( &ctx, info_md, 1 ) ) != 0 )
        goto exit;

    ssv_mbedtls_md_hmac_starts( &ctx, key, key_len );
    for(i = 0; i < num_elem; i++)
        ssv_mbedtls_md_hmac_update( &ctx, addr[i], len[i] );
    ssv_mbedtls_md_hmac_finish( &ctx, mac );

    ssv_mbedtls_md_free( &ctx );

exit:    
    return ret;
}
/*---------------------------------------------------------------------------*/
int ssv_hmac_common(ssv_mbedtls_md_type_t type, const u8 *key, size_t key_len, const u8 *data, size_t data_len, u8 *mac)
{
    return ssv_hmac_common_vector(type, key, key_len, 1, &data, &data_len, mac);    
}

