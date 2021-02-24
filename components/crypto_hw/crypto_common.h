/*
 * crypto_common.h
 *
 *  Created on: May 21, 2019
 *      Author: Matt
 */


#ifndef INCLUDE_CRYPTO_CRYPTO_COMMON_H_
#define INCLUDE_CRYPTO_CRYPTO_COMMON_H_

#include "osal.h"

#define CRYPTO_C_CODE

void crypto_init(void);
void crypto_deinit(void);
void clear_trap_reason(void);
void crypto_lock(void);
void crypto_unlock(void); 
int check_and_enable_cp1(void);

#endif /* INCLUDE_CRYPTO_CRYPTO_COMMON_H_ */
