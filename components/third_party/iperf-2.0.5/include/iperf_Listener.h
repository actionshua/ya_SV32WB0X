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
 * Listener.h
 * by Mark Gates <mgates@nlanr.net>
 * -------------------------------------------------------------------
 * Listener sets up a socket listening on the server host. For each
 * connected socket that accept() returns, this creates a Server
 * socket and spawns a thread for it.
 * ------------------------------------------------------------------- */

#ifndef IPERF_LISTENER_H
#define IPERF_LISTENER_H

#include "iperf_Thread.h"
#include "iperf_Settings.h"

//class Listener;

typedef struct Listener_t {
    int mClients;
    char* mBuf;
    thread_Settings *mSettings;
    thread_Settings *server;

} Listener; // end class Listener

void Listener_init( Listener *inst,thread_Settings *inSettings );
void Listener_deinit( Listener *inst );

// accepts connections and starts Servers
void Listener_Run( Listener *inst );

// Starts the Servers as a daemon 
void Listener_runAsDaemon( const char *, int );

void Listener_Listen(Listener *inst);

void Listener_McastJoin(Listener *inst);

void Listener_McastSetTTL(Listener *inst, int val );

void Listener_Accept( Listener *inst, thread_Settings *server );

void Listener_UDPSingleServer (Listener *inst);
#endif // LISTENER_H
