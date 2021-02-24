
#include "mbedtls/cipher.h"
#include "mbedtls/ecp.h"
#include "mbedtls/bignum.h"
#include "mbedtls/cmac.h"
#include "mbedtls/hmac.h"
#include "mbedtls/aes.h"
#include "mbedtls/pkcs5.h"
#include "mbedtls/arc4.h"
#include "mbedtls/md5.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"

//cipher wrap
const int *mbedtls_cipher_list()
{
    return ssv_mbedtls_cipher_list();
}

const mbedtls_cipher_info_t *mbedtls_cipher_info_from_string( const char *cipher_name)
{
    return (mbedtls_cipher_info_t *)ssv_mbedtls_cipher_info_from_string(cipher_name);
}

const mbedtls_cipher_info_t *mbedtls_cipher_info_from_type(const mbedtls_cipher_type_t cipher_type )
{
    return (ssv_mbedtls_cipher_info_t *)ssv_mbedtls_cipher_info_from_type((ssv_mbedtls_cipher_type_t)cipher_type);
}

const mbedtls_cipher_info_t *mbedtls_cipher_info_from_values(const mbedtls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const mbedtls_cipher_mode_t mode)
{
    return (ssv_mbedtls_cipher_info_t *)ssv_mbedtls_cipher_info_from_values( (ssv_mbedtls_cipher_id_t) cipher_id,
                                              key_bitlen, (ssv_mbedtls_cipher_mode_t) mode );
}

void mbedtls_cipher_init(mbedtls_cipher_context_t *ctx)
{
    ssv_mbedtls_cipher_init((ssv_mbedtls_cipher_context_t *)ctx);
}

void mbedtls_cipher_free(mbedtls_cipher_context_t *ctx)
{
    ssv_mbedtls_cipher_free((ssv_mbedtls_cipher_context_t *)ctx);
}

int mbedtls_cipher_setup(mbedtls_cipher_context_t *ctx, const mbedtls_cipher_info_t *cipher_info)
{
    return ssv_mbedtls_cipher_setup((ssv_mbedtls_cipher_context_t *)ctx, (ssv_mbedtls_cipher_info_t *)cipher_info);
}

int mbedtls_cipher_get_block_size(const mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_get_block_size((ssv_mbedtls_cipher_context_t *)ctx);
}

int  mbedtls_cipher_get_cipher_mode(const mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_get_cipher_mode((ssv_mbedtls_cipher_context_t *)ctx);
}

int mbedtls_cipher_get_iv_size(const mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_get_iv_size((ssv_mbedtls_cipher_context_t *)ctx);
}

int mbedtls_cipher_get_type(const mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_get_type((ssv_mbedtls_cipher_context_t *)ctx);
}

const char *mbedtls_cipher_get_name(const mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_get_name((ssv_mbedtls_cipher_context_t *)ctx);
}

int mbedtls_cipher_get_key_bitlen(const mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_get_key_bitlen((ssv_mbedtls_cipher_context_t *)ctx);
}

mbedtls_operation_t mbedtls_cipher_get_operation(const mbedtls_cipher_context_t *ctx)
{
    return (mbedtls_operation_t)ssv_mbedtls_cipher_get_operation((ssv_mbedtls_cipher_context_t *)ctx);
}

int mbedtls_cipher_setkey(mbedtls_cipher_context_t *ctx,
                           const unsigned char *key,
                           int key_bitlen,
                           const mbedtls_operation_t operation)
{
    return ssv_mbedtls_cipher_setkey((ssv_mbedtls_cipher_context_t *)ctx,
                           key, key_bitlen, (ssv_mbedtls_operation_t)operation);
}

#if defined(SSV_MBEDTLS_CIPHER_MODE_WITH_PADDING)
int mbedtls_cipher_set_padding_mode(mbedtls_cipher_context_t *ctx,
                                     mbedtls_cipher_padding_t mode)
{
    return ssv_mbedtls_cipher_set_padding_mode( (ssv_mbedtls_cipher_context_t *)ctx,
                                     (ssv_mbedtls_cipher_padding_t) mode);
}
#endif

int mbedtls_cipher_set_iv(mbedtls_cipher_context_t *ctx,
                           const unsigned char *iv,
                           size_t iv_len)
{
    return ssv_mbedtls_cipher_set_iv((ssv_mbedtls_cipher_context_t *)ctx,
                           iv, iv_len);
}

int mbedtls_cipher_reset(mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_reset((ssv_mbedtls_cipher_context_t *)ctx);
}

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
int mbedtls_cipher_update_ad( mbedtls_cipher_context_t *ctx,
                      const unsigned char *ad, size_t ad_len)
{
    return ssv_mbedtls_cipher_update_ad((ssv_mbedtls_cipher_context_t *)ctx,
                      ad, ad_len);
}
#endif

int mbedtls_cipher_update(mbedtls_cipher_context_t *ctx, const unsigned char *input,
                   size_t ilen, unsigned char *output, size_t *olen)
{
    return ssv_mbedtls_cipher_update((ssv_mbedtls_cipher_context_t *)ctx, input,
                   ilen, output, olen);
}

int mbedtls_cipher_finish( mbedtls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen )
{
    return ssv_mbedtls_cipher_finish((ssv_mbedtls_cipher_context_t *)ctx,
                   output, olen );
}

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
int mbedtls_cipher_write_tag(mbedtls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len )
{
    return ssv_mbedtls_cipher_write_tag((ssv_mbedtls_cipher_context_t *)ctx,
                      tag, tag_len);
}

int mbedtls_cipher_check_tag(mbedtls_cipher_context_t *ctx,
                      const unsigned char *tag, size_t tag_len )
{
    return ssv_mbedtls_cipher_check_tag((ssv_mbedtls_cipher_context_t *)ctx,
                     tag, tag_len);
}
#endif

int mbedtls_cipher_crypt(mbedtls_cipher_context_t *ctx,
                  const unsigned char *iv, size_t iv_len,
                  const unsigned char *input, size_t ilen,
                  unsigned char *output, size_t *olen  )
{
    return ssv_mbedtls_cipher_crypt((ssv_mbedtls_cipher_context_t *)ctx,
                  iv, iv_len, input, ilen, output, olen );
}

#if defined(SSV_MBEDTLS_CIPHER_MODE_AEAD)
int mbedtls_cipher_auth_encrypt(mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len )
{
    return ssv_mbedtls_cipher_auth_encrypt((ssv_mbedtls_cipher_context_t *)ctx,
                         iv, iv_len, ad, ad_len, input, ilen, output, olen, tag, tag_len);
}

int mbedtls_cipher_auth_decrypt(mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len )
{
    return ssv_mbedtls_cipher_auth_decrypt((ssv_mbedtls_cipher_context_t *)ctx,
                         iv, iv_len, ad, ad_len, input, ilen, output, olen, tag, tag_len);
}
#endif

//ecp wrap
#if defined(MBEDTLS_ECP_RESTARTABLE)
void mbedtls_ecp_set_max_ops( unsigned max_ops )
{
    ssv_mbedtls_ecp_set_max_ops(max_ops);
}

void ssv_mbedtls_ecp_restart_is_enabled()
{
    mbedtls_ecp_restart_is_enabled();
}
#endif

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_list()
{
    return (const mbedtls_ecp_curve_info*)ssv_mbedtls_ecp_curve_list();
}

const mbedtls_ecp_group_id *mbedtls_ecp_grp_id_list()
{
    return (const mbedtls_ecp_group_id*)ssv_mbedtls_ecp_grp_id_list();
}

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_grp_id(mbedtls_ecp_group_id grp_id)
{
    return (const mbedtls_ecp_curve_info*)ssv_mbedtls_ecp_curve_info_from_grp_id((ssv_mbedtls_ecp_group_id) grp_id);
}

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_tls_id(uint16_t tls_id)
{
    return (const mbedtls_ecp_curve_info*)ssv_mbedtls_ecp_curve_info_from_tls_id(tls_id);
}

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_name(const char *name )
{
    return (const mbedtls_ecp_curve_info*)ssv_mbedtls_ecp_curve_info_from_name(name);
}

void mbedtls_ecp_point_init(mbedtls_ecp_point *pt )
{
    ssv_mbedtls_ecp_point_init((ssv_mbedtls_ecp_point *)pt);
}

void mbedtls_ecp_group_init(mbedtls_ecp_group *grp )
{
    ssv_mbedtls_ecp_group_init((ssv_mbedtls_ecp_group *)grp );
}

void mbedtls_ecp_keypair_init(mbedtls_ecp_keypair *key )
{
    ssv_mbedtls_ecp_keypair_init((ssv_mbedtls_ecp_keypair *)key );
}

void mbedtls_ecp_point_free(mbedtls_ecp_point *pt )
{
    ssv_mbedtls_ecp_point_free((ssv_mbedtls_ecp_point *)pt);
}

void mbedtls_ecp_group_free(mbedtls_ecp_group *grp  )
{
    ssv_mbedtls_ecp_group_free((ssv_mbedtls_ecp_group *)grp );
}

void mbedtls_ecp_keypair_free(mbedtls_ecp_keypair *key)
{
    ssv_mbedtls_ecp_keypair_free((ssv_mbedtls_ecp_keypair *)key);
}

#if defined(MBEDTLS_ECP_RESTARTABLE)
void mbedtls_ecp_restart_init(mbedtls_ecp_restart_ctx *ctx)
{
    ssv_mbedtls_ecp_restart_init((ssv_mbedtls_ecp_restart_ctx *)ctx);
}

void mbedtls_ecp_restart_free(mbedtls_ecp_restart_ctx *ctx)
{
    ssv_mbedtls_ecp_restart_free((ssv_mbedtls_ecp_restart_ctx *)ctx);
}
#endif

int mbedtls_ecp_copy(mbedtls_ecp_point *P, const mbedtls_ecp_point *Q)
{
    return ssv_mbedtls_ecp_copy((ssv_mbedtls_ecp_point *)P, (ssv_mbedtls_ecp_point *)Q);
}

int mbedtls_ecp_group_copy(mbedtls_ecp_group *dst, const mbedtls_ecp_group *src )
{
    return ssv_mbedtls_ecp_group_copy((ssv_mbedtls_ecp_group *)dst, (ssv_mbedtls_ecp_group *)src );
}

int mbedtls_ecp_set_zero(mbedtls_ecp_point *pt )
{
    return ssv_mbedtls_ecp_set_zero((ssv_mbedtls_ecp_point *)pt);
}

int mbedtls_ecp_is_zero(mbedtls_ecp_point *pt )
{
    return ssv_mbedtls_ecp_is_zero((ssv_mbedtls_ecp_point *)pt);
}

int mbedtls_ecp_point_cmp(const mbedtls_ecp_point *P,
                           const mbedtls_ecp_point *Q)
{
    return ssv_mbedtls_ecp_point_cmp((ssv_mbedtls_ecp_point *)P,
                            (ssv_mbedtls_ecp_point *)Q);
}

int mbedtls_ecp_point_read_string(mbedtls_ecp_point *P, int radix,
                           const char *x, const char *y )
{
    return ssv_mbedtls_ecp_point_read_string((ssv_mbedtls_ecp_point *)P, radix, x, y);
}

int mbedtls_ecp_point_write_binary( const mbedtls_ecp_group *grp,
                                    const mbedtls_ecp_point *P,
                                    int format, size_t *olen,
                                    unsigned char *buf, size_t buflen )
{
    return ssv_mbedtls_ecp_point_write_binary((ssv_mbedtls_ecp_group *)grp,
                                    (ssv_mbedtls_ecp_point *)P, format, olen, buf, buflen );
}

int mbedtls_ecp_point_read_binary(const mbedtls_ecp_group *grp,
                                   mbedtls_ecp_point *pt,
                                   const unsigned char *buf, size_t ilen)
{
    return ssv_mbedtls_ecp_point_read_binary((ssv_mbedtls_ecp_group *)grp,
                                   (ssv_mbedtls_ecp_point *)pt, buf, ilen);
}

int mbedtls_ecp_tls_read_point(const mbedtls_ecp_group *grp,
                                mbedtls_ecp_point *pt,
                                const unsigned char **buf, size_t buf_len)
{
    return ssv_mbedtls_ecp_tls_read_point((ssv_mbedtls_ecp_group *)grp,
                                (mbedtls_ecp_point *)pt, buf, buf_len);
}

int mbedtls_ecp_tls_write_point(const mbedtls_ecp_group *grp, const mbedtls_ecp_point *pt,
                         int format, size_t *olen,
                         unsigned char *buf, size_t blen)
{
    return ssv_mbedtls_ecp_tls_write_point((ssv_mbedtls_ecp_group *)grp, (ssv_mbedtls_ecp_point *)pt,
                         format, olen, buf, blen);
}

int mbedtls_ecp_group_load(mbedtls_ecp_group *grp, mbedtls_ecp_group_id id)
{
    return ssv_mbedtls_ecp_group_load((ssv_mbedtls_ecp_group *)grp, (ssv_mbedtls_ecp_group_id) id);
}

int mbedtls_ecp_tls_read_group(mbedtls_ecp_group *grp,
                                const unsigned char **buf, size_t len)
{
    return ssv_mbedtls_ecp_tls_read_group((ssv_mbedtls_ecp_group *)grp, buf, len);
}

int mbedtls_ecp_tls_read_group_id(mbedtls_ecp_group_id *grp,
                                   const unsigned char **buf, size_t len )
{
    return ssv_mbedtls_ecp_tls_read_group_id((ssv_mbedtls_ecp_group_id *)grp, buf, len);
}

int mbedtls_ecp_tls_write_group(const mbedtls_ecp_group *grp, size_t *olen,
                         unsigned char *buf, size_t blen )
{
    return ssv_mbedtls_ecp_tls_write_group((ssv_mbedtls_ecp_group *)grp, olen, buf, blen);
}

int mbedtls_ecp_mul(mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    return ssv_mbedtls_ecp_mul((ssv_mbedtls_ecp_group *)grp, (ssv_mbedtls_ecp_point *)R,
             (ssv_mbedtls_mpi *)m, (ssv_mbedtls_ecp_point *)P, f_rng, p_rng);
}

int mbedtls_ecp_mul_restartable(mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
             mbedtls_ecp_restart_ctx *rs_ctx )
{
    return ssv_mbedtls_ecp_mul_restartable((ssv_mbedtls_ecp_group *)grp, (ssv_mbedtls_ecp_point *)R,
             (ssv_mbedtls_mpi *)m, (ssv_mbedtls_ecp_point *)P, f_rng, p_rng,
             (ssv_mbedtls_ecp_restart_ctx *)rs_ctx );
}

int mbedtls_ecp_muladd(mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q)
{
    return ssv_mbedtls_ecp_muladd((ssv_mbedtls_ecp_group *)grp, (ssv_mbedtls_ecp_point *)R,
             (ssv_mbedtls_mpi *)m, (ssv_mbedtls_ecp_point *)P,
             (ssv_mbedtls_mpi *)n,  (ssv_mbedtls_ecp_point *)Q);
}

int mbedtls_ecp_muladd_restartable(
             mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q,
             mbedtls_ecp_restart_ctx *rs_ctx)
{
    return ssv_mbedtls_ecp_muladd_restartable(
             (ssv_mbedtls_ecp_group *)grp, (ssv_mbedtls_ecp_point *)R,
             (ssv_mbedtls_mpi *)m, (ssv_mbedtls_ecp_point *)P,
             (ssv_mbedtls_mpi *)n, (ssv_mbedtls_ecp_point *)Q,
             (ssv_mbedtls_ecp_restart_ctx *)rs_ctx);
}

int mbedtls_ecp_check_pubkey( const mbedtls_ecp_group *grp,
                              const mbedtls_ecp_point *pt )
{
    return ssv_mbedtls_ecp_check_pubkey((ssv_mbedtls_ecp_group *)grp,
                              (ssv_mbedtls_ecp_point *)pt );
}

int mbedtls_ecp_check_privkey(const mbedtls_ecp_group *grp,
                               const mbedtls_mpi *d )
{
    return ssv_mbedtls_ecp_check_privkey((ssv_mbedtls_ecp_group *)grp,
                               (ssv_mbedtls_mpi *)d);
}

int mbedtls_ecp_gen_privkey( const mbedtls_ecp_group *grp,
                     mbedtls_mpi *d,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    return ssv_mbedtls_ecp_gen_privkey((ssv_mbedtls_ecp_group *)grp,
                     (ssv_mbedtls_mpi *)d, f_rng, p_rng);
}

int mbedtls_ecp_gen_keypair_base( mbedtls_ecp_group *grp,
                     const mbedtls_ecp_point *G,
                     mbedtls_mpi *d, mbedtls_ecp_point *Q,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng)
{
    return ssv_mbedtls_ecp_gen_keypair_base((ssv_mbedtls_ecp_group *)grp,
                     (ssv_mbedtls_ecp_point *)G,
                     (ssv_mbedtls_mpi *)d, (ssv_mbedtls_ecp_point *)Q, f_rng, p_rng);
}

int mbedtls_ecp_gen_keypair(mbedtls_ecp_group *grp,
                             mbedtls_mpi *d, mbedtls_ecp_point *Q,
                             int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng )
{
    return ssv_mbedtls_ecp_gen_keypair((ssv_mbedtls_ecp_group *)grp,
                             (ssv_mbedtls_mpi *)d, (ssv_mbedtls_ecp_point *)Q, f_rng, p_rng);
}

int mbedtls_ecp_gen_key(mbedtls_ecp_group_id grp_id, mbedtls_ecp_keypair *key,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng)
{
    return ssv_mbedtls_ecp_gen_key((ssv_mbedtls_ecp_group_id) grp_id, (ssv_mbedtls_ecp_keypair *)key,
                         f_rng, p_rng);
}

int mbedtls_ecp_check_pub_priv( const mbedtls_ecp_keypair *pub,
                                const mbedtls_ecp_keypair *prv )
{
    return ssv_mbedtls_ecp_check_pub_priv((ssv_mbedtls_ecp_keypair *)pub,
                                (ssv_mbedtls_ecp_keypair *)prv );
}

#if defined(MBEDTLS_SELF_TEST) 
int mbedtls_ecp_self_test(int verbose)
{
    return ssv_mbedtls_ecp_self_test(verbose);
}
#endif 

//mpi wrap
void mbedtls_mpi_init(mbedtls_mpi *X)
{
    ssv_mbedtls_mpi_init((ssv_mbedtls_mpi *)X);
}

void mbedtls_mpi_free(mbedtls_mpi *X)
{
    ssv_mbedtls_mpi_free((ssv_mbedtls_mpi *)X);
}

int mbedtls_mpi_grow(mbedtls_mpi *X, size_t nblimbs)
{
    return ssv_mbedtls_mpi_grow((ssv_mbedtls_mpi *)X, nblimbs);
}

int mbedtls_mpi_shrink(mbedtls_mpi *X, size_t nblimbs)
{
    return ssv_mbedtls_mpi_shrink((ssv_mbedtls_mpi *)X, nblimbs);
}

int mbedtls_mpi_copy(mbedtls_mpi *X, const mbedtls_mpi *Y)
{
    return ssv_mbedtls_mpi_copy((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)Y);
}

void mbedtls_mpi_swap(mbedtls_mpi *X, const mbedtls_mpi *Y)
{
    ssv_mbedtls_mpi_swap((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)Y);
}

int mbedtls_mpi_safe_cond_assign(mbedtls_mpi *X, const mbedtls_mpi *Y, unsigned char assign)
{
    return ssv_mbedtls_mpi_safe_cond_assign((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)Y, assign);
}

int mbedtls_mpi_safe_cond_swap(mbedtls_mpi *X, const mbedtls_mpi *Y, unsigned char assign)
{
    return ssv_mbedtls_mpi_safe_cond_swap((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)Y, assign);
}

int mbedtls_mpi_lset(mbedtls_mpi *X, mbedtls_mpi_sint z)
{
    return ssv_mbedtls_mpi_lset((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi_sint)z);
}

int mbedtls_mpi_get_bit(const mbedtls_mpi *X, size_t pos)
{
    return ssv_mbedtls_mpi_get_bit((ssv_mbedtls_mpi *)X, pos);
}

int mbedtls_mpi_set_bit(const mbedtls_mpi *X, size_t pos, unsigned char val)
{
    return ssv_mbedtls_mpi_set_bit((ssv_mbedtls_mpi *)X, pos, val);
}

size_t mbedtls_mpi_lsb(const mbedtls_mpi *X )
{
    return ssv_mbedtls_mpi_lsb((ssv_mbedtls_mpi *)X);
}

size_t mbedtls_mpi_bitlen(const mbedtls_mpi *X )
{
    return ssv_mbedtls_mpi_bitlen((ssv_mbedtls_mpi *)X);
}

size_t mbedtls_mpi_size(const mbedtls_mpi *X )
{
    return ssv_mbedtls_mpi_size((ssv_mbedtls_mpi *)X);
}

int mbedtls_mpi_read_string( mbedtls_mpi *X, int radix, const char *s )
{
    return ssv_mbedtls_mpi_read_string((ssv_mbedtls_mpi *)X, radix, s);
}

int mbedtls_mpi_write_string(  const mbedtls_mpi *X, int radix,
                              char *buf, size_t buflen, size_t *olen)
{
    return ssv_mbedtls_mpi_write_string((ssv_mbedtls_mpi *)X, radix, buf, buflen, olen);
}

#if defined(MBEDTLS_FS_IO)
int mbedtls_mpi_read_file(mbedtls_mpi *X, int radix, FILE *fin )
{
    return ssv_mbedtls_mpi_read_file((ssv_mbedtls_mpi *)X, radix, fin);
}

int mbedtls_mpi_write_file( const char *p, const mbedtls_mpi *X, int radix, FILE *fout )
{
    return ssv_mbedtls_mpi_write_file(p, (ssv_mbedtls_mpi *)X, radix, fout);
}
#endif

int mbedtls_mpi_read_binary(mbedtls_mpi *X, const unsigned char *buf, size_t buflen )
{
    return ssv_mbedtls_mpi_read_binary((ssv_mbedtls_mpi *)X, buf, buflen);
}

int mbedtls_mpi_write_binary( const mbedtls_mpi *X,
                              unsigned char *buf, size_t buflen)
{
    return ssv_mbedtls_mpi_write_binary((ssv_mbedtls_mpi *)X, buf, buflen);
}

int mbedtls_mpi_shift_l(mbedtls_mpi *X, size_t count )
{
    return ssv_mbedtls_mpi_shift_l((ssv_mbedtls_mpi *)X, count);
}

int mbedtls_mpi_shift_r(mbedtls_mpi *X, size_t count )
{
    return ssv_mbedtls_mpi_shift_r((ssv_mbedtls_mpi *)X, count);
}

int mbedtls_mpi_cmp_abs(const mbedtls_mpi *X, const mbedtls_mpi *Y )
{
    return ssv_mbedtls_mpi_cmp_abs((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)Y);
}

int mbedtls_mpi_cmp_mpi(const mbedtls_mpi *X, const mbedtls_mpi *Y )
{
    return ssv_mbedtls_mpi_cmp_mpi((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)Y);
}

int mbedtls_mpi_cmp_int( const mbedtls_mpi *X, mbedtls_mpi_sint z )
{
    return ssv_mbedtls_mpi_cmp_int((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi_sint)z);
}

int mbedtls_mpi_add_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    return ssv_mbedtls_mpi_add_abs((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_sub_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    return ssv_mbedtls_mpi_sub_abs((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_add_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    return ssv_mbedtls_mpi_add_mpi((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_sub_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    return ssv_mbedtls_mpi_sub_mpi((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_add_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_sint b )
{
    return ssv_mbedtls_mpi_add_int((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi_sint) b);
}

int mbedtls_mpi_sub_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_sint b )
{
    return ssv_mbedtls_mpi_sub_int((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi_sint) b);
}

int mbedtls_mpi_mul_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    return ssv_mbedtls_mpi_mul_mpi((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_mul_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_sint b )
{
    return ssv_mbedtls_mpi_mul_int((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi_sint) b);
}

int mbedtls_mpi_div_mpi(mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A,
                         const mbedtls_mpi *B)
{
    return ssv_mbedtls_mpi_div_mpi((ssv_mbedtls_mpi *)Q, (ssv_mbedtls_mpi *)R, (ssv_mbedtls_mpi *)A,
                         (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_div_int(mbedtls_mpi *Q, mbedtls_mpi *R,
                         const mbedtls_mpi *A,
                         mbedtls_mpi_sint b )
{
    return ssv_mbedtls_mpi_div_int((ssv_mbedtls_mpi *)Q, (ssv_mbedtls_mpi *)R,
                         (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi_sint) b );
}

int mbedtls_mpi_mod_mpi(mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    return ssv_mbedtls_mpi_mod_mpi((ssv_mbedtls_mpi *)R, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_mod_int(mbedtls_mpi_uint *r, const mbedtls_mpi *A, mbedtls_mpi_sint b )
{
    return ssv_mbedtls_mpi_mod_int( (ssv_mbedtls_mpi_uint *)r, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi_sint)b);
}

int mbedtls_mpi_exp_mod(mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *E, const mbedtls_mpi *N,
                         mbedtls_mpi *_RR )
{
    return ssv_mbedtls_mpi_exp_mod((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A,
                         (ssv_mbedtls_mpi *)E, (ssv_mbedtls_mpi *)N, (ssv_mbedtls_mpi *)_RR);
}


int mbedtls_mpi_fill_random( mbedtls_mpi *X, size_t size,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    return ssv_mbedtls_mpi_fill_random( (ssv_mbedtls_mpi *)X, size,
                     f_rng, p_rng );
}

int mbedtls_mpi_gcd(mbedtls_mpi *G, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    return ssv_mbedtls_mpi_gcd((ssv_mbedtls_mpi *)G, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)B);
}

int mbedtls_mpi_inv_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N)
{
    return ssv_mbedtls_mpi_inv_mod((ssv_mbedtls_mpi *)X, (ssv_mbedtls_mpi *)A, (ssv_mbedtls_mpi *)N);
}

int mbedtls_mpi_is_prime(const mbedtls_mpi *X,
                  int (*f_rng)(void *, unsigned char *, size_t),
                  void *p_rng )
{
    return ssv_mbedtls_mpi_is_prime((ssv_mbedtls_mpi *)X,
                  f_rng, p_rng );
}

int mbedtls_mpi_is_prime_ext( const mbedtls_mpi *X, int rounds,
                              int (*f_rng)(void *, unsigned char *, size_t),
                              void *p_rng )
{
    return ssv_mbedtls_mpi_is_prime_ext((ssv_mbedtls_mpi *)X,  rounds,
                              f_rng, p_rng );
}

int mbedtls_mpi_gen_prime( mbedtls_mpi *X, size_t nbits, int flags,
                   int (*f_rng)(void *, unsigned char *, size_t),
                   void *p_rng)
{
    return ssv_mbedtls_mpi_gen_prime((ssv_mbedtls_mpi *)X, nbits, flags,
                   f_rng, p_rng);
}

int mbedtls_mpi_self_test(int verbose)
{
    return ssv_mbedtls_mpi_self_test(verbose);
}

//cmac wrap
int mbedtls_cipher_cmac_starts(mbedtls_cipher_context_t *ctx,
                                const unsigned char *key, size_t keybits)
{
    return ssv_mbedtls_cipher_cmac_starts((ssv_mbedtls_cipher_context_t *)ctx, key, keybits);
}

int mbedtls_cipher_cmac_update(mbedtls_cipher_context_t *ctx,
                                const unsigned char *input, size_t ilen)
{
    return ssv_mbedtls_cipher_cmac_update((ssv_mbedtls_cipher_context_t *)ctx, input, ilen);
}

int mbedtls_cipher_cmac_finish(mbedtls_cipher_context_t *ctx,
                                unsigned char *output)
{
    return ssv_mbedtls_cipher_cmac_finish((ssv_mbedtls_cipher_context_t *)ctx, output);
}

int mbedtls_cipher_cmac_reset(mbedtls_cipher_context_t *ctx)
{
    return ssv_mbedtls_cipher_cmac_reset((ssv_mbedtls_cipher_context_t *)ctx);
}

int mbedtls_cipher_cmac(const mbedtls_cipher_info_t *cipher_info,
                         const unsigned char *key, size_t keylen,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output)
{
    return ssv_mbedtls_cipher_cmac((ssv_mbedtls_cipher_info_t *)cipher_info, key, keylen,
                         input, ilen, output);
}

#if defined(MBEDTLS_AES_C)
int mbedtls_aes_cmac_prf_128(const unsigned char *key, size_t key_length,
                              const unsigned char *input, size_t in_len,
                              unsigned char *output)
{
    return ssv_mbedtls_aes_cmac_prf_128(key, key_length, input, in_len, output);
}
#endif
#if defined(MBEDTLS_SELF_TEST) && ( defined(MBEDTLS_AES_C) || defined(MBEDTLS_DES_C) )
int mbedtls_cmac_self_test(int verbose)
{
    return ssv_mbedtls_cmac_self_test(verbose);
}
#endif

//hmac wrap
int hmac_common_vector(mbedtls_md_type_t type, const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], size_t *len, u8 *mac)
{
    return ssv_hmac_common_vector((ssv_mbedtls_md_type_t)type, key, key_len, num_elem, addr, len, mac);
}

int hmac_common(mbedtls_md_type_t type, const u8 *key, size_t key_len, const u8 *data, size_t data_len, u8 *mac)
{
    return ssv_hmac_common((ssv_mbedtls_md_type_t) type, key, key_len, data, data_len, mac);
}

//aes wrap
void mbedtls_aes_init(mbedtls_aes_context *ctx )
{
    ssv_mbedtls_aes_init((ssv_mbedtls_aes_context *)ctx);
}

void mbedtls_aes_free(mbedtls_aes_context *ctx )
{
    ssv_mbedtls_aes_free((ssv_mbedtls_aes_context *)ctx);
}

#if defined(MBEDTLS_CIPHER_MODE_XTS)
void mbedtls_aes_xts_init(mbedtls_aes_xts_context *ctx )
{
    ssv_mbedtls_aes_xts_init((ssv_mbedtls_aes_xts_context *)ctx);
}

void mbedtls_aes_xts_free(mbedtls_aes_xts_context *ctx )
{
    ssv_mbedtls_aes_xts_free((ssv_mbedtls_aes_xts_context *)ctx);
}
#endif

int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits )
{
    return ssv_mbedtls_aes_setkey_enc((ssv_mbedtls_aes_context *)ctx, key, keybits);
}

int mbedtls_aes_setkey_dec(mbedtls_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits )
{
    return ssv_mbedtls_aes_setkey_dec((ssv_mbedtls_aes_context *)ctx, key, keybits);
}

#if defined(MBEDTLS_CIPHER_MODE_XTS)
int mbedtls_aes_xts_setkey_enc(mbedtls_aes_xts_context *ctx,
                                const unsigned char *key,
                                unsigned int keybits)
{
    return ssv_mbedtls_aes_xts_setkey_enc((ssv_mbedtls_aes_xts_context *)ctx, key, keybits);
}

int mbedtls_aes_xts_setkey_dec(mbedtls_aes_xts_context *ctx,
                                const unsigned char *key,
                                unsigned int keybits)
{
    return ssv_mbedtls_aes_xts_setkey_dec((ssv_mbedtls_aes_xts_context *)ctx, key, keybits);
}
#endif

int mbedtls_aes_crypt_ecb(mbedtls_aes_context *ctx,
                           int mode,
                           const unsigned char input[16],
                           unsigned char output[16] )
{
    return ssv_mbedtls_aes_crypt_ecb((ssv_mbedtls_aes_context *)ctx, mode, input, output);
}

#if defined(MBEDTLS_CIPHER_MODE_CBC)
int mbedtls_aes_crypt_cbc(mbedtls_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output )
{
    return ssv_mbedtls_aes_crypt_cbc((ssv_mbedtls_aes_context *)ctx, mode, length, iv, input, output);
}
#endif

#if defined(MBEDTLS_CIPHER_MODE_XTS)
int mbedtls_aes_crypt_xts(mbedtls_aes_xts_context *ctx,
                           int mode,
                           size_t length,
                           const unsigned char data_unit[16],
                           const unsigned char *input,
                           unsigned char *output )
{
    return ssv_mbedtls_aes_crypt_xts((ssv_mbedtls_aes_xts_context *)ctx, mode, length, data_unit, input, output);
}
#endif

#if defined(MBEDTLS_CIPHER_MODE_CFB)
int mbedtls_aes_crypt_cfb128(mbedtls_aes_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output)
{
    return ssv_mbedtls_aes_crypt_cfb128((ssv_mbedtls_aes_context *)ctx, mode, length, iv_off, iv, input, output);
}

int mbedtls_aes_crypt_cfb8(mbedtls_aes_context *ctx,
                            int mode,
                            size_t length,
                            unsigned char iv[16],
                            const unsigned char *input,
                            unsigned char *output )
{
    return ssv_mbedtls_aes_crypt_cfb8((ssv_mbedtls_aes_context *)ctx, mode, length, iv, input, output);
}
#endif

#if defined(MBEDTLS_CIPHER_MODE_OFB)
int mbedtls_aes_crypt_ofb(mbedtls_aes_context *ctx,
                           size_t length,
                           size_t *iv_off,
                           unsigned char iv[16],
                           const unsigned char *input,
                           unsigned char *output )
{
    return ssv_mbedtls_aes_crypt_ofb((ssv_mbedtls_aes_context *)ctx, length, iv_off, iv, input, output);
}
#endif

#if defined(MBEDTLS_CIPHER_MODE_CTR)
int mbedtls_aes_crypt_ctr(mbedtls_aes_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output )
{
    return ssv_mbedtls_aes_crypt_ctr((ssv_mbedtls_aes_context *)ctx, length, nc_off, nonce_counter, stream_block, input, output);
}
#endif

int mbedtls_internal_aes_encrypt(mbedtls_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] )
{
    return ssv_mbedtls_internal_aes_encrypt((ssv_mbedtls_aes_context *)ctx, input, output);
}

int mbedtls_internal_aes_decrypt(mbedtls_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16])
{
    return ssv_mbedtls_internal_aes_decrypt((ssv_mbedtls_aes_context *)ctx, input, output);
}

void mbedtls_aes_encrypt(mbedtls_aes_context *ctx,
                          const unsigned char input[16],
                          unsigned char output[16] )
{
    ssv_mbedtls_aes_encrypt((ssv_mbedtls_aes_context *)ctx, input, output);
}

void mbedtls_aes_decrypt(mbedtls_aes_context *ctx,
                          const unsigned char input[16],
                          unsigned char output[16])
{
    ssv_mbedtls_aes_decrypt((ssv_mbedtls_aes_context *)ctx, input, output);
}

int mbedtls_aes_self_test(int verbose )
{
    return ssv_mbedtls_aes_self_test(verbose);
}

//pkcs5 wrap
#if defined(MBEDTLS_ASN1_PARSE_C)
int mbedtls_pkcs5_pbes2(const mbedtls_asn1_buf *pbe_params, int mode,
                 const unsigned char *pwd,  size_t pwdlen,
                 const unsigned char *data, size_t datalen,
                 unsigned char *output )
{
    return ssv_mbedtls_pkcs5_pbes2(pbe_params, mode, pwd, pwdlen, data, datalen, output);
}
#endif
int mbedtls_pkcs5_pbkdf2_hmac(mbedtls_md_context_t *ctx, const unsigned char *password,
                       size_t plen, const unsigned char *salt, size_t slen,
                       unsigned int iteration_count,
                       uint32_t key_length, unsigned char *output)
{
    return ssv_mbedtls_pkcs5_pbkdf2_hmac((ssv_mbedtls_md_context_t *)ctx, password, plen, salt, slen, iteration_count, key_length, output);
}

int mbedtls_pkcs5_self_test(int verbose)
{
    return ssv_mbedtls_pkcs5_self_test(verbose);
}

//arc4 wrap
void mbedtls_arc4_init(mbedtls_arc4_context* ctx)
{
    ssv_mbedtls_arc4_init((ssv_mbedtls_arc4_context *)ctx);
}

void mbedtls_arc4_free(mbedtls_arc4_context* ctx)
{
    ssv_mbedtls_arc4_free((ssv_mbedtls_arc4_context *)ctx);
}

void mbedtls_arc4_setup(mbedtls_arc4_context *ctx, const unsigned char *key,
                 unsigned int keylen )
{
    ssv_mbedtls_arc4_setup((ssv_mbedtls_arc4_context *)ctx, key, keylen);
}

int mbedtls_arc4_crypt(mbedtls_arc4_context *ctx, size_t length, const unsigned char *input,
                unsigned char *output )
{
    return ssv_mbedtls_arc4_crypt((ssv_mbedtls_arc4_context *)ctx, length, input, output);
}

int mbedtls_arc4_self_test(int verbose)
{
    return ssv_mbedtls_arc4_self_test(verbose);
}

//md wrap
const int  *mbedtls_md_list()
{
    return ssv_mbedtls_md_list();
}

const mbedtls_md_info_t *mbedtls_md_info_from_string(const char *md_name)
{
    return (mbedtls_md_info_t *)ssv_mbedtls_md_info_from_string(md_name);
}

const mbedtls_md_info_t *mbedtls_md_info_from_type(ssv_mbedtls_md_type_t md_type)
{
    return (mbedtls_md_info_t *)ssv_mbedtls_md_info_from_type(md_type);
}

void mbedtls_md_init(mbedtls_md_context_t *ctx)
{
    ssv_mbedtls_md_init((ssv_mbedtls_md_context_t *)ctx);
}

void mbedtls_md_free(mbedtls_md_context_t *ctx)
{
    ssv_mbedtls_md_free((ssv_mbedtls_md_context_t *)ctx);
}

int mbedtls_md_init_ctx(mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info)
{
    return ssv_mbedtls_md_init_ctx((ssv_mbedtls_md_context_t *)ctx, (ssv_mbedtls_md_info_t *)md_info);
}

int mbedtls_md_setup(mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info, int hmac)
{
    return ssv_mbedtls_md_setup((ssv_mbedtls_md_context_t *)ctx, (ssv_mbedtls_md_info_t *)md_info, hmac);
}

int mbedtls_md_clone(mbedtls_md_context_t *dst,
                      const mbedtls_md_context_t *src)
{
    return ssv_mbedtls_md_clone((ssv_mbedtls_md_context_t *)dst, (ssv_mbedtls_md_context_t *)src);
}

int mbedtls_md_get_size( const mbedtls_md_info_t *md_info)
{
    return ssv_mbedtls_md_get_size((ssv_mbedtls_md_info_t *)md_info);
}

mbedtls_md_type_t mbedtls_md_get_type(const mbedtls_md_info_t *md_info )
{
    return (mbedtls_md_type_t)ssv_mbedtls_md_get_type((ssv_mbedtls_md_info_t *)md_info);
}

const char *mbedtls_md_get_name( const mbedtls_md_info_t *md_info )
{
    return ssv_mbedtls_md_get_name((ssv_mbedtls_md_info_t *)md_info);
}

int mbedtls_md_starts(mbedtls_md_context_t *ctx )
{
    return ssv_mbedtls_md_starts((mbedtls_md_context_t *)ctx );
}

int mbedtls_md_update(mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen )
{
    return ssv_mbedtls_md_update((ssv_mbedtls_md_context_t *)ctx,input, ilen );
}

int mbedtls_md_finish(mbedtls_md_context_t *ctx, unsigned char *output )
{
    return ssv_mbedtls_md_finish((ssv_mbedtls_md_context_t *)ctx, output );
}

int mbedtls_md(const mbedtls_md_info_t *md_info, const unsigned char *input, size_t ilen,
            unsigned char *output  )
{
    return ssv_mbedtls_md((ssv_mbedtls_md_info_t *)md_info, input, ilen, output );
}

#if defined(MBEDTLS_FS_IO)
int mbedtls_md_file(const mbedtls_md_info_t *md_info, const char *path, unsigned char *output)
{
    return ssv_mbedtls_md_file((ssv_mbedtls_md_info_t *)md_info, path, output);
}
#endif

int mbedtls_md_hmac_starts(mbedtls_md_context_t *ctx, const unsigned char *key, size_t keylen)
{
    return ssv_mbedtls_md_hmac_starts((ssv_mbedtls_md_context_t *)ctx, key, keylen);
}

int mbedtls_md_hmac_update(mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen)
{
    return ssv_mbedtls_md_hmac_update((ssv_mbedtls_md_context_t *)ctx, input, ilen);
}

int mbedtls_md_hmac_finish( mbedtls_md_context_t *ctx, unsigned char *output )
{
    return ssv_mbedtls_md_hmac_finish((ssv_mbedtls_md_context_t *)ctx, output);
}

int mbedtls_md_hmac_reset( mbedtls_md_context_t *ctx)
{
    return ssv_mbedtls_md_hmac_reset((ssv_mbedtls_md_context_t *)ctx);
}

int mbedtls_md_hmac(  const mbedtls_md_info_t *md_info,
                     const unsigned char *key, size_t keylen,
                     const unsigned char *input, size_t ilen,
                     unsigned char *output )
{
    return ssv_mbedtls_md_hmac((ssv_mbedtls_md_info_t *)md_info,
                     key, keylen, input, ilen, output);
}

int mbedtls_md_process(mbedtls_md_context_t *ctx, const unsigned char *data)
{
    return ssv_mbedtls_md_process((ssv_mbedtls_md_context_t *)ctx, data);
}

//md5 wrap
void mbedtls_md5_init(mbedtls_md5_context* ctx)
{
    ssv_mbedtls_md5_init((ssv_mbedtls_md5_context *)ctx);
}

void mbedtls_md5_free(mbedtls_md5_context* ctx)
{
    ssv_mbedtls_md5_free((ssv_mbedtls_md5_context *)ctx);
}

void mbedtls_md5_clone(mbedtls_md5_context *dst,
                        const mbedtls_md5_context *src)
{
    ssv_mbedtls_md5_clone((ssv_mbedtls_md5_context *)dst, (ssv_mbedtls_md5_context *)src);
}

int mbedtls_md5_starts_ret(mbedtls_md5_context *ctx)
{
    return ssv_mbedtls_md5_starts_ret((ssv_mbedtls_md5_context *)ctx);
}

int mbedtls_md5_update_ret(mbedtls_md5_context *ctx,
                            const unsigned char *input,
                            size_t ilen )
{
    return ssv_mbedtls_md5_update_ret((ssv_mbedtls_md5_context *)ctx, input, ilen);
}

int mbedtls_md5_finish_ret(mbedtls_md5_context *ctx,
                            unsigned char output[16] )
{
    return ssv_mbedtls_md5_finish_ret((ssv_mbedtls_md5_context *)ctx, output);
}

int mbedtls_internal_md5_process(mbedtls_md5_context *ctx,
                            const unsigned char data[64])
{
    return ssv_mbedtls_internal_md5_process((ssv_mbedtls_md5_context *)ctx, data);
}
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_md5_starts(mbedtls_md5_context* ctx)
{
    ssv_mbedtls_md5_starts((ssv_mbedtls_md5_context *)ctx);
}

void mbedtls_md5_update(mbedtls_md5_context *ctx,
                         const unsigned char *input,
                         size_t ilen )
{
    ssv_mbedtls_md5_update((ssv_mbedtls_md5_context *)ctx, input, ilen);
}

void mbedtls_md5_finish(mbedtls_md5_context *ctx,
                         unsigned char output[16])
{
    ssv_mbedtls_md5_finish((ssv_mbedtls_md5_context *)ctx, output);
}

void mbedtls_md5_process(mbedtls_md5_context *ctx,
                         const unsigned char data[64] )
{
    ssv_mbedtls_md5_process((ssv_mbedtls_md5_context *)ctx, data);
}
#endif
int mbedtls_md5_ret(const unsigned char *input,
                     size_t ilen,
                     unsigned char output[16] )
{
    return ssv_mbedtls_md5_ret(input, ilen, output);
}
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_md5(const unsigned char *input,
                  size_t ilen,
                  unsigned char output[16] )
{
    ssv_mbedtls_md5(input, ilen, output);
}
#endif
int mbedtls_md5_self_test(int verbose)
{
    return ssv_mbedtls_md5_self_test(verbose);
}

//sha1 wrap
void mbedtls_sha1_init(mbedtls_sha1_context* ctx)
{
    ssv_mbedtls_sha1_init((ssv_mbedtls_sha1_context *)ctx);
}

void mbedtls_sha1_free(mbedtls_sha1_context* ctx)
{
    ssv_mbedtls_sha1_free((ssv_mbedtls_sha1_context *)ctx);
}

void mbedtls_sha1_clone(mbedtls_sha1_context *dst,
                         const mbedtls_sha1_context *src )
{
    ssv_mbedtls_sha1_clone((ssv_mbedtls_sha1_context *)dst, (ssv_mbedtls_sha1_context *)src);
}

int mbedtls_sha1_starts_ret(mbedtls_sha1_context* ctx)
{
    return ssv_mbedtls_sha1_starts_ret((ssv_mbedtls_sha1_context *)ctx);
}

int mbedtls_sha1_update_ret(mbedtls_sha1_context *ctx,
                             const unsigned char *input,
                             size_t ilen)
{
    return ssv_mbedtls_sha1_update_ret((ssv_mbedtls_sha1_context *)ctx, input, ilen);
}

int mbedtls_sha1_finish_ret(mbedtls_sha1_context *ctx,
                             unsigned char output[20] )
{
    return ssv_mbedtls_sha1_finish_ret((ssv_mbedtls_sha1_context *)ctx, output);
}

int mbedtls_internal_sha1_process(mbedtls_sha1_context *ctx,
                             const unsigned char data[64] )
{
    return ssv_mbedtls_internal_sha1_process((ssv_mbedtls_sha1_context *)ctx, data);
}
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha1_starts(mbedtls_sha1_context *ctx)
{
    ssv_mbedtls_sha1_starts((ssv_mbedtls_sha1_context *)ctx);
}

void mbedtls_sha1_update(mbedtls_sha1_context *ctx,
                          const unsigned char *input,
                          size_t ilen )
{
    ssv_mbedtls_sha1_update((ssv_mbedtls_sha1_context *)ctx, input, ilen);
}

void mbedtls_sha1_finish(mbedtls_sha1_context *ctx,
                          unsigned char output[20])
{
    ssv_mbedtls_sha1_finish((ssv_mbedtls_sha1_context *)ctx, output);
}

void mbedtls_sha1_process(mbedtls_sha1_context *ctx,
                           const unsigned char data[64] )
{
    ssv_mbedtls_sha1_process((ssv_mbedtls_sha1_context *)ctx, data);
}
#endif
int mbedtls_sha1_ret(const unsigned char *input,
                      size_t ilen,
                      unsigned char output[20])
{
    return ssv_mbedtls_sha1_ret(input, ilen, output);
}
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha1(const unsigned char *input,
                   size_t ilen,
                   unsigned char output[20] )
{
    ssv_mbedtls_sha1(input, ilen, output);
}
#endif
int mbedtls_sha1_self_test(int verbose )
{
    return ssv_mbedtls_sha1_self_test(verbose);
}

//sha256 wrap
void mbedtls_sha256_init(mbedtls_sha256_context* ctx)
{
    ssv_mbedtls_sha256_init((ssv_mbedtls_sha256_context *)ctx);
}

void mbedtls_sha256_free(mbedtls_sha256_context* ctx)
{
    ssv_mbedtls_sha256_free((ssv_mbedtls_sha256_context *)ctx);
}

void mbedtls_sha256_clone(mbedtls_sha256_context *dst,
                           const mbedtls_sha256_context *src)
{
    ssv_mbedtls_sha256_clone((ssv_mbedtls_sha256_context *)dst, (ssv_mbedtls_sha256_context *)src);
}

int mbedtls_sha256_starts_ret(mbedtls_sha256_context *ctx, int is224)
{
    return ssv_mbedtls_sha256_starts_ret((ssv_mbedtls_sha256_context *)ctx, is224);
}

int mbedtls_sha256_update_ret(mbedtls_sha256_context *ctx,
                               const unsigned char *input,
                               size_t ilen )
{
    return ssv_mbedtls_sha256_update_ret((ssv_mbedtls_sha256_context *)ctx, input, ilen);
}

int mbedtls_sha256_finish_ret(mbedtls_sha256_context *ctx,
                               unsigned char output[32] )
{
    return ssv_mbedtls_sha256_finish_ret((ssv_mbedtls_sha256_context *)ctx, output);
}

int mbedtls_internal_sha256_process(mbedtls_sha256_context *ctx,
                                const unsigned char data[64])
{
    return ssv_mbedtls_internal_sha256_process((ssv_mbedtls_sha256_context *)ctx, data);
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256_starts(mbedtls_sha256_context *ctx,
                            int is224 )
{
    ssv_mbedtls_sha256_starts((ssv_mbedtls_sha256_context *)ctx, is224);
}

void mbedtls_sha256_update(mbedtls_sha256_context *ctx,
                            const unsigned char *input,
                            size_t ilen )
{
    ssv_mbedtls_sha256_update((ssv_mbedtls_sha256_context *)ctx, input, ilen);
}

void mbedtls_sha256_finish(mbedtls_sha256_context *ctx,
                            unsigned char output[32] )
{
    ssv_mbedtls_sha256_finish((ssv_mbedtls_sha256_context *)ctx, output);
}

void mbedtls_sha256_process(mbedtls_sha256_context *ctx,
                             const unsigned char data[64] )
{
    ssv_mbedtls_sha256_process((ssv_mbedtls_sha256_context *)ctx, data);
}
#endif
int mbedtls_sha256_ret(const unsigned char *input,
                        size_t ilen,
                        unsigned char output[32],
                        int is224 )
{
    return ssv_mbedtls_sha256_ret(input, ilen, output, is224);
}
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256(const unsigned char *input,
                     size_t ilen,
                     unsigned char output[32],
                     int is224 )
{
    ssv_mbedtls_sha256(input, ilen, output, is224);
}
#endif
int mbedtls_sha256_self_test(int verbose )
{
    return ssv_mbedtls_sha256_self_test(verbose);
}

