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
 * Server.cpp
 * by Mark Gates <mgates@nlanr.net>
 *     Ajay Tirumala (tirumala@ncsa.uiuc.edu>.
 * -------------------------------------------------------------------
 * A server thread is initiated for each connection accept() returns.
 * Handles sending and receiving data, and then closes socket.
 * Changes to this version : The server can be run as a daemon
 * ------------------------------------------------------------------- */

#define HEADERS()

#include "iperf_headers.h"
#include "iperf_Server.h"
#include "iperf_List.h"
//#include "Extractor.h"
#include "iperf_Reporter.h"
#include "iperf_Locale.h"
#include "iperf_PerfSocket.h"

/* -------------------------------------------------------------------
 * Stores connected socket and socket info.
 * ------------------------------------------------------------------- */

void Server_init( Server *inst, thread_Settings *inSettings ) {
    inst->mSettings = inSettings;
    inst->mBuf = NULL;

    // initialize buffer
    inst->mBuf = (char *)iperf_malloc( inst->mSettings->mBufLen );
    FAIL_errno( inst->mBuf == NULL, "No memory for buffer\n", inst->mSettings );
}

/* -------------------------------------------------------------------
 * Destructor close socket.
 * ------------------------------------------------------------------- */

void Server_deinit(Server *inst) {
    if ( inst->mSettings->mSock != INVALID_SOCKET ) {
        int rc = close( inst->mSettings->mSock );
        WARN_errno( rc == SOCKET_ERROR, "close" );
        inst->mSettings->mSock = INVALID_SOCKET;
    }
    DELETE_ARRAY( inst->mBuf );
}

void Server_Sig_Int( int inSigno ) {
}

/* ------------------------------------------------------------------- 
 * Receive data from the (connected) socket.
 * Sends termination flag several times at the end. 
 * Does not close the socket. 
 * ------------------------------------------------------------------- */ 
void Server_Run( Server *inst ) {
    long currLen; 
    max_size_t totLen = 0;
    struct UDP_datagram* mBuf_UDP  = (struct UDP_datagram*) inst->mBuf; 

    ReportStruct *reportstruct = NULL;

    reportstruct = (ReportStruct *)iperf_malloc(sizeof(ReportStruct));
    if ( reportstruct != NULL ) {
        reportstruct->packetID = 0;
        inst->mSettings->reporthdr = InitReport( inst->mSettings );
        do {
            // perform read 
            fd_set fd;
            struct timeval tv;
            int ret = 0;
            do {
                tv.tv_sec = 1;
                tv.tv_usec = 0;
                FD_SET(inst->mSettings->mSock, &fd);
                ret = select((inst->mSettings->mSock+1), &fd, NULL, NULL, &tv);
                if ((FD_ISSET(inst->mSettings->mSock, &fd)) || ((sInterupted == 1) && (ret == 0)))
                    break;                               
            }
            while(1);
            
            if(sInterupted == 1)
                break;
            
            currLen = recv( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen, 0 ); 
        
            if ( isUDP( inst->mSettings ) ) {
                // read the datagram ID and sentTime out of the buffer 
                reportstruct->packetID = ntohl( mBuf_UDP->id ); 
                reportstruct->sentTime.tv_sec = ntohl( mBuf_UDP->tv_sec  );
                reportstruct->sentTime.tv_usec = ntohl( mBuf_UDP->tv_usec ); 
                reportstruct->packetLen = currLen;
                iperf_gettimeofday( &(reportstruct->packetTime), NULL );
            } else {
                totLen += currLen;
            }
        
            // terminate when datagram begins with negative index 
            // the datagram ID should be correct, just negated 
            if ( reportstruct->packetID < 0 ) {
                reportstruct->packetID = -reportstruct->packetID;
                currLen = -1; 
            }

            if ( isUDP (inst->mSettings)) {
                ReportPacket( inst->mSettings->reporthdr, reportstruct );
            } else if ( !isUDP (inst->mSettings) && inst->mSettings->mInterval > 0) {
                reportstruct->packetLen = currLen;
                iperf_gettimeofday( &(reportstruct->packetTime), NULL );
                ReportPacket( inst->mSettings->reporthdr, reportstruct );
            }



        } while ( currLen > 0 ); 
        
        
        // stop timing 
        iperf_gettimeofday( &(reportstruct->packetTime), NULL );
        
        if ( !isUDP (inst->mSettings)) {
            if(0 == inst->mSettings->mInterval) {
                reportstruct->packetLen = totLen;
            }
            ReportPacket( inst->mSettings->reporthdr, reportstruct );
        }
        CloseReport( inst->mSettings->reporthdr, reportstruct );
        
        // send a acknowledgement back only if we're NOT receiving multicast 
        if ( isUDP( inst->mSettings ) && !isMulticast( inst->mSettings ) ) {
            // send back an acknowledgement of the terminating datagram 
            Server_write_UDP_AckFIN( inst ); 
        }
    } else {
        FAIL(1, "Out of memory! Closing server thread\n", inst->mSettings);
    }

    Mutex_Lock( &clients_mutex );     
    Iperf_delete( &(inst->mSettings->peer), &clients ); 
    Mutex_Unlock( &clients_mutex );

    DELETE_PTR( reportstruct );
    EndReport( inst->mSettings->reporthdr );
} 
// end Recv 

/* ------------------------------------------------------------------- 
 * Send an AckFIN (a datagram acknowledging a FIN) on the socket, 
 * then select on the socket for some time. If additional datagrams 
 * come in, probably our AckFIN was lost and they are re-transmitted 
 * termination datagrams, so re-transmit our AckFIN. 
 * ------------------------------------------------------------------- */ 

void Server_write_UDP_AckFIN( Server* inst) {

    int rc; 

    fd_set readSet; 
    FD_ZERO( &readSet ); 

    struct timeval timeout; 

    int count = 0; 
    while ( count < 10 ) {
        count++; 

        UDP_datagram *UDP_Hdr;
        server_hdr *hdr;

        UDP_Hdr = (UDP_datagram*) inst->mBuf;

        if ( inst->mSettings->mBufLen > (int) ( sizeof( UDP_datagram )
                                          + sizeof( server_hdr ) ) ) {
            Transfer_Info *stats = GetReport( inst->mSettings->reporthdr );
            hdr = (server_hdr*) (UDP_Hdr+1);

            hdr->flags        = htonl( HEADER_VERSION1 );
            hdr->total_len1   = htonl( ((long long)stats->TotalLen >> 32) );
            hdr->total_len2   = htonl( (long) (stats->TotalLen & 0xFFFFFFFF) );
            hdr->stop_sec     = htonl( (long) stats->endTime.tv_sec );
            hdr->stop_usec    = htonl( (long) stats->endTime.tv_usec );
            hdr->error_cnt    = htonl( stats->cntError );
            hdr->outorder_cnt = htonl( stats->cntOutofOrder );
            hdr->datagrams    = htonl( stats->cntDatagrams );
            hdr->jitter1      = htonl( (long)(stats->jitter_us/rMillion) );//hdr->jitter1      = htonl( (long) stats->jitter );
            hdr->jitter2      = htonl( (long)(stats->jitter_us%rMillion) );//hdr->jitter2      = htonl( (long) ((stats->jitter - (long)stats->jitter) * rMillion) );

        }

        // write data 
        write( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 

        // wait until the socket is readable, or our timeout expires 
        FD_SET( inst->mSettings->mSock, &readSet ); 
        timeout.tv_sec  = 1; 
        timeout.tv_usec = 0; 

        rc = select( inst->mSettings->mSock+1, &readSet, NULL, NULL, &timeout ); 
        FAIL_errno( rc == SOCKET_ERROR, "select", inst->mSettings ); 

        if ( rc == 0 ) {
            // select timed out 
            return; 
        } else {
            // socket ready to read 
            rc = read( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 
            WARN_errno( rc < 0, "read" );
            if ( rc <= 0 ) {
                // Connection closed or errored
                // Stop using it.
                return;
            }
        } 
    } 

    printf ( warn_ack_failed, inst->mSettings->mSock, count ); 
} 
// end write_UDP_AckFIN 

