/*
 * crypto_gf128mul.h
 *
 *  Created on: Apr 26, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_GF128MUL_H_
#define INCLUDE_CRYPTO_CRYPTO_GF128MUL_H_
#include <stdio.h>
#include <stdint.h>

/*__attribute__((noinline)) */
int gf128mul(unsigned char c[16],
				const unsigned char a[16],	const unsigned char b[16]);


#endif /* INCLUDE_CRYPTO_CRYPTO_GF128MUL_H_ */
