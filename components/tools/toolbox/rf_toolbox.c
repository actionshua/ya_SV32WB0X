#include "toolbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osal.h"
#include "sa_cfg.h"
#include "error.h"
#include "wificonf.h"

#include <phy/drv_phy.h>
#if EXTPA_EN
#include <phy/extpa_api.h>
#endif
#if BLE_EN
#include "ble_dtm.h"
#endif

struct st_rf_table ssv_rf_table;

////RF AT Command
#define SAVE_RF_TABLE() \
    load_rf_table_to_mac(&ssv_rf_table); \
    save_rf_table_to_flash()

struct st_rf_table *get_ssv_rf_table()
{
    return &ssv_rf_table;
}


int load_rf_table_from_flash()
{
    volatile uint8_t *ptr = (volatile uint8_t *)&g_sa_cfg;

    memcpy((uint8_t*)&ssv_rf_table, (uint8_t*)ptr, sizeof(ssv_rf_table));
    return 0;    
}

int save_rf_table_to_flash()
{
    uint8_t *ptr = (uint8_t *)OS_MemAlloc(sizeof(g_sa_cfg));
    if (ptr == NULL) 
    {
        printf("[%s] no memory, please check\n", __func__);
        return ERROR_MEMORY_FAILED;
    }
    memset(ptr, 0, sizeof(g_sa_cfg));
    memcpy(ptr, &ssv_rf_table, sizeof(ssv_rf_table));

    cfg_sa_write_cfg((struct sa_cfg*)ptr, sizeof(g_sa_cfg));
    OS_MemFree(ptr);
    return 0;
}

int rf_table_init()
{

    load_rf_table_from_flash();
    if(ssv_rf_table.boot_flag == 0xFF)
    {
        printf("\33[35m ssv_rf_table is replaced by default rf table\33[0m\r\n");
        printf("\33[35m ssv_rf_table is replaced by default rf table\33[0m\r\n");
        printf("\33[35m ssv_rf_table is replaced by default rf table\33[0m\r\n");
        printf("\33[35m ssv_rf_table is replaced by default rf table\33[0m\r\n");
        printf("\33[35m ssv_rf_table is replaced by default rf table\33[0m\r\n");
        build_default_rf_table(&ssv_rf_table);
        load_rf_table_to_mac(&ssv_rf_table);
        save_rf_table_to_flash();
        //dump_rf_table();
    }
    else
    {
        load_rf_table_to_mac(&ssv_rf_table);
        //dump_rf_table();
    }

    return 0;
}

#if (CHIP_ID == 6006) || (CHIP_ID==6020)
int At_RadioRFStart(stParam *param)
{	
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    int cont = 0;
    int interval = 0;
    
    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    cont = atoi(param->argv[0]);
    if(param->argc == 2)
        interval = atoi(param->argv[1]);

    if( (interval < 0) || (interval > 255) )
    {
        printf("interval must between 0 and 255\n");
        return ERROR_INVALID_PARAMETER;
    }
        
    ret = rf_tx_start(cont, interval); 	
    
    return ret;
}

int At_RadioChannel(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    
    int ch = atoi(param->argv[0]);
    int ch_type = NL80211_CHAN_HT20;
    
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("+", param->argv[1]) == 0)
    {
        ch_type = NL80211_CHAN_HT40PLUS;
    }
    else if(strcmp("-", param->argv[1]) == 0)
    {
        ch_type= NL80211_CHAN_HT40MINUS;
    }

    ret = rf_set_ch(ch, 0, ch_type);

    return ret;
}
int At_RadioChannelHT40(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    
    int ch_ht40 = atoi(param->argv[0]);
    
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    ret = rf_set_ch_ht40(ch_ht40);

    return ret;
}
int At_RadioRFRate(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    
    int rate_id = 0;
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    rate_id = atoi(param->argv[0]);
    ret = rf_set_rate(rate_id);

	return ret;
}
int At_RadioRFPacketLen(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    
    int len = 0;
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    len = atoi(param->argv[0]);
    ret = rf_set_packet_len(len);

	return ret;
}
int At_RadioRFBandGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_band_gain(atoi(param->argv[0]));
    
    return ret;
}
int At_RadioRFGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    ret = write_reg_rf_gain(atoi(param->argv[0]));
        
    return ret;
}
int At_RadioRFRateGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int gain_idx = 0;
    struct st_rate_gain rate_config = {0};
        
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    gain_idx = atoi(param->argv[1]); 

    ATCMD_LOG_I("argv0 = %s, \n", param->argv[0]);
    if( strncmp(param->argv[0], "b", 1) == 0 )
    {
        ATCMD_LOG_I("set b mode\n");
        ret = write_reg_rate_gain_b(gain_idx);
    }
    else if( strncmp(param->argv[0], "g", 1) == 0 )
    {
        ATCMD_LOG_I("set g mode\n");
        if(strcmp(param->argv[0], "g6") == 0)
        {
            rate_config.rate1 = gain_idx;
            ret = write_reg_rate_gain_g(rate_config, 0x8); //
        }
        else if(strcmp(param->argv[0], "g12") == 0)
        {
            rate_config.rate2 = gain_idx;
            ret = write_reg_rate_gain_g(rate_config, 0x4);
        }
        else if(strcmp(param->argv[0], "g24") == 0)
        {
            rate_config.rate3 = gain_idx;
            ret = write_reg_rate_gain_g(rate_config, 0x2);
        }
        else if(strcmp(param->argv[0], "g48") == 0)
        {
            rate_config.rate4 = gain_idx;
            ret = write_reg_rate_gain_g(rate_config, 0x1);
        }
        else
        {
            return ERROR_NOT_IMPLEMENT;
        }
    }    
    else if( strncmp(param->argv[0], "20n", 3) == 0 )
    {

        ATCMD_LOG_I("set 20n mode\n");
        if(strcmp(param->argv[0], "20n0") == 0)
        {
            rate_config.rate1 = gain_idx;
            ret = write_reg_rate_gain_20n(rate_config, 0x8);
        }
        else if(strcmp(param->argv[0], "20n1") == 0)
        {
            rate_config.rate2 = gain_idx;
            ret = write_reg_rate_gain_20n(rate_config, 0x4);            
        }
        else if(strcmp(param->argv[0], "20n3") == 0)
        {
            rate_config.rate3 = gain_idx;
            ret = write_reg_rate_gain_20n(rate_config, 0x2);
        }
        else if(strcmp(param->argv[0], "20n5") == 0)
        {
            rate_config.rate4 = gain_idx;
            ret = write_reg_rate_gain_20n(rate_config, 0x1);
        }
        else
        {
            return ERROR_NOT_IMPLEMENT;
        }
    }
    else if( strncmp(param->argv[0], "40n", 3) == 0 )
    {

        ATCMD_LOG_I("set 40n mode\n");

        if(strcmp(param->argv[0], "40n0") == 0)
        {
            rate_config.rate1 = gain_idx;
            ret = write_reg_rate_gain_40n(rate_config, 0x8);
        }
        else if(strcmp(param->argv[0], "40n1") == 0)
        {
            rate_config.rate2 = gain_idx;
            ret = write_reg_rate_gain_40n(rate_config, 0x4);
        }
        else if(strcmp(param->argv[0], "40n3") == 0)
        {
            rate_config.rate3 = gain_idx;
            ret = write_reg_rate_gain_40n(rate_config, 0x2);
        }
        else if(strcmp(param->argv[0], "40n5") == 0)
        {
            rate_config.rate4 = gain_idx;
            ret = write_reg_rate_gain_40n(rate_config, 0x1);
        }
        else
        {
            return ERROR_NOT_IMPLEMENT;
        }
    }
    else
    {
        return ERROR_NOT_IMPLEMENT;
    }
    
    return ret;
}
int At_RadioRFReadTempcs(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    int value = 0;
    get_current_temperature(&value);

    ATCMD_LOG_I("temperature = %d\n", value);
    return ret;
}
int At_RadioRFStop(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	
 #if EXTPA_EN  
	drv_phy_init_extpa_cfg();
	
	drv_phy_init_extpa();
#endif
    ret = rf_tx_stop();
    
    return ret;
}
int At_RadioRFReset(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int rx_mode = 0;

    if(param->argc > 0)
    {
        //printf("argc = %d\n", param->argc);
        rx_mode = atoi(param->argv[0]);
        //printf("rx_mode = %d\n", rx_mode);
    }
    
    ret = rf_rx_reset_ex(rx_mode);

    return ret;
}
int At_RadioRFCount(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    uint32_t err_rxpkt = 0;
    uint32_t total_rxpkt = 0;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    if( atoi(param->argv[0]) == 1 )
    {
        ATCMD_LOG_I("B Mode Count:\n");
        rf_bmode_count(&total_rxpkt, &err_rxpkt);
    }
    else
    {
        ATCMD_LOG_I("G/N Mode Count:\n");
        rf_gmode_count(&total_rxpkt, &err_rxpkt);
    }
        
    ATCMD_LOG_I("crc count = '%ld'\n", err_rxpkt);
    ATCMD_LOG_I("total count = '%ld'\n", total_rxpkt);	

    return ret;
}
int At_RadioRFRSSI(stParam *param)
{
    ATCMD_LOG_I("\n");
    uint8_t rssi;
    
    int ret = rf_get_rssi(&rssi);
#if 0    
    uint8_t rssi_arr[20] = {0};
    uint32_t rssi = 0;
    int i;
    uint8_t max = 0, min = 0;
    for(i=0; i<20; i++)
    {
        rssi_arr[i] = ((*((uint32_t*)0xCCB0F3D8))>>16);
        if(i==0)
        {
            max=min=rssi_arr[0];
        }
        
        if(max < rssi_arr[i])
            max = rssi_arr[i];
        if(min < rssi_arr[i])
            min = rssi_arr[i];

        rssi+=rssi_arr[i];
        OS_MsDelay(2);
    }

    rssi -= max;
    rssi -= min;
#endif
    ATCMD_LOG_I("RSSI = -%d\n", rssi);	

    return ret;
}

#if BLE_EN
int At_RadioRFBleStop(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    u16 packet_count = 0, pkt_err = 0;

    ble_dtm_end(&packet_count, &pkt_err);
    rf_ble_enable(0);
    return ret;
}

int At_RadioRFBleReset(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    u8 rfch = 0;

    ble_dtm_reset();
    rfch = GetBleChannelVariable();
    ble_dtm_rx(rfch);
    return ret;
}

int At_RadioRFBleCount(stParam *param)
{
    int ret = ERROR_SUCCESS;
    u16 count = 0, err_cnt = 0;
    ATCMD_LOG_I("\n");

    ble_dtm_end(&count, &err_cnt);

    ATCMD_LOG_I("crc count = '%d'\n", err_cnt);
    ATCMD_LOG_I("total count = '%d'\n", count + err_cnt);

    return ret;
}


#endif
int At_RadioEnableTCSR(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    ret = rf_enable_tcsr(atoi(param->argv[0]));
    return ret;
}
int At_RadioRFDump(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    dump_rf_table();
    return ret;
}
int At_RfCaliDPD(stParam *param)    
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
   ret = write_reg_padpd_cali(atoi(param->argv[0]));
     
    return ret;    

}
int At_RfManuDPD(stParam *param)    
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    ret = rf_manu_padpd_cali();
     
    return ret;    

}
int At_RadioRFFreqoffset(stParam *param)    
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_freq_xi_xo(atoi(param->argv[0]), atoi(param->argv[1]), 0x3);
        
    return ret;
}
int At_RadioRFFreqoffset_readxo(stParam *param)    
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    uint32_t xo_value = 0;
    ret = rf_freqoffset_readxo(&xo_value);
    
    ATCMD_LOG_I("%s=%ld\n", ATCMD_RF_FREQOFFSET_READXO, xo_value);
         
    return ret;
}   
int At_RadioRFFreqoffset_readxi(stParam *param)    
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    uint32_t xi_value = 0;
    ret = rf_freqoffset_readxi(&xi_value);

    ATCMD_LOG_I("%s=%ld\n", ATCMD_RF_FREQOFFSET_READXI, xi_value);
         
    return ret;
}    
int At_RadioRF2Gpa1(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_2gpa(atoi(param->argv[0]), 0, 0, 0, 0x8);
        
    return ret;
}    
int At_RadioRF2Gpa2(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_2gpa(0, atoi(param->argv[0]), 0, 0, 0x4);
        
    return ret;
}   
int At_RadioRF2Gpa3(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_2gpa(0, 0, atoi(param->argv[0]), 0, 0x2);
        
    return ret;
}   
int At_RadioRF2GpaBias(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_2gpa(0, 0, 0, atoi(param->argv[0]), 0x1);
        
    return ret;
}   
int At_RadioRF2GpaCell(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_2gpa_cell(atoi(param->argv[0]));
        
    return ret;
}   
int At_RadioRF2GpaCap(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_2gpa_cap(atoi(param->argv[0]));
        
    return ret;
}   
int At_RadioRFLdo(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_rxfe(atoi(param->argv[0]));
        
    return ret;
}     
int At_RadioRFDcdc(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_dcdc(atoi(param->argv[0]));
        
    return ret;
} 
int At_RadioRFDcdcv(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_ldo(atoi(param->argv[0]), 0, 0x2);
        
    return ret;
} 
int At_RadioRFDldov(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_ldo(0, atoi(param->argv[0]), 0x1);
        
    return ret;
}     
int At_RadioRFXoldo(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_xoldo(atoi(param->argv[0]));
        
    return ret;
}     
int At_RadioRFRxPadCh13(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_rxpad_ch13(atoi(param->argv[0]));
        
    return ret;
}

int At_RadioRFTempBoundary(stParam *param)
{

    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    set_temper_value(atoi(param->argv[0]), atoi(param->argv[1]));
    ssv_rf_table.low_boundary = atoi(param->argv[0]);
    ssv_rf_table.high_boundary = atoi(param->argv[1]);
    SAVE_RF_TABLE();
    
    return ret;
}
int At_RfTableRT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    //ATCMD_LOG_I("arg1 = %s, arg2 = %s, ... , arg18 = %s\n", param->argv[0], param->argv[1], param->argv[17]);
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", ATCMD_RF_TABLE_RT
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[0]
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[1]
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[2]
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[3]
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[4]
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[5]
                                                                                                                                     , ssv_rf_table.rt_config.band_gain[6]
                                                                                                                                     , ssv_rf_table.rt_config.freq_xi
                                                                                                                                     , ssv_rf_table.rt_config.freq_xo
                                                                                                                                     , ssv_rf_table.rt_config.ldo_rxafe
                                                                                                                                     , ssv_rf_table.rt_config.ldo_dcdcv
                                                                                                                                     , ssv_rf_table.rt_config.ldo_dldov
                                                                                                                                     , ssv_rf_table.rt_config.pa_vcas1
                                                                                                                                     , ssv_rf_table.rt_config.pa_vcas2
                                                                                                                                     , ssv_rf_table.rt_config.pa_vcas3
                                                                                                                                     , ssv_rf_table.rt_config.pa_bias
                                                                                                                                     , ssv_rf_table.rt_config.pa_cap
                                                                                                                                     , ssv_rf_table.rt_config.padpd_cali
                                                                                                                                     );
    }
    else
    {
        struct st_tempe_table tempe_config;
        tempe_config.band_gain[0] = atoi(param->argv[0]);
        tempe_config.band_gain[1] = atoi(param->argv[1]);
        tempe_config.band_gain[2] = atoi(param->argv[2]);
        tempe_config.band_gain[3] = atoi(param->argv[3]);
        tempe_config.band_gain[4] = atoi(param->argv[4]);
        tempe_config.band_gain[5] = atoi(param->argv[5]);
        tempe_config.band_gain[6] = atoi(param->argv[6]);
        
        tempe_config.freq_xi = atoi(param->argv[7]);
        tempe_config.freq_xo = atoi(param->argv[8]);
        tempe_config.ldo_rxafe = atoi(param->argv[9]);
        tempe_config.ldo_dcdcv = atoi(param->argv[10]);
        tempe_config.ldo_dldov = atoi(param->argv[11]);

        tempe_config.pa_vcas1 = atoi(param->argv[12]);
        tempe_config.pa_vcas2 = atoi(param->argv[13]);
        tempe_config.pa_vcas3 = atoi(param->argv[14]);
        tempe_config.pa_bias = atoi(param->argv[15]);
        tempe_config.pa_cap = atoi(param->argv[16]);
        tempe_config.padpd_cali = atoi(param->argv[17]);

        get_current_tempe_state(&now_temp_state, &now_temp_value);
        if(now_temp_state == 0)
        ret = write_reg_tempe_table(tempe_config);

        if(ret != 0)
            return ret;

        memcpy(&ssv_rf_table.rt_config, &tempe_config, sizeof(tempe_config) );
        SAVE_RF_TABLE();
    }
        
    return ret;
}   

int At_RfTableHT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    //ATCMD_LOG_I("arg1 = %s, arg2 = %s, ... , arg18 = %s\n", param->argv[0], param->argv[1], param->argv[17]);
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", ATCMD_RF_TABLE_HT
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[0]
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[1]
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[2]
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[3]
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[4]
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[5]
                                                                                                                                     , ssv_rf_table.ht_config.band_gain[6]
                                                                                                                                     , ssv_rf_table.ht_config.freq_xi
                                                                                                                                     , ssv_rf_table.ht_config.freq_xo
                                                                                                                                     , ssv_rf_table.ht_config.ldo_rxafe
                                                                                                                                     , ssv_rf_table.ht_config.ldo_dcdcv
                                                                                                                                     , ssv_rf_table.ht_config.ldo_dldov
                                                                                                                                     , ssv_rf_table.ht_config.pa_vcas1
                                                                                                                                     , ssv_rf_table.ht_config.pa_vcas2
                                                                                                                                     , ssv_rf_table.ht_config.pa_vcas3
                                                                                                                                     , ssv_rf_table.ht_config.pa_bias
                                                                                                                                     , ssv_rf_table.ht_config.pa_cap
                                                                                                                                     , ssv_rf_table.ht_config.padpd_cali
                                                                                                                                     );
    }
    else
    {
        struct st_tempe_table tempe_config;
        tempe_config.band_gain[0] = atoi(param->argv[0]);
        tempe_config.band_gain[1] = atoi(param->argv[1]);
        tempe_config.band_gain[2] = atoi(param->argv[2]);
        tempe_config.band_gain[3] = atoi(param->argv[3]);
        tempe_config.band_gain[4] = atoi(param->argv[4]);
        tempe_config.band_gain[5] = atoi(param->argv[5]);
        tempe_config.band_gain[6] = atoi(param->argv[6]);
        
        tempe_config.freq_xi = atoi(param->argv[7]);
        tempe_config.freq_xo = atoi(param->argv[8]);
        tempe_config.ldo_rxafe = atoi(param->argv[9]);
        tempe_config.ldo_dcdcv = atoi(param->argv[10]);
        tempe_config.ldo_dldov = atoi(param->argv[11]);

        tempe_config.pa_vcas1 = atoi(param->argv[12]);
        tempe_config.pa_vcas2 = atoi(param->argv[13]);
        tempe_config.pa_vcas3 = atoi(param->argv[14]);
        tempe_config.pa_bias = atoi(param->argv[15]);
        tempe_config.pa_cap = atoi(param->argv[16]);
        tempe_config.padpd_cali = atoi(param->argv[17]);

        get_current_tempe_state(&now_temp_state, &now_temp_value);
        if(now_temp_state == 1)
        ret = write_reg_tempe_table(tempe_config);

        if(ret != 0)
            return ret;

        memcpy(&ssv_rf_table.ht_config, &tempe_config, sizeof(tempe_config) );
        SAVE_RF_TABLE();
    }
    return ret;
}      
int At_RfTableLT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    //ATCMD_LOG_I("arg1 = %s, arg2 = %s, ... , arg18 = %s\n", param->argv[0], param->argv[1], param->argv[17]);
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", ATCMD_RF_TABLE_LT
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[0]
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[1]
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[2]
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[3]
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[4]
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[5]
                                                                                                                                     , ssv_rf_table.lt_config.band_gain[6]
                                                                                                                                     , ssv_rf_table.lt_config.freq_xi
                                                                                                                                     , ssv_rf_table.lt_config.freq_xo
                                                                                                                                     , ssv_rf_table.lt_config.ldo_rxafe
                                                                                                                                     , ssv_rf_table.lt_config.ldo_dcdcv
                                                                                                                                     , ssv_rf_table.lt_config.ldo_dldov
                                                                                                                                     , ssv_rf_table.lt_config.pa_vcas1
                                                                                                                                     , ssv_rf_table.lt_config.pa_vcas2
                                                                                                                                     , ssv_rf_table.lt_config.pa_vcas3
                                                                                                                                     , ssv_rf_table.lt_config.pa_bias
                                                                                                                                     , ssv_rf_table.lt_config.pa_cap
                                                                                                                                     , ssv_rf_table.lt_config.padpd_cali
                                                                                                                                     );
    }
    else
    {
        struct st_tempe_table tempe_config;
        tempe_config.band_gain[0] = atoi(param->argv[0]);
        tempe_config.band_gain[1] = atoi(param->argv[1]);
        tempe_config.band_gain[2] = atoi(param->argv[2]);
        tempe_config.band_gain[3] = atoi(param->argv[3]);
        tempe_config.band_gain[4] = atoi(param->argv[4]);
        tempe_config.band_gain[5] = atoi(param->argv[5]);
        tempe_config.band_gain[6] = atoi(param->argv[6]);
        
        tempe_config.freq_xi = atoi(param->argv[7]);
        tempe_config.freq_xo = atoi(param->argv[8]);
        tempe_config.ldo_rxafe = atoi(param->argv[9]);
        tempe_config.ldo_dcdcv = atoi(param->argv[10]);
        tempe_config.ldo_dldov = atoi(param->argv[11]);

        tempe_config.pa_vcas1 = atoi(param->argv[12]);
        tempe_config.pa_vcas2 = atoi(param->argv[13]);
        tempe_config.pa_vcas3 = atoi(param->argv[14]);
        tempe_config.pa_bias = atoi(param->argv[15]);
        tempe_config.pa_cap = atoi(param->argv[16]);
        tempe_config.padpd_cali = atoi(param->argv[17]);

        get_current_tempe_state(&now_temp_state, &now_temp_value);
        if(now_temp_state == 2)
        ret = write_reg_tempe_table(tempe_config);

        if(ret != 0)
            return ret;

        memcpy(&ssv_rf_table.lt_config, &tempe_config, sizeof(tempe_config) );
        SAVE_RF_TABLE();
    }
    return ret;
}      
#if BLE_EN

uint32_t g_rfbleRate = 0;/*DTM tx pattern */

int At_EnableBleMode(stParam *param)
{
    ATCMD_LOG_I("At_EnableBleMode\n");
    u8 val=0;
    s32 ret =0;
    if (param->argc >= 1)
    {
        val = atoi(param->argv[0]);
        ATCMD_LOG_I("Set BleMode %d\n", val);
        ATCMD_LOG_I("0:MESH, 1:DTM, 2:HCI %d\n");
        ssv_rf_table.ble_dtm_enable = val;
        SAVE_RF_TABLE();
        return ERROR_SUCCESS;
    }
    else {
        ATCMD_LOG_E("At_EnableBleMode error\n");
        return ERROR_INVALID_PARAMETER;
    }

}

u8 convert_freq_to_ble_channel(u8 freq_ch)
{
    u8 rfch = 0;

    if (freq_ch == 0)
        rfch = 37;
    else if (freq_ch == 12)
        rfch = 38;
    else if (freq_ch == 39)
        rfch = 39;
    else if (freq_ch >= 1 && freq_ch <= 11)
        rfch = (freq_ch - 1);
    else if (freq_ch >= 13 && freq_ch <= 38)
        rfch = (freq_ch - 2);

    return rfch;
}

int At_RadioRFBleStart(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    u8 rfch = 0;
    int count = 0;
    int interval = 0, packet_len = 0;
    int pattern = 0;
    uint8_t rf_enable = 1;

    rfch = GetBleChannelVariable();
    count = atoi(param->argv[0]);
    if (param->argc < 2)
        interval = 0;
    else
        interval = atoi(param->argv[1]);

    if (param->argc < 3)
        packet_len = 37;
    else
        packet_len = atoi(param->argv[2]);

    if (param->argc < 4)
        rf_enable = 1;//only enable rf_ble_enable
    else
        rf_enable = atoi(param->argv[3]);// rf_enable 2 == enable temp compensation log

    rf_ble_enable(rf_enable);
    ble_dtm_tx(rfch, count, packet_len, g_rfbleRate);
    return ret;
}

extern u32 drv_phy_set_rfch(u32 rfch);
int At_RadioBleChannel(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    u8 rfch = 0;
    u8 blech = 0;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    rfch = atoi(param->argv[0]);
    blech = convert_freq_to_ble_channel(rfch);
    //SetBleChannelVariable(blech);
    drv_phy_set_rfch(blech);
    ATCMD_LOG_I("Set blech %d\n", blech);

    return ret;
}

int At_RadioRFBleRate(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    g_rfbleRate = atoi(param->argv[0]);
    ATCMD_LOG_I("Set g_rfbleRate %d\n", g_rfbleRate);
    return ret;
}

int At_Rf_BleTableRT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d\n", ATCMD_RF_BLE_TABLE_RT
            , ssv_rf_table.ble_rt_config.band_gain[0], ssv_rf_table.ble_rt_config.band_gain[1]);
    }
    else
    {
        ssv_rf_table.ble_rt_config.band_gain[0] = atoi(param->argv[0]);
        ssv_rf_table.ble_rt_config.band_gain[1] = atoi(param->argv[1]);
        SetBlePower(GetBleChannelVariable(), EN_NORMAL_TEMPERATURE_STATE, true);
        SAVE_RF_TABLE();
    }

    return ret;

}

int At_Rf_BleTableHT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d\n", ATCMD_RF_BLE_TABLE_HT
            ,ssv_rf_table.ble_ht_config.band_gain[0] ,ssv_rf_table.ble_ht_config.band_gain[1]);
    }
    else
    {
        ssv_rf_table.ble_ht_config.band_gain[0] = atoi(param->argv[0]);
        ssv_rf_table.ble_ht_config.band_gain[1] = atoi(param->argv[1]);
        SetBlePower(GetBleChannelVariable(), EN_HIGH_TEMPERATURE_STATE, true);
        SAVE_RF_TABLE();
    }

    return ret;
}

int At_Rf_BleTableLT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d\n", ATCMD_RF_BLE_TABLE_LT
            ,ssv_rf_table.ble_lt_config.band_gain[0] ,ssv_rf_table.ble_lt_config.band_gain[1]);
    }
    else
    {
        ssv_rf_table.ble_lt_config.band_gain[0] = atoi(param->argv[0]);
        ssv_rf_table.ble_lt_config.band_gain[1] = atoi(param->argv[1]);
        SetBlePower(GetBleChannelVariable(), EN_LOW_TEMPERATURE_STATE, true);
        SAVE_RF_TABLE();
    }

    return ret;
}
#endif

int At_RfTableGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("RF Gain = %d\n", ssv_rf_table.rf_gain );
    }
    else
    {
        uint8_t rf_gain = atoi(param->argv[0]);
        ret = write_reg_rf_gain(rf_gain);
        if(ret != 0)
            return ret;
        ssv_rf_table.rf_gain = rf_gain;
        SAVE_RF_TABLE(); 
    }
    return ret;
}
int At_RfTableBRateGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("B Mode Rate Gain = %d\n", ssv_rf_table.rate_gain_b);
    }
    else
    {
        uint8_t rate_gain = atoi(param->argv[0]);
        ret = write_reg_rate_gain_b(rate_gain);
        if(ret != 0)
            return ret;
        ssv_rf_table.rate_gain_b = rate_gain;
        SAVE_RF_TABLE();
    }
    return ret;
}   
int At_RfTableGRateGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("G Mode Rate Gain = %d,%d,%d,%d\n", ssv_rf_table.rate_config_g.rate1, 
                                                                              ssv_rf_table.rate_config_g.rate2, 
                                                                              ssv_rf_table.rate_config_g.rate3, 
                                                                              ssv_rf_table.rate_config_g.rate4 );
    }
    else
    {
        struct st_rate_gain g_rate_gain = {0};
        g_rate_gain.rate1 = atoi(param->argv[0]);
        g_rate_gain.rate2 = atoi(param->argv[1]);
        g_rate_gain.rate3 = atoi(param->argv[2]);
        g_rate_gain.rate4 = atoi(param->argv[3]);
        
        ret = write_reg_rate_gain_g(g_rate_gain, 0xf);
        if(ret != 0)
            return ret;

        memcpy(&ssv_rf_table.rate_config_g, &g_rate_gain, sizeof(g_rate_gain));
        SAVE_RF_TABLE(); 
    }
    return ret;
}   
int At_RfTable20NRateGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("20N Mode Rate Gain = %d,%d,%d,%d\n", ssv_rf_table.rate_config_20n.rate1, 
                                                                              ssv_rf_table.rate_config_20n.rate2, 
                                                                              ssv_rf_table.rate_config_20n.rate3, 
                                                                              ssv_rf_table.rate_config_20n.rate4 );
    }
    else
    {
        struct st_rate_gain rate_gain_20n = {0};
        rate_gain_20n.rate1 = atoi(param->argv[0]);
        rate_gain_20n.rate2 = atoi(param->argv[1]);
        rate_gain_20n.rate3 = atoi(param->argv[2]);
        rate_gain_20n.rate4 = atoi(param->argv[3]);
        
        ret = write_reg_rate_gain_20n(rate_gain_20n, 0xf);
        if(ret != 0)
            return ret;

        memcpy(&ssv_rf_table.rate_config_20n, &rate_gain_20n, sizeof(rate_gain_20n));
        SAVE_RF_TABLE(); 
    }
    return ret;
}   
int At_RfTable40NRateGain(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("40N Mode Rate Gain = %d,%d,%d,%d\n", ssv_rf_table.rate_config_40n.rate1, 
                                                                              ssv_rf_table.rate_config_40n.rate2, 
                                                                              ssv_rf_table.rate_config_40n.rate3, 
                                                                              ssv_rf_table.rate_config_40n.rate4 );
    }
    else
    {
        struct st_rate_gain rate_gain_40n = {0};
        rate_gain_40n.rate1 = atoi(param->argv[0]);
        rate_gain_40n.rate2 = atoi(param->argv[1]);
        rate_gain_40n.rate3 = atoi(param->argv[2]);
        rate_gain_40n.rate4 = atoi(param->argv[3]);
        
        ret = write_reg_rate_gain_40n(rate_gain_40n, 0xf);
        if(ret != 0)
            return ret;

        memcpy(&ssv_rf_table.rate_config_40n, &rate_gain_40n, sizeof(rate_gain_40n));
        SAVE_RF_TABLE(); 
    }
    return ret;
}   

int At_RfTableDcdc(stParam *param)
{
    int ret = ERROR_SUCCESS;	

    ATCMD_LOG_I("\n");
    
    if (param->argc < 1)
        return ERROR_INVALID_PARAMETER;
    
    if (strcmp("?", param->argv[0]) == 0)
    {
        ATCMD_LOG_I("DCDC flag = %d\n", ssv_rf_table.dcdc_flag); 
    }
    else
    {
        int dcdc_flag = atoi(param->argv[0]);
        
        ret = write_reg_dcdc(dcdc_flag);
        if (ret != 0)
            return ret;
        
        ssv_rf_table.dcdc_flag = dcdc_flag;
        SAVE_RF_TABLE(); 
    }
    return ret;
}

int At_RfTableTxlowpower(stParam *param)
{
    int ret = ERROR_SUCCESS;	

    ATCMD_LOG_I("\n");
    
    if (param->argc < 1)
        return ERROR_INVALID_PARAMETER;
    
    if (strcmp("?", param->argv[0]) == 0)
    {
        ATCMD_LOG_I("DCDC flag = %d\n", ssv_rf_table.tx_lowpower_flag); 
    }
    else
    {
        int tx_lowpower_flag = atoi(param->argv[0]);
        
        ssv_rf_table.tx_lowpower_flag = tx_lowpower_flag;
        SAVE_RF_TABLE(); 
    }
    return ret;
}

int At_RfTableExtpadpd(stParam *param)
{
    int ret = ERROR_SUCCESS;	

    ATCMD_LOG_I("\n");
    
    if (param->argc < 1)
        return ERROR_INVALID_PARAMETER;
    
    if (strcmp("?", param->argv[0]) == 0)
    {
        ATCMD_LOG_I("DCDC flag = %d\n", ssv_rf_table.extpadpd_flag); 
    }
    else
    {
        int extpadpd_flag = atoi(param->argv[0]);
        
        ssv_rf_table.extpadpd_flag = extpadpd_flag;
        SAVE_RF_TABLE(); 
    }
    return ret;
}

int At_RfTableExtpadpd_setting(stParam *param)
{
    int ret = ERROR_SUCCESS;	

    ATCMD_LOG_I("\n");
    
    if (param->argc < 1)
        return ERROR_INVALID_PARAMETER;
    
    if (strcmp("?", param->argv[0]) == 0)
    {
        #if 0
        ATCMD_LOG_I("Extpadpd_setting = 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,\n"
            , ssv_rf_table.extpadpd_setting[0], ssv_rf_table.extpadpd_setting[1], ssv_rf_table.extpadpd_setting[2], ssv_rf_table.extpadpd_setting[3], ssv_rf_table.extpadpd_setting[4], ssv_rf_table.extpadpd_setting[5], ssv_rf_table.extpadpd_setting[6], ssv_rf_table.extpadpd_setting[7], ssv_rf_table.extpadpd_setting[8], ssv_rf_table.extpadpd_setting[9]
            , ssv_rf_table.extpadpd_setting[10], ssv_rf_table.extpadpd_setting[11], ssv_rf_table.extpadpd_setting[12], ssv_rf_table.extpadpd_setting[13], ssv_rf_table.extpadpd_setting[14], ssv_rf_table.extpadpd_setting[15], ssv_rf_table.extpadpd_setting[16], ssv_rf_table.extpadpd_setting[17], ssv_rf_table.extpadpd_setting[18], ssv_rf_table.extpadpd_setting[19]
            , ssv_rf_table.extpadpd_setting[20], ssv_rf_table.extpadpd_setting[21], ssv_rf_table.extpadpd_setting[22], ssv_rf_table.extpadpd_setting[23], ssv_rf_table.extpadpd_setting[24], ssv_rf_table.extpadpd_setting[25], ssv_rf_table.extpadpd_setting[26], ssv_rf_table.extpadpd_setting[27], ssv_rf_table.extpadpd_setting[28], ssv_rf_table.extpadpd_setting[29]
            , ssv_rf_table.extpadpd_setting[30], ssv_rf_table.extpadpd_setting[31], ssv_rf_table.extpadpd_setting[32], ssv_rf_table.extpadpd_setting[33], ssv_rf_table.extpadpd_setting[34], ssv_rf_table.extpadpd_setting[35], ssv_rf_table.extpadpd_setting[36], ssv_rf_table.extpadpd_setting[37], ssv_rf_table.extpadpd_setting[38], ssv_rf_table.extpadpd_setting[39]
            , ssv_rf_table.extpadpd_setting[40], ssv_rf_table.extpadpd_setting[41], ssv_rf_table.extpadpd_setting[42], ssv_rf_table.extpadpd_setting[43], ssv_rf_table.extpadpd_setting[44], ssv_rf_table.extpadpd_setting[45], ssv_rf_table.extpadpd_setting[46], ssv_rf_table.extpadpd_setting[47], ssv_rf_table.extpadpd_setting[48], ssv_rf_table.extpadpd_setting[49]
            , ssv_rf_table.extpadpd_setting[50], ssv_rf_table.extpadpd_setting[51], ssv_rf_table.extpadpd_setting[52], ssv_rf_table.extpadpd_setting[53], ssv_rf_table.extpadpd_setting[54], ssv_rf_table.extpadpd_setting[55], ssv_rf_table.extpadpd_setting[56], ssv_rf_table.extpadpd_setting[57]
            );
        #endif
    }
    else if(RF_TABLE_EXTPADPD_NUM == param->argc)
    {
        uint16_t extpadpd_setting[RF_TABLE_EXTPADPD_NUM] = {0};
        int i = 0;

        ATCMD_LOG_I("padpd set start\n");
        for(i = 0; i < RF_TABLE_EXTPADPD_NUM; i++)
        {
            extpadpd_setting[i] = (uint16_t)strtoul((const char *)param->argv[i], NULL, 16);
        }    
        ATCMD_LOG_I("1~9:   0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x\n", extpadpd_setting[0], extpadpd_setting[1],extpadpd_setting[2], extpadpd_setting[3], extpadpd_setting[4], extpadpd_setting[5], extpadpd_setting[6], extpadpd_setting[7], extpadpd_setting[8], extpadpd_setting[9]);
        ATCMD_LOG_I("10~19: 0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x\n", extpadpd_setting[10], extpadpd_setting[11],extpadpd_setting[12], extpadpd_setting[13], extpadpd_setting[14], extpadpd_setting[15], extpadpd_setting[16], extpadpd_setting[17], extpadpd_setting[18], extpadpd_setting[19]);
        ATCMD_LOG_I("20~29: 0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x\n", extpadpd_setting[20], extpadpd_setting[21],extpadpd_setting[22], extpadpd_setting[23], extpadpd_setting[24], extpadpd_setting[25], extpadpd_setting[26], extpadpd_setting[27], extpadpd_setting[28], extpadpd_setting[29]);
        ATCMD_LOG_I("30~39: 0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x\n", extpadpd_setting[30], extpadpd_setting[31],extpadpd_setting[32], extpadpd_setting[33], extpadpd_setting[34], extpadpd_setting[35], extpadpd_setting[36], extpadpd_setting[37], extpadpd_setting[38], extpadpd_setting[39]);
        ATCMD_LOG_I("40~49: 0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x\n", extpadpd_setting[40], extpadpd_setting[41],extpadpd_setting[42], extpadpd_setting[43], extpadpd_setting[44], extpadpd_setting[45], extpadpd_setting[46], extpadpd_setting[47], extpadpd_setting[48], extpadpd_setting[49]);
        ATCMD_LOG_I("50~57: 0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x,0x%04x\n", extpadpd_setting[50], extpadpd_setting[51],extpadpd_setting[52], extpadpd_setting[53], extpadpd_setting[54], extpadpd_setting[55], extpadpd_setting[56], extpadpd_setting[57]);

        //ssv_rf_table.extpadpd_flag = ext_padpd_flag;
        memcpy(&ssv_rf_table.extpadpd_setting, &extpadpd_setting, sizeof(extpadpd_setting));
        SAVE_RF_TABLE(); 
    }    
    return ret;
}

int At_RfTablePadpd_get(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    ret = read_reg_extpadpd();

    return ret;

}

#if EXTPA_EN
int At_RfTableExtpa(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("extpa parametes = %d,%d,%d,%d,%d,%d\n",
            ssv_rf_table.extpa_tbl.lna_trigger_2G, ssv_rf_table.extpa_tbl.lna_trigger_5G, 
            ssv_rf_table.extpa_tbl.rssi_lna_on_offset, ssv_rf_table.extpa_tbl.rssi_lna_off_offset,
            ssv_rf_table.extpa_tbl.rssi_5g_lna_on_offset, ssv_rf_table.extpa_tbl.rssi_5g_lna_off_offset);
    }
    else
    {
        ssv_rf_table.extpa_tbl.lna_trigger_2G = atoi(param->argv[0]);
        ssv_rf_table.extpa_tbl.lna_trigger_5G = atoi(param->argv[1]);
        ssv_rf_table.extpa_tbl.rssi_lna_on_offset = atoi(param->argv[2]);
        ssv_rf_table.extpa_tbl.rssi_lna_off_offset = atoi(param->argv[3]);
        ssv_rf_table.extpa_tbl.rssi_5g_lna_on_offset = atoi(param->argv[4]);
        ssv_rf_table.extpa_tbl.rssi_5g_lna_off_offset = atoi(param->argv[5]);
        SAVE_RF_TABLE();
		ATCMD_LOG_I("extpa parametes = %d,%d,%d,%d,%d,%d\n",
            ssv_rf_table.extpa_tbl.lna_trigger_2G, ssv_rf_table.extpa_tbl.lna_trigger_5G, 
            ssv_rf_table.extpa_tbl.rssi_lna_on_offset, ssv_rf_table.extpa_tbl.rssi_lna_off_offset,
            ssv_rf_table.extpa_tbl.rssi_5g_lna_on_offset, ssv_rf_table.extpa_tbl.rssi_5g_lna_off_offset);
		drv_phy_init_extpa_cfg();
	}
    return ret;
}  

int At_RfExtpaEn(stParam *param)
{
     TCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("extpa enable = %d\n", ssv_rf_table.extpa_tbl.extpa_en);
    }
    else
    {
        ssv_rf_table.extpa_tbl.extpa_en = atoi(param->argv[0]);
        if (ssv_rf_table.extpa_tbl.extpa_en == 1){
            if (ssv_rf_table.version == 1){
                ssv_rf_table.version = 2;
                ssv_rf_table.extpa_tbl.lna_trigger_2G=0;
                ssv_rf_table.extpa_tbl.lna_trigger_5G=1;
                ssv_rf_table.extpa_tbl.rssi_lna_on_offset=8;
                ssv_rf_table.extpa_tbl.rssi_lna_off_offset=0xc;
                ssv_rf_table.extpa_tbl.rssi_5g_lna_on_offset=0xd;
                ssv_rf_table.extpa_tbl.rssi_5g_lna_off_offset=0;
            }
        }
        SAVE_RF_TABLE(); 
    }
    return ret;   
}

int At_RfExtpaStatus(stParam *param)
{
    ATCMD_LOG_I("\n");    
    drv_phy_show_extpa_status();
    return ERROR_SUCCESS;
}

int At_RfAutoLnaEn(stParam *param)
{
    ATCMD_LOG_I("\n");
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if (atoi(param->argv[0]) == 1)
        drv_phy_set_auto_lna(true);
    else
        drv_phy_set_auto_lna(false);

    return ERROR_SUCCESS;
}

int At_RfSetExtLNA(stParam *param)
{
    ATCMD_LOG_I("\n");
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if (atoi(param->argv[0]) == 1)
        drv_phy_set_external_lna_pin(true);
    else
        drv_phy_set_external_lna_pin(false);    
    return ERROR_SUCCESS;
}
#endif
//5G
int At_Rf5GBBScale(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	
    
    if(param->argc < 4)
        return ERROR_INVALID_PARAMETER;
  
    if( write_reg_5g_bbscale_5100(atoi(param->argv[0])) != 0)
        return -1;
    if( write_reg_5g_bbscale_5500(atoi(param->argv[1])) != 0)
        return -1;
    if( write_reg_5g_bbscale_5700(atoi(param->argv[2])) != 0)
        return -1;
    if( write_reg_5g_bbscale_5900(atoi(param->argv[3])) != 0)
        return -1;

    return ret;
}
int At_Rf5GBias1(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_5g_bias1(strtoul(param->argv[0], NULL, 16));
        
    return ret;
}
int At_Rf5GBias2(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    ret = write_reg_5g_bias2(strtoul(param->argv[0], NULL, 16));
        
    return ret;
}
int At_Rf5GTableRT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d,%d\n", ATCMD_RF_5GTABLE_RT, ssv_rf_table.rt_5g_config.bbscale_band0
                                                                                           , ssv_rf_table.rt_5g_config.bbscale_band1
                                                                                           , ssv_rf_table.rt_5g_config.bbscale_band2
                                                                                           , ssv_rf_table.rt_5g_config.bbscale_band3);
        return ret;
    }
    
    if(param->argc < 4)
        return ERROR_INVALID_PARAMETER;

    struct st_tempe_5g_table tempe_config = {0};
     
    tempe_config.bbscale_band0 = atoi(param->argv[0]);
    tempe_config.bbscale_band1 = atoi(param->argv[1]);
    tempe_config.bbscale_band2 = atoi(param->argv[2]);
    tempe_config.bbscale_band3 = atoi(param->argv[3]);
    tempe_config.bias1 = ssv_rf_table.rt_5g_config.bias1;
    tempe_config.bias2 = ssv_rf_table.rt_5g_config.bias2;

    get_current_tempe_state(&now_temp_state, &now_temp_value);
    if(now_temp_state == 0)
    ret = write_reg_tempe_5g_table(tempe_config);

    if(ret != 0)
        return ret;
        
    memcpy(&ssv_rf_table.rt_5g_config, &tempe_config, sizeof(tempe_config) );    
    SAVE_RF_TABLE(); 

    return ret;    
}
int At_Rf5GTableHT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d,%d\n", ATCMD_RF_5GTABLE_HT, ssv_rf_table.ht_5g_config.bbscale_band0
                                                                                           , ssv_rf_table.ht_5g_config.bbscale_band1
                                                                                           , ssv_rf_table.ht_5g_config.bbscale_band2
                                                                                           , ssv_rf_table.ht_5g_config.bbscale_band3);
        return ret;
    }
    
    if(param->argc < 4)
        return ERROR_INVALID_PARAMETER;

    struct st_tempe_5g_table tempe_config = {0};
     
    tempe_config.bbscale_band0 = atoi(param->argv[0]);
    tempe_config.bbscale_band1 = atoi(param->argv[1]);
    tempe_config.bbscale_band2 = atoi(param->argv[2]);
    tempe_config.bbscale_band3 = atoi(param->argv[3]);
    tempe_config.bias1 = ssv_rf_table.ht_5g_config.bias1;
    tempe_config.bias2 = ssv_rf_table.ht_5g_config.bias2;

    get_current_tempe_state(&now_temp_state, &now_temp_value);
    if(now_temp_state == 1)
    ret = write_reg_tempe_5g_table(tempe_config);

    if(ret != 0)
        return ret;
        
    memcpy(&ssv_rf_table.ht_5g_config, &tempe_config, sizeof(tempe_config) );    
    SAVE_RF_TABLE(); 

    return ret;    
}
int At_Rf5GTableLT(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int now_temp_state = 0;
    int now_temp_value = 0;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d,%d\n", ATCMD_RF_5GTABLE_LT, ssv_rf_table.lt_5g_config.bbscale_band0
                                                                                          , ssv_rf_table.lt_5g_config.bbscale_band1
                                                                                          , ssv_rf_table.lt_5g_config.bbscale_band2
                                                                                          , ssv_rf_table.lt_5g_config.bbscale_band3);
        return ret;
    }
    
    if(param->argc < 4)
        return ERROR_INVALID_PARAMETER;

    struct st_tempe_5g_table tempe_config = {0};
     
    tempe_config.bbscale_band0 = atoi(param->argv[0]);
    tempe_config.bbscale_band1 = atoi(param->argv[1]);
    tempe_config.bbscale_band2 = atoi(param->argv[2]);
    tempe_config.bbscale_band3 = atoi(param->argv[3]);
    tempe_config.bias1 = ssv_rf_table.lt_5g_config.bias1;
    tempe_config.bias2 = ssv_rf_table.lt_5g_config.bias2;

    get_current_tempe_state(&now_temp_state, &now_temp_value);
    if(now_temp_state == 2)
    ret = write_reg_tempe_5g_table(tempe_config);

    if(ret != 0)
        return ret;
        
    memcpy(&ssv_rf_table.lt_5g_config, &tempe_config, sizeof(tempe_config) );    
    SAVE_RF_TABLE(); 

    return ret; 
}
int At_Rf5GTableBIAS1(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	
    uint32_t rt_bias1 = 0, ht_bias1 = 0, lt_bias1 = 0;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=0x%x,0x%x,0x%x\n", ATCMD_RF_5GTABLE_BIAS1, ssv_rf_table.rt_5g_config.bias1
                                                                                           , ssv_rf_table.ht_5g_config.bias1
                                                                                           , ssv_rf_table.lt_5g_config.bias1);
        return ret;
    }
    
    if(param->argc < 3)
        return ERROR_INVALID_PARAMETER;

    rt_bias1 = strtoul(param->argv[0], NULL, 16);
    ht_bias1 = strtoul(param->argv[1], NULL, 16);
    lt_bias1 = strtoul(param->argv[2], NULL, 16);
    
    ret = write_reg_5g_three_bias(rt_bias1, ht_bias1, lt_bias1);

    if(ret != 0)
        return ret;

    ssv_rf_table.rt_5g_config.bias1 = rt_bias1;
    ssv_rf_table.ht_5g_config.bias1 = ht_bias1;
    ssv_rf_table.lt_5g_config.bias1 = lt_bias1;
    
    SAVE_RF_TABLE(); 

    return ret;    
}
int At_Rf5GTableBIAS2(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;	
    uint32_t rt_bias2 = 0, ht_bias2 = 0, lt_bias2 = 0;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=0x%x,0x%x,0x%x\n", ATCMD_RF_5GTABLE_BIAS2, ssv_rf_table.rt_5g_config.bias2
                                                                                           , ssv_rf_table.ht_5g_config.bias2
                                                                                           , ssv_rf_table.lt_5g_config.bias2);
        return ret;
    }
    
    if(param->argc < 3)
        return ERROR_INVALID_PARAMETER;

    rt_bias2 = strtoul(param->argv[0], NULL, 16);
    ht_bias2 = strtoul(param->argv[1], NULL, 16);
    lt_bias2 = strtoul(param->argv[2], NULL, 16);
    
    ret = write_reg_5g_three_bias(rt_bias2, ht_bias2, lt_bias2);

    if(ret != 0)
        return ret;

    ssv_rf_table.rt_5g_config.bias2 = rt_bias2;
    ssv_rf_table.ht_5g_config.bias2 = ht_bias2;
    ssv_rf_table.lt_5g_config.bias2 = lt_bias2;
    
    SAVE_RF_TABLE(); 

    return ret; 
}
int At_Rf5GBandThreshold(stParam *param)
{
    printf("\n");
    int ret = ERROR_SUCCESS;
    uint16_t thr_f0, thr_f1, thr_f2;

    if(strcmp("?" , param->argv[0])==0)
    {
        ATCMD_LOG_I("%s=%d,%d,%d\n", ATCMD_RF_5GTABLE_BAND_THRESHOLD, ssv_rf_table.band_f0_threshold, ssv_rf_table.band_f1_threshold, ssv_rf_table.band_f2_threshold);
        return ret;
    }
    
    if(param->argc < 3)
        return ERROR_INVALID_PARAMETER;

    struct st_tempe_5g_table tempe_config = {0};
     
    thr_f0 = strtoul(param->argv[0], NULL, 10);
    thr_f1 = strtoul(param->argv[1], NULL, 10);
    thr_f2 = strtoul(param->argv[2], NULL, 10);
    
    ret = write_reg_5g_band_threshold(thr_f0, thr_f1, thr_f2);

    if(ret != 0)
        return ret;
        
    ssv_rf_table.band_f0_threshold = thr_f0;
    ssv_rf_table.band_f1_threshold = thr_f1;
    ssv_rf_table.band_f2_threshold = thr_f2;
    
    SAVE_RF_TABLE(); 

    return ret; 
}
int At_RfSingleTone(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    ret = rf_tone_gen(atoi(param->argv[0]));

    return ret; 
}
int At_RfWorkMode(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    
    if(param->argc < 1)
        return ERROR_INVALID_PARAMETER;

    if(atoi(param->argv[0]) == 1)
            ssv_rf_table.work_mode = 1;
    else
            ssv_rf_table.work_mode = 0;
    
    SAVE_RF_TABLE(); 
        
    return ret; 
}
#endif

