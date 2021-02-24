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
 * Client.cpp
 * by Mark Gates <mgates@nlanr.net>
 * -------------------------------------------------------------------
 * A client thread initiates a connect to the server and handles
 * sending and receiving data, then closes the socket.
 * ------------------------------------------------------------------- */

#include "iperf_headers.h"
#include "iperf_Client.h"
#include "iperf_Thread.h"
#include "iperf_SocketAddr.h"
#include "iperf_PerfSocket.h"
//#include "Extractor.h"
#include "iperf_delay.h"
#include "iperf_util.h"
#include "iperf_Locale.h"

/* -------------------------------------------------------------------
 * Store server hostname, optionally local hostname, and socket info.
 * ------------------------------------------------------------------- */

void Client_init( Client *inst, thread_Settings *inSettings ) {
    inst->mSettings = inSettings;
    inst->mBuf = NULL;

    // initialize buffer
    inst->mBuf = (char *)iperf_malloc(inst->mSettings->mBufLen);
    pattern( inst->mBuf, inst->mSettings->mBufLen );
#if 0
    if ( isFileInput( mSettings ) ) {
        if ( !isSTDIN( mSettings ) )
            Extractor_Initialize( mSettings->mFileName, mSettings->mBufLen, mSettings );
        else
            Extractor_InitializeFile( stdin, mSettings->mBufLen, mSettings );

        if ( !Extractor_canRead( mSettings ) ) {
            unsetFileInput( mSettings );
        }
    }
#endif

    // connect
    Client_Connect(inst);

    if ( isReport( inSettings ) ) {
        ReportSettings( inSettings );
        if ( inst->mSettings->multihdr && isMultipleReport( inSettings ) ) {
            inst->mSettings->multihdr->report->connection.peer = inst->mSettings->peer;
            inst->mSettings->multihdr->report->connection.size_peer = inst->mSettings->size_peer;
            inst->mSettings->multihdr->report->connection.local = inst->mSettings->local;
            SockAddr_setPortAny( &inst->mSettings->multihdr->report->connection.local );
            inst->mSettings->multihdr->report->connection.size_local = inst->mSettings->size_local;
        }
    }

} // end Client

/* -------------------------------------------------------------------
 * Delete memory (hostname strings).
 * ------------------------------------------------------------------- */

void Client_deinit(Client *inst) {
    if ( inst->mSettings->mSock != INVALID_SOCKET ) {
        int rc = close( inst->mSettings->mSock );
        WARN_errno( rc == SOCKET_ERROR, "close" );
        inst->mSettings->mSock = INVALID_SOCKET;
    }
    DELETE_ARRAY( inst->mBuf );
} // end ~Client

const int kSecs_to_usecs = rMillion; 
const int    kBytes_to_Bits = 8; 

void Client_RunTCP( Client *inst ) {
    unsigned long currLen = 0; 
    //struct itimerval it;
    max_size_t totLen = 0;

    int err;

//    char* readAt = inst->mBuf;

    // Indicates if the stream is readable 
    bool canRead = true, mMode_Time = isModeTime( inst->mSettings ); 

    ReportStruct *reportstruct = NULL;

    // InitReport handles Barrier for multiple Streams
    inst->mSettings->reporthdr = InitReport( inst->mSettings );
    reportstruct = (ReportStruct *)iperf_malloc(sizeof(ReportStruct));
    reportstruct->packetID = 0;

    Timestamp_setnow(&inst->lastPacketTime);
    if ( mMode_Time ) {
#if 0
        memset (&it, 0, sizeof (it));
        it.it_value.tv_sec = (int) (inst->mSettings->mAmount / 100.0);
        it.it_value.tv_usec = (int) 10000 * (inst->mSettings->mAmount -
            it.it_value.tv_sec * 100.0);
        err = setitimer( ITIMER_REAL, &it, NULL );
        if ( err != 0 ) {
            perror("setitimer");
            exit(1);
        }
#endif
    }
    do {
        // Read the next data block from 
        // the file if it's file input 
#if 0
        if ( isFileInput( mSettings ) ) {
            Extractor_getNextDataBlock( readAt, mSettings ); 
            canRead = Extractor_canRead( mSettings ) != 0; 
        } else
#endif
            canRead = true; 

        // perform write 
        currLen = write( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 
        if ( currLen < 0 ) {
            WARN_errno( currLen < 0, "write2" ); 
            break; 
        }
        totLen += currLen;

        if(inst->mSettings->mInterval > 0) {
    	    iperf_gettimeofday( &(reportstruct->packetTime), NULL );
            reportstruct->packetLen = currLen;
            ReportPacket( inst->mSettings->reporthdr, reportstruct );
        }	

        if ( !mMode_Time ) {
            /* mAmount may be unsigned, so don't let it underflow! */
            if( inst->mSettings->mAmount >= currLen ) {
                inst->mSettings->mAmount -= currLen;
            } else {
                inst->mSettings->mAmount = 0;
            }
        }

    } while ( ! (sInterupted  || 
                   (!mMode_Time  &&  0 >= inst->mSettings->mAmount)) && canRead ); 

    // stop timing
    iperf_gettimeofday( &(reportstruct->packetTime), NULL );

    // if we're not doing interval reporting, report the entire transfer as one big packet
    if(0 == inst->mSettings->mInterval) {
        reportstruct->packetLen = totLen;
        ReportPacket( inst->mSettings->reporthdr, reportstruct );
    }
    CloseReport( inst->mSettings->reporthdr, reportstruct );

    DELETE_PTR( reportstruct );
    EndReport( inst->mSettings->reporthdr );
}

/* ------------------------------------------------------------------- 
 * Send data using the connected UDP/TCP socket, 
 * until a termination flag is reached. 
 * Does not close the socket. 
 * ------------------------------------------------------------------- */ 

void Client_Run( Client *inst ) {
    struct UDP_datagram* mBuf_UDP = (struct UDP_datagram*) inst->mBuf; 
    unsigned long currLen = 0; 

    int delay_target = 0; 
    int delay = 0; 
    int adjust = 0; 

//    char* readAt = mBuf;

#if HAVE_THREAD
    if ( !isUDP( inst->mSettings ) ) {
        Client_RunTCP(inst);
        return;
    }
#endif
    
    // Indicates if the stream is readable 
    bool canRead = true, mMode_Time = isModeTime( inst->mSettings ); 

    // setup termination variables
    if ( mMode_Time ) {
        Timestamp t_time;
        Timestamp_setnow(&inst->mEndTime);
        Timestamp_set(&t_time, (inst->mSettings->mAmount/100),  (inst->mSettings->mAmount%100));
        Timestamp_add( &inst->mEndTime, t_time );
    }

    if ( isUDP( inst->mSettings ) ) {
        // Due to the UDP timestamps etc, included 
        // reduce the read size by an amount 
        // equal to the header size
    
        // compute delay for bandwidth restriction, constrained to [0,1] seconds 
        delay_target = (int) ( inst->mSettings->mBufLen * ((kSecs_to_usecs * kBytes_to_Bits) 
                                                     / inst->mSettings->mUDPRate) ); 
        if ( delay_target < 0  || 
             delay_target > (int) 1 * kSecs_to_usecs ) {
            printf ( warn_delay_large, delay_target / kSecs_to_usecs ); 
            delay_target = (int) kSecs_to_usecs * 1; 
        }
#if 0
        if ( isFileInput( mSettings ) ) {
            if ( isCompat( mSettings ) ) {
                Extractor_reduceReadSize( sizeof(struct UDP_datagram), mSettings );
                readAt += sizeof(struct UDP_datagram);
            } else {
                Extractor_reduceReadSize( sizeof(struct UDP_datagram) +
                                          sizeof(struct client_hdr), mSettings );
                readAt += sizeof(struct UDP_datagram) +
                          sizeof(struct client_hdr);
            }
        }
#endif
    }

    ReportStruct *reportstruct = NULL;

    // InitReport handles Barrier for multiple Streams
    inst->mSettings->reporthdr = InitReport( inst->mSettings );
    reportstruct = (ReportStruct *)iperf_malloc(sizeof(ReportStruct));
    reportstruct->packetID = 0;

    Timestamp_setnow(&inst->lastPacketTime);
    
    do {

        // Test case: drop 17 packets and send 2 out-of-order: 
        // sequence 51, 52, 70, 53, 54, 71, 72 
        //switch( datagramID ) { 
        //  case 53: datagramID = 70; break; 
        //  case 71: datagramID = 53; break; 
        //  case 55: datagramID = 71; break; 
        //  default: break; 
        //} 
        iperf_gettimeofday( &(reportstruct->packetTime), NULL );

        if ( isUDP( inst->mSettings ) ) {
            // store datagram ID into buffer 
            mBuf_UDP->id      = htonl( (reportstruct->packetID)++ ); 
            mBuf_UDP->tv_sec  = htonl( reportstruct->packetTime.tv_sec ); 
            mBuf_UDP->tv_usec = htonl( reportstruct->packetTime.tv_usec );

            // delay between writes 
            // make an adjustment for how long the last loop iteration took 
            // TODO this doesn't work well in certain cases, like 2 parallel streams 
            adjust = delay_target + Timestamp_subUsec(&inst->lastPacketTime, reportstruct->packetTime ); 
            Timestamp_set(&inst->lastPacketTime, reportstruct->packetTime.tv_sec, 
                                reportstruct->packetTime.tv_usec ); 

            if ( adjust > 0  ||  delay > 0 ) {
                delay += adjust; 
            }
        }

        // Read the next data block from 
        // the file if it's file input 
#if 0
        if ( isFileInput( mSettings ) ) {
            Extractor_getNextDataBlock( readAt, mSettings ); 
            canRead = Extractor_canRead( mSettings ) != 0; 
        } else
#endif
            canRead = true; 

        // perform write 
        currLen = write( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 
        if ( currLen < 0 && errnoicomm != ENOBUFS ) {
            WARN_errno( currLen < 0, "write2" ); 
            break; 
        }

        // report packets 
        reportstruct->packetLen = currLen;
        ReportPacket( inst->mSettings->reporthdr, reportstruct );
        
        if ( delay > 0 ) {
            delay_loop( delay ); 
        }
        if ( !mMode_Time ) {
            /* mAmount may be unsigned, so don't let it underflow! */
            if( inst->mSettings->mAmount >= currLen ) {
                inst->mSettings->mAmount -= currLen;
            } else {
                inst->mSettings->mAmount = 0;
            }
        }

    } while ( ! (sInterupted  || 
                 (mMode_Time   &&  Timestamp_before_( &inst->mEndTime, reportstruct->packetTime ))  || 
                 (!mMode_Time  &&  0 >= inst->mSettings->mAmount)) && canRead ); 

    // stop timing
    iperf_gettimeofday( &(reportstruct->packetTime), NULL );
    CloseReport( inst->mSettings->reporthdr, reportstruct );

    if ( isUDP( inst->mSettings ) ) {
        // send a final terminating datagram 
        // Don't count in the mTotalLen. The server counts this one, 
        // but didn't count our first datagram, so we're even now. 
        // The negative datagram ID signifies termination to the server. 
    
        // store datagram ID into buffer 
        mBuf_UDP->id      = htonl( -(reportstruct->packetID)  ); 
        mBuf_UDP->tv_sec  = htonl( reportstruct->packetTime.tv_sec ); 
        mBuf_UDP->tv_usec = htonl( reportstruct->packetTime.tv_usec ); 

        if ( isMulticast( inst->mSettings ) ) {
            write( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 
        } else {
            Client_write_UDP_FIN(inst); 
        }
    }
    DELETE_PTR( reportstruct );
    EndReport( inst->mSettings->reporthdr );
} 
// end Run

void Client_InitiateServer( Client * inst) {
    if ( !isCompat( inst->mSettings ) ) {
        int currLen;
        client_hdr* temp_hdr;
        if ( isUDP( inst->mSettings ) ) {
            UDP_datagram *UDPhdr = (UDP_datagram *)inst->mBuf;
            temp_hdr = (client_hdr*)(UDPhdr + 1);
        } else {
            temp_hdr = (client_hdr*)inst->mBuf;
        }
        Settings_GenerateClientHdr( inst->mSettings, temp_hdr );
        if ( !isUDP( inst->mSettings ) ) {
            currLen = send( inst->mSettings->mSock, inst->mBuf, sizeof(client_hdr), 0 );
            if ( currLen < 0 ) {
                WARN_errno( currLen < 0, "write1" );
            }
        }
    }
}

/* -------------------------------------------------------------------
 * Setup a socket connected to a server.
 * If inLocalhost is not null, bind to that address, specifying
 * which outgoing interface to use.
 * ------------------------------------------------------------------- */

void Client_Connect(Client *inst) {
    int rc;
    SockAddr_remoteAddr( inst->mSettings );

    //assert( inst->mSettings->inHostname != NULL );

    // create an internet socket
    int type = ( isUDP( inst->mSettings )  ?  SOCK_DGRAM : SOCK_STREAM);

    int domain = (SockAddr_isIPv6( &inst->mSettings->peer ) ? 
#ifdef HAVE_IPV6
                  AF_INET6
#else
                  AF_INET
#endif
                  : AF_INET);

    inst->mSettings->mSock = socket( domain, type, 0 );
    WARN_errno( inst->mSettings->mSock == INVALID_SOCKET, "socket" );

    SetSocketOptions( inst->mSettings );


    SockAddr_localAddr( inst->mSettings );
    if ( inst->mSettings->mLocalhost != NULL ) {
        // bind socket to local address
        rc = bind( inst->mSettings->mSock, (struct sockaddr*) &inst->mSettings->local, 
                   SockAddr_get_sizeof_sockaddr( &inst->mSettings->local ) );
        WARN_errno( rc == SOCKET_ERROR, "bind" );
    }

    // connect socket
#if 0
	char tmp0[24];
	//iperf_sockaddr peer;
	struct sockaddr_in peer;
    memset(&peer, 0, sizeof(peer));
    peer.sin_family= AF_INET;
	peer.sin_port = htons(5001);
	memset(tmp0,0x0,sizeof(tmp0));
	strcpy(tmp0,"192.168.0.100");
	inet_aton(tmp0, &peer.sin_addr);
	peer.sin_len = sizeof(peer);
	inst->mSettings->mSock = socket(AF_INET, SOCK_STREAM, 0);
	printf("== inst->mSettings->mSock: %d ==\n", );
    rc = connect( inst->mSettings->mSock, &peer,sizeof(peer));
	
#else
    //s_sockaddr.sin_len = sizeof(s_sockaddr);

	int g_now_sram_size = OS_MemRemainSize();
	printf("!!!!!!!now_sram_size = %d\n", g_now_sram_size);
    rc = connect( inst->mSettings->mSock, (struct sockaddr*) &inst->mSettings->peer, 
                  SockAddr_get_sizeof_sockaddr( &inst->mSettings->peer ));
#endif
    FAIL_errno( rc == SOCKET_ERROR, "connect", inst->mSettings );

    getsockname( inst->mSettings->mSock, (struct sockaddr*) &inst->mSettings->local, 
                 &inst->mSettings->size_local );
    getpeername( inst->mSettings->mSock, (struct sockaddr*) &inst->mSettings->peer,
                 &inst->mSettings->size_peer );
} // end Connect

/* ------------------------------------------------------------------- 
 * Send a datagram on the socket. The datagram's contents should signify 
 * a FIN to the application. Keep re-transmitting until an 
 * acknowledgement datagram is received. 
 * ------------------------------------------------------------------- */ 

void Client_write_UDP_FIN(Client *inst) {
    int rc; 
    fd_set readSet; 
    struct timeval timeout; 

    int count = 0; 
    while ( count < 10 ) {
        count++; 

        // write data 
        write( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 

        // wait until the socket is readable, or our timeout expires 
        FD_ZERO( &readSet ); 
        FD_SET( inst->mSettings->mSock, &readSet ); 
        timeout.tv_sec  = 0; 
        timeout.tv_usec = 250000; // quarter second, 250 ms 

        rc = select( inst->mSettings->mSock+1, &readSet, NULL, NULL, &timeout ); 
        FAIL_errno( rc == SOCKET_ERROR, "select", inst->mSettings ); 

        if ( rc == 0 ) {
            // select timed out 
            continue; 
        } else {
            // socket ready to read 
            rc = read( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen ); 
            WARN_errno( rc < 0, "read" );
    	    if ( rc < 0 ) {
                break;
            } else if ( rc >= (int) (sizeof(UDP_datagram) + sizeof(server_hdr)) ) {
                ReportServerUDP( inst->mSettings, (server_hdr*) ((UDP_datagram*)inst->mBuf + 1) );
            }

            return; 
        } 
    } 

    printf ( warn_no_ack, inst->mSettings->mSock, count ); 
} 
// end write_UDP_FIN 
