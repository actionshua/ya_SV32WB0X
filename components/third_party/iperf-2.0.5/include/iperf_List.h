
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
 * List.h
 * by Kevin Gibbs <kgibbs@ncsa.uiuc.edu> 
 * ------------------------------------------------------------------- 
 */

#ifndef IPERF_LIST_H
#define IPERF_LIST_H

#include "iperf_headers.h"
#include "iperf_Settings.h"
#include "iperf_Reporter.h"
#include "iperf_Mutex.h"

/*
 * List handling utilities to replace STD vector
 */

struct Iperf_ListEntry;

/*
 * A List entry that consists of a sockaddr
 * a pointer to the Audience that sockaddr is
 * associated with and a pointer to the next
 * entry
 */
struct Iperf_ListEntry {
    iperf_sockaddr data;
    MultiHeader *holder;
    thread_Settings *server;
    struct Iperf_ListEntry *next;
};

extern Mutex clients_mutex;
extern struct Iperf_ListEntry *clients;

/*
 * Functions to modify or search the List
 */
void Iperf_pushback ( struct Iperf_ListEntry *add, struct Iperf_ListEntry **root );

void Iperf_delete ( iperf_sockaddr *del, struct Iperf_ListEntry **root );

void Iperf_destroy ( struct Iperf_ListEntry **root );

struct Iperf_ListEntry* Iperf_present ( iperf_sockaddr *find, struct Iperf_ListEntry *root );

struct Iperf_ListEntry* Iperf_hostpresent ( iperf_sockaddr *find, struct Iperf_ListEntry *root );

#endif
