/*
 * Simultaneous authentication of equals
 * Copyright (c) 2012-2013, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef SAE_H
#define SAE_H

#include <third_party/mbedtls/include/mbedtls/ecp.h>

#define SAE_KCK_LEN 32
#define SAE_PMK_LEN 32
#define SAE_PMKID_LEN 16
#define SAE_KEYSEED_KEY_LEN 32
#define SAE_MAX_PRIME_LEN 512
#define SAE_MAX_ECC_PRIME_LEN 66
#define SAE_COMMIT_MAX_LEN (2 + 3 * SAE_MAX_PRIME_LEN)
#define SAE_CONFIRM_MAX_LEN (2 + SAE_MAX_PRIME_LEN)

/* Special value returned by sae_parse_commit() */
#define SAE_SILENTLY_DISCARD 65535

enum sae_state {
	SAE_NOTHING, 
    SAE_COMMITTED,
    SAE_CONFIRMED,
    SAE_ACCEPTED
};

struct sae_temporary_data {
	u8 pmk[SAE_PMK_LEN];
	u8 pmkid[SAE_PMKID_LEN];
	u8 kck[SAE_KCK_LEN];
	ssv_mbedtls_ecp_point own_commit_element_ecc;
	ssv_mbedtls_ecp_point peer_commit_element_ecc;
	ssv_mbedtls_ecp_point pwe_ecc;
	ssv_mbedtls_mpi sae_rand;
	ssv_mbedtls_mpi own_commit_scalar;
	ssv_mbedtls_mpi peer_commit_scalar;
	ssv_mbedtls_ecp_group grp;
};

struct sae_data {
	enum sae_state state;
	u16 send_confirm;
	u16 rc; /* protocol instance variable: Rc (received send-confirm) */
	unsigned int sync; /* protocol instance variable: Sync */
	u16 group;
    struct sae_temporary_data *tmp;
};


s16 sae_parse_commit(struct sae_data *sae, const u8 *data, size_t len);
int sae_prepare_commit(const u8 *addr1, const u8 *addr2,
		       const u8 *password, size_t password_len, struct sae_data *sae);
int sae_gen_commit_pkt(struct sae_data *sae, u8 *pkt);
int sae_process_commit(struct sae_data *sae);
int sae_check_confirm(struct sae_data *sae, const u8 *data, size_t len);
void sae_write_confirm(struct sae_data *sae, u8 *buf);
int sae_set_group(struct sae_data *ctx);
int sae_clear_group(struct sae_data *ctx);
int sae_init(struct sae_data *ctx);
int sae_deinit(struct sae_data *ctx);



#endif /* SAE_H */
