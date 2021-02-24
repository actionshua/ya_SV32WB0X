/**
 *
 * @page ATCMD
 *
 * @section ATCMD_socket Socket AT Command
 * 
 * @subsection ATCMD_socket_1 Create TCP connection.
 *
 * | command     | AT+TCPCONNECT=<RemoteIP>,<Port> |
 * |---------------|-------------------|
 * | param         | <RemoteIP>: The remote IP address for TCP connection<br><Port>: The port number for TCP connection. |
 * | return value  | AT+NEWTCPCONNECT OK:<socket><br>+ERROR:error number |
 * | example       | AT+TCPCONNECT=192.168.1.100,11111 |
 *
 * @subsection ATCMD_socket_2 Transmit IP data to Internet.
 *
 * | command     | AT+TCPSEND=<socket>,<payload> |
 * |---------------|-------------------|
 * | param         | <socket>: socket index<br><payload>: Data for sending to remote connection |
 * | return value  | +OK<br>+ERROR:error number |
 * | example       | AT+TCPSEND=0,hello world |
 *
 * @subsection ATCMD_socket_3 Disconnect TCP connection.
 *
 * | command     | AT+TCPDISCONNECT=<socket> |
 * |---------------|-------------------|
 * | param         | <socket>: socket index |
 * | return value  | +OK<br>+ERROR:error number |
 * | example       | AT+TCPDISCONNECT=0 |
 *
 *
 * @subsection ATCMD_socket_4 Create TCP Server.
 *
 * | command     | AT+TCPLISTEN=<port> |
 * |---------------|-------------------|
 * | param         | <port>: port number |
 * | return value  | TCP Listen at Socket:<socket_index><br>+ERROR:error number |
 * | example       | AT+TCPLISTEN=11111 |
 *
 * @subsection ATCMD_socket_5 Delete TCP Server.
 *
 * | command     | AT+TCPUNLISTEN=<port> |
 * |---------------|-------------------|
 * | param         | <port>: port number |
 * | return value  | socket close: <socket_index><br>+ERROR:error number |
 * | example       | AT+TCPUNLISTEN=11111 |
 *
 * @subsection ATCMD_socket_6 Create UDP Connection.
 *
 * | command     | AT+UDPCREATE=<port> |
 * |---------------|-------------------|
 * | param         | <port>: port number |
 * | return value  | UDP Create at Socket:<socket_index><br>+ERROR:error number |
 * | example       | AT+UDPCREATE=22222 |
 *
 * @subsection ATCMD_socket_7 Transmit UDP data to Internet.
 *
 * | command     | AT+UDPSEND=<socket>,<remote_ip>,<remote_port>,<payload> |
 * |---------------|-------------------|
 * | param         | <socket>: socket index<br><remote_ip>: remote IP can be send in UDP connection<br><remote_port>: remote port<br><payload> Data for sending to UDP connection |
 * | return value  | AT+UDPSEND=OK<br>+ERROR:error number |
 * | example       | AT+UDPSEND=0,192.168.1.100,33333,hello world |
 *
 * @subsection ATCMD_socket_8 Delete UDP Connection.
 *
 * | command     | AT+UDPCLOSE=<socket> |
 * |---------------|-------------------|
 * | param         | <socket>: socket index |
 * | return value  | socket close: <socket_index><br>+ERROR:error number |
 * | example       | AT+UDPCLOSE=0 |
 *
 * @subsection ATCMD_socket_9 DNS function.
 *
 * | command     | AT+NSLOOKUP=<hostname> |
 * |---------------|-------------------|
 * | param         | <hostname>: FQDN of host  |
 * | return value  | socket close: Name: hostname<br>Address: ip address<br>+ERROR:error number |
 * | example       | AT+NSLOOKUP=www.google.com | 
 *
 * @subsection ATCMD_socket_10 Sync time from SNTP Server
 *
 * | command     | AT+SNTP_SYNC |
 * |---------------|-------------------|
 * | param         | none  |
 * | return value  | AT+SNTP_SYNC=OK |
 * | example       | AT+SNTP_SYNC | 
 * 
 * @subsection ATCMD_socket_11 Show Current Time
 *
 * | command     | AT+SNTP_TIME |
 * |---------------|-------------------|
 * | param         | none  |
 * | return value  | Current Time: Thu Dec 20 16:33:45 2018<br>AT+SNTP_TIME=OK |
 * | example       | AT+SNTP_TIME | 
 * 
 * @subsection ATCMD_socket_12 Start JD Cloud Demo
 *
 * | command     | ATCMD_JD_START |
 * |---------------|-------------------|
 * | param         | none  |
 * | return value  | ATCMD_JD_START=OK |
 * | example       | ATCMD_JD_START | 
 * | commit       | please refenance Joylink_Cloud.docx |  
 * 
 * @subsection ATCMD_socket_13 Remove JD Cloud Device
 *
 * | command     | ATCMD_JD_DEVICE_REMOVE |
 * |---------------|-------------------|
 * | param         | none  |
 * | return value  | ATCMD_JD_DEVICE_REMOVE=OK |
 * | example       | ATCMD_JD_DEVICE_REMOVE | 
 * | commit       | please refenance Joylink_Cloud.docx |  
 *  
 */
#ifndef ATCMD_SOCKET_H__
#define ATCMD_SOCKET_H__


//TCP
#define ATCMD_TCPCONNECT            "AT+TCPCONNECT"
#define ATCMD_TCPSEND               "AT+TCPSEND"
#define ATCMD_TCPRECV               "AT+TCPRECV"
#define ATCMD_TCPDISCONNECT         "AT+TCPDISCONNECT"
#define ATCMD_TCPLISTEN	            "AT+TCPLISTEN"
#define ATCMD_TCPUNLISTEN           "AT+TCPUNLISTEN"
#define ATCMD_MESHCOEXTEST           "AT+MESHCOEXTEST"
#define ATCMD_MESHCOEXCONNECT        "AT+MESHCOEXCONNECT"


#define ATCMD_TCPSEND6              "AT+IPV6SEND"
#define ATCMD_TCPLISTEN6	        "AT+IPV6LISTEN"

//UDP
#define ATCMD_UDPCREATE             "AT+UDPCREATE"
#define ATCMD_UDPSEND               "AT+UDPSEND"
#define ATCMD_UDPCLOSE              "AT+UDPCLOSE"

#define ATCMD_NSLOOKUP              "AT+NSLOOKUP"

#define ATCMD_SNTP_SYNC         "AT+SNTP_SYNC"
#define ATCMD_SNTP_TIME         "AT+SNTP_TIME"
//jd cloud cmd
#define ATCMD_JD_DEVICE_REMOVE              "AT+JD_DEVICE_REMOVE"
#define ATCMD_JD_START              "AT+JD_START"

//HTTP
#define ATCMD_HTTPTEST               "AT+HTTPTEST"
//SSL
#define ATCMD_SSLTEST               "AT+SSLTEST"
#define ATCMD_SSLCONNECT            "AT+SSLCONNECT"
#define ATCMD_SSLSEND               "AT+SSLSEND"
#define ATCMD_SSLDISCONNECT         "AT+SSLDISCONNECT"

//ota cmd
#define ATCMD_OTASETSERVER          "AT+OTASETSERVER"
#define ATCMD_OTASETPARAM           "AT+OTASETPARAM"
#define ATCMD_OTASTART              "AT+OTASTART"
#define ATCMD_OTASTOP               "AT+OTASTOP"
#define ATCMD_OTAREBOOT             "AT+OTAREBOOT"

#ifdef SMARTCONFIG_EN
#define ATCMD_SMARTCONFIG    "AT+SC"
#endif

#define ATCMD_IPERF                     "iperf"



#endif
