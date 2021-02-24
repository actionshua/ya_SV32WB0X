
#include <stdio.h>
#include "soc_types.h"
#include "osal.h"
#include "cli.h"
#include "cli_cmd.h"
#include <attrs.h>
#include "sys/intc.h"
#include <drv_spislv.h>

/*---------------------------------- CMDs -----------------------------------*/
#define SPI_PORT DRV_SPISLV_0  

//OsEvent spi_slv_data_ready = NULL;
//uint8_t g_slv_rx_buf[1024] = {0}; 
//int g_slv_rx_cnt = 0;

uint8_t *spi_rx_buf;  
uint8_t *spi_tx_buf;
uint8_t dump_data = 0;

int test_spi_slave_mcu(int32_t argc, char *argv[]) 
{

    uint8_t ret = 0; 
    uint32_t i = 0;
    uint8_t compare_error = 0;
    
    uint8_t cpha;
    uint8_t cpol;
    uint32_t data_length;
    
    if (argc != 4) 
    {
        printf("Usage           : %s <length> <cpha> <cpol>\n", argv[0]);
        printf("<length>        : data length\n");
        printf("<cpha>          : CPHA(0, 1)\n");
        printf("<cpol>          : CPOL(0, 1)\n");
        return 0;
    }
    
    data_length = strtoul(argv[1], NULL, 10);
    cpha = strtoul(argv[2], NULL, 10);
    cpol = strtoul(argv[3], NULL, 10);

    drv_spislv_init(SPI_PORT, cpha, cpol);

    spi_tx_buf = OS_MemAlloc(data_length);
    spi_rx_buf = OS_MemAlloc(data_length);
   
    for (i = 0; i < data_length; i++) 
    {
        if(dump_data)
        {
            //fill random
            spi_tx_buf[i] = OS_Random();
            spi_rx_buf[i] = 0;
        }
        else
        {
        spi_tx_buf[i] = i % 256;
        spi_rx_buf[i] = 0;
        }
    } 

    //block function
    int read_len = drv_spislv_trx(SPI_PORT, spi_tx_buf, spi_rx_buf, data_length);
    
    if(dump_data)
    {
        printf("SPI Slave RX Data from Master:\n");
        printf("===============================================");
        for(i=0; i<read_len; i++)
        {
            if(i%16 == 0)
                printf("\n");
                        
            printf("%02X  ", spi_rx_buf[i]);
        }
        printf("\n===============================================\n");

        printf("SPI Slave TX Data to Master:\n");
        printf("===============================================");
        for(i=0; i<read_len; i++)
        {
            if(i%16 == 0)
                printf("\n");
                        
            printf("%02X  ", spi_tx_buf[i]);
        }
        printf("\n===============================================\n");
    }
    else
    {
        for(i=0; i<read_len; i++)
        {
            if( spi_rx_buf[i] != i % 256 )
            {
                compare_error = 1;
                break;
    }
        }        
    }
    
    OS_MemFree(spi_tx_buf);  //drv_spislv_free_dma_buffer(tx_buf);
    OS_MemFree(spi_rx_buf);  //drv_spislv_free_dma_buffer(rx_buf);
    drv_spislv_deinit(SPI_PORT);

   if(dump_data)
   {
   }
   else
   {
    if(compare_error == 0)
        printf("SLAVE RX Match (%d)\n", read_len);
    else
        printf("SLAVE RX NOT Match (%d)!!\n ", read_len);
   }    
    printf("[SPI SLAVE Test : FINISH!]\n");
    
    return 0;
}


int test_spi_slave_dma(int32_t argc, char *argv[]) 
{

    uint8_t ret = 0; 
    uint32_t i = 0;
    uint8_t compare_error = 0;
    
    uint8_t cpha;
    uint8_t cpol;
    uint32_t data_length;
    
    if (argc != 4) 
    {
        printf("Usage           : %s <length> <cpha> <cpol>\n", argv[0]);
        printf("<length>        : dma data length(1-4095)\n");
        printf("<cpha>          : CPHA(0, 1)\n");
        printf("<cpol>          : CPOL(0, 1)\n");
        return 0;
    }
    
    data_length = strtoul(argv[1], NULL, 10);
    cpha = strtoul(argv[2], NULL, 10);
    cpol = strtoul(argv[3], NULL, 10);

    drv_spislv_init(SPI_PORT, cpha, cpol);

    spi_tx_buf = OS_MemAlloc(data_length);
    spi_rx_buf = OS_MemAlloc(data_length);

    for (i = 0; i < data_length; i++) 
    {
        if(dump_data)
        {
            //fill random
            spi_tx_buf[i] = OS_Random();
            spi_rx_buf[i] = 0;
        }
        else
        {
        spi_tx_buf[i] = i % 256;
        spi_rx_buf[i] = 0;
        }
    } 

    //block function
    drv_spislv_dma_trx(SPI_PORT, spi_tx_buf, spi_rx_buf, data_length);

    if(dump_data)
    {
        printf("SPI Slave RX Data from Master:\n");
        printf("===============================================");
        for(i=0; i<data_length; i++)
        {
            if(i%16 == 0)
                printf("\n");
                        
            printf("%02X  ", spi_rx_buf[i]);
        }
        printf("\n===============================================\n");

        printf("SPI Slave TX Data to Master:\n");
        printf("===============================================");
        for(i=0; i<data_length; i++)
        {
            if(i%16 == 0)
                printf("\n");
                        
            printf("%02X  ", spi_tx_buf[i]);
        }
        printf("\n===============================================\n");
    }
    else
    {
        for(i=0; i<data_length; i++)
        {
            if( spi_rx_buf[i] != i % 256 )
            {
                compare_error = 1;
                break;
    }
        }        
    }
    
    OS_MemFree(spi_tx_buf);
    OS_MemFree(spi_rx_buf);
    drv_spislv_deinit(SPI_PORT);

   if(dump_data)
   {
   }
   else
   {
    if(compare_error == 0)
        printf("SLAVE RX Match\n ");
    else
        printf("SLAVE RX NOT Match!!\n ");
   }    
    printf("[SPI SLAVE Test : FINISH!]\n");
    
    return 0;
}

int test_spi_slave_dma_test(int32_t argc, char *argv[]) 
{
    dump_data = 0;

    return test_spi_slave_dma(argc, argv);
}

int test_spi_slave_dma_dump(int32_t argc, char *argv[]) 
{
    dump_data = 1;

    return test_spi_slave_dma(argc, argv);    
}

int test_spi_slave_trx_checksum(int32_t argc, char *argv[]) 
{

    uint8_t ret = 0; 
    uint32_t i = 0;
    
    uint8_t cpha;
    uint8_t cpol;
    uint32_t data_length;
    uint32_t tx_checksum = 0;
    uint32_t rx_checksum = 0;    

    uint8_t use_dma = 1; 
    
    if (argc < 4) 
    {
        printf("Usage           : %s <length> <cpha> <cpol>\n", argv[0]);
        printf("<length>        : data length(1-4095), if over 4096 must be an even number\n");
        printf("<cpha>          : CPHA(0, 1)\n");
        printf("<cpol>          : CPOL(0, 1)\n");
        return 0;
    }
    
    data_length = strtoul(argv[1], NULL, 10);
    cpha = strtoul(argv[2], NULL, 10);
    cpol = strtoul(argv[3], NULL, 10);

    drv_spislv_init(SPI_PORT, cpha, cpol);

    if(argc > 4)
        use_dma = strtoul(argv[4], NULL, 10);

    spi_tx_buf = OS_MemAlloc(data_length);
    spi_rx_buf = OS_MemAlloc(data_length);

    for (i = 0; i < data_length-4; i++) 
    {
        spi_tx_buf[i] = OS_Random();
        tx_checksum += spi_tx_buf[i];
    } 
    
    printf("Slave TX Checksum = 0x%x\n", tx_checksum);
    spi_tx_buf[data_length-4] = (tx_checksum>>0)&0xff;
    spi_tx_buf[data_length-3] = (tx_checksum>>8)&0xff;
    spi_tx_buf[data_length-2] = (tx_checksum>>16)&0xff;
    spi_tx_buf[data_length-1] = (tx_checksum>>24)&0xff;
    
    //block function
    if(use_dma)
    drv_spislv_dma_trx(SPI_PORT, spi_tx_buf, spi_rx_buf, data_length);
    else
        data_length = drv_spislv_trx(SPI_PORT, spi_tx_buf, spi_rx_buf, data_length);


    for(i=0; i<data_length-4; i++)
    {
        rx_checksum += spi_rx_buf[i];
    }

    uint32_t checksum = (spi_rx_buf[data_length-4]<<0) |
                        (spi_rx_buf[data_length-3]<<8) |
                        (spi_rx_buf[data_length-2]<<16)|
                        (spi_rx_buf[data_length-1]<<24); 

    if(checksum == rx_checksum)
        printf("Slave RX Checksum MATCH (0x%x)\n", checksum);
    else
        printf("Slave RX Checksum Not MATCH (0x%x vs 0x%x)\n", checksum, rx_checksum);
        
    OS_MemFree(spi_tx_buf);
    OS_MemFree(spi_rx_buf);
    drv_spislv_deinit(SPI_PORT);

    
    return 0;
}

/*
SPI Slave dma_lli example
*/

#define USE_BUF_NUM 3
#define SPI_BUF_LEN 4092


struct _args
{
    char args;
    char argv[9][64];
};

static int spi_buf_init(spi_buffer *spi_buf, int buf_len)
{
    int cnt = 0;
    memset(spi_buf, 0, sizeof(spi_buffer));
    spi_buf->use_buf_num = USE_BUF_NUM;
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) 
    {
        spi_buf->ping_pong[cnt].buffer_idx = 0;
        spi_buf->ping_pong[cnt].data_ready = 0;
        spi_buf->ping_pong[cnt].buffer = OS_MemAlloc(buf_len);
        memset(spi_buf->ping_pong[cnt].buffer,0, buf_len);
        if(spi_buf->ping_pong[cnt].buffer == NULL) 
        {
            printf("buf alloc fail, cnt: %d, size: %d \n", cnt, buf_len);
            return -1;
        }
        spi_buf->ping_pong[cnt].buffer_len = buf_len;
    }
    spi_buf->pingpong_idx = 0;

    return 0;
}
static void spi_buf_deinit(spi_buffer *spi_buf)
{
    int cnt = 0;
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) 
    {
        if(spi_buf->ping_pong[cnt].buffer != NULL) 
        {
            OS_MemFree(spi_buf->ping_pong[cnt].buffer);
            spi_buf->ping_pong[cnt].buffer = NULL;
        }
    }
}

void spi_rx_only_task(void *param) 
{
    struct _args *args = (struct _args*)param;

    int ret;
    int i;
    //int j;
    int buf_len = SPI_BUF_LEN;
    int idx = 0;
    uint32_t rx_length = 0;
    uint32_t rx_checksum = 0;
    uint8_t b_run;
 
    uint32_t max_length = strtol(args->argv[0], NULL, 10);
    uint8_t cpha = strtol(args->argv[1], NULL, 10);
    uint8_t cpol = strtol(args->argv[2], NULL, 10);

    OS_MemFree(param);

    spi_buffer slv_buf;
    spi_buf_init(&slv_buf, buf_len);

    drv_spislv_init(DRV_SPISLV_0, cpha, cpol);
    hal_spislv_set_trx_mode(DRV_SPISLV_0, SPI_SLV_RX_MODE);

    drv_spislv_dma_lli_trx(DRV_SPISLV_0, NULL, &slv_buf, buf_len);

    b_run = 1;
    while(b_run)
    {
        while(slv_buf.ping_pong[idx].data_ready)
        {  
            struct _spi_buffer_st *buf = &slv_buf.ping_pong[idx];
            uint8_t *local_buf = (uint8_t*)buf->buffer;
            int local_len = buf->buffer_len;
            
            //frame_send(local_buf, local_len);
            for(i=0;i<local_len;i++)
            {
                rx_checksum += local_buf[i];
            }

            rx_length += local_len;

            slv_buf.ping_pong[idx].data_ready = 0;
            idx = ((idx + 1) % USE_BUF_NUM);

            if(rx_length == max_length)
            {
                b_run = 0;
                rx_checksum = rx_checksum - local_buf[local_len-4] - local_buf[local_len-3] - local_buf[local_len-2] - local_buf[local_len-1];
                printf("Slave RX checksum = 0x%x\n", rx_checksum);
                break;
            }

        }

        OS_UsDelay(1);

    }
    
    ret = drv_spislv_dma_lli_trx_stop(DRV_SPISLV_0);
    drv_spislv_deinit(DRV_SPISLV_0);
    spi_buf_deinit(&slv_buf);
    
    if(ret == 0)
        printf("Slave RX Only task end\n");
    else
        printf("ERROR! Slave RX Only task end timeout\n");
    OS_TaskDelete(NULL);

    return;
}

int Cmd_slv_dma_lli_read (int32_t argc, char *argv[])
{

    if (argc < 3) 
    {
        printf("Usage           : %s <length> <cpha> <cpol>\n", argv[0]);
        printf("<length>        : data length(4092*n)\n");
        printf("<cpha>          : CPHA(0, 1)\n");
        printf("<cpol>          : CPOL(0, 1)\n");
        return 0;
    }
    
    struct _args *cmd_args = (struct _args*)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[1]);
    strcpy(cmd_args->argv[1], argv[2]);
    strcpy(cmd_args->argv[2], argv[3]);

    printf("Slave RX Only task start\n");
    OS_TaskCreate(spi_rx_only_task, "spi rx only task", 1024, cmd_args, OS_TASK_LOW_PRIO, NULL);

    return 0;
}

void spi_tx_only_task(void *param) 
{
    struct _args *args = (struct _args*)param;

    int ret;
    int i;
    int buf_len = SPI_BUF_LEN;
    int idx = 0;

    int tx_length = 0;
    int tx_checksum = 0;
    uint8_t b_run;

    int one_time = 0;
    
    //prepare random buf for tx
    uint8_t *random_buf = OS_MemAlloc(SPI_BUF_LEN);
    for(i=0; i<SPI_BUF_LEN; i++)
    {
        random_buf[i] = OS_Random();
    }
    
    uint32_t max_length = strtol(args->argv[0], NULL, 10);
    uint8_t cpha = strtol(args->argv[1], NULL, 10);
    uint8_t cpol = strtol(args->argv[2], NULL, 10);

    OS_MemFree(param);
    
    spi_buffer slv_buf;
    spi_buf_init(&slv_buf, buf_len);
    
    drv_spislv_init(DRV_SPISLV_0, cpha, cpol);
    hal_spislv_set_trx_mode(DRV_SPISLV_0, SPI_SLV_TX_MODE);
    
    //drv_spislv_dma_lli_trx(DRV_SPISLV_0, &slv_buf, NULL, buf_len); 

    b_run = 1;
    while(b_run)
    {
        struct _spi_buffer_st *buf = &slv_buf.ping_pong[idx];

        while( buf->data_ready == 0 ) //mean buffer is empty
        {      
            uint8_t *local_buf = (uint8_t*)buf->buffer;
            for(i=0; i<buf_len; i++)
            {
                //local_buf[i] = OS_Random();   //too slow for send tx data 
                local_buf[i] = random_buf[i];

                if(tx_length < max_length)
                    tx_checksum+=local_buf[i];
                    
            }
            
            tx_length+=buf_len;
            buf->buffer_idx = 0;
            buf->buffer_len =buf_len;
            buf->data_ready=1;
            
            if(tx_length == max_length)
            {
                tx_checksum = tx_checksum - local_buf[buf_len-4] - local_buf[buf_len-3] - local_buf[buf_len-2] - local_buf[buf_len-1];
            }

            idx = (idx+1) % USE_BUF_NUM;

            if(tx_length >= (max_length+USE_BUF_NUM*SPI_BUF_LEN))
            {
                printf("Slave TX Checksum = 0x%x\n", tx_checksum);
                b_run = 0;
            }
        }
    
                if(!one_time)
                {
                    one_time = !one_time;
                    printf("spi slave tx start\n");
                    drv_spislv_dma_lli_trx(DRV_SPISLV_0, &slv_buf, NULL, buf_len);
                }
 
        }
        
        ret = drv_spislv_dma_lli_trx_stop(DRV_SPISLV_0);
        drv_spislv_deinit(DRV_SPISLV_0);
        spi_buf_deinit(&slv_buf);
        
        if(ret == 0)
            printf("Slave TX Only task end\n");
        else
            printf("ERROR! Slave TX Only task end timeout\n");
        OS_TaskDelete(NULL);
        

}

int Cmd_slv_dma_lli_write (int32_t argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage           : %s <length> <cpha> <cpol>\n", argv[0]);
        printf("<length>        : data length(4092*n)\n");
        printf("<cpha>          : CPHA(0, 1)\n");
        printf("<cpol>          : CPOL(0, 1)\n");
        return 0;
    }
    
    struct _args *cmd_args = (struct _args*)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[1]);
    strcpy(cmd_args->argv[1], argv[2]);
    strcpy(cmd_args->argv[2], argv[3]);

    printf("Slave TX Only task start\n");
    OS_TaskCreate(spi_tx_only_task, "spi tx only task", 1024, cmd_args, OS_TASK_LOW_PRIO, NULL);


    return 0;
}

int Cmd_help (int32_t argc, char *argv[])
{
    printf ("\n*************************************************************************\n");
    printf ("Test SPI Target : \n");
    printf ("                   GPIO_08 : SPI_M_CLK\n");
    printf ("                   GPIO_10 : SPI_M_MISO\n");
    printf ("                   GPIO_12 : SPI_M_MOSI\n");
    printf ("                   GPIO_13 : SPI_M_CS\n");
    printf ("\n*************************************************************************\n");


    return 0;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    //for spi slave test with dma
    { "spi_slave_dma_test"              , test_spi_slave_dma_test              , "spi_slave_dma_test <length> <cpha> <cpol>"              } ,
    { "spi_slave_dma_dump"              , test_spi_slave_dma_dump              , "spi_slave_dma_dump <length> <cpha> <cpol>"              } ,
        
    //for spi slave test with mcu
    { "spi_slave_test"              , test_spi_slave_mcu              , "spi_slave_dma_test <length> <cpha> <cpol>"              } ,

    //
    { "spi_slave_trx_crc"     , test_spi_slave_trx_checksum     , "spi_master_trx_checksum <length> <cpha> <cpol>"     } ,

    //test command
    
    { "spi_slave_lli_read"     , Cmd_slv_dma_lli_read     , "for RD Test"     } ,
    { "spi_slave_lli_write"     , Cmd_slv_dma_lli_write     , "for RD Test"     } ,
        
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


