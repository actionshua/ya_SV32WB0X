/*--------------------------------------------------------------- 
 * Copyright (c) 1999,2000,2001,2002,2003                       
 * The Board of Trustees of the University of Illinois            
 * All Rights Reserved.                                           
 *--------------------------------------------------------------- 
 * Permission is hereby granted, free of charge, to any person    
 * obtaining a copy of this software (Iperf) and associated       
 * documentation files (the "Software"), to deal in the Software  
 * without restriction, including without limitation the          
 * rights to use, copy, modify, merge, publish, distribute,        
 * sublicense, and/or sell copies of the Software, and to permit     
 * persons to whom the Software is furnished to do
 * so, subject to the following conditions: 
 *
 *     
 * Redistributions of source code must retain the above 
 * copyright notice, this list of conditions and 
 * the following disclaimers. 
 *
 *     
 * Redistributions in binary form must reproduce the above 
 * copyright notice, this list of conditions and the following 
 * disclaimers in the documentation and/or other materials 
 * provided with the distribution. 
 * 
 *     
 * Neither the names of the University of Illinois, NCSA, 
 * nor the names of its contributors may be used to endorse 
 * or promote products derived from this Software without
 * specific prior written permission. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE CONTIBUTORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * ________________________________________________________________
 * National Laboratory for Applied Network Research 
 * National Center for Supercomputing Applications 
 * University of Illinois at Urbana-Champaign 
 * http://www.ncsa.uiuc.edu
 * ________________________________________________________________ 
 *
 * Timestamp.h
 * by Mark Gates <mgates@nlanr.net>
 * -------------------------------------------------------------------
 * A generic interface to a timestamp.
 * This implementation uses the unix gettimeofday().
 * -------------------------------------------------------------------
 * headers
 * uses
 *   <sys/types.h>
 *   <sys/time.h>
 *   <unistd.h>
 * ------------------------------------------------------------------- */

#ifndef IPERF_TIMESTAMP_H
#define IPERF_TIMESTAMP_H

#include "iperf_headers.h"
#include "osal.h"

/* ------------------------------------------------------------------- */
typedef struct Timestamp_t {
    enum _kMillion_def{
        kMillion = 1000000
    } kMillion_def;

    struct timeval mTime;

} Timestamp; // end class Timestamp


/* -------------------------------------------------------------------
 * Set timestamp to current time.
 * ------------------------------------------------------------------- */
void Timestamp_setnow_(struct timeval *tv);
void Timestamp_setnow( Timestamp *inst );

#define iperf_gettimeofday(a, b) Timestamp_setnow_(a)


/* -------------------------------------------------------------------
 * Set timestamp to the given seconds/microseconds
 * ------------------------------------------------------------------- */
void Timestamp_set(Timestamp *inst, long sec, long usec );

/* -------------------------------------------------------------------
 * return seconds portion of timestamp
 * ------------------------------------------------------------------- */
long Timestamp_getSecs( Timestamp *inst );

/* -------------------------------------------------------------------
 * subtract the right timestamp from my timestamp.
 * return the difference in microseconds.
 * ------------------------------------------------------------------- */
long Timestamp_subUsec( Timestamp *inst, struct timeval right );


/* -------------------------------------------------------------------
 * add the right timestamp to my timestamp.
 * ------------------------------------------------------------------- */
void Timestamp_add( Timestamp *inst, Timestamp right );


/* -------------------------------------------------------------------
 * return true if my timestamp is before the right timestamp.
 * ------------------------------------------------------------------- */
bool Timestamp_before_( Timestamp *inst, struct timeval right );
bool Timestamp_before( Timestamp *inst, Timestamp right );

void TimeDifference( struct timeval left, struct timeval right, struct timeval *result );
void TimeAdd( struct timeval *left, struct timeval right);
int TimeDifferenceUsec( struct timeval left, struct timeval right);
int TimeDifferenceSec( struct timeval left, struct timeval right);
//void TimeCopy( struct timeval *dst, struct timeval *src);
//long Time_getSecs( struct timeval *inst ) { return inst->tv_sec; };
//long Time_getUSecs( struct timeval *inst ) { return inst->tv_usec; };

#define rMillion 1000000

#endif // TIMESTAMP_H
