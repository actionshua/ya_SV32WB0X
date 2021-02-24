/*
 * crypto_trng.h
 *
 *  Created on: Apr 25, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_TRNG_H_
#define INCLUDE_CRYPTO_CRYPTO_TRNG_H_

void crypto_trng_clock_enable(void);
void crypto_trng_clock_disable(void);
int crypto_trng_generator(unsigned int *seed);

#endif /* INCLUDE_CRYPTO_CRYPTO_TRNG_H_ */
