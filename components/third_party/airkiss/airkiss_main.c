#include "airkiss.h"
#include "airkiss_main.h"
#include "smart_config.h"
#include "ssv_lib.h"
#include "wifi_api.h"
#include "logger.h"
#include "lwip/sockets.h"

#define PRINT_AIRKISS_TAG LOG_TAG_AIRKISS

#define AIRKISS_KEY	"1234567890123456"
#define SCAN_CH_TIME_MS 80
#define LOCK_CH_TIMEOUT_MS 10000
//#define SUPPORT_5G

static int cur_ch_idx = 0;
static int airkiss_state = 0;
static u8 g_airkiss_key[32];
static airkiss_result_t airkiss_wifi_result;
static OsTimer ch_change_timer = NULL;
static OsTimer ch_lock_timeout_timer = NULL;

airkiss_context_t air_context;
const airkiss_config_t air_conf = {
    (airkiss_memset_fn)&memset,
    (airkiss_memcpy_fn)&memcpy,
    (airkiss_memcmp_fn)&memcmp,
    (airkiss_printf_fn)&printf
};

typedef struct _ch_scan_list_t{
    int ch;
    int type;
}ch_scan_list;

static void airkiss_reset(void);

const ch_scan_list ch_list[] = {
    {1  ,NL80211_CHAN_HT40PLUS},
    {6  ,NL80211_CHAN_HT40PLUS},
    {6  ,NL80211_CHAN_HT40MINUS},
    {11  ,NL80211_CHAN_HT40MINUS},
    {2  ,NL80211_CHAN_HT40PLUS},
    {7  ,NL80211_CHAN_HT40PLUS},
    {7  ,NL80211_CHAN_HT40MINUS},
    {12  ,NL80211_CHAN_HT40MINUS},
    {3  ,NL80211_CHAN_HT40PLUS},
    {8  ,NL80211_CHAN_HT40PLUS},
    {8  ,NL80211_CHAN_HT40MINUS},
    {13  ,NL80211_CHAN_HT40MINUS},
    {4  ,NL80211_CHAN_HT40PLUS},
    {9  ,NL80211_CHAN_HT40PLUS},
    {9  ,NL80211_CHAN_HT40MINUS},
    {5  ,NL80211_CHAN_HT40PLUS},
    {5  ,NL80211_CHAN_HT40MINUS},
    {10  ,NL80211_CHAN_HT40MINUS},

#ifdef SUPPORT_5G	
    {36,NL80211_CHAN_HT40PLUS}, /* Channel 36 */
    {40,NL80211_CHAN_HT40MINUS}, /* Channel 40 */
    {44,NL80211_CHAN_HT40PLUS}, /* Channel 44 */
    {48,NL80211_CHAN_HT40MINUS}, /* Channel 48 */
    {52,NL80211_CHAN_HT40PLUS}, /* Channel 52 */
    {56,NL80211_CHAN_HT40MINUS}, /* Channel 56 */
    {60,NL80211_CHAN_HT40PLUS}, /* Channel 60 */
    {64,NL80211_CHAN_HT40MINUS}, /* Channel 64 */
    {100,NL80211_CHAN_HT40PLUS}, /* Channel 100 */
    {104,NL80211_CHAN_HT40MINUS}, /* Channel 104 */
    {108,NL80211_CHAN_HT40PLUS}, /* Channel 108 */
    {112,NL80211_CHAN_HT40MINUS}, /* Channel 112 */
    {116,NL80211_CHAN_HT40PLUS}, /* Channel 116 */
    {120,NL80211_CHAN_HT40MINUS}, /* Channel 120 */
    {128,NL80211_CHAN_HT40PLUS}, /* Channel 128 */
    {132,NL80211_CHAN_HT40MINUS}, /* Channel 132 */
    {136,NL80211_CHAN_HT40PLUS}, /* Channel 136 */
    {140,NL80211_CHAN_HT40MINUS}, /* Channel 140 */
    {149,NL80211_CHAN_HT40PLUS}, /* Channel 149 */
    {153,NL80211_CHAN_HT40MINUS}, /* Channel 153 */
    {157,NL80211_CHAN_HT40PLUS}, /* Channel 157 */
    {161,NL80211_CHAN_HT40MINUS}, /* Channel 161 */
    {165,NL80211_CHAN_HT20}, /* Channel 165 */
#endif
};

extern OsBufQ xwificonnque;

void airkiss_ch_change_cb(void)
{
    airkiss_change_channel(&air_context);
}

void airkiss_conncet_ack(unsigned char randomVal){
    char  *pport = 0;
    u16 localport;
    int socket;
    struct sockaddr_in sock_addr;
    localport = 10000;

    if ((socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        log_e(PRINT_AIRKISS_TAG, "Failed to create socket:%d\n");
        return;
    }

    const int opt = 1;
    int nb = 0;
    nb = setsockopt(socket, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
    if(nb == -1)
    {
        log_e(PRINT_AIRKISS_TAG, "Failed to create socket:%d\n");
        return;
    }

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(localport);
    sock_addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);
    sock_addr.sin_len = sizeof(sock_addr);

    for(int i = 0; i < 100; i++){
        int ret = sendto(socket, &randomVal, sizeof(randomVal), 0, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
        if(ret >= 0) {
            log_i(PRINT_AIRKISS_TAG, "ok random:%d\n",randomVal);
            close(socket);
            return;
        }
        OS_MsDelay(2);
    }
    log_i(PRINT_AIRKISS_TAG, "send random data NG\n");
}

void airkisswificbfunc(WIFI_RSP *msg)
{
    log_i(PRINT_AIRKISS_TAG, "=========\n");
    log_i(PRINT_AIRKISS_TAG, "joylinkwificbfunc wifistatus = %d\n", msg->wifistatus);
    
    uint8_t dhcpen;
    u8 mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

    if(msg->wifistatus == 1) {
        if(msg->id == 0)
            get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        else
            get_if_config_2("et1", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        log_i(PRINT_AIRKISS_TAG, "Wifi Connect\n");
        log_i(PRINT_AIRKISS_TAG, "STA%d:\n", msg->id);
        log_i(PRINT_AIRKISS_TAG, "mac addr        - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        log_i(PRINT_AIRKISS_TAG, "ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        log_i(PRINT_AIRKISS_TAG, "netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        log_i(PRINT_AIRKISS_TAG, "default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        log_i(PRINT_AIRKISS_TAG, "DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
        airkiss_conncet_ack(airkiss_wifi_result.random);
    } else {
        log_i(PRINT_AIRKISS_TAG, "Wifi Disconnect\n");
    }
}

static void airkiss_set_state(int state) {
    airkiss_state = state;
}

static int airkiss_get_state(void) {
    return airkiss_state;
}

void airkiss_connect_ap_task(void *args)
{
    DUT_wifi_start(DUT_STA);
    while(xwificonnque==NULL) {
        OS_MsDelay(5);
    }
    wifi_connect_active_3((u8 *)airkiss_wifi_result.ssid, airkiss_wifi_result.ssid_length,(u8 *)airkiss_wifi_result.pwd,airkiss_wifi_result.pwd_length,5,0,NULL,airkisswificbfunc);

    OS_TaskDelete(NULL);
    
    return;
}
int airkiss_connect_ap(airkiss_result_t *pResult)
{
    int ret = 0;
    memset(&airkiss_wifi_result, 0, sizeof(airkiss_wifi_result));
    memcpy(&airkiss_wifi_result, pResult, sizeof(airkiss_wifi_result));
    OS_TaskCreate(airkiss_connect_ap_task, "airkiss_connect_ap_task", 512, NULL, OS_TASK_LOW_PRIO, NULL);
    return ret;
}

void airkiss_result(void)
{
    airkiss_result_t air_result;
    airkiss_get_result(&air_context, &air_result);
    if(air_result.pwd_length == 1)//if ap is open, pwd length is zero, otherwise connect will be fail
        air_result.pwd_length = 0;
    log_i(PRINT_AIRKISS_TAG, "# airkiss get result ################\n");
    log_i(PRINT_AIRKISS_TAG, "# SSID: %s, len: %d\n", air_result.ssid, air_result.ssid_length);
    log_i(PRINT_AIRKISS_TAG, "# PAWD: %s, len: %d\n", air_result.pwd,  air_result.pwd_length);
    log_i(PRINT_AIRKISS_TAG, "#####################################\n");

    airkiss_connect_ap(&air_result);
}

static void ch_lock_timeout_handler(void)
{
    if(ch_lock_timeout_timer != NULL) {
        OS_TimerDelete(ch_lock_timeout_timer);
        ch_lock_timeout_timer = NULL;
    }
    memset(&air_context,0 ,sizeof(air_context));
    airkiss_reset();
    OS_TimerStart(ch_change_timer);
}

static void airkiss_sniffer_cb(packetinfo *packet)
{
    airkiss_status_t ret = AIRKISS_STATUS_CONTINUE;
    struct ieee80211_hdr_3addr  hdr;
    struct ieee80211_hdr_3addr *data = (struct ieee80211_hdr_3addr *)packet->data;

    if(data == NULL && packet->len>=sizeof(struct ieee80211_hdr_3addr)){
        data=(struct ieee80211_hdr_3addr *)(&hdr);
        memcpy(data->addr1,gwifistatus.local_mac[0],sizeof(data->addr1));
        memcpy(data->addr2,gwifistatus.local_mac[1],sizeof(data->addr2));
        memset(data->addr3,0xff,sizeof(data->addr3));
    }

    ret = airkiss_recv(&air_context, data, (unsigned short)packet->len);
    if(ret == AIRKISS_STATUS_CHANNEL_LOCKED) {
        OS_TimerStop(ch_change_timer);
        log_i(PRINT_AIRKISS_TAG, "airkiss channel locked\n");
        log_i(PRINT_AIRKISS_TAG, "lock ch: %d\n", ch_list[cur_ch_idx].ch);
        OS_TimerCreate(&ch_lock_timeout_timer, LOCK_CH_TIMEOUT_MS, (u8)FALSE, NULL, (OsTimerHandler)ch_lock_timeout_handler);
        OS_TimerStart(ch_lock_timeout_timer);
    } else if(ret == AIRKISS_STATUS_COMPLETE) {
        log_i(PRINT_AIRKISS_TAG, "airkiss status complete\n");
        airkiss_stop();
        airkiss_result();
    }
}


static void ch_change_handler(void)
{
    wifi_set_channel(ch_list[cur_ch_idx].ch, ch_list[cur_ch_idx].type);
    airkiss_ch_change_cb();
    OS_TimerStart(ch_change_timer);
    cur_ch_idx ++;
    if(cur_ch_idx >= (sizeof(ch_list)/sizeof(ch_list[0]))){
        cur_ch_idx = 0;
    }
}

static int init_scan_ch_timer(void)
{
    if( OS_TimerCreate(&ch_change_timer, SCAN_CH_TIME_MS, (u8)FALSE, NULL, (OsTimerHandler)ch_change_handler) == OS_FAILED)
        return OS_FAILED;

    OS_TimerStart(ch_change_timer);
    return OS_SUCCESS;
}

static void airkiss_reset(void){
    int ret = 0;
    ret = airkiss_init(&air_context, &air_conf);
    if (ret) {
        log_e(PRINT_AIRKISS_TAG, "airkiss_init failed: %d\n", ret);
        return;
    }
    airkiss_set_state(1);
#if AIRKISS_ENABLE_CRYPT
    ret = airkiss_set_key(&air_context, g_airkiss_key, 16);
    if (ret) {
        log_e(PRINT_AIRKISS_TAG, "airkiss_set_key failed: %d\n", ret);
        return;
    }
#endif
}

void airkiss_start(u8 *key)
{
    u8 *version = NULL;
    int ret = 0;
    if(airkiss_get_state() == 1) {
        log_e(PRINT_AIRKISS_TAG, "airkiss already run\n");
        return;
    }
    airkiss_set_state(1);
    DUT_wifi_start(DUT_NONE);
    OS_MsDelay(400);
    version = (u8 *)airkiss_version();
    log_i(PRINT_AIRKISS_TAG, "%s: version %s\n", __func__, version);
    ret = airkiss_init(&air_context, &air_conf);
    if (ret) {
        log_e(PRINT_AIRKISS_TAG, "airkiss_init failed: %d\n", ret);
        airkiss_set_state(0);
        return;
    }
#if AIRKISS_ENABLE_CRYPT
    if(key == NULL) {
        strcpy((char *)g_airkiss_key, (char *)AIRKISS_KEY);//use default key
    } else {
        if(strlen((char *)key) == 16) {
            strcpy((char *)g_airkiss_key, (char *)key);
        } else {
            log_e(PRINT_AIRKISS_TAG, "airkiss key len failed: (%d %d)\n", ret, strlen((char *)key));
            airkiss_set_state(0);
            return;
        }
    }
    ret = airkiss_set_key(&air_context, g_airkiss_key, 16);
    if (ret) {
        log_e(PRINT_AIRKISS_TAG, "airkiss_set_key failed: %d\n", ret);
        airkiss_set_state(0);
        return;
    }
#endif

    cur_ch_idx = 0;
    attach_sniffer_cb(RECV_DATA_BCN, &airkiss_sniffer_cb, 512);
    init_scan_ch_timer();
    start_sniffer_mode();
}

void airkiss_stop(void)
{
    if(airkiss_get_state() == 0) {
        log_e(PRINT_AIRKISS_TAG, "airkiss not run, don't need stop\n");
        return;
    }

    log_i(PRINT_AIRKISS_TAG, "%s\n", __func__);
    if (ch_change_timer) {
        OS_TimerStop(ch_change_timer);
        OS_TimerDelete(ch_change_timer);
        ch_change_timer = NULL;
    }
    if(ch_lock_timeout_timer != NULL) {
        OS_TimerStop(ch_lock_timeout_timer);
        OS_TimerDelete(ch_lock_timeout_timer);
        ch_lock_timeout_timer = NULL;
    }
    deattach_sniffer_cb();
    stop_sniffer_mode();
    airkiss_set_state(0);
    DUT_wifi_start(DUT_STA);
    OS_MsDelay(200);
}
