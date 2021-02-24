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

#include "iperf_Timestamp.h"

#include "soc_types.h" //FIXME!
#include "assert.h"

const unsigned long ticks_1sec = 1000/os_tick2ms(1);
void Timestamp_setnow_(struct timeval *tv)
{
    u32 systick;
    systick = OS_GetSysTick();
    tv->tv_sec = systick/ticks_1sec;
    tv->tv_usec = os_tick2ms(systick%ticks_1sec)*1000;
}

void Timestamp_setnow( Timestamp *inst ) {
    Timestamp_setnow_(&inst->mTime);
}

void Timestamp_set(Timestamp *inst, long sec, long usec ) {
    assert( sec  >= 0 );
    assert( usec >= 0  &&  usec < kMillion );

    inst->mTime.tv_sec  = sec;
    inst->mTime.tv_usec = usec;      
}

long Timestamp_getSecs( Timestamp *inst ) {
    return inst->mTime.tv_sec;
}

long Timestamp_subUsec( Timestamp *inst, struct timeval right ) {
    return(inst->mTime.tv_sec  - right.tv_sec) * kMillion +
    (inst->mTime.tv_usec - right.tv_usec);
}

/* -------------------------------------------------------------------
 * add the right timestamp to my timestamp.
 * ------------------------------------------------------------------- */
void Timestamp_add( Timestamp *inst, Timestamp right ) {
    inst->mTime.tv_sec  += right.mTime.tv_sec;
    inst->mTime.tv_usec += right.mTime.tv_usec;

    // watch for under- and overflow
    if ( inst->mTime.tv_usec < 0 ) {
        inst->mTime.tv_usec += kMillion;
        inst->mTime.tv_sec--;
    }
    if ( inst->mTime.tv_usec >= kMillion ) {
        inst->mTime.tv_usec -= kMillion;
        inst->mTime.tv_sec++;
    }

    assert( inst->mTime.tv_usec >= 0  &&
            inst->mTime.tv_usec <  kMillion );
}

/* -------------------------------------------------------------------
 * return true if my timestamp is before the right timestamp.
 * ------------------------------------------------------------------- */
bool Timestamp_before_( Timestamp *inst, struct timeval right ) {
    return inst->mTime.tv_sec < right.tv_sec  ||
    (inst->mTime.tv_sec == right.tv_sec &&
     inst->mTime.tv_usec < right.tv_usec);
}

bool Timestamp_before( Timestamp *inst, Timestamp right ) { 
    return Timestamp_before_(inst, right.mTime); 
}



void TimeDifference( struct timeval left, struct timeval right, struct timeval *result )
{   
    result->tv_sec = left.tv_sec  - right.tv_sec;
    if(left.tv_usec >= right.tv_usec)
        result->tv_usec = (left.tv_usec - right.tv_usec);
    else
    {
        result->tv_usec = (rMillion + left.tv_usec - right.tv_usec);
        result->tv_sec --;
    }
}

void TimeAdd( struct timeval *left, struct timeval right)
{    
    do {        
        left->tv_usec += right.tv_usec;
        if ( left->tv_usec > rMillion ) {
            left->tv_usec -= rMillion;
            left->tv_sec++;
        }
        left->tv_sec += right.tv_sec;
    } while ( 0 );
}

int TimeDifferenceUsec( struct timeval left, struct timeval right )
{   
    int usec = 0;
    usec = ((left.tv_sec - right.tv_sec)*rMillion) + (left.tv_usec - right.tv_usec);
    return usec;
}

int TimeDifferenceSec( struct timeval left, struct timeval right )
{   
    return (TimeDifferenceUsec(left, right)/rMillion);
}
