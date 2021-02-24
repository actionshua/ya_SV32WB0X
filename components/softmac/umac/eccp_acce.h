/*
 * Simultaneous authentication of equals
 * Copyright (c) 2012-2013, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef ECCP_ACCE_H
#define ECCP_ACCE_H

typedef struct _eccp_commit_param
{
    u8 *pwe_x; 
    u8 *pwe_y;
    u8 *rand; 
    u8 *mask; 
    u8 *commit_x; 
    u8 *commit_y;
}eccp_commit_param;

typedef struct _eccp_k_param
{
    u8 *pwe_x; 
    u8 *pwe_y;
    u8 *rand; 
    u8 *peer_scalar; 
    u8 *peer_x; 
    u8 *peer_y;
    u8 *k;
}eccp_k_param;

enum eccp_state
{
    ECCP_IDLE = 0,
    ECCP_READY,
    ECCP_FETCH,
    ECCP_DECODE,
    ECCP_HALT,
};

void eccp_init();
void eccp_deinit();
void eccp_gen_commit(eccp_commit_param *data);
void eccp_gen_k(eccp_k_param *data);


#endif /* ECCP_ACCE_H */
