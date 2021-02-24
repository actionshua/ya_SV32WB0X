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
 * Listener.cpp
 * by Mark Gates <mgates@nlanr.net> 
 * &  Ajay Tirumala <tirumala@ncsa.uiuc.edu> 
 * ------------------------------------------------------------------- 
 * Listener sets up a socket listening on the server host. For each 
 * connected socket that accept() returns, this creates a Server 
 * socket and spawns a thread for it. 
 * 
 * Changes to the latest version. Listener will run as a daemon 
 * Multicast Server is now Multi-threaded 
 * ------------------------------------------------------------------- 
 * headers 
 * uses 
 *   <stdlib.h> 
 *   <stdio.h> 
 *   <string.h> 
 *   <errno.h> 
 * 
 *   <sys/types.h> 
 *   <unistd.h> 
 * 
 *   <netdb.h> 
 *   <netinet/in.h> 
 *   <sys/socket.h> 
 * ------------------------------------------------------------------- */ 


#define HEADERS() 

#include "iperf_headers.h" 
#include "iperf_Listener.h"
#include "iperf_SocketAddr.h"
#include "iperf_PerfSocket.h"
#include "iperf_List.h"
#include "iperf_util.h" 
#include "iperf_Timestamp.h"

/* ------------------------------------------------------------------- 
 * Stores local hostname and socket info. 
 * ------------------------------------------------------------------- */ 

void Listener_init( Listener *inst, thread_Settings *inSettings ) {

    inst->mClients = inSettings->mThreads;
    inst->mBuf = NULL;
    inst->mSettings = inSettings;

    // initialize buffer
    inst->mBuf = (char *)iperf_malloc( inst->mSettings->mBufLen );

    // open listening socket 
    Listener_Listen( inst ); 
    ReportSettings( inSettings );

} // end Listener 

/* ------------------------------------------------------------------- 
 * Delete memory (buffer). 
 * ------------------------------------------------------------------- */ 
void Listener_deinit(Listener *inst) {
    if ( inst->mSettings->mSock != INVALID_SOCKET ) {
        int rc = close( inst->mSettings->mSock );
        WARN_errno( rc == SOCKET_ERROR, "close" );
        inst->mSettings->mSock = INVALID_SOCKET;
    }
    DELETE_ARRAY( inst->mBuf );
} // end ~Listener 

/* ------------------------------------------------------------------- 
 * Listens for connections and starts Servers to handle data. 
 * For TCP, each accepted connection spawns a Server thread. 
 * For UDP, handle all data in this thread for Win32 Only, otherwise
 *          spawn a new Server thread. 
 * ------------------------------------------------------------------- */ 
void Listener_Run( Listener *inst ) {
#ifdef WIN32
    if ( isUDP( mSettings ) && !isSingleUDP( mSettings ) ) {
        UDPSingleServer();
    } else
#else
#ifdef sun
    if ( ( isUDP( mSettings ) && 
           isMulticast( mSettings ) && 
           !isSingleUDP( mSettings ) ) ||
         isSingleUDP( mSettings ) ) {
        UDPSingleServer();
    } else
#else
    if ( isSingleUDP( inst->mSettings ) ) {
        Listener_UDPSingleServer(inst);
    } else
#endif
#endif
    {
        bool client = false, UDP = isUDP( inst->mSettings ), mCount = (inst->mSettings->mThreads != 0);
        thread_Settings *tempSettings = NULL;
        struct Iperf_ListEntry *exist, *listtemp;
        client_hdr* hdr = ( UDP ? (client_hdr*) (((UDP_datagram*)inst->mBuf) + 1) : 
                                  (client_hdr*) inst->mBuf);
        
        if ( inst->mSettings->mHost != NULL ) {
            client = true;
            SockAddr_remoteAddr( inst->mSettings );
        }
        Settings_Copy( inst->mSettings, &inst->server );
        inst->server->mThreadMode = kMode_Server;
    
    
        // Accept each packet, 
        // If there is no existing client, then start  
        // a new thread to service the new client 
        // The listener runs in a single thread 
        // Thread per client model is followed 
        do {
            // Get a new socket
            Listener_Accept( inst, inst->server );
            if ( inst->server->mSock == INVALID_SOCKET ) {
                break;
            }
            if ( sInterupted != 0 ) {
                close( inst->server->mSock );
                break;
            }
            // Reset Single Client Stuff
            if ( isSingleClient( inst->mSettings ) && clients == NULL ) {
                inst->mSettings->peer = inst->server->peer;
                inst->mClients--;
                client = true;
                // Once all the server threads exit then quit
                // Must keep going in case this client sends
                // more streams
                if ( inst->mClients == 0 ) {
                    thread_release_nonterm( 0 );
                    inst->mClients = 1;
                }
            }
            // Verify that it is allowed
            if ( client ) {
                if ( !SockAddr_Hostare_Equal( (struct sockaddr*) &inst->mSettings->peer, 
                                              (struct sockaddr*) &inst->server->peer ) ) {
                    // Not allowed try again
                    close( inst->server->mSock );
                    if ( isUDP( inst->mSettings ) ) {
                        inst->mSettings->mSock = -1;
                        Listener_Listen(inst);
                    }
                    continue;
                }
            }
    
            // Create an entry for the connection list
            listtemp = (struct Iperf_ListEntry *) iperf_malloc(sizeof(struct Iperf_ListEntry));
            memcpy(listtemp, &inst->server->peer, sizeof(iperf_sockaddr));
            listtemp->next = NULL;
    
            // See if we need to do summing
            Mutex_Lock( &clients_mutex );
            exist = Iperf_hostpresent( &inst->server->peer, clients); 
    
            if ( exist != NULL ) {
                // Copy group ID
                listtemp->holder = exist->holder;
                inst->server->multihdr = exist->holder;
            } else {
                inst->server->mThreads = 0;
                Mutex_Lock( &groupCond );
                groupID--;
                listtemp->holder = InitMulti( inst->server, groupID );
                inst->server->multihdr = listtemp->holder;
                Mutex_Unlock( &groupCond );
            }
    
            // Store entry in connection list
            Iperf_pushback( listtemp, &clients ); 
            Mutex_Unlock( &clients_mutex ); 
    
            tempSettings = NULL;
            if ( !isCompat( inst->mSettings ) && !isMulticast( inst->mSettings ) ) {
                if ( !UDP ) {
                    // TCP does not have the info yet
                    if ( recv( inst->server->mSock, (char*)hdr, sizeof(client_hdr), 0) > 0 ) {
                        Settings_GenerateClientSettings( inst->server, &tempSettings, 
                                                          hdr );
                    }
                } else {
                    Settings_GenerateClientSettings( inst->server, &tempSettings, 
                                                      hdr );
                }
            }
    
    
            if ( tempSettings != NULL ) {
                client_init( tempSettings );
                if ( tempSettings->mMode == kTest_DualTest ) {
#ifdef HAVE_THREAD
                    server->runNow =  tempSettings;
#else
                    inst->server->runNext = tempSettings;
#endif
                } else {
                    inst->server->runNext =  tempSettings;
                }
            }
    
            // Start the server
#if defined(WIN32) && defined(HAVE_THREAD)
            if ( UDP ) {
                // WIN32 does bad UDP handling so run single threaded
                if ( server->runNow != NULL ) {
                    thread_start( server->runNow );
                }
                server_spawn( server );
                if ( server->runNext != NULL ) {
                    thread_start( server->runNext );
                }
            } else
#endif
            thread_start( inst->server );
    
            // create a new socket
            if ( UDP ) {
                inst->mSettings->mSock = -1;                
                Listener_Listen(inst);
            }
    
            // Prep for next connection
            if ( !isSingleClient( inst->mSettings ) ) {
                inst->mClients--;
            }            
            Settings_Copy( inst->mSettings, &inst->server );
            inst->server->mThreadMode = kMode_Server;
        } while ( !sInterupted && (/*!mCount || */ (mCount == true)&& (inst->mClients > 0) ) );
        
        Settings_Destroy( inst->server );
    }
} // end Run 

/* -------------------------------------------------------------------
 * Setup a socket listening on a port.
 * For TCP, this calls bind() and listen().
 * For UDP, this just calls bind().
 * If inLocalhost is not null, bind to that address rather than the
 * wildcard server address, specifying what incoming interface to
 * accept connections on.
 * ------------------------------------------------------------------- */
void Listener_Listen( Listener *inst) {
    int rc;

    SockAddr_localAddr( inst->mSettings );

    // create an internet TCP socket
    int type = (isUDP( inst->mSettings )  ?  SOCK_DGRAM  :  SOCK_STREAM);
    int domain = (SockAddr_isIPv6( &inst->mSettings->local ) ? 
#ifdef HAVE_IPV6
                  AF_INET6
#else
                  AF_INET
#endif
                  : AF_INET);

#ifdef WIN32
    if ( SockAddr_isMulticast( &mSettings->local ) ) {
        // Multicast on Win32 requires special handling
        mSettings->mSock = WSASocket( domain, type, 0, 0, 0, WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF );
        WARN_errno( mSettings->mSock == INVALID_SOCKET, "socket" );

    } else
#endif
    {
        inst->mSettings->mSock = socket( domain, type, 0 );
        WARN_errno( inst->mSettings->mSock == INVALID_SOCKET, "socket" );
    } 

    SetSocketOptions( inst->mSettings );

    // reuse the address, so we can run if a former server was killed off
    int boolean = 1;
    Socklen_t len = sizeof(boolean);
    //setsockopt( inst->mSettings->mSock, SOL_SOCKET, SO_REUSEADDR, (char*) &boolean, len );
    
    // bind socket to server address
#ifdef WIN32
    if ( SockAddr_isMulticast( &mSettings->local ) ) {
        // Multicast on Win32 requires special handling
        rc = WSAJoinLeaf( mSettings->mSock, (struct sockaddr*) &mSettings->local, mSettings->size_local,0,0,0,0,JL_BOTH);
        WARN_errno( rc == SOCKET_ERROR, "WSAJoinLeaf (aka bind)" );
    } else
#endif
    {
        rc = bind( inst->mSettings->mSock, (struct sockaddr*) &inst->mSettings->local, inst->mSettings->size_local );
        WARN_errno( rc == SOCKET_ERROR, "bind" );
    }
    // listen for connections (TCP only).
    // default backlog traditionally 5
    if ( !isUDP( inst->mSettings ) ) {
        rc = listen( inst->mSettings->mSock, 5 );
        WARN_errno( rc == SOCKET_ERROR, "listen" );
    }

#ifndef WIN32
    // if multicast, join the group
    if ( SockAddr_isMulticast( &inst->mSettings->local ) ) {
        Listener_McastJoin( inst );
    }
#endif
} // end Listen

/* -------------------------------------------------------------------
 * Joins the multicast group, with the default interface.
 * ------------------------------------------------------------------- */

void Listener_McastJoin( Listener *inst) {
#ifdef HAVE_MULTICAST
    if ( !SockAddr_isIPv6( &inst->mSettings->local ) ) {
        struct ip_mreq mreq;

        memcpy( &mreq.imr_multiaddr, SockAddr_get_in_addr( &inst->mSettings->local ), 
                sizeof(mreq.imr_multiaddr));

        mreq.imr_interface.s_addr = htonl( INADDR_ANY );

        int rc = setsockopt( inst->mSettings->mSock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                             (char*) &mreq, sizeof(mreq));
        WARN_errno( rc == SOCKET_ERROR, "multicast join" );
    }
#ifdef HAVE_IPV6_MULTICAST
      else {
        struct ipv6_mreq mreq;

        memcpy( &mreq.ipv6mr_multiaddr, SockAddr_get_in6_addr( &mSettings->local ), 
                sizeof(mreq.ipv6mr_multiaddr));

        mreq.ipv6mr_interface = 0;

        int rc = setsockopt( mSettings->mSock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
                             (char*) &mreq, sizeof(mreq));
        WARN_errno( rc == SOCKET_ERROR, "multicast join" );
    }
#endif
#endif
}
// end McastJoin

/* -------------------------------------------------------------------
 * Sets the Multicast TTL for outgoing packets.
 * ------------------------------------------------------------------- */

void Listener_McastSetTTL( Listener *inst, int val ) {
#ifdef HAVE_MULTICAST
    if ( !SockAddr_isIPv6( &inst->mSettings->local ) ) {
        int rc = setsockopt( inst->mSettings->mSock, IPPROTO_IP, IP_MULTICAST_TTL,
                             (char*) &val, sizeof(val));
        WARN_errno( rc == SOCKET_ERROR, "multicast ttl" );
    }
#ifdef HAVE_IPV6_MULTICAST
      else {
        int rc = setsockopt( mSettings->mSock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
                             (char*) &val, sizeof(val));
        WARN_errno( rc == SOCKET_ERROR, "multicast ttl" );
    }
#endif
#endif
}
// end McastSetTTL

/* -------------------------------------------------------------------
 * After Listen() has setup mSock, this will block
 * until a new connection arrives.
 * ------------------------------------------------------------------- */

void Listener_Accept( Listener *inst, thread_Settings *server ) {

    server->size_peer = sizeof(iperf_sockaddr); 
    if ( isUDP( server ) ) {
        /* ------------------------------------------------------------------- 
         * Do the equivalent of an accept() call for UDP sockets. This waits 
         * on a listening UDP socket until we get a datagram. 
         * ------------------------------------------------------------------- */
        int rc;
        struct Iperf_ListEntry *exist;
        int32_t datagramID;
        server->mSock = INVALID_SOCKET;
        while ( server->mSock == INVALID_SOCKET ) {
            fd_set fd;
            struct timeval tv;
            do
            {
                int ret = 0;
                tv.tv_sec = 1;
                tv.tv_usec = 0;
                FD_SET(inst->mSettings->mSock, &fd);
                ret = select((inst->mSettings->mSock+1), &fd, NULL, NULL, &tv);
                if ((ret == 0) && (sInterupted == 1))
                {
                    return ;
                }
                if(FD_ISSET(inst->mSettings->mSock, &fd))
                {
                    break;
                }
                
            }while(1);
            rc = recvfrom( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen, 0, 
                           (struct sockaddr*) &server->peer, &server->size_peer );
            FAIL_errno( rc == SOCKET_ERROR, "recvfrom", inst->mSettings );

            Mutex_Lock( &clients_mutex );
    
            // Handle connection for UDP sockets.
            exist = Iperf_present( &server->peer, clients);
            datagramID = ntohl( ((UDP_datagram*) inst->mBuf)->id ); 
            if ( exist == NULL && datagramID >= 0 ) {
                server->mSock = inst->mSettings->mSock;
                int rc = connect( server->mSock, (struct sockaddr*) &server->peer,
                                  server->size_peer );
                FAIL_errno( rc == SOCKET_ERROR, "connect UDP", mSettings );
            } else {
                server->mSock = INVALID_SOCKET;
            }
            Mutex_Unlock( &clients_mutex );
        }
    } else {
        // Handles interupted accepts. Returns the newly connected socket.
        server->mSock = INVALID_SOCKET;
    
        while ( server->mSock == INVALID_SOCKET ) {
            // accept a connection
            fd_set fd;
            struct timeval tv;
            do
            {
                int ret = 0;
                tv.tv_sec = 1;
                tv.tv_usec = 0;
                FD_SET(inst->mSettings->mSock, &fd);
                ret = select((inst->mSettings->mSock+1), &fd, NULL, NULL, &tv);
                if ((ret == 0) && (sInterupted == 1))
                {
                    return ;
                }
                if(FD_ISSET(inst->mSettings->mSock, &fd))
                {
                    break;                
                }
            }while(1);
            server->mSock = accept( inst->mSettings->mSock, 
                                    (struct sockaddr*) &server->peer, &server->size_peer );
            if ( server->mSock == INVALID_SOCKET &&  errnoicomm == EINTR ) {
                continue;
            }
        }
    }
    server->size_local = sizeof(iperf_sockaddr); 
    getsockname( server->mSock, (struct sockaddr*) &server->local, 
                 &server->size_local );
} // end Accept

void Listener_UDPSingleServer( Listener *inst) {
    
    bool client = false, UDP = isUDP( inst->mSettings ), mCount = (inst->mSettings->mThreads != 0);
    thread_Settings *tempSettings = NULL;
    struct Iperf_ListEntry *exist, *listtemp;
    int rc;
    int32_t datagramID;
    client_hdr* hdr = ( UDP ? (client_hdr*) (((UDP_datagram*)inst->mBuf) + 1) : 
                              (client_hdr*) inst->mBuf);
    ReportStruct *reportstruct = (ReportStruct *)iperf_malloc(sizeof(ReportStruct));
    
    if ( inst->mSettings->mHost != NULL ) {
        client = true;
        SockAddr_remoteAddr( inst->mSettings );
    }
    Settings_Copy( inst->mSettings, &inst->server );
    inst->server->mThreadMode = kMode_Server;


    // Accept each packet, 
    // If there is no existing client, then start  
    // a new report to service the new client 
    // The listener runs in a single thread 
    Mutex_Lock( &clients_mutex );
    do {
        // Get next packet
        while ( sInterupted == 0) {
            inst->server->size_peer = sizeof( iperf_sockaddr );
            rc = recvfrom( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen, 0, 
                           (struct sockaddr*) &inst->server->peer, &inst->server->size_peer );
            WARN_errno( rc == SOCKET_ERROR, "recvfrom" );
            if ( rc == SOCKET_ERROR ) {
                return;
            }
        
        
            // Handle connection for UDP sockets.
            exist = Iperf_present( &inst->server->peer, clients);
            datagramID = ntohl( ((UDP_datagram*) inst->mBuf)->id ); 
            if ( datagramID >= 0 ) {
                if ( exist != NULL ) {
                    // read the datagram ID and sentTime out of the buffer 
                    reportstruct->packetID = datagramID; 
                    reportstruct->sentTime.tv_sec = ntohl( ((UDP_datagram*) inst->mBuf)->tv_sec);
                    reportstruct->sentTime.tv_usec = ntohl( ((UDP_datagram*) inst->mBuf)->tv_usec ); 
        
                    reportstruct->packetLen = rc;
                    iperf_gettimeofday( &(reportstruct->packetTime), NULL );
        
                    ReportPacket( exist->server->reporthdr, reportstruct );
                } else {
                    Mutex_Lock( &groupCond );
                    groupID--;
                    inst->server->mSock = -groupID;
                    Mutex_Unlock( &groupCond );
                    inst->server->size_local = sizeof(iperf_sockaddr); 
                    getsockname( inst->mSettings->mSock, (struct sockaddr*) &inst->server->local, 
                                 &inst->server->size_local );
                    break;
                }
            } else {
                if ( exist != NULL ) {
                    // read the datagram ID and sentTime out of the buffer 
                    reportstruct->packetID = -datagramID; 
                    reportstruct->sentTime.tv_sec = ntohl( ((UDP_datagram*) inst->mBuf)->tv_sec  );
                    reportstruct->sentTime.tv_usec = ntohl( ((UDP_datagram*) inst->mBuf)->tv_usec ); 
        
                    reportstruct->packetLen = rc;
                    iperf_gettimeofday( &(reportstruct->packetTime), NULL );
        
                    ReportPacket( exist->server->reporthdr, reportstruct );
                    // stop timing 
                    iperf_gettimeofday( &(reportstruct->packetTime), NULL );
                    CloseReport( exist->server->reporthdr, reportstruct );
        
                    if ( rc > (int) ( sizeof( UDP_datagram )
                                                      + sizeof( server_hdr ) ) ) {
                        UDP_datagram *UDP_Hdr;
                        server_hdr *hdr;
        
                        UDP_Hdr = (UDP_datagram*) inst->mBuf;
                        Transfer_Info *stats = GetReport( exist->server->reporthdr );
                        hdr = (server_hdr*) (UDP_Hdr+1);
        
                        hdr->flags        = htonl( HEADER_VERSION1 );
                        hdr->total_len1   = htonl( ((long long)stats->TotalLen >> 32) );
                        hdr->total_len2   = htonl( (long) (stats->TotalLen & 0xFFFFFFFF) );
                        hdr->stop_sec     = htonl( stats->endTime.tv_sec );//hdr->stop_sec     = htonl( (long) stats->endTime );
                        hdr->stop_usec    = htonl( stats->endTime.tv_usec );//hdr->stop_usec    = htonl( (long)((stats->endTime - (long)stats->endTime) * rMillion));
                        hdr->error_cnt    = htonl( stats->cntError );
                        hdr->outorder_cnt = htonl( stats->cntOutofOrder );
                        hdr->datagrams    = htonl( stats->cntDatagrams );
                        hdr->jitter1      = htonl( (long)(stats->jitter_us/rMillion) );//hdr->jitter1      = htonl( (long) stats->jitter );
                        hdr->jitter2      = htonl( (long)(stats->jitter_us%rMillion) );//hdr->jitter2      = htonl( (long) ((stats->jitter - (long)stats->jitter) * rMillion) );
        
                    }
                    EndReport( exist->server->reporthdr );
                    exist->server->reporthdr = NULL;
                    Iperf_delete( &(exist->server->peer), &clients );
                } else if ( rc > (int) ( sizeof( UDP_datagram )
                                                  + sizeof( server_hdr ) ) ) {
                    UDP_datagram *UDP_Hdr;
                    server_hdr *hdr;
        
                    UDP_Hdr = (UDP_datagram*) inst->mBuf;
                    hdr = (server_hdr*) (UDP_Hdr+1);
                    hdr->flags = htonl( 0 );
                }
                sendto( inst->mSettings->mSock, inst->mBuf, inst->mSettings->mBufLen, 0,
                        (struct sockaddr*) &inst->server->peer, inst->server->size_peer);
            }
        }
        if ( inst->server->mSock == INVALID_SOCKET ) {
            break;
        }
        if ( sInterupted != 0 ) {
            close( inst->server->mSock );
            break;
        }
        // Reset Single Client Stuff
        if ( isSingleClient( inst->mSettings ) && clients == NULL ) {
            inst->mSettings->peer = inst->server->peer;
            inst->mClients--;
            client = true;
            // Once all the server threads exit then quit
            // Must keep going in case this client sends
            // more streams
            if ( inst->mClients == 0 ) {
                thread_release_nonterm( 0 );
                inst->mClients = 1;
            }
        }
        // Verify that it is allowed
        if ( client ) {
            if ( !SockAddr_Hostare_Equal( (struct sockaddr*) &inst->mSettings->peer, 
                                          (struct sockaddr*) &inst->server->peer ) ) {
                // Not allowed try again
                connect( inst->mSettings->mSock, 
                         (struct sockaddr*) &inst->server->peer, 
                         inst->server->size_peer );
                close( inst->mSettings->mSock );
                inst->mSettings->mSock = -1; 
                Listener_Listen( inst );
                continue;
            }
        }

        // Create an entry for the connection list
        listtemp = (struct Iperf_ListEntry *)iperf_malloc(sizeof(struct Iperf_ListEntry));
        memcpy(listtemp, &inst->server->peer, sizeof(iperf_sockaddr));
        listtemp->server = inst->server;
        listtemp->next = NULL;

        // See if we need to do summing
        exist = Iperf_hostpresent( &inst->server->peer, clients); 

        if ( exist != NULL ) {
            // Copy group ID
            listtemp->holder = exist->holder;
            inst->server->multihdr = exist->holder;
        } else {
            inst->server->mThreads = 0;
            Mutex_Lock( &groupCond );
            groupID--;
            listtemp->holder = InitMulti( inst->server, groupID );
            inst->server->multihdr = listtemp->holder;
            Mutex_Unlock( &groupCond );
        }

        // Store entry in connection list
        Iperf_pushback( listtemp, &clients ); 

        tempSettings = NULL;
        if ( !isCompat( inst->mSettings ) && !isMulticast( inst->mSettings ) ) {
            Settings_GenerateClientSettings( inst->server, &tempSettings, 
                                              hdr );
        }


        if ( tempSettings != NULL ) {
            client_init( tempSettings );
            if ( tempSettings->mMode == kTest_DualTest ) {
#ifdef HAVE_THREAD
                thread_start( tempSettings );
#else
                inst->server->runNext = tempSettings;
#endif
            } else {
                inst->server->runNext =  tempSettings;
            }
        }
        inst->server->reporthdr = InitReport( inst->server );

        // Prep for next connection
        if ( !isSingleClient( inst->mSettings ) ) {
            inst->mClients--;
        }
        Settings_Copy( inst->mSettings, &inst->server );
        inst->server->mThreadMode = kMode_Server;
    } while ( !sInterupted && (!mCount || ( mCount && inst->mClients > 0 )) );
    Mutex_Unlock( &clients_mutex );

    Settings_Destroy( inst->server );
}

/* -------------------------------------------------------------------- 
 * Run the server as a daemon  
 * --------------------------------------------------------------------*/ 

void Listener_runAsDaemon(const char *pname, int facility) {
#if 0//#ifndef WIN32 
    pid_t pid; 

    /* Create a child process & if successful, exit from the parent process */ 
    if ( (pid = fork()) == -1 ) {
        printf ( "error in first child create\n");     
        exit(0); 
    } else if ( pid != 0 ) {
        exit(0); 
    }

    /* Try becoming the session leader, once the parent exits */
    if ( setsid() == -1 ) {           /* Become the session leader */ 
        printf ( "Cannot change the session group leader\n"); 
    } else {
    } 
    signal(SIGHUP,SIG_IGN); 


    /* Now fork() and get released from the terminal */  
    if ( (pid = fork()) == -1 ) {
        printf ( "error\n");   
        exit(0); 
    } else if ( pid != 0 ) {
        exit(0); 
    }

    chdir("."); 
    printf ( "Running Iperf Server as a daemon\n"); 
    printf ( "The Iperf daemon process ID : %d\n",((int)getpid())); 
    fflush(stderr); 

    fclose(stdin); 
#else 
    printf ( "Use the precompiled windows version for service (daemon) option\n"); 
#endif  

}

