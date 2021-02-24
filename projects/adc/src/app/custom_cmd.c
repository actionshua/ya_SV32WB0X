#include <stdio.h>
#include <string.h>
#include "osal.h"

#include "cli.h"
#include "error.h"

#include <drv_adc.h>
#include <drv_pwm.h>

#if defined(SUPPORT_PERIPHERAL_ADCBTN) && (SUPPORT_PERIPHERAL_ADCBTN==1)
#include <drv_adcbtn.h>
#endif

#include <drv_tmr.h>
#include "logger.h"

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

/*---------------------------------- CMDs -----------------------------------*/
int Cmd_echo(int32_t argc, char *argv[])
{
	int loop_i;
	for (loop_i = 0;loop_i < argc; loop_i++) {
		printf("argv[%d] = %s\n", loop_i, argv[loop_i]);
	}
    return 0;
}

void ms_irq_handler(uint32_t irq_num) 
{ 
  drv_tmr_clear_interrupt_status(TM_TM1_MS);

  static uint32_t second = 0;
  second ++;
  
  uint32_t adc_value = 0;
  uint16_t adc_code = 0;
  if(0 != drv_adc_read(&adc_code)){
      CMD_LOG_W("read out fail!\n");
      return;
  }
  adc_value = adc_code;
  printf("%ld @ %ld\n", adc_value ,second);

  drv_tmr_enable(TM_TM1_MS, TM_MODE_ONE_SHOT, 1000); 

} 

int Cmd_adc_22_start(s32 argc, char *argv[])
{
    

    uint32_t adc_id = 0;
	
	adc_id = strtoul(argv[1], NULL, 10);

    if ((argc != 2) || (adc_id > 7) || (adc_id < 0)) {
        printf("Usage   : adc_start <id>\n");
        printf("<id>    : adc id(0-3)\n");
        return 0;
    }

    printf("run ADC_%d start...%s %s\n" , adc_id, __DATE__ , __TIME__);

    if(0 != drv_adc_init(adc_id)){
        CMD_LOG_E("init fail!\n");
        return -1;
    };
     
    drv_tmr_sw_rst(TM_TM1_MS); 
    drv_tmr_init(TM_TM1_MS); 
    drv_tmr_register_irq_handler(TM_TM1_MS, ms_irq_handler); 
    drv_tmr_enable(TM_TM1_MS, TM_MODE_ONE_SHOT, 1000); 

        return 0;
}

int Cmd_adc_22_stop(s32 argc, char *argv[])
{

    uint32_t adc_id = 0;
	
	adc_id = strtoul(argv[1], NULL, 10);

    if ((argc != 2) || (adc_id > 7) || (adc_id < 0)) {
        printf("Usage   : adc_stop <id>\n");
        printf("<id>    : adc id(0-7)\n");
        return 0;
    }

    printf("run ADC_%d stop...%s %s\n" , adc_id, __DATE__ , __TIME__);

    if(0 != drv_adc_deinit(adc_id)){
        CMD_LOG_E("deinit fail!\n");
        return -1;
    }

    drv_tmr_disable(TM_TM1_MS); 

        return 0;
}

int Cmd_adc_isr_start(s32 argc, char *argv[]) //get adc value 16 times then average 
{

    uint32_t adc_id = 0;
    adc_id = strtoul(argv[1], NULL, 10);
    if ((argc != 2) || (adc_id > 7) || (adc_id < 0)) {
        printf("Usage   : adc_isr_testt <id>\n");
        printf("<id>    : adc id(0-7)\n");
        return 0;
    }

    if(0 != drv_adc_init(adc_id)){
        CMD_LOG_E("init fail!\n");
        return -1;
    };

    drv_adc_enable_isr();

    return 0;
}

void read_temp_task(void *pdata)
{
    uint16_t temp_code = 0;
    while(1)
    {
        drv_adc_read_temp(&temp_code);
        printf("temp code = %d\n", temp_code);
        OS_MsDelay(5000);
    }
    OS_TaskDelete(NULL);
}

int Cmd_adc_temp_task(s32 argc, char *argv[])
{
    OS_TaskCreate(read_temp_task, "temperature task", 256, NULL, OS_TASK_LOW_PRIO, NULL);
    return 0;
}

int Cmd_help (int32_t argc, char *argv[])
{
    printf ("\n*************************************************************************\n");
    printf ("Test ADC Target : \n");
    printf ("                   GPIO_00 : ADC_id:3\n");
    printf ("                   SIO_20  : ADC_id:2\n");
    printf ("                   GPIO_21 : ADC_id:1\n");
    printf ("                   GPIO_22 : ADC_id:0\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       adc_start  <id>\n");
    printf ("brief:\n");
    printf ("       This function start the ADC measure.\n");
    printf ("Options:\n");
    printf (    "<id>                       The ADC target number(0-3).\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       adc_stop  <id>\n");
    printf ("brief:\n");
    printf ("       This function stop the ADC measure.\n");
    printf ("Options:\n");
    printf (    "<id>                       The ADC target number(0-3).\n");

    return 0;
}



int Cmd_adc_external_channel(s32 argc, char *argv[])
{

    int count = 0;
    int i=0;
    uint32_t channel_set = 0;
    uint32_t write_value = 0;
    uint32_t reg_value = 0;

    uint16_t *adc_buf;
    if (argc < 3) {
        printf("%s [input_set] [size]\n", argv[0]);
        printf("input_set: input channel set\n");
        printf("size: dump size\n");
        printf("%s 0xFC 0x10", argv[0]);
        return ERROR_INVALID_PARAMETER;
    }

    channel_set = strtoul(argv[1], NULL, 16);
    count = strtoul(argv[2], NULL, 16);

    //printf("channel_set = 0x%x\n", channel_set);
    //printf("count = 0x%x\n", count);
    
    adc_buf = (uint16_t*)OS_MemAlloc(2*count);

    printf("adc channel test start\n");

    //
    REG32(0xc0000f08) = 0x05;
    REG32(0xc0000f14) = 0x04;



        write_value = 0x117900|channel_set;

    printf("write_value = 0x%x\n", write_value);


        REG32(0xc0000f00) = write_value;       

        for(i=0; i<count; )
        {
            if( (REG32(0xc0000f0c)&0x1) == 1 )
            {
                adc_buf[i]=REG32(0xc0000f10);
                i++;
            }
            
        }

        //printf("value = %d\n", reg_value / 28);
        for(i=0;i<count;i++)
        {
            printf("%x\n", adc_buf[i]);
        }
        printf("\n\n");

        REG32(0xc0000f00) = 0x0;     

        OS_MemFree(adc_buf);

    return 0;
}

int Cmd_adc_internal_tmp(s32 argc, char *argv[])
{
    int count = 0;
    int i=0;
    uint32_t channel_set = 0;
    uint32_t write_value = 0;
    uint32_t reg_value = 0;

    uint16_t *adc_buf;
    if (argc < 2) {
        printf("%s  [size]\n", argv[0]);
        printf("size: dump size\n");
        printf("%s 0x10", argv[0]);
        return ERROR_INVALID_PARAMETER;
    }

    count = strtoul(argv[1], NULL, 16);

    //printf("channel_set = 0x%x\n", channel_set);
    //printf("count = 0x%x\n", count);
    
    adc_buf = (uint16_t*)OS_MemAlloc(2*count);

    printf("adc channel test start\n");

    //
    REG32(0xc0000f08) = 0x05;
    REG32(0xc0000f14) = 0x04;



        write_value = 0x1B7A00;

    printf("write_value = 0x%x\n", write_value);


        REG32(0xc0000f00) = write_value;       

        for(i=0; i<count; )
        {
            uint32_t adc_code = REG32(0xc0000f9c);
            if( (adc_code&0x1000) == 0x1000 )
            {
                adc_buf[i]=adc_code;
                i++;
            }
            else
            {
                OS_MsDelay(1);
            }
            
        }

        //printf("value = %d\n", reg_value / 28);
        for(i=0;i<count;i++)
        {
            printf("%x\n", adc_buf[i]);
        }
        printf("\n\n");

        //REG32(0xc0000f00) = 0x0;     

        OS_MemFree(adc_buf);

    return 0;
}

int Cmd_adc_internal_vdd(s32 argc, char *argv[])
{
    int count = 0;
    int i=0;

    uint32_t write_value = 0;
    uint32_t reg_value = 0;

    uint16_t *adc_buf;
    if (argc < 2) {
        printf("%s  [size]\n", argv[0]);
        printf("size: dump size\n");
        printf("%s 0x10", argv[0]);
        return ERROR_INVALID_PARAMETER;
    }

    count = strtoul(argv[1], NULL, 16);

    //printf("channel_set = 0x%x\n", channel_set);
    //printf("count = 0x%x\n", count);
    
    adc_buf = (uint16_t*)OS_MemAlloc(2*count);

    printf("adc channel test start\n");

    //
    REG32(0xc0000f08) = 0x05;
    REG32(0xc0000f14) = 0x04;



        write_value = 0x1B7C00;

    printf("write_value = 0x%x\n", write_value);


        REG32(0xc0000f00) = write_value;       

        for(i=0; i<count; )
        {
            uint32_t adc_code = REG32(0xc0000f98);
            if( (adc_code&0x1000) == 0x1000 )
            {
                adc_buf[i]=adc_code;
                i++;
            }
            else
            {
                OS_MsDelay(1);
            }

            
        }

        //printf("value = %d\n", reg_value / 28);
        for(i=0;i<count;i++)
        {
            printf("%x\n", adc_buf[i]);
        }
        printf("\n\n");

        //REG32(0xc0000f00) = 0x0;     

        OS_MemFree(adc_buf);

    return 0;
}


int Cmd_adc_custom_cfg(s32 argc, char *argv[])
{
    int count = 0;
    int i=0;

    uint32_t write_value = 0;
    uint32_t reg_value = 0;

    uint16_t *adc_buf;
    if (argc < 2) {
        printf("%s  [size]\n", argv[0]);
        printf("size: dump size\n");
        printf("%s 0x10", argv[0]);
        return ERROR_INVALID_PARAMETER;
    }

    count = strtoul(argv[1], NULL, 16);

    //printf("channel_set = 0x%x\n", channel_set);
    //printf("count = 0x%x\n", count);
    
    adc_buf = (uint16_t*)OS_MemAlloc(2*count);

    printf("adc channel test start\n");

    //
    REG32(0xc0000f08) = 0x05;
    REG32(0xc0000f14) = 0x04;




    printf("read 0xc0000f00 = 0x%x\n", REG32(0xc0000f00) );

    for(i=0; i<count; )
    {
        if( (REG32(0xc0000f0c)&0x1) == 1 )
        {
            adc_buf[i]=REG32(0xc0000f10);
            i++;
        }
            
    }

        //printf("value = %d\n", reg_value / 28);
        for(i=0;i<count;i++)
        {
            printf("%x\n", adc_buf[i]);
        }
        printf("\n\n");

        

        OS_MemFree(adc_buf);

    return 0;
}

int Cmd_adc3_test(s32 argc, char *argv[])
{


    //test adc channel
    int i, n;
    uint32_t write_value;
    uint32_t reg_value = 0;

    uint16_t adc_raw[28] = {0};

    printf("adc channel test start\n");

	//input channel = ADC0
	REG32(0xc0000f00) = 0x117900 | (1<<0);	
	
    //
    REG32(0xc0000f08) = 0x05;
    REG32(0xc0000f14) = 0x04;

	//triggerSignal[ch] = signal[signalSel[ch]]
	//assign pipe0 = ch0, pipe1 = ch1, pipe2 = ch2, ... , pipe7 = ch7
	printf("read 0xc0000f20 = 0x%x\n", REG32(0xc0000f20));
	printf("write 0xc0000f20 = 0x%x\n", 0x76543210);
	REG32(0xc0000f20) = 0x76543210;
	
	//triggle signal sel gpio 1
	printf("read 0xc0000f24 = 0x%x\n", REG32(0xc0000f24));
	printf("write 0xc0000f24 = 0x%x\n", 0x1);
	REG32(0xc0000f24) = 0x1;	//bit 5:0 set gpio1
	//triggle signal sel pwm 0	
	//REG32(0xc0000f24) = 48;	//bit 5:0 set pwm0
	
	//triggle adc
	//write to triggle adc , should move to another function
	//REG32(0xc0000f2c) = 1; //write 1 to trigger adc pip0
	
	//triggle event 
	//write
	printf("read 0xc0000f30 = 0x%x\n", REG32(0xc0000f30));
	printf("write 0xc0000f30 = 0x%x\n", 0x4);
	REG32(0xc0000f30) = 0x4;	//pipe0 use csr write
	
	//decimate 
	//pass
	
	//delay
	//pass
	
	//forget factor
	//pass
	
	//latch_threshold
	//pass
	
	
	////////////
	//////////
    for(n=0;n<1;n++)
    {
        write_value = 0x117900 | (1<<n);

        printf("test channel %d , cfg = 0x%x\n", n, write_value);

        REG32(0xc0000f00) = write_value;       

        for(i=0; i<28; )
        {
            if( (REG32(0xc0000f0c)&0x1) == 1 )
            {
                adc_raw[i]=REG32(0xc0000f10);
                i++;
            }
            
        }

        printf("value = %d\n", reg_value / 28);
        for(i=0;i<28;i++)
        {
            printf("%x ", adc_raw[i]);
        }
        printf("\n\n");

        REG32(0xc0000f00) = 0x0;     

    }

	printf("over\n");
    return 0;
}


int Cmd_adc3_cp1(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint16_t adc_raw[32] = {0};

    printf("unit test : IOTADC CP1 test!!\n");

    REG32(0xCCB0B010) = 0x0a800024;
    REG32(0xC0000F08) = 0x5;
    REG32(0xC0000F00) = 0x1bb902;
    REG32(0xC0000F1C) = 0x21;

    OS_MsDelay(2);
    REG32(0xC0000F18) = 0x1;

    
    REG32(0xC0000F14) = 0x8; 
    OS_MsDelay(2);
    REG32(0xC0000F14) = 0x8; 
    printf("Measure CALVLO:\n");
    for(i=0;i<16;i++)
    {
        printf("CALVLO = %d\n", REG32(0xC0000F10)&0xfff);  
    }

    //if(read_value < 332 || read_value > 578)
    //{
    //    printf("Error: CALVLO out of range(332,578) %d\n", read_value);
    //}

    OS_MsDelay(2);
    REG32(0xC0000F18) = 0x3;

    REG32(0xC0000F14) = 0x8; 
    OS_MsDelay(2);
    REG32(0xC0000F14) = 0x8;     
    printf("Measure CALVHI:\n");
    for(i=0;i<16;i++)
    {
        printf("CALVHI = %d\n", REG32(0xC0000F10)&0xfff);  
    }
    //if(read_value < 3359 || read_value > 3923)
    //{
    //    printf("Error: CALVHI out of range(3359,3923) %d\n", read_value);
    //}

  
    
    printf("IOTADC FT test complete!!\n");

    
    return 0;
}

#if(CHIP_SUB_ID == 2)
int Cmd_adc3_pipe_test(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint8_t adc_ch = 0;
    uint16_t adc_raw[32] = {0};

    uint32_t timeout = 10000;
    
    printf("adc pipe test ADC0 !!\n");
    
    drv_adc_init(adc_ch);
    //REG32(0xC0000F08) = 0x5;
    //REG32(0xC0000F00) = 0x117901;
    hal_adc_fifo_ctrl(0x3);    
    
    OS_MsDelay(1);

    
    printf("dump 28 sample\n");
    
    hal_adc_fifo_src_switch(adc_ch, 0); //sample into pipe
    //REG32(0xC0000F74) = 0xFE;

    hal_adc_enable();

    hal_adc_fifo_rst();
    //REG32(0xC0000F14) = 0xc;
   
    for(i=0; i<24;)
    {
        adc_raw[i] = hal_adc_pipe_read(adc_ch);
        if( (adc_raw[i] & 0xf000) != 0xf000)
        {
            adc_raw[i] = (adc_raw[i]&0xfff);
            i++;
        }

        timeout--;
        if(timeout == 0)
            break;
    }

    for(i=0; i<24;i++)
    {
        printf("%d\n", adc_raw[i]);
    }
    
 
    printf("adc pipe test complete!!\n");

    
    return 0;
}

//////////////////////////////////
static uint8_t adc_ch = 1;
static int src_to_fifo = 1;
void app_adc_isr (uint32_t irq_num)
{
    uint32_t sum = 0;
    uint16_t adc_raw;
    int i;
    
    adc_raw = hal_adc_pipe_read(adc_ch);
    ///adc_raw = REG32(0xc0000f78);

    hal_adc_disable();
    intc_irq_disable(IRQ_ADC);

    printf("adc code = %d\n", adc_raw & 0xFFF);

}
int adc3_threshold_test(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint16_t adc_raw[32] = {0};

    printf("adc threadhold test ADC %d !!\n", adc_ch);

    //set irq
    hal_adc_fifo_ctrl(0x3);    
    intc_irq_enable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , app_adc_isr);

    //set adc ctrl    
    drv_adc_init(adc_ch);
    //REG32(0xC0000F08) = 0x5;
    //REG32(0xC0000F00) = 0x117901;

    hal_adc_latch_threshold(adc_ch, 1, 0x800);
    //REG32(0xC0000F60) = 0x10001800;

    hal_adc_fifo_src_switch(adc_ch, 0);    //0: sample to pipe, 1: sample to fifo
    //REG32(0xC0000F74) = 0xFD;

    hal_adc_fifo_rst();
    //REG32(0xC0000F14) = 0xc;
    
    hal_adc_enable();

    return 0;
}

void app_adc_isr2 (uint32_t irq_num)
{
    uint16_t adc_raw;

    if(src_to_fifo)
    {
        adc_raw = hal_adc_fifo_read();
    }
    else
    {
        adc_raw = hal_adc_pipe_read(adc_ch);
    }

    //hal_adc_disable();
    //intc_irq_disable(IRQ_ADC);

    printf("adc code = %d\n", adc_raw & 0xFFF);

}
int adc3_timer_trigger(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint16_t adc_raw[32] = {0};

    printf("adc threadhold test ADC %d !!\n", adc_ch);

    //set irq
    //hal_adc_fifo_ctrl(0x3);    
    intc_irq_enable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , app_adc_isr2);

    //set adc ctrl    
    drv_adc_init(adc_ch);
    
    hal_adc_fifo_ctrl(0x3);   

    //
    hal_adc_trigger_event_en(adc_ch, 0x20); //trigger event set ms timer3
    
    hal_adc_fifo_src_switch(adc_ch, src_to_fifo);    //0: sample to pipe, 1: sample to fifo

    hal_adc_fifo_rst();

    hal_adc_enable();

    printf("need config timer\n");

    return 0;
}

int adc3_kick_trigger(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint16_t adc_raw[32] = {0};

    printf("adc threadhold test ADC %d !!\n", adc_ch);

    //set irq
    //hal_adc_fifo_ctrl(0x3);    
    intc_irq_enable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , app_adc_isr2);

    //set adc ctrl    
    drv_adc_init(adc_ch);
    
    hal_adc_fifo_ctrl(0x0);   

    //
    hal_adc_trigger_event_en(adc_ch, 4); //trigger event set ms timer3
    
    hal_adc_fifo_src_switch(adc_ch, src_to_fifo);    //0: sample to pipe, 1: sample to fifo

    hal_adc_fifo_rst();

    hal_adc_enable();

    printf("0xc0000f2c set 1 to kick adc\n");

    return 0;
}

int adc3_pwm_trigger(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint16_t adc_raw[32] = {0};

    printf("adc threadhold test ADC %d !!\n", adc_ch);

    //set irq
    //hal_adc_fifo_ctrl(0x3);    
    intc_irq_enable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , app_adc_isr2);

    //set adc ctrl    
    drv_adc_init(adc_ch);
    
    hal_adc_fifo_ctrl(0x3);   

    //
    hal_adc_triggle_signal_sel(adc_ch, 48); //PWM 0 triggle
    hal_adc_trigger_event_en(adc_ch, 0x1); //trigger event set ms timer3
    
    hal_adc_fifo_src_switch(adc_ch, src_to_fifo);    //0: sample to pipe, 1: sample to fifo

    hal_adc_fifo_rst();

    hal_adc_enable();

    printf("execute pwm_0 to config pwm 0\n");

    return 0;
}

int Cmd_pwm(s32 argc, char *argv[])
{

    //assign GPIO 4 to pwm0
    //REG32(0xc0000700) = 1<<4;
    //REG32(0xc0000708) = 1<<4;
        
    drv_pwm_init(0);
    drv_pwm_config(0, 10, 2048, 0);
    drv_pwm_enable(0);

    return 0;
}

int adc3_average(s32 argc, char *argv[])
{
    uint32_t read_value;
    int i;
    uint16_t adc_raw[32] = {0};

    printf("adc average ADC %d !!\n", adc_ch);

REG32(0xCCB0B010) = 0x0a800024;

    //set adc ctrl    
    drv_adc_init(adc_ch);
    
REG32(0xC0000F00) = 0x1bb902; 

    hal_adc_fifo_ctrl(0x3);   

    hal_adc_forget_factor(adc_ch, 1);

    hal_adc_fifo_rst();

    hal_adc_enable();

    OS_MsDelay(10);
    for(i=0; i<16;i++)
    {
        adc_raw[i] = (hal_adc_fifo_read() & 0x0fff);
    }

    for(i=0; i<16;i++)
    {
        printf("value = %d\n", adc_raw[i]);
    }
    
    return 0;
}


/////////////////////////////
//TASK
/////////////////////////////

void adc3_pipe_run(void *pdata)
{

    OS_TaskDelete(NULL);
}

int adc3_pipe_read_task(s32 argc, char *argv[])
{
    OS_TaskCreate(adc3_pipe_run, "adc3 pipe read", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL);
    return 0;
}

int adc3_fifo_read_task(s32 argc, char *argv[])
{
    return 0;
}
#endif

/* ---------------------- ADC Button example code (Start)---------------------- */
#if defined(SUPPORT_PERIPHERAL_ADCBTN) && (SUPPORT_PERIPHERAL_ADCBTN==1)

adc_arr_t btns[USER_BUTTON_MAX];

void Cmd_adc_button_callback (void *user_data, int adc, int id, adc_btn_state_t state)
{
    //printf("%d btn is %d\n", id, state);
    
    if (id == 1){
        printf("PLAY/PAUSE\n");
    }
    else if (id == 2){
        printf("REC/STOP\n");
    }
    else if (id == 3){
        printf("NEXT\n");
    }
    else if (id == 4){
        printf("PREVIOUS\n");
    }
    else if (id == 5){
        printf("VOL+\n");
    }
    else if (id == 6){
        printf("VOL-\n");
    }
    else if (id == 7){
        printf("BTN_7\n");
    }
    else if (id == 8){
        printf("BTN_8\n");
    }
    
}
#endif

#if defined(SUPPORT_PERIPHERAL_ADCBTN) && (SUPPORT_PERIPHERAL_ADCBTN==1)
int Cmd_adc_btn(s32 argc, char *argv[])
{
    //adc_btn_init(btns ,USER_BUTTON_MAX, ADC_EXT_VOLTAGE_GPIO_GPIO34, Cmd_adc_button_callback);
    adc_btn_init(btns ,USER_BUTTON_MAX, 5, Cmd_adc_button_callback);
    return 0;
}
#endif
/* ---------------------- ADC Button example code (End)---------------------- */

int Cmd_WriteReg32 (s32 argc, char *argv[])
{ 
    char *pkey = 0, *pvalue = 0;

    if (argc < 3) {
        return ERROR_INVALID_PARAMETER;
    }
  
    pkey = argv[1];
    pvalue = argv[2];
    
    if( pkey == 0 || pvalue == 0)
        return ERROR_INVALID_PARAMETER;
    
    unsigned int address = strtoul(pkey, NULL, 16);
    unsigned int data = strtoul(pvalue, NULL, 16);

    printf("reg : write 0x%x  0x%x \n", address, data);

    REG32(address)  = data;

    return ERROR_SUCCESS;
}

int Cmd_ReadReg32 (s32 argc, char *argv[])
{
    char *pkey = 0;
    unsigned int address;
    if (argc < 2) {
        return ERROR_INVALID_PARAMETER;
    }

    pkey = argv[1];

    address = strtoul(pkey, NULL, 16);

    printf("reg : read 0x%08x  0x%08x \n", address, (unsigned int)REG32(address));
    return ERROR_SUCCESS;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "help",                   Cmd_help,                  "ADC test help"         },
    { "adc_start",              Cmd_adc_22_start,          "adc_start <id>"        },
    { "adc_stop",               Cmd_adc_22_stop,           "adc_stop <id>"         },
    { "adc_isr_start",          Cmd_adc_isr_start,         "adc_isr_start <id>"    },
    { "adc_temp_task",          Cmd_adc_temp_task,         "adc_temp_task"         },
    { "adc3_test",              Cmd_adc3_test,             "adc3_test"         },
    { "adc3_cp1",               Cmd_adc3_cp1,              "adc3_test"         },
#if(CHIP_SUB_ID == 2)    
    { "adc3_pipe_test",         Cmd_adc3_pipe_test,        "adc3_pipe"         },  
    { "adc3_threshold_test",    adc3_threshold_test,       "adc3_pipe"         },  

    { "adc3_timer_trigger",     adc3_timer_trigger,        "adc3_pipe"         },  
    { "adc3_pwm_trigger",       adc3_pwm_trigger,          "adc3_pipe"         },      
    { "adc3_kick_trigger",      adc3_kick_trigger,         "adc3_pipe"         },     

    { "pwm_0",                  Cmd_pwm,                   "pwm"         },     

    { "adc3_average",           adc3_average,              "adc3_average"         },     

    //task
    { "adc3_pipe_read_task",    adc3_pipe_read_task,       "adc3_pipe"         },  
    { "adc3_fifo_read_task",    adc3_fifo_read_task,       "adc3_pipe"         },  
#endif    
    //adc test
    { "adc_external_channel",   Cmd_adc_external_channel,  "adc_external_channel " }, 
    { "adc_internal_tmp",       Cmd_adc_internal_tmp,      "adc_internal_tmp "     }, 
    { "adc_internal_vdd",       Cmd_adc_internal_vdd,      "adc_internal_vdd "     }, 
    { "adc_custom_cfg",         Cmd_adc_custom_cfg,        "adc_custom_cfg "       },
    #if defined (SUPPORT_PERIPHERAL_ADCBTN) && (SUPPORT_PERIPHERAL_ADCBTN==1)
    { "adc_btn",                Cmd_adc_btn,               "adc button function"   },
    #endif    
    
    { (const char *)NULL,       (CliCmdFunc)NULL,          (const char *)NULL      },
};


