#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <ctype.h>
#include "osal.h"
#include "ssv_lib.h"
//#include "soc_regs.h"
#include "soc_types.h"
#include "bsp.h"
#include "ilog.h"
#include "uart/drv_uart.h"
#include "hsuart/drv_hsuart.h"

#define M_ILOG_STATUS_TASK_SW       (0xC00C02 | (M_ILOG_STATUS_INDICATOR<<24))

#define ILOG_PORT              0 //0:debug uart, 1:data uart, only apply at blocking mode
#define HCILOG_PORT            0 //0:debug uart, 1:data uart, only apply at blocking mode
#define NONBLOCKING_PORT       0 //0:debug uart, 1:data uart, Don't work with the same port of printf.
#define ILOG_OUTPUTMODE        0 //0:nonblocking 1:blocking
#define HCILOG_OUTPUTMODE      0 //0:nonblocking 1:blocking
#define UART_MAX_FIFO 16
#define ADR_UART0_TRX_CHAR                               (0xc0000c00+0x00000000)
#define ADR_HSUART_TRX_CHAR                              (0xc0000d00+0x00000000)

log_st g_log_data = {.ring.start = 0, .ring.end = 0, .ring.size = M_ILOG_BUFFER_SIZE};

//NV_DATA idx_t g_ilog_idx_start = 0;
//NV_DATA idx_t g_ilog_idx_end = 0;
//
////#define M_STR_TEST(V) #V
//
log_level_t g_log_sw = LOG_INFO;
enum E_TASK g_log_task_sw = (0xFFFFFFFF);

void irqh_log_tx(void) ATTRIBUTE_SECTION_FAST;
void push_data_into_log_buf(const u8 *data, u16 datalen) ATTRIBUTE_SECTION_FAST;
static void push_ilog(uint32_t data) ATTRIBUTE_SECTION_FAST;

void ilog_hcilog_init()
{
    u8 uart0enable = 0;
    u8 uart1enable = 0;

#ifdef SUPPORT_ILOG
#if(ILOG_OUTPUTMODE == 0)
#if(ILOG_PORT == 0)
    uart0enable = 1;
#elif(ILOG_PORT == 1)
    uart1enable = 1;
#endif
#elif(ILOG_OUTPUTMODE == 1)
#if(NONBLOCKING_PORT == 0)
    uart0enable = 1;
#elif(NONBLOCKING_PORT == 1)
    uart1enable = 1;
#endif
#endif
#endif

#ifdef SUPPORT_HCILOG
#if(HCILOG_OUTPUTMODE == 0)
#if(HCILOG_PORT == 0)
    uart0enable = 1;
#elif(HCILOG_PORT == 1)
    uart1enable = 1;
#endif
#elif(HCILOG_OUTPUTMODE == 1)
#if(NONBLOCKING_PORT == 0)
    uart0enable = 1;
#elif(NONBLOCKING_PORT == 1)
    uart1enable = 1;
#endif
#endif
#endif
    printf("init uart0:%d uart1:%d\n", uart0enable, uart1enable);
    if(uart0enable == 1)
    {
#if(UART_IO_NUM != 0)
        drv_uart_init();
        drv_uart_sw_rst();
        drv_uart_set_fifo(HSUART_INT_RX_FIFO_TRIG_LV_1, 0);
        drv_uart_set_format (115200, HSUART_WLS_8, HSUART_STB_1, HSUART_PARITY_DISABLE);
#endif
    }

    if(uart1enable == 1)
    {
#if(UART_IO_NUM != 1)
        drv_hsuart_init();
        drv_hsuart_sw_rst();
        drv_hsuart_set_fifo(HSUART_INT_RX_FIFO_TRIG_LV_1);
        drv_hsuart_set_format (115200, HSUART_WLS_8, HSUART_STB_1, HSUART_PARITY_DISABLE);
#endif
    }
}

void irqh_log_tx(void) {

    u32 vidx_r;
    u32 vidx_r_end;
    u32 idx_r;
    u32 cnt_r;

    vidx_r        = g_log_data.ring.start;
    vidx_r_end  = g_log_data.ring.end;

    cnt_r = 0;
    while((cnt_r < UART_MAX_FIFO) && (vidx_r != vidx_r_end)) {
#if(NONBLOCKING_PORT == 0)
        REG32(ADR_UART0_TRX_CHAR) = g_log_data.ring.buffer[vidx_r];
#else
        REG32(ADR_HSUART_TRX_CHAR) = g_log_data.ring.buffer[vidx_r];
#endif
        vidx_r = M_INC_INDEX(vidx_r);
        cnt_r++;
    }
    g_log_data.ring.start = vidx_r;
    g_log_data.ring.size += cnt_r;

    // turn off uart tx empty notification
    if(vidx_r == vidx_r_end) {
#if(NONBLOCKING_PORT == 0)
        drv_uart_register_isr (UART_TX_THRL_IE, NULL);
#else
        drv_hsuart_register_isr (HSUART_THR_EMPTY_IE, NULL);
#endif
    }
}

void push_data_into_log_buf(const u8 *data, u16 datalen)
{
    int i;
    
    for(i = 0; i < datalen; i++)
    {
        g_log_data.ring.buffer[g_log_data.ring.end] = data[i];
        g_log_data.ring.end = M_INC_INDEX(g_log_data.ring.end);
    }
    g_log_data.ring.size -= datalen;

#if(NONBLOCKING_PORT == 0)
    drv_uart_register_isr (UART_TX_THRL_IE, irqh_log_tx);
#else
    drv_hsuart_register_isr (HSUART_THR_EMPTY_IE, irqh_log_tx);
#endif
}

int push_data_into_log_buf_ex(const u8 *data, int datalen)
{
    if(GET_SIZE(g_log_data.ring) >= datalen)
    {
        push_data_into_log_buf(data, (u16)datalen);
        return datalen;
    }

    return 0;
}

#define invert_endian(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
        ((((unsigned long)(n) & 0xFF00)) << 8) | \
        ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
        ((((unsigned long)(n) & 0xFF000000)) >> 24))

static void push_ilog_block(uint32_t data)
{
    uint32_t big_endian = invert_endian(data);
#if (ILOG_PORT == 0)
    hal_uart_write_fifo((uint8_t *)&big_endian, 4, UART_BLOCKING);
    //while (GET_TX_EMPTY == 0) ;
    //REG32(ADR_UART_DATA) = (data & 0xFF000000) >> 24;
    //REG32(ADR_UART_DATA) = (data & 0x00FF0000) >> 16;
    //REG32(ADR_UART_DATA) = (data & 0x0000FF00) >> 8;
    //REG32(ADR_UART_DATA) = (data & 0x000000FF) >> 0;
#else
    hal_hsuart_write_fifo((uint8_t *)&big_endian, 4, HSUART_BLOCKING);
    //while (GET_HSUART_THRE == 0) ;
    //REG32(ADR_HSUART_TRX_CHAR) = (data & 0xFF000000) >> 24;
    //REG32(ADR_HSUART_TRX_CHAR) = (data & 0x00FF0000) >> 16;
    //REG32(ADR_HSUART_TRX_CHAR) = (data & 0x0000FF00) >> 8;
    //REG32(ADR_HSUART_TRX_CHAR) = (data & 0x000000FF) >> 0;
#endif
}

static void push_ilog(uint32_t data)
{
    u8 tmpdata[4];
#if ((ILOG_OUTPUTMODE == 1) || (ILOG_PORT == 0))
    push_ilog_block(data);
#else
    if (GET_SIZE_U32(g_log_data.ring) > 0)
    {
//        push_data_into_log_buf((u8 *)&data, 4);

        tmpdata[0] = (data & 0xFF000000) >> 24;
        tmpdata[1] = (data & 0x00FF0000) >> 16;
        tmpdata[2] = (data & 0x0000FF00) >> 8;
        tmpdata[3] = (data & 0x000000FF);
        push_data_into_log_buf(tmpdata, 4);
    }
#endif
}

/*
 */
int icomm_memdump(uint8_t severity, uint8_t *ptr, int len)
{
    uint8_t reserved = 0, i;
    uint32_t data;
    if (len <= 0) {
        return -1;
    }
    OS_EnterCritical();
    if (((len>>2)+1) >= GET_SIZE_U32(g_log_data.ring)) {
        OS_ExitCritical();
        return -1;
    }
    for (i=0;i<len;i++) {
        reserved ^= ptr[i];
    }
    data = (M_ILOG_DUMP_INDICATOR << 24) | (severity << 16) | (len<<8) | (reserved);
    push_ilog(data);
    //push_ilog(M_ILOG_INDICATOR);
    //push_ilog(severity);
    //push_ilog(len);
    //for (i=0;i<len;i++) {
    //    reserved ^= ptr[i];
    //}
    //push_ilog(reserved);

    for (i=0;i<(len-3);i+=4) {
    //for (i=0;i<((len+3)>>2);i++) {
        data = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
        push_ilog(data);
        ptr+=4;
        //push_ilog(ptr[i]);
    }
    data = 0;
    switch (len & 0x3) {
        case 3:
            data = (ptr[2] << 8);
        case 2:
            data |= (ptr[1] << 16);
        case 1:
            data |= (ptr[0] << 24);
            push_ilog(data);
            break;
    }

    //CONDOR_DAT0_UART_REG->DAT0_UART_IER |= (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_TX_THR_IE_Pos) | (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_THR_EMPTY_IE_Pos);
//    DBG_ENABLE_IER();
    OS_ExitCritical();
    return 0;
}

int icomm_log(int param_count, ...)
{
    int32_t i;
    uint32_t val, data;
    va_list params;
    if (param_count < 2)
    {
        return -1;
    }
    va_start(params, param_count);
    //ind, severity, variable count, ???
    val = va_arg(params, uint32_t); // severity
    OS_EnterCritical();
    if (GET_SIZE_U32(g_log_data.ring) < param_count+1)
    {
        OS_ExitCritical();
        va_end(params);
        return -1;
    }
    data = (M_ILOG_INDICATOR << 24) | ((val & 0xFF) << 16) | ((param_count & 0xFF)<<8);
    push_ilog(data);
    for (i = 1; i < param_count; i++)
    {
        val = va_arg(params, uint32_t);
        push_ilog(val);
        //printf("get param is %u\n", val);
    }

//    DBG_ENABLE_IER();
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER |= (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_TX_THR_IE_Pos) | (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_THR_EMPTY_IE_Pos);
    OS_ExitCritical();
    va_end(params);
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER_b.DAT0_THR_EMPTY_IE = 1;
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER_b.DAT0_TX_THR_IE = 1;
    return 0;
    //printf("end\n");
}

int icomm_blocking_log(int param_count, ...)
{
    int32_t i;
    uint32_t val, data;
    va_list params;
    
    if (param_count < 2)
    {
        return -1;
    }
    va_start(params, param_count);
    //ind, severity, variable count, ???
    val = va_arg(params, uint32_t); // severity
    OS_EnterCritical();

    data = (M_ILOG_INDICATOR << 24) | ((val & 0xFF) << 16) | ((param_count & 0xFF)<<8);
    push_ilog_block(data);

    for (i = 1; i < param_count; i++)
    {
        val = va_arg(params, uint32_t);
        push_ilog_block(val);
    }

    OS_ExitCritical();
    va_end(params);
    return 0;
    //printf("end\n");
}

int icomm_status(int status_id, int status) {
    OS_EnterCritical();
    if (GET_SIZE_U32(g_log_data.ring) < 2)
    {
        OS_ExitCritical();
        return -1;
    }
    push_ilog(status_id);
    push_ilog(status);
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER_b.DAT0_THR_EMPTY_IE = 1;
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER_b.DAT0_TX_THR_IE = 1;
//    DBG_ENABLE_IER();
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER |= (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_TX_THR_IE_Pos) | (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_THR_EMPTY_IE_Pos);
    OS_ExitCritical();
    return 0;
}

int icomm_string(const uint8_t *ptr)
{
    int i;
    uint32_t data;
    int len = strlen((char*)ptr);
    OS_EnterCritical();

    if ((len>>2) >= GET_SIZE_U32(g_log_data.ring) || len <= 0) {
        OS_ExitCritical();
        return -1;
    }
    for (i=0;i<(len-3);i+=4) {
    //for (i=0;i<((len+3)>>2);i++) {
        data = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
        push_ilog(data);
        ptr+=4;
        //push_ilog(ptr[i]);
    }
    data = 0;
    switch (len & 0x3) {
        case 3:
            data = (ptr[2] << 8);
        case 2:
            data |= (ptr[1] << 16);
        case 1:
            data |= (ptr[0] << 24);
            push_ilog(data);
            break;
    }
//    DBG_ENABLE_IER();
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER |= (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_TX_THR_IE_Pos) | (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_THR_EMPTY_IE_Pos);
    OS_ExitCritical();
    return 0;
}

int icomm_stringln(const uint8_t *ptr)
{
    int i;
    uint32_t data = 0;
    int len = strlen((char*)ptr); // add enter.
    OS_EnterCritical();
    if (((len+1)>>2) >= GET_SIZE_U32(g_log_data.ring) || len <= 0) {
        OS_ExitCritical();
        return -1;
    }
    for (i=0;i<(len-3);i+=4) {
    //for (i=0;i<((len+3)>>2);i++) {
        data = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
        push_ilog(data);
        ptr+=4;
        //push_ilog(ptr[i]);
    }
    switch (len & 0x3) {
        case 3:
            data = ((ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ('\n' & 0xFF));
            break;
        case 2:
            data = ((ptr[0] << 24) | (ptr[1] << 16) | (('\n' & 0xFF) << 8));
            break;
        case 1:
            data = (ptr[0] << 24) | (('\n' & 0xFF) << 16);
            break;
        case 0:
            data = ('\n' & 0xFF) << 24;
            break;
    }
    push_ilog(data);
//    DBG_ENABLE_IER();
    //CONDOR_DAT0_UART_REG->DAT0_UART_IER |= (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_TX_THR_IE_Pos) | (1<<DAT0_UART_REG_DAT0_UART_IER_DAT0_THR_EMPTY_IE_Pos);
    OS_ExitCritical();
    return 0;
}

void ilog_echo(s32 argc, s8 **argv) {
    s32 i;
    ILOG(LOG_INFO, "call echo function!!!\n");
    for (i = 0; i < argc; i++) {
        ILOG(LOG_INFO, "argv[%d] = ", i);
        icomm_stringln((uint8_t *)argv[i]);
    }
}

uint32_t g_timestamp = 0;

void ilog_timestamp(s32 argc, s8 **argv) {
    ILOG(LOG_INFO, "call timestamp\ntime: %d\n", g_timestamp);
}

void ilog_level(s32 argc, s8 **argv) {
    if (argc < 1) {
        ILOG_INFO("The level setup failed.\n");
    } else {
        int tmp = atoi((char *)argv[0]);
        if (tmp <= LOG_VERBOSE && tmp >= LOG_CRIT) {
            g_log_sw = tmp;
            ILOG(LOG_CRIT, "setup log level %d success!!\n", tmp);
        } else {
            ILOG(LOG_CRIT, "setup log level %d failed!!\n", tmp);
        }
        //ILOG_INFO("try to setup!!! %d\n", tmp);
    }
}

void ilog_task(s32 argc, s8 **argv) {
    if (argc < 1) {
        icomm_status(M_ILOG_STATUS_TASK_SW, g_log_task_sw);
    } else {
        int tmp = atoi((char *)&argv[0][2]);
        if (argv[0][0] == 's') {
            g_log_task_sw |= tmp;
        } else {
            g_log_task_sw &= ~tmp;
        }
//        ILOG(LOG_CRIT, "setup task switch 0x%X success!!\n", g_log_task_sw);
//        icomm_status(M_ILOG_STATUS_TASK_SW, g_log_task_sw);
        //ILOG_INFO("try to setup!!! %d\n", tmp);
    }
}

void ilog_reg(s32 argc, s8 **argv)
{
#if 0
    u32 addr, value, count;
    int s;

    /* reg [r|w] [address] [value|word-count] */


    if (argc == 4 && strcmp((char *)argv[1], "w")==0) {
        /* reg w <address> <word_value> */
        if (argv[2][0]=='0' && (argv[2][1]=='x'||argv[2][1]=='X')){
            argv[2][1] = '0';
        }
        
        addr = strtol((char *)argv[2], NULL, 16);
        addr = 4 * ssv_div(addr ,4);

        if (argv[3][0]=='0' && (argv[3][1]=='x'||argv[3][1]=='X')){
            argv[3][1] = '0';
        }    

        value = strtol((char *)argv[3], NULL, 16);

        //REG32(addr) = value;
        //printf("[0x%08x]:%08x " ,addr , REG32(addr));

        PHY_WRITE(addr,value);
        ILOG(LOG_INFO, "[0x%08x] <- 0x%08x\n" ,addr , PHY_READ(addr));

        return ;
    }
    
    if ((argc==4||argc==3) && strcmp((char *)argv[1], "r")==0) {
        /* reg r <address> <word_count> */
        count = (argc==3)? 1: strtol((char *)argv[3], NULL, 10);
        if (argv[2][0]=='0' && (argv[2][1]=='x'||argv[2][1]=='X')){
            argv[2][1] = '0';
        }
        
        addr = strtol((char *)argv[2], NULL, 16);
        addr = 4 * ssv_div(addr ,4);

        for(s=0; s<count; s++, addr+=4) {
            if(ssv_mod(s,8) == 0){ 
                ILOG(LOG_INFO, "[0x%08x] -> \n" ,addr);
            }            
            ILOG(LOG_INFO, "0x%08x\n" , PHY_READ(addr));
            //printf("%08x " , REG32(addr));
            if (ssv_mod(s+1,8)==0){
                ILOG(LOG_INFO, "\n");
            }
        }
        return ;
    }

    ILOG(LOG_INFO, "Usage: reg [r|w] <reg_addr> [value|word-count]\n");
#endif
}

void ouput_hcilog(u8 direct, u8 *cmd, u8 cmdlen) ATTRIBUTE_SECTION_FAST;
void ouput_hcilog_2(u8 direct, u8 cmdtype, u8 *cmd, u8 cmdlen) ATTRIBUTE_SECTION_FAST;
void ouput_hcilog_2(u8 direct, u8 cmdtype, u8 *cmd, u8 cmdlen)
{
    u8 packetflag = 0, outputlen, i, offset = 0;
    u8 outlen = cmdlen + 1;
    u8 header[4];

    if((cmdtype == 0x1) || (cmdtype == 0x4))
    {
        packetflag |= 0x2;
    }

    if(direct == DIR_CTRL_TO_HOST)
    {
        packetflag |= 0x1;
    }

    OS_EnterCritical();

    header[0] = 0xC1;
    header[1] = cmdlen + 1;
    header[2] = packetflag;
    header[3] = cmdtype;
    //output packet record
#if (HCILOG_OUTPUTMODE == 1)
#if (HCILOG_PORT == 0)
    hal_uart_write_fifo((uint8_t *)header, 4, UART_BLOCKING);
    hal_uart_write_fifo((uint8_t *)cmd, cmdlen, UART_BLOCKING);
#elif (HCILOG_PORT == 1)
    hal_hsuart_write_fifo((uint8_t *)header, 4, UART_BLOCKING);
    hal_hsuart_write_fifo((uint8_t *)cmd, cmdlen, UART_BLOCKING);
#endif
#else
    if(GET_SIZE(g_log_data.ring) >= cmdlen + 4)
    {
        push_data_into_log_buf(header, 4);
        push_data_into_log_buf(cmd, cmdlen);
    }
#endif
    OS_ExitCritical();
}

void ouput_hcilog(u8 direct, u8 *cmd, u8 cmdlen)
{
    ouput_hcilog_2(direct, cmd[0], cmd + 1, cmdlen - 1);
}

