#ifndef _LE_KEYGEN_H_
#define _LE_KEYGEN_H_



#include "stdint.h"
#include "les_if/api/inc/les_api.h"
#include "appl/common/appl_error.h"



typedef struct
{
    uint8_t     key_init;
    uint8_t     er[SMP_KEY_SIZE_16BYTE];
    uint8_t     ir[SMP_KEY_SIZE_16BYTE];

} le_keygen_ctrlblock_st;



void le_keygen_init(uint8_t *er, uint8_t *ir);
void le_keygen_deinit(void);
uint8_t le_keygen_is_init(void);
uint8_t le_keygen_gen_er_ir(uint8_t *seed, uint8_t *er, uint8_t *ir);
uint8_t le_keygen_gen_div(uint8_t authen, uint8_t key_size, uint8_t *div);
uint8_t le_keygen_gen_ediv_rand(uint8_t *div, uint8_t *ediv, uint8_t *rand_num);
uint8_t le_keygen_gen_ltk(uint8_t *div, uint8_t *ltk);
uint8_t le_keygen_gen_irk(uint8_t *irk);
uint8_t le_keygen_gen_csrk(uint8_t *div, uint8_t *csrk);
uint8_t le_keygen_recover_ltk(uint8_t *ediv, uint8_t *rand64, uint8_t *ltk, uint8_t *authen, uint8_t *key_size);
uint8_t le_keygen_recover_div(uint8_t *ediv, uint8_t *rand64, uint8_t *div);
uint8_t le_keygen_recover_ltk_from_div(uint8_t *div, uint8_t *ltk, uint8_t *authen, uint8_t *key_size);



#endif  /// end of _LE_KEYGEN_H_
