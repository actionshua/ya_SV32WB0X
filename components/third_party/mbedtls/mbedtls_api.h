
#ifndef MBEDTLS_API_H
#define MBEDTLS_API_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLSTEST)
int main_test_suite_aes_cbc(int argc, const char *argv[]);
int main_test_suite_aes_ecb(int argc, const char *argv[]);
int main_test_suite_aes_cfb(int argc, const char *argv[]);
int main_test_suite_aes_rest(int argc, const char *argv[]);
int main_test_suite_ccm(int argc, const char *argv[]);
int main_test_suite_arc4(int argc, const char *argv[]);
int main_test_suite_asn1write(int argc, const char *argv[]);
int main_test_suite_base64(int argc, const char *argv[]);
int main_test_suite_blowfish(int argc, const char *argv[]);
int main_test_suite_camellia(int argc, const char *argv[]);
int main_test_suite_chipher_aes(int argc, const char *argv[]);
int main_test_suite_chipher_arc4(int argc, const char *argv[]);
int main_test_suite_chipher_blowfish(int argc, const char *argv[]);
int main_test_suite_chipher_camellia(int argc, const char *argv[]);
int main_test_suite_chipher_ccm(int argc, const char *argv[]);
int main_test_suite_chipher_des(int argc, const char *argv[]);
int main_test_suite_chipher_gcm(int argc, const char *argv[]);
int main_test_suite_chipher_null(int argc, const char *argv[]);
int main_test_suite_chipher_padding(int argc, const char *argv[]);
int main_test_suite_cmac(int argc, const char *argv[]);
int main_test_suite_ctr_drbg(int argc, const char *argv[]);
int main_test_suite_debug(int argc, const char *argv[]);
int main_test_suite_des(int argc, const char *argv[]);
int main_test_suite_dhm(int argc, const char *argv[]);
int main_test_suite_ecdh(int argc, const char *argv[]);
int main_test_suite_ecdsa(int argc, const char *argv[]);
int main_test_suite_ecjpake(int argc, const char *argv[]);
int main_test_suite_ecp(int argc, const char *argv[]);
int main_test_suite_entropy(int argc, const char *argv[]);
int main_test_suite_error(int argc, const char *argv[]);
int main_test_suite_gcm_aes128_de(int argc, const char *argv[]);
int main_test_suite_gcm_aes128_en(int argc, const char *argv[]);
int main_test_suite_gcm_aes192_de(int argc, const char *argv[]);
int main_test_suite_gcm_aes192_en(int argc, const char *argv[]);
int main_test_suite_gcm_aes256_de(int argc, const char *argv[]);
int main_test_suite_gcm_aes256_en(int argc, const char *argv[]);
int main_test_suite_gcm_camellia(int argc, const char *argv[]);
int main_test_suite_hmac_drbg_nopr(int argc, const char *argv[]);
int main_test_suite_hmac_drbg_misc(int argc, const char *argv[]);
int main_test_suite_hmac_drbg_no_ressed(int argc, const char *argv[]);
int main_test_suite_hmac_drbg_pr(int argc, const char *argv[]);
int main_test_suite_md(int argc, const char *argv[]);
int main_test_suite_mdx(int argc, const char *argv[]);
int main_test_suite_mem_buf_alloc(int argc, const char *argv[]);
int main_test_suite_mpi(int argc, const char *argv[]);
int main_test_suite_pem(int argc, const char *argv[]);
int main_test_suite_pk(int argc, const char *argv[]);
int main_test_suite_pkcs1_v15(int argc, const char *argv[]);
int main_test_suite_pkcs1_v21(int argc, const char *argv[]);
int main_test_suite_pkcs5(int argc, const char *argv[]);
int main_test_suite_pkparse(int argc, const char *argv[]);
int main_test_suite_pkwrite(int argc, const char *argv[]);
int main_test_suite_rsa(int argc, const char *argv[]);
int main_test_suite_shax(int argc, const char *argv[]);
int main_test_suite_ssl(int argc, const char *argv[]);
int main_test_suite_timing(int argc, const char *argv[]);
int main_test_suite_version(int argc, const char *argv[]);
int main_test_suite_X509parse(int argc, const char *argv[]);
int main_test_suite_X509write(int argc, const char *argv[]);
int main_test_suite_xtea(int argc, const char *argv[]);
int test_suite_aes_ofb(int argc, const char *argv[]);
int test_suite_aes_xts(int argc, const char *argv[]);
int test_suite_aria(int argc, const char *argv[]);
int test_suite_chacha20(int argc, const char *argv[]);
int test_suite_chachapoly(int argc, const char *argv[]);
int test_suite_cipher_chacha20(int argc, const char *argv[]);
int test_suite_cipher_chachapoly(int argc, const char *argv[]);
int test_suite_cipher_misc(int argc, const char *argv[]);
int test_suite_gcm_misc(int argc, const char *argv[]);
int test_suite_hkdf(int argc, const char *argv[]);
int test_suite_nist_kw(int argc, const char *argv[]);
int test_suite_poly1305(int argc, const char *argv[]);    
int benchmark(int argc, const char *argv[]);    
#endif

void ssl_mbed_test();
void ssl_mbed_thoughtput_test(char *ip, u16 port, u8 sec);
#ifdef __cplusplus
}
#endif

#endif
