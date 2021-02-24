#include "soc_types.h"
#include "atcmd.h"
#include "error.h"
#include "Cabrio-conf.h"

#include "netstack_def.h"


#include "ssv_lib.h"

#include "wifi_api.h"
#include <time.h>
#include <third_party/sntp/sntp.h> 

#ifdef SMARTCONFIG_EN
#ifdef JOYLINK_EN
#include "joylink/joylink_main.h"
#endif
#if defined(AIRKISS_EN) && (AIRKISS_EN == 1)
#include "airkiss/airkiss_main.h"
#endif
#ifdef RTLINK_EN
#include "rtlink/rtlink_main.h"
#endif
#endif

#if defined(FOTA_OPTION) && (FOTA_OPTION != 0)
#include "fota_api.h"
#endif
#include "osal.h"
#include "atcmd_socket.h"

//#define atcmdprintf printf

void easy_httpclient_test();
/////////////////Link list/////////////////

void list_q_init(struct list_q *qhd)
{
    qhd->prev = (struct list_q *)qhd;
    qhd->next = (struct list_q *)qhd;
    qhd->qlen = 0;
}

void list_q_qtail(struct list_q *qhd, struct list_q *newq)
{
    struct list_q *next = qhd;
    struct list_q* prev = qhd->prev;

    newq->next = next;
    newq->prev = prev;
    next->prev = newq;
    prev->next = newq;
    qhd->qlen++;
}

void list_q_insert(struct list_q *qhd, struct list_q *prev, struct list_q *newq)
{
    struct list_q *next = prev->next;

    newq->next = next;
    newq->prev = prev;
    next->prev = newq;
    prev->next = newq;
    qhd->qlen++;
}

void list_q_remove(struct list_q *qhd,struct list_q *curt)
{
    struct list_q *next = curt->next;
    struct list_q *prev = curt->prev;

    prev->next = next;
    next->prev = prev;
    qhd->qlen--;
}

u8 listhead_is_inited = 0;

////////////////////////////////////
#define buf_size 2048
#define RCV_TASK_NAME "ATCMD_SocketTask"
struct listen_socket_q
{
    struct list_q list;
    int socket;
    u16 port;
};

struct socket_q
{
    struct list_q list;
    int socket;
    int parent_sd;
};


enum task_st
{
    TASK_ST_Term = -1,
    TASK_ST_Stop,
    TASK_ST_Running,
};

struct list_q g_listen_socket;
struct list_q g_normal_socket;
volatile int recv_task_st = 0;
OsTaskHandle recv_task_inst = NULL;
int max_sd = -1; 
fd_set g_r_set;
fd_set g_clr_set;

int mark_rm_listen_sd_by_port(u16 port)
{
    int socket = -1;
    //ATCMD_LOG_I("%s::%d\n",__FUNCTION__, __LINE__);
    
    if (g_listen_socket.qlen == 0)
        return socket;
    
    struct listen_socket_q* item = (struct listen_socket_q*)g_listen_socket.next;
    while ((item != (struct listen_socket_q*)&g_listen_socket) && (item->port != port))
        item = (struct listen_socket_q*)item->list.next;
    
    if (item->port == port)
    {
        socket = item->socket;
        FD_SET(socket, &g_clr_set);
        //ATCMD_LOG_I("%s::%d, socket = %d\n",__FUNCTION__, __LINE__, socket);
    }
    
    return socket;
}

int mark_rm_sd(int sd)
{    
    //ATCMD_LOG_I("%s::%d\n",__FUNCTION__, __LINE__);
    if (g_normal_socket.qlen == 0)
        return -1;
    
    struct socket_q* item = (struct socket_q*)g_normal_socket.next;
    
    while (item != (struct socket_q*)&g_normal_socket)
    {
        if (item->socket == sd)
        {
            FD_SET(sd, &g_clr_set);
            //ATCMD_LOG_I("%s::%d, socket = %d, opt = %x\n",__FUNCTION__, __LINE__, sd);
            return sd;
        }
        item = (struct socket_q*)item->list.next;        
    }
    
    return -1;
}

int _rm_sd(int sd)
{    
    //ATCMD_LOG_I("%s::%d\n",__FUNCTION__, __LINE__);
    if (g_normal_socket.qlen == 0)
        return -1;
    
    struct socket_q* item = (struct socket_q*)g_normal_socket.next;
    
    while (item != (struct socket_q*)&g_normal_socket)
    {
        if (item->socket == sd)
        {
            list_q_remove(&g_normal_socket, (struct list_q*)item);
            free(item);
            //ATCMD_LOG_I("%s::%d, socket = %d, opt = %x\n",__FUNCTION__, __LINE__, sd);
            return sd;
        }
        item = (struct socket_q*)item->list.next;        
    }
    
    return -1;
}

int _rm_listen_sd(int sd)
{    
    //ATCMD_LOG_I("%s::%d\n",__FUNCTION__, __LINE__);
    if (g_listen_socket.qlen == 0)
        return -1;
    
    struct listen_socket_q* item = (struct listen_socket_q*)g_listen_socket.next;
    
    while (item != (struct listen_socket_q*)&g_listen_socket)
    {
        if (item->socket == sd)
        {
            list_q_remove(&g_listen_socket, (struct list_q*)item);
            free(item);
            //ATCMD_LOG_I("%s::%d, socket = %d, opt = %x\n",__FUNCTION__, __LINE__, sd);
            return sd;
        }
        item = (struct listen_socket_q*)item->list.next;        
    }
    
    return -1;
}

int update_new_listen_sd(int socket, u16 port)
{
    struct listen_socket_q* item = (struct listen_socket_q*)g_listen_socket.next;
    struct listen_socket_q* newitem = (struct listen_socket_q*)malloc(sizeof(struct listen_socket_q));
    
    if(newitem == NULL)
        return -1;
    //ATCMD_LOG_I("%s::%d, newitem = %x, socket = %d, g_listen_socket = %x\n",__FUNCTION__, __LINE__, newitem, socket, &g_listen_socket);
    newitem->socket = socket;
    newitem->port = port;
    // Insert by ordering of socket descriptor, good for finding max socket descriptor
    if(g_listen_socket.qlen == 0)
        list_q_qtail(&g_listen_socket, (struct list_q*)newitem);
    else
    {
        while ((item != (struct listen_socket_q*)&g_listen_socket) && (item->socket < socket))
            item = (struct listen_socket_q*)item->list.next;

        if(item->socket > socket)
            item = (struct listen_socket_q*)item->list.prev;        

        list_q_insert(&g_listen_socket, (struct list_q *)item, (struct list_q *)newitem);
    }
    return 0;
}

int update_new_sd(int socket, int parent_sd)
{
    struct socket_q* item = (struct socket_q*)g_normal_socket.next;
    struct socket_q* newitem = (struct socket_q*)malloc(sizeof(struct socket_q));
    
    if(newitem == NULL)
    {
        return -1;
    }
    //ATCMD_LOG_I("%s::%d, newitem = %x, socket = %d, g_normal_socket = %x\n",__FUNCTION__, __LINE__, newitem, socket, &g_normal_socket);
    
    newitem->socket = socket;
    newitem->parent_sd = parent_sd;
    // Insert by ordering of socket descriptor, good for finding max socket descriptor
    if(g_normal_socket.qlen == 0)
        list_q_qtail(&g_normal_socket, (struct list_q*)newitem);
    else
    {
        while ((item != (struct socket_q*)&g_normal_socket) && (item->socket < socket))
            item = (struct socket_q*)item->list.next;

        if(item->socket > socket)
            item = (struct socket_q*)item->list.prev;        

        list_q_insert(&g_normal_socket, (struct list_q *)item, (struct list_q *)newitem);
    }    
    return 0;
}

void update_max_sd()
{
    //ATCMD_LOG_I("%s::%d\n",__FUNCTION__, __LINE__);
    struct list_q* item;
    if (g_normal_socket.qlen != 0)
    {    
        item = g_normal_socket.prev;
        //ATCMD_LOG_I("addr:%x nsocket:%d max:%d\n", item, ((struct socket_q*)item)->socket, max_sd);
        if(max_sd < ((struct socket_q*)item)->socket)
            max_sd = ((struct socket_q*)item)->socket;        
    }
    
    if (g_listen_socket.qlen != 0)
    {    
        item = g_listen_socket.prev;
        //ATCMD_LOG_I("addr:%x lsocket:%d max:%d\n", item, ((struct listen_socket_q*)item)->socket, max_sd);
        if(max_sd < ((struct listen_socket_q*)item)->socket)
            max_sd = ((struct listen_socket_q*)item)->socket;
    }
}
int g_tcp_recv_len = 0;
OsMutex recv_len_mutex;
u8 g_MeshCoexTest = 0;

int socket_mutex_init(OsMutex *mutex)
{
    int xReturn = -1;
    OS_STATUS ret = 0;
    ret = OS_MutexInit(mutex);

    if (ret == OS_SUCCESS) {
        xReturn = 0;
    } else
        printf("!!!socket_mutex_init init fail\n");

    return xReturn;
}

static void recv_task(void *arg)
{
#if (LWIP_IPV6==1) 
    struct sockaddr_in6 addr;
#else
	struct sockaddr addr;
#endif
    socklen_t addrlen = sizeof(addr), sel_result = 0;
    fd_set r_set;
    struct timeval timeout = { .tv_sec = 10, .tv_usec = 0};
    char buf[buf_size + 1];
    OS_STATUS ret = 0;

    socket_mutex_init(&recv_len_mutex);

    recv_task_st = TASK_ST_Running;

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
				
    while(recv_task_st == TASK_ST_Running)
    {        
        FD_ZERO(&g_clr_set);
        update_max_sd();
        memcpy(&r_set, &g_r_set, sizeof(fd_set));
        sel_result = select((max_sd + 1), &r_set, NULL, NULL, &timeout);
        if (sel_result < 0)
            goto TERMINATE;
        else if (sel_result == 0)
        {
            fd_set zero;
            FD_ZERO(&zero);
            if (memcmp(&zero, &g_clr_set, sizeof(fd_set)) != 0)
            {
                struct list_q *item = NULL;                
                for(item = g_listen_socket.next; item != &g_listen_socket;)
                {
                    struct list_q *next = item->next;
                    int socket = ((struct listen_socket_q *)item)->socket;
                    if(FD_ISSET(socket, &g_clr_set))
                    {
                        list_q_remove(&g_listen_socket, item);
                        close(socket);
                        free(item);                    
                        item = NULL;                    
                        ATCMD_LOG_I("socket close: %d\n", socket);
                    }
                    item = next;
                }
                item = NULL;
                for(item = g_normal_socket.next; item != &g_normal_socket;)
                {
                    struct list_q *next = item->next;
                    int socket = ((struct socket_q *)item)->socket;
                    if(FD_ISSET(socket, &g_clr_set))
                    {
                        list_q_remove(&g_normal_socket, item);
                        close(socket);
                        free(item);                    
                        item = NULL;
                        ATCMD_LOG_I("socket close: %d\n", socket);
                    }
                    item = next;
                }
            }
            if(recv_task_st != TASK_ST_Running)
                goto TERMINATE;
        }
        else
        {   
            struct list_q *item = NULL;
            struct list_q *closeitem = NULL;
            for(item = g_listen_socket.next; item != &g_listen_socket; item = item->next)
            {
                int mainsocket = ((struct listen_socket_q *)item)->socket, forksocket = -1;                
                //printf("check listen %x, socket = %d, next = %x\n", item, mainsocket, item->next);
                
                if(closeitem != NULL)
                {
                    int former_socket = ((struct listen_socket_q *)closeitem)->socket;                    
                    list_q_remove(&g_listen_socket, closeitem);
                    close(former_socket);
                    free(closeitem);                    
                    closeitem = NULL;                    
                    ATCMD_LOG_I("socket close: %d\n", former_socket);
                }
                
                if(FD_ISSET(mainsocket, &g_clr_set))
                {
                    closeitem = item;
                    //printf("Get close item = %x\n", item);
                }
                else if(FD_ISSET(mainsocket, &r_set))
                {
                    //printf("fork here\n");
                    forksocket = accept(((struct listen_socket_q *)item)->socket, (struct sockaddr*)&addr, &addrlen);
                    if (forksocket != -1)
                    {                    
                        if(update_new_sd(forksocket, mainsocket) == 0)
                        {
                            FD_SET(forksocket, &g_r_set);
                            ATCMD_LOG_I("%s fork socket %d is from accept \n", RCV_TASK_NAME, forksocket);
                        }
                        else
                            ATCMD_LOG_I("%s failed add fork socket \n", RCV_TASK_NAME, forksocket);
                    }
                    else
                        ATCMD_LOG_I("Failed to fork socket\n");
                }                      
            }
            
            if(closeitem != NULL)
            {
                int former_socket = ((struct listen_socket_q *)closeitem)->socket;                
                list_q_remove(&g_listen_socket, closeitem);
                close(former_socket);
                free(closeitem);                    
                closeitem = NULL;
                ATCMD_LOG_I("socket close: %d\n", former_socket);
            }
                        
            item = NULL;
            for(item = g_normal_socket.next; item != &g_normal_socket; item = item->next)
            {   
                int recv_sd = ((struct socket_q *)item)->socket;                
                //printf("check data %x, socket = %d, next = %x\n", item, recv_sd, item->next);
                
                if(closeitem != NULL)
                {
                    int former_socket = ((struct socket_q *)closeitem)->socket;                    
                    list_q_remove(&g_normal_socket, closeitem);
                    close(former_socket);
                    free(closeitem);
                    closeitem = NULL;
                    ATCMD_LOG_I("socket close: %d\n", former_socket);
                }
                
                if(FD_ISSET(recv_sd, &g_clr_set))
                    closeitem = item;
                else if(FD_ISSET(recv_sd, &r_set))
                {
                    int readlen = 0;
                    int printheader = 0;

                    while((readlen = recv(recv_sd, &buf, buf_size, 0)) > 0)
                    {
                        OS_MutexLock(recv_len_mutex);
                        g_tcp_recv_len += readlen;
                        OS_MutexUnLock(recv_len_mutex);
                        if (printheader == 0)
                        {
                            if (g_MeshCoexTest)
                                ATCMD_LOG_I("RECEIVE from %d length %d \n", recv_sd, readlen);
                            else
                                ATCMD_LOG_I("RECEIVE from %d : \n", recv_sd);
                            printheader = 1;
                        }
                        buf[readlen] = 0;
                        if (!g_MeshCoexTest)
                            ATCMD_LOG_I("%s", buf);

                        if(readlen < buf_size)
                            break;
                    }

                    if ((readlen <= 0) && ((errno == ENOTCONN) || (errno == ECONNRESET) ||(errno == ECONNABORTED)))
                    {                        
                        FD_CLR(recv_sd, &g_r_set);                        
                        closeitem = item;
                    }
                }
            }
            
            if(closeitem != NULL)
            {
                int former_socket = ((struct socket_q *)closeitem)->socket;                    
                list_q_remove(&g_normal_socket, closeitem);
                close(former_socket);
                free(closeitem);
                closeitem = NULL;
                ATCMD_LOG_I("socket close: %d\n", former_socket);
			    recv_task_st = TASK_ST_Stop;
            }
        }
    }    
TERMINATE:
    while(g_normal_socket.qlen > 0)
    {
        struct list_q* item = g_normal_socket.next;
        list_q_remove(&g_normal_socket, item);
        close(((struct socket_q *)item)->socket);
        free(item);
    }

    while(g_listen_socket.qlen > 0)
    {
        struct list_q* item = g_listen_socket.next;
        list_q_remove(&g_listen_socket, item);
        close(((struct socket_q *)item)->socket);
        free(item);
    }
    FD_ZERO(&g_r_set);
    recv_task_st = TASK_ST_Term;
    recv_task_inst = NULL;
    OS_MutexDelete(recv_len_mutex);
    OS_TaskDelete(NULL);
}

void chk_socket_task()
{
    fd_set zero;
    FD_ZERO(&zero);
    if (memcmp(&zero, &g_r_set, sizeof(fd_set)) == 0)
    {
        if (recv_task_st == TASK_ST_Running)
            recv_task_st = TASK_ST_Stop;    
        while(recv_task_st != TASK_ST_Term)
            OS_MsDelay(500);
        recv_task_st = TASK_ST_Stop;
    }
}

int At_HTTPTest(stParam *param)
{
    easy_httpclient_test();
    return ERROR_SUCCESS;

}
/*---------------------------------------------------------------------------*/
void ATudp_recv(int *socket)
{
}

char g_tcp_connect_ip[ATCMD_TCP_IP_STRING_LEN] = {0};
char g_tcp_connect_port[ATCMD_TCP_PORT_STRING_LEN] = {0};

/*---------------------------------------------------------------------------*/
int At_TCPConnect (stParam *param)
{

	char *pIp = 0, *pport = 0;
    u16 port;    
    int socket;
    struct sockaddr_in s_sockaddr;
    int listen = 0;

    if (param->argc < 2) 
        return ERROR_INVALID_PARAMETER;

	pIp = param->argv[0];
	pport = param->argv[1];

	port = atoi (pport);
	if (port == 0) 
		return ERROR_INVALID_PARAMETER;    
          
    
    memset(&s_sockaddr, 0, sizeof(s_sockaddr));
    s_sockaddr.sin_family = AF_INET;
    s_sockaddr.sin_port = htons(port);
    
    //hostname convert to ip
    /*if( netconn_gethostbyname(pIp, (ip_addr_t*)&s_sockaddr.sin_addr) != 0 )
    {
        ATCMD_LOG_I("\nresolve %s fails\n", pIp);
        return ERROR_TCP_CONNECTION;
    }*/
    
    struct hostent *hp;
    hp = gethostbyname(pIp);
    
    if( hp == NULL )
    {
        ATCMD_LOG_I("\nresolve %s fails\n", pIp);
        return ERROR_TCP_CONNECTION;
    }
    
    //inet_aton(pIp, &s_sockaddr.sin_addr);
    s_sockaddr.sin_addr.s_addr = *(u32_t *)hp->h_addr; 
    s_sockaddr.sin_len = sizeof(s_sockaddr);
    
    if ((socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        ATCMD_LOG_I("Failed to create socket\n");
        return ERROR_INVALID_PARAMETER;
    }
    
    if (connect(socket, (struct sockaddr *) &s_sockaddr, sizeof(s_sockaddr)) < 0)
    {
        ATCMD_LOG_I("Failed to connect\n");
        close(socket);        
        return ERROR_INVALID_PARAMETER;
    }
    
    if(listhead_is_inited == 0)
    {
        list_q_init(&g_listen_socket);
        list_q_init(&g_normal_socket);
        listhead_is_inited = 1;
    }

    if (update_new_sd(socket, -1) != 0)
    {
        close(socket);
        ATCMD_LOG_I("%s fail to add socket\n", ATCMD_TCPCONNECT);
        return ERROR_TCP_CONNECTION;
    }
    FD_SET(socket, &g_r_set);
    
    //create th 
    if ((recv_task_inst == NULL) && (OS_TaskCreate( recv_task, RCV_TASK_NAME, 1536, &listen, OS_TASK_MIDDLE_PRIO, &recv_task_inst ) != 1))
    {
        FD_CLR(socket, &g_r_set);
        close(socket);
        _rm_sd(socket);
        ATCMD_LOG_I("%s fail to create receive task\n", ATCMD_TCPCONNECT);
        return ERROR_TCP_CONNECTION;
    }

    ATCMD_LOG_I("AT+NEWTCPCONN OK:%d\n", socket);
    return ERROR_SUCCESS;
}

char* At_TCPGetConnectIP (stParam *param)
{    
    return g_tcp_connect_ip;
}

char* At_TCPGetConnectPort (stParam *param)
{    
    return g_tcp_connect_port;
}

/*---------------------------------------------------------------------------*/
int At_TCPDisconnect (stParam *param)
{    
    int conn;
    
    if (param->argc < 1) 
    {
        return ERROR_INVALID_PARAMETER;
    }
    
	conn = atoi(param->argv[0]);
    if(FD_ISSET(conn, &g_r_set) == 0)
    {
        ATCMD_LOG_I("%s socket %d is not found\n", ATCMD_TCPDISCONNECT, conn);
        return ERROR_INVALID_PARAMETER;
    }  
    
    FD_CLR(conn, &g_r_set);
    mark_rm_sd(conn);
    if (g_MeshCoexTest)
        OS_MsDelay(200);
    else
        OS_MsDelay(2000);
    chk_socket_task();
    
    //delete th
    //OS_TaskDelete(recv_task_inst);
    //recv_task_inst = NULL;
    
    ATCMD_LOG_I("%s OK\n", ATCMD_TCPDISCONNECT);
   
    return ERROR_SUCCESS;
}
/*---------------------------------------------------------------------------*/
#if (LWIP_IPV6==1) 
int At_TCPSend6 (stParam *param)
{	
#define USE_IPV6
	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);

	//char *pIp = 0, *pport = 0;
#ifdef USE_IPV6	
	char pIp[]="fe80::7cf3:5223:71de:b760";
#else
	char pIp[]="192.168.50.138";
#endif

	char pport[]="5001";
	char pdata[]= "1234567890";
	u16 port;

	int socket;
	struct sockaddr_in6 s_sockaddr;
	int listen = 0;
		
#if 0
	pIp = param->argv[0];
	pport = param->argv[1];
#endif	
	port = atoi (pport);
	ATCMD_LOG_I("port = %d\n",port);
	
	if (port == 0) 
		return ERROR_INVALID_PARAMETER;    
	
	memset(&s_sockaddr, 0, sizeof(s_sockaddr));
#ifdef USE_IPV6
	s_sockaddr.sin6_family = AF_INET6;
#else
	s_sockaddr.sin6_family = AF_INET;
#endif
	
	
	
	s_sockaddr.sin6_port = htons(port);

#ifdef USE_IPV6
	inet6_aton(pIp, &s_sockaddr.sin6_addr);
#else
	inet_aton(pIp, &s_sockaddr.sin6_addr);
#endif
	
	s_sockaddr.sin6_len = sizeof(s_sockaddr);

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
	
	if ((socket = socket(s_sockaddr.sin6_family, SOCK_STREAM, 0)) < 0)
	{
		ATCMD_LOG_I("Failed to create socket\n");
		return ERROR_INVALID_PARAMETER;
	}

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);	
	if (connect(socket, (struct sockaddr *) &s_sockaddr, sizeof(s_sockaddr)) < 0)
	{
		ATCMD_LOG_I("Failed to connect\n");
		close(socket);		  
		return ERROR_INVALID_PARAMETER;
	}

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);

	if(listhead_is_inited == 0)
	{
		list_q_init(&g_listen_socket);
		list_q_init(&g_normal_socket);
		listhead_is_inited = 1;
	}


    if (send(socket, pdata, strlen(pdata), 0) > 0)
    {
        ATCMD_LOG_I("%s OK\n", ATCMD_TCPSEND);
        return ERROR_SUCCESS;
    }
    else
    {
        ATCMD_LOG_I("%s Fail to send\n", ATCMD_TCPSEND);
        return ERROR_TCP_CONNECTION;
    }

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);

	if (update_new_sd(socket, -1) != 0)
	{
		close(socket);
		ATCMD_LOG_I("%s fail to add socket\n", ATCMD_TCPCONNECT);
		return ERROR_TCP_CONNECTION;
	}
	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
	
	FD_SET(socket, &g_r_set);

#if 0	
	//create th 
	if ((recv_task_inst == NULL) && (OS_TaskCreate( recv_task, RCV_TASK_NAME, 1536, &listen, OS_TASK_MIDDLE_PRIO, &recv_task_inst ) != 1))
	{
		FD_CLR(socket, &g_r_set);
		close(socket);
		_rm_sd(socket);
		ATCMD_LOG_I("%s fail to create receive task\n", ATCMD_TCPCONNECT);
		return ERROR_TCP_CONNECTION;
	}
	ATCMD_LOG_I("AT+NEWTCPCONN OK:%d\n", socket);
	return ERROR_SUCCESS;
#endif

    return 0;
}
#endif
/*---------------------------------------------------------------------------*/
int replace_special_str(char *source_str)
{
    int source_str_len =strlen(source_str)+1;
    char *buffer_str = (char*)malloc(source_str_len);
    char *search_str = source_str;
    char *result_str = buffer_str;
    memset(result_str, 0, source_str_len);

    while(*search_str)
    {
        if( *search_str == '\\'  && *(search_str+1) == 'r' )
        {
            *result_str = 0x0d;
            result_str++;
            search_str+=2;
        }
        else if( *search_str == '\\'  && *(search_str+1) == 'n')
        {
            *result_str = 0x0a;
            result_str++;
            search_str+=2;
        }
        else if(*search_str == '\\'  && *(search_str+1) == '\\')
        {
            *result_str = '\\';
            result_str++;
            search_str+=2;
        }
        else
        {
            *result_str = *search_str;
            result_str++;
            search_str++;
        }
    }

    *result_str = 0;
    memcpy(source_str, buffer_str, strlen(buffer_str)+1);

    free(buffer_str);
   
    return strlen(source_str);
}
int At_TCPSend (stParam *param)
{	
	char *pdata = 0;
    int conn;
	
    if (param->argc < 2) 
    {
        return ERROR_INVALID_PARAMETER;
    }
    
	conn = atoi(param->argv[0]);
	pdata = param->argv[1];

    if(FD_ISSET(conn, &g_r_set) == 0)
    {
        ATCMD_LOG_I("%s socket %d is not found\n", ATCMD_TCPDISCONNECT, conn);
        return ERROR_INVALID_PARAMETER;
    }

    replace_special_str(pdata);
    if (send(conn, pdata, strlen(pdata), 0) > 0)

    {
        ATCMD_LOG_I("%s OK\n", ATCMD_TCPSEND);
        return ERROR_SUCCESS;
    }
    else
    {
        ATCMD_LOG_I("%s Fail to send\n", ATCMD_TCPSEND);
        return ERROR_TCP_CONNECTION;
    }
    
}

int At_TCPRecvlen(stParam *param)
{   
    char *pdata = 0;
    int conn;
    char buffer[1024];
    int ret = 0;

    if (param->argc < 1) 
    {
        return ERROR_INVALID_PARAMETER;
    }
    
    conn = atoi(param->argv[0]);
    pdata = param->argv[1];

    OS_MutexLock(recv_len_mutex);
    ret = g_tcp_recv_len;
    g_tcp_recv_len = 0;
    OS_MutexUnLock(recv_len_mutex);

    return ret;
    
}

/*---------------------------------------------------------------------------*/
#if (LWIP_IPV6==1) 
int At_TCPListen6(stParam *param)
{    
//	char  *pport = 0;
    u16 listenport;
	char pport[]="5001";
    struct sockaddr_in6 sock_addr;
    int conn = -1;

	listenport = strtoul(pport, NULL, 10);
	ATCMD_LOG_I("<%s>%d listenport=%d\n",__func__,__LINE__,listenport);

	if (listenport == 0) 
    {
		return ERROR_INVALID_PARAMETER;
	}

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);     
    if ((conn = socket(AF_INET6, SOCK_STREAM, 0)) < 0) 
    {
        ATCMD_LOG_I("%s failed to create listen socket \n", ATCMD_TCPLISTEN6);
        return ERROR_TCP_CONNECTION;
    }    
	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
	
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin6_family = AF_INET6;
	memcpy(sock_addr.sin6_addr.s6_addr, IP6_ADDR_ANY, 16);	//added for IPV6
    sock_addr.sin6_port = htons(listenport);
    sock_addr.sin6_len = sizeof(sock_addr);

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
    if (bind(conn, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) 
    {
        close(conn);
        ATCMD_LOG_I("%s listen socket failed to bind\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }
	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
    
		
    if(listen(conn, 5) != 0)
    {
        close(conn);
        ATCMD_LOG_I("%s listen socket failed to listen\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
    if(listhead_is_inited == 0)
    {
        list_q_init(&g_listen_socket);
        list_q_init(&g_normal_socket);
        listhead_is_inited = 1;
    }

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
    if(update_new_listen_sd(conn, listenport) != 0)
    {
        close(conn);
        ATCMD_LOG_I("%s fail to add socket\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }

    FD_SET(conn, &g_r_set);

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
    //create th 
    if ((recv_task_inst == NULL) && (OS_TaskCreate( recv_task, RCV_TASK_NAME, 1536, NULL, OS_TASK_MIDDLE_PRIO, &recv_task_inst ) != 1))
    {
        FD_CLR(conn, &g_r_set);
        close(conn);        
        _rm_listen_sd(conn);
        ATCMD_LOG_I("%s fail to create receive task\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }

	ATCMD_LOG_I("<%s>%d\n",__func__,__LINE__);
    return ERROR_SUCCESS;
}
#endif
/*---------------------------------------------------------------------------*/
int At_TCPListen (stParam *param)
{    
	char  *pport = 0;
    u16 listenport;
#ifndef TCPIP_UIP
    struct sockaddr_in sock_addr;
    int conn = -1;
#endif    

    if (param->argc < 1) 
    {
        return ERROR_INVALID_PARAMETER;
    }

	pport = param->argv[0];
    
	listenport = strtoul(pport, NULL, 10);

	if (listenport == 0) 
    {
		return ERROR_INVALID_PARAMETER;
	}
#ifdef TCPIP_UIP
	if(tcp_listen(listenport, ATtcp_eventhandler) == -1)
	{
		return ERROR_TCP_CONNECTION;
	}
#else       
    if ((conn = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        ATCMD_LOG_I("%s failed to create listen socket \n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }    
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(listenport);
    sock_addr.sin_len = sizeof(sock_addr);
    
    if (bind(conn, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) 
    {
        close(conn);
        ATCMD_LOG_I("%s listen socket failed to bind\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }
    
    if(listen(conn, 5) != 0)
    {
        close(conn);
        ATCMD_LOG_I("%s listen socket failed to listen\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }
    
    if(listhead_is_inited == 0)
    {
        list_q_init(&g_listen_socket);
        list_q_init(&g_normal_socket);
        listhead_is_inited = 1;
    }
    
    if(update_new_listen_sd(conn, listenport) != 0)
    {
        close(conn);
        ATCMD_LOG_I("%s fail to add socket\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }

    FD_SET(conn, &g_r_set);
    
    //create th 
    if ((recv_task_inst == NULL) && (OS_TaskCreate( recv_task, RCV_TASK_NAME, 1536, NULL, OS_TASK_MIDDLE_PRIO, &recv_task_inst ) != 1))
    {
        FD_CLR(conn, &g_r_set);
        close(conn);        
        _rm_listen_sd(conn);
        ATCMD_LOG_I("%s fail to create receive task\n", ATCMD_TCPLISTEN);
        return ERROR_TCP_CONNECTION;
    }
#endif

	if(conn == -1)
	{
		return ERROR_UDP_CONNECTION;
	}
	else
	{
		ATCMD_LOG_I("TCP Listen at Socket:%d\n", conn);
		return ERROR_SUCCESS;
	}
    return ERROR_SUCCESS;
}
/*---------------------------------------------------------------------------*/
int At_MeshCoexTest (stParam *param)
{
    char  *val = 0;

    if (param->argc < 1) 
    {
        return ERROR_INVALID_PARAMETER;
    }

    val = param->argv[0];
    g_MeshCoexTest = atoi (val);
    ATCMD_LOG_I("%s set MeshCoexTest %d\n", ATCMD_MESHCOEXTEST, g_MeshCoexTest);
    return ERROR_SUCCESS;
}

/*---------------------------------------------------------------------------*/
int At_MeshCoexConnect (stParam *param)
{
    char *pIp = 0, *pport = 0;

    if (param->argc < 2) 
    {
        return ERROR_INVALID_PARAMETER;
    }

    g_MeshCoexTest = 1;
    pIp = param->argv[0];
    pport = param->argv[1];
    memset(g_tcp_connect_ip, 0, sizeof(g_tcp_connect_ip));
    strcpy(g_tcp_connect_ip, pIp);

    memset(g_tcp_connect_port, 0, sizeof(g_tcp_connect_port));
    strcpy(g_tcp_connect_port, pport);

    ATCMD_LOG_I("%s set MeshCoexTest %d, connect %s:%s\n",
        ATCMD_MESHCOEXCONNECT, g_MeshCoexTest, g_tcp_connect_ip, g_tcp_connect_port);
    return ERROR_SUCCESS;
}

/*---------------------------------------------------------------------------*/
int At_TCPUnlisten (stParam *param)
{
	char  *pport = 0;
    u16 listenport;

    if (param->argc < 1) 
    {
        return ERROR_INVALID_PARAMETER;
    }

	pport = param->argv[0];
	
	listenport = atoi (pport);
	if (listenport == 0) 
    {
		return ERROR_INVALID_PARAMETER;
	}
#ifdef TCPIP_UIP    
	if(tcp_unlisten(listenport) == -1)
	{
		return ERROR_TCP_CONNECTION;
	}
#else
    int socket;
    socket = mark_rm_listen_sd_by_port(listenport);
    if (socket == -1)
    {
        ATCMD_LOG_I("%s listen socket doesn't exist\n", ATCMD_TCPUNLISTEN);
        return ERROR_INVALID_PARAMETER;
    }
    FD_CLR(socket, &g_r_set);
    OS_MsDelay(2000);        
    chk_socket_task();

    //delete th
    //OS_TaskDelete(recv_task_inst);
    //recv_task_inst = NULL;
    ATCMD_LOG_I("%s stop listen on port %d\n", ATCMD_TCPUNLISTEN, listenport);    
#endif
	return ERROR_SUCCESS;
}
/*---------------------------------------------------------------------------*/
int At_UDPCreate (stParam *param)
{    
	char  *pport = 0;
    u16 localport;
    int socket;
#ifndef TCPIP_UIP
    int listen = 0;
    struct sockaddr_in sock_addr;
#endif    

    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }

	pport = param->argv[0];
	
	localport = atoi (pport);
	if (localport == 0) {
		return ERROR_INVALID_PARAMETER;
	}
#ifdef TCPIP_UIP
	socket = udpcreate(localport, ATudp_recv);
#else
    if ((socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        ATCMD_LOG_I("Failed to create socket:%d\n");
        return ERROR_INVALID_PARAMETER;
    }
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(localport);
    sock_addr.sin_len = sizeof(sock_addr);
    
    if (bind(socket, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) 
    {
        close(socket);
        ATCMD_LOG_I("%s listen socket failed to bind\n", ATCMD_UDPCREATE);
        return ERROR_UDP_CONNECTION;
    }    
    
    if(listhead_is_inited == 0)
    {
        list_q_init(&g_listen_socket);
        list_q_init(&g_normal_socket);
        listhead_is_inited = 1;
    }
    
    if(update_new_sd(socket, -1) != 0)
    {
        close(socket);
        ATCMD_LOG_I("%s fail to add socket\n", ATCMD_UDPCREATE);
        return ERROR_UDP_CONNECTION;
    }
    FD_SET(socket, &g_r_set);    
    
    //create th 
    if ((recv_task_inst == NULL) && (OS_TaskCreate( recv_task, RCV_TASK_NAME, 1536, &listen, OS_TASK_MIDDLE_PRIO, &recv_task_inst ) != 1))
    {
        FD_CLR(socket, &g_r_set);
        close(socket);        
        _rm_sd(socket);
        ATCMD_LOG_I("%s fail to create receive task\n", ATCMD_UDPCREATE);
        return ERROR_UDP_CONNECTION;
    }
#endif
	if(socket == -1)
	{
		return ERROR_UDP_CONNECTION;
	}
	else
	{
		ATCMD_LOG_I("UDP Create at Socket:%d\n", socket);
		return ERROR_SUCCESS;
	}

    return ERROR_SUCCESS;
}
/*---------------------------------------------------------------------------*/
int At_UDPSend (stParam *param)
{

	int sock;
	u16 peerport;    
	char *pIp = 0, *pport = 0, *psock = 0, *pdata = 0;
#ifdef TCPIP_UIP            
    uip_ip4addr_t ipaddr;
#else
    struct sockaddr_in s_sockaddr;
#endif
	
    if (param->argc < 4) {
        return ERROR_INVALID_PARAMETER;
    }

	psock = param->argv[0];
	pIp = param->argv[1];
	pport = param->argv[2];
	pdata = param->argv[3];
    peerport = atoi (pport);
	sock = atoi(psock);
#ifdef TCPIP_UIP            
	if( uiplib_ipaddrconv(pIp, &ipaddr) == 0 )	
	{
        return ERROR_INVALID_PARAMETER;
	}
#else
    if(FD_ISSET(sock, &g_r_set) == 0)
    {
        ATCMD_LOG_I("%s socket %d is not found\n", ATCMD_TCPDISCONNECT, sock);
        return ERROR_INVALID_PARAMETER;
    } 
    memset(&s_sockaddr, 0, sizeof(s_sockaddr));
    s_sockaddr.sin_family = AF_INET;
    
    //hostname convert to ip
    /*if( netconn_gethostbyname(pIp, (ip_addr_t*)&s_sockaddr.sin_addr) != 0 )
    {
        ATCMD_LOG_I("\nresolve %s fails\n", pIp);
        return ERROR_TCP_CONNECTION;
    }*/

    struct hostent *hp;
    hp = gethostbyname(pIp);
    
    if( hp == NULL )
    {
        ATCMD_LOG_I("\nresolve %s fails\n", pIp);
        return ERROR_TCP_CONNECTION;
    }
    s_sockaddr.sin_addr.s_addr = *(u32_t *)hp->h_addr; 
    
    //inet_aton(pIp, &s_sockaddr.sin_addr);    
    s_sockaddr.sin_port = htons(peerport);
    s_sockaddr.sin_len = sizeof(s_sockaddr);
    //inet_aton(pIp, &s_sockaddr.sin_addr);;
#endif
		
#ifdef TCPIP_UIP	
	if(udpsendto(sock, pdata, strlen(pdata), &ipaddr, peerport) == -1)
#else
    if(sendto(sock, pdata, strlen(pdata), 0,(struct sockaddr *) &s_sockaddr, sizeof(s_sockaddr)) < 0)
#endif
	{
        ATCMD_LOG_I("%s Failed to send UDP:%d\n", ATCMD_UDPSEND, sock);
		return ERROR_UDP_CONNECTION;
	}
	else
	{
		return ERROR_SUCCESS;
	}
}
/*---------------------------------------------------------------------------*/
int At_UDPClose (stParam *param)
{
        
	int sock;
	
    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }
	
	sock = atoi(param->argv[0]);
#ifdef TCPIP_UIP	
	if(udpclose(sock) == -1)
    {
        ATCMD_LOG_I("%s Failed to close UDP:%d\n", ATCMD_UDPCLOSE, sock);
		return ERROR_UDP_CONNECTION;
	}
	else
	{
        ATCMD_LOG_I("%s UDP close successfully:%d\n", ATCMD_UDPCLOSE, sock);
		return ERROR_SUCCESS;
	}
#else
    if(FD_ISSET(sock, &g_r_set) == 0)
    {
        ATCMD_LOG_I("%s wrong socket id:%d\n", ATCMD_UDPCLOSE, sock);
        return ERROR_INVALID_PARAMETER;
    }
    
    FD_CLR(sock, &g_r_set);
    mark_rm_sd(sock);
    OS_MsDelay(2000);
    chk_socket_task();
    
    ATCMD_LOG_I("%s UDP close successfully:%d\n", ATCMD_UDPCLOSE, sock);
    return ERROR_SUCCESS;
#endif        
	
}
/*---------------------------------------------------------------------------*/
int At_NSLookup(stParam *param)
{

    char *pIp = 0;
    ip_addr_t ip4;
    int ret = ERROR_SUCCESS;
    
    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }

    if(get_wifi_status() == 0)
    {
        return ERROR_WIFI_CONNECTION;
    }
        
    pIp = param->argv[0];
    
    //hostname convert to ip
    struct hostent *hp;
    hp = gethostbyname(pIp);
    
    if( hp == NULL )
    {
        ATCMD_LOG_I("\nresolve %s fails\n", pIp);
        return ERROR_TCP_CONNECTION;
    }

    uint32_t peer_ip = *(u32_t *)hp->h_addr;

    ATCMD_LOG_I("\nName: %s\nAddress: %d.%d.%d.%d\n", pIp, (peer_ip>>0)& 0xFF, (peer_ip>>8)& 0xFF, (peer_ip>>16)& 0xFF, (peer_ip>>24)& 0xFF);
    return ret;    
}
int At_SNTPSync(stParam *param)
{

    int ret = ERROR_SUCCESS;
    if( get_wifi_status() == 0 )
    {
        ATCMD_LOG_I("\nPlease connect to wifi first\n");
        return ERROR_WIFI_CONNECTION;
    }
    sntp_init();
    return ret;    
}
int At_SNTPTime(stParam *param)
{
    int ret = ERROR_SUCCESS;
    unsigned int update_tick = 0;
    long update_sec = 0, update_usec = 0;    
   
    sntp_get_lasttime(&update_sec, &update_usec, &update_tick);

    if(update_sec)
    {
        unsigned int current_tick = OS_GetSysTick();
        long current_sec = update_sec + (current_tick - update_tick)/1000;
        current_sec += 8*60*60;
        ATCMD_LOG_I("\nCurrent Time: %s", ctime(&current_sec)); 
    }
    else
    {
        ret = ERROR_UNKNOWN_COMMAND;
        ATCMD_LOG_I("\nPlease execute AT+SNTP_SYNC to sync system time first\n");
    }
    
    return ret;    
}

#ifdef IPERF_ENABLE
extern int iperf( int argc, char **argv ) ;
int At_iperf_main(stParam *param)
{    
    if(get_wifi_status() == 1)
        iperf(param->argc, &param->argv);
    else
        ATCMD_LOG_I("not connect to wifi, iperf can not used\n");
}
#endif

#if LWIP_DEBUG
extern u32 g_log_module;
extern u32 g_log_min_level;
#endif

extern int ping(stParam *pParam);
int At_Ping(stParam *param)
{    
#ifdef PING_EN
    if (ping(param) < 0) {
        return ERROR_INVALID_PARAMETER;
    }
#else
    ATCMD_LOG_I("please enable PING_EN flag\n");
#endif
    return ERROR_SUCCESS;
}

extern void dhcp_rember_ip(char *rember_ip);
int At_RemberIP(stParam *param)
{    
    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }
    printf("rember ip: %s\n", param->argv[0]);
    dhcp_rember_ip(param->argv[0]);
    return ERROR_SUCCESS;
}

int At_tcp_dbg(stParam *param)
{
    int val = 0;
    bool add = 0;
#if LWIP_DEBUG
    
    if (memcmp(param->argv[0],"add", sizeof("add")) == 0)
        add = true;
    else if (memcmp(param->argv[0],"rem", sizeof("rem")) == 0)
        add = false;
    else if (memcmp(param->argv[0],"st", sizeof("st")) == 0)
    {
        ATCMD_LOG_I("g_log_module = %X, g_log_min_level = %d\n", g_log_module, g_log_min_level);
        return ERROR_SUCCESS;
    }
    else if (memcmp(param->argv[0],"lv", sizeof("lv")) == 0)
    {
        val = atoi(param->argv[1]);
        if ((val >= LWIP_DBG_LEVEL_ALL) && (val <= LWIP_DBG_MASK_LEVEL))
        {
            g_log_min_level = val;
            ATCMD_LOG_I("g_log_min_level = %d\n", g_log_min_level);
            return ERROR_SUCCESS;
        }
        else
            goto INVALID_PARAM;
    }
    else
        goto INVALID_PARAM;
        
    if (memcmp(param->argv[1],"mod", sizeof("mod")) == 0)
    {        
        if (memcmp(param->argv[2],"all", sizeof("all")) == 0)
            val = LWIP_DBG_ALL_MODULES;
        else if (memcmp(param->argv[2],"mem", sizeof("mem")) == 0)
            val = LWIP_DBG_MOD_MEM;
        else if (memcmp(param->argv[2],"socket", sizeof("socket")) == 0)
            val = LWIP_DBG_MOD_L3_SOCKET;
        else if (memcmp(param->argv[2],"api", sizeof("api")) == 0)
            val = LWIP_DBG_MOD_L3_API;
        else if (memcmp(param->argv[2],"tcp", sizeof("tcp")) == 0)
            val = LWIP_DBG_MOD_L3_TCP;
        else if (memcmp(param->argv[2],"udp", sizeof("udp")) == 0)
            val = LWIP_DBG_MOD_L3_UDP;
        else if (memcmp(param->argv[2],"ip", sizeof("ip")) == 0)
            val = LWIP_DBG_MOD_L3_IP;
        else if (memcmp(param->argv[2],"other", sizeof("other")) == 0)
            val = LWIP_DBG_MOD_L3_OTHER_PROTO;
        else
            goto INVALID_PARAM;
        
        if(true == add)
            g_log_module |= val;
        else
            g_log_module &= (~val);
        
        ATCMD_LOG_I("g_log_module = %X\n", g_log_module);
        return ERROR_SUCCESS;
    }
INVALID_PARAM:  
    ATCMD_LOG_I("tcpdbg [add/rem] mod [all/mem/socket/api/tcp/udp/ip/other],\nTCPDBG lv [0-3],\nTCPDBG st\n");
    return ERROR_INVALID_PARAMETER;
#else
    ATCMD_LOG_I("Not enable LWIP_DEBUG\n");
    return ERROR_SUCCESS;
#endif
}

#ifdef JD_CLOUD_EN
void joylink_remove_conf();
int joylink_main_start();
int At_JDDeviceRemove (stParam *param)
{
    joylink_remove_conf();
    return ERROR_SUCCESS;
}
int At_JDStart (stParam *param)
{
    ATCMD_LOG_I("joylink_main_start\n");
    joylink_main_start();
    OS_MsDelay(1000);
    ATCMD_LOG_I("joylink smartlink start\n");
    joylink_init((u8*)"9CTGIVN6AEK77EGI");    
    return ERROR_SUCCESS;
}
#endif

#ifdef SMARTCONFIG_EN
int At_SmartConfig(stParam *param)
{
    u8 enable, sc_len, key[17];
    u8 *sc = NULL;
    if (param->argc < 1)  {
        ATCMD_LOG_I("\nAT+SC [joylink/ smartlink"
#if defined(AIRKISS_EN) && (AIRKISS_EN == 1)
                "/ airkiss"
#endif
                "],[xxx]\n");
        ATCMD_LOG_I("ex: \n");
        ATCMD_LOG_I("\tAT+SC joylink,0123456789123456 => start joylink with key_code\n");
        ATCMD_LOG_I("\tAT+SC smartlink,1              => start smartlink\n");
        return ERROR_INVALID_PARAMETER;
    }

    ATCMD_LOG_I("\n");
    sc_len = sizeof(u8)*strlen(param->argv[0]);
    sc = (u8 *) malloc(sc_len);
    memcpy(sc, param->argv[0], sc_len);
    sc[sc_len] = '\0';

    if (!memcmp(sc, "default", sc_len)) {
		//do nothing
	}
#if defined(JOYLINK_EN)
	else if (!memcmp(sc, "joylink", sc_len)) {
        memcpy(key, param->argv[1], sizeof(key));
        if (strlen(param->argv[1]) == 16) {
            joylink_init(key);    
        } 
        else {
            joylink_stop();    
        }
    }
#endif
#if defined(AIRKISS_EN) && (AIRKISS_EN == 1)
    else if (!memcmp(sc, "airkiss", sc_len)) {
        strcpy((char *)key, param->argv[1]);
        if (strlen(param->argv[1]) == 16) {
            airkiss_start(NULL);
        }
        else {
            airkiss_stop();
        }
    }
#endif
#if defined(RTLINK_EN)
    else if (!memcmp(sc, "rtlink", sc_len)) {
        memcpy(key, param->argv[1], sizeof(key));
        if (strlen(param->argv[1]) == 16) {
            if (strcmp(param->argv[2],"1") == 0) {
                RTSmntSetBand(1);
            } else if (strcmp(param->argv[2],"2") == 0) {
                RTSmntSetBand(2);
            }
            RTInit(key);    
        } else if (strlen(param->argv[1]) == 4) {
            if (strcmp(param->argv[1],"stop") == 0) {
                RTStop();
            }
        }
        else {
            RTStop();    
        } 
    }
#endif
#if 0
    else if (!memcmp(sc, "smartlink", sc_len)) {
        enable = atoi(param->argv[1]);
        if (enable) {
            smartlink_init();    
        }
        else {
            smartlink_stop();    
        } 
    }
#endif
    if (sc) {
        free(sc);
        sc = NULL;    
    }

    
    return ERROR_SUCCESS;
}
#endif

#if defined(FOTA_OPTION) && (FOTA_OPTION != 0)
int At_OTASetServer (stParam *param)
{
	char *pIp = 0, *pport = 0;

	if (get_wifi_status() != 1)
		return ERROR_WIFI_CONNECTION;

    if (param->argc < 3) {
        return ERROR_INVALID_PARAMETER;
    }

	pIp = param->argv[0];
	pport = param->argv[1];
	
	if (atoi(pport) == 0) 
	{
		return ERROR_INVALID_PARAMETER;
	}

	ota_set_server(atoi(param->argv[2]), pIp, atoi(pport));

	return ERROR_SUCCESS;
}
/*---------------------------------------------------------------------------*/
int At_OTASetParam (stParam *param)
{
	char *pFilename = 0, *pPathname = 0;

	pFilename = param->argv[0];
	pPathname = param->argv[1];

	if(pFilename == 0)
		return 1;
	if(pPathname == NULL)
		ota_set_parameter(pFilename, "");
	else
		ota_set_parameter(pFilename, pPathname);
	return ERROR_SUCCESS;	
}
/*---------------------------------------------------------------------------*/
void ota_progress(int per)
{
    ATCMD_LOG_I("\rpercentage: %d\n", per);
}

void ota_status(OTA_STATUS status)
{
    if(status == OTA_SUCCESS)
    {
        ATCMD_LOG_I("ota pass: %d\n", status);
    }
    else
    {
        ATCMD_LOG_I("ota fail: %d\n", status);
    }
}

void ota_state(OTA_STATE_TYPE state)
{
    ATCMD_LOG_I("\rstate: %d\n", state);
}

int At_OTAStart (stParam *param)
{
	ota_register_progress_callback(ota_progress);
	ota_register_status_callback(ota_status);
    ota_register_state_callback(ota_state);
	ota_update();
	return ERROR_SUCCESS;
}

int At_OTAStop (stParam *param)
{
    ota_stop();
    return ERROR_SUCCESS;
}

int At_OTAReboot (stParam *param)
{
	ota_reboot();
	return ERROR_SUCCESS;
}
#endif
