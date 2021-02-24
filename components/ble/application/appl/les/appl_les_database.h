#ifndef _APPL_LES_DATABASE_H_
#define _APPL_LES_DATABASE_H_



#include <stdint.h>
#include "les_if/api/inc/les_api.h"
#include "appl/common/appl_error.h"



/// please be noted that the database entry should be smaller than 255.
#define APPL_LES_DATABASE_SECURITY_ENTRY_MAX                3
#define APPL_LES_DATABASE_CONNECTION_ENTRY_MAX              1

#define APPL_LES_DATABASE_ENTRY_HEADER_SIZE                 (sizeof(appl_les_database_entry_header_st))
#define APPL_LES_DATABASE_SECURITY_ENTRY_SIZE               (sizeof(appl_les_database_security_entry_st))
#define APPL_LES_DATABASE_CONNECTION_ENTRY_SIZE             (sizeof(appl_les_database_connection_entry_st))



typedef enum
{
    APPL_LES_DATABASE_TYPE_SECURITY = 0,
    APPL_LES_DATABASE_TYPE_CONNECTION,
    APPL_LES_DATABASE_TYPE_MAX,

} APPL_LES_DATABASE_TYPE;



typedef enum
{
    APPL_LES_DATABASE_ENTRY_EMPTY = 0,
    APPL_LES_DATABASE_ENTRY_USED,

} APPL_LES_DATABASE_ENTRY;



typedef struct
{
    uint8_t mitm;
    uint8_t enc_key_size;
    uint8_t init_key_dist;
    uint8_t rsp_key_dist;
    uint8_t addr_type;
    uint32_t sign_counter;
    smp_encryption_ltk_info_st encryption_ltk_info;
    smp_encryption_ediv_rand64_info_st encryption_ediv_rand64_info;
    smp_signing_csrk_info_st signing_csrk_info;
    smp_identity_irk_info_st identity_irk_info;

} appl_les_database_security_entry_st;



typedef struct
{
    GAP_ROLE local_role;
    bd_addr_st remote_addr;
    uint16_t conn_interval;

} appl_les_database_connection_entry_st;



typedef struct
{
    uint8_t nvram_handler;

} appl_les_database_control_st;



typedef struct
{
    uint64_t valid : 16;
    uint64_t key : 48;

} appl_les_database_entry_header_st;



void appl_les_database_create(void);
APPL_RESULT appl_les_database_find(APPL_LES_DATABASE_TYPE type, uint64_t key, uint8_t **dst);
APPL_RESULT appl_les_database_query(APPL_LES_DATABASE_TYPE type, uint64_t key, uint8_t *dst);
APPL_RESULT appl_les_database_update(APPL_LES_DATABASE_TYPE type, uint64_t key, uint8_t *src);
APPL_RESULT appl_les_database_delete(APPL_LES_DATABASE_TYPE type, uint64_t key);



#endif  /// end of _APPL_LES_DATABASE_H_
