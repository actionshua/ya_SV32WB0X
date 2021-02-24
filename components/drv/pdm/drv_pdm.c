
#include "hal_i2s.h"
#include <math.h>

#if(CHIP_ID == 6020)
#include "hal_pdm.h"
#include "drv_pdm.h"

#define PDM_TONE_GEN 32000

#if (CHIP_SUB_ID !=0)
static int cal_gcd(int x, int y)
{
    int tmp;
    while (x % y != 0) {
        tmp = y;
        y = x % y;
        x = tmp;
    }
    return y;
}

static int downsampler(drv_pdm_port port, int src_sample, int dest_sample)
{
    int gcd = cal_gcd(src_sample, dest_sample);
    int x = 0, y = 0, z = 0, k = 0, n =0, m = 0;
    if(gcd > 0) {
        x = src_sample / gcd;
        y = dest_sample / gcd;
    }
    z =  x / y;
    if(z > 0) {
        k = z;
        n = x - (z * y);
        m = y;
    } else {
        k = 0;
        n = x;
        m = y;
    }

    hal_pdm_rx_resamp_k_set(port, k);
    hal_pdm_rx_resamp_n_set(port, n);
    hal_pdm_rx_resamp_m_set(port, m);

    int i =0;
    long approx_num = n;
    long approx_den = m;
    long rg_rx_resamp_inv_m_exp=0;
    long rg_rx_resamp_inv_m_mant=0;
    
    if( approx_den <= 512 ) {
        for(i=1;i<9;i++){
            if( approx_den*pow(2.0,i) > 512 ) {
                break;
            }
        }
        approx_num = approx_num * pow(2.0, i-1);
        approx_den = approx_den * pow(2.0, i-1);
        rg_rx_resamp_inv_m_exp = 9;
    } else if( approx_den <= 1024 ) {
        rg_rx_resamp_inv_m_exp = 10;
    } else if( approx_den <= 2048 ) {
        rg_rx_resamp_inv_m_exp = 11;
    } else {
        rg_rx_resamp_inv_m_exp = 12;
    }
    rg_rx_resamp_inv_m_mant = pow(2.0, rg_rx_resamp_inv_m_exp+10)/approx_den;

    if(rg_rx_resamp_inv_m_mant >= 2048) {
        rg_rx_resamp_inv_m_mant = rg_rx_resamp_inv_m_mant /2;
        rg_rx_resamp_inv_m_exp = rg_rx_resamp_inv_m_exp - 1;
    }
    printf("k: %d n: %d m: %d\n",k, approx_num, approx_den);    
    printf("m_exp: %d m_mant: %d\n", rg_rx_resamp_inv_m_exp, rg_rx_resamp_inv_m_mant);
    hal_pdm_rx_resamp_n_set(port, approx_num);
    hal_pdm_rx_resamp_m_set(port, approx_den);
    hal_pdm_rx_resamp_inv_m_mant_set(port, rg_rx_resamp_inv_m_mant);
    hal_pdm_rx_resamp_inv_m_exp_set(port, rg_rx_resamp_inv_m_exp);
    return 0;
}
#ifdef I2S_SUPPORT_DS
void pdm_downsampler_disable(drv_pdm_port port)
{
    hal_pdm_rx_ch_disable(port);
    hal_pdm_rx_stereo_disable(port);
    hal_pdm_ctl_rx_ds_disable(port);
    hal_pdm_ctl_tonegen_disable(port);
    hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_ONLY_L);
}

void pdm_downsampler_enable(drv_pdm_port port, int src_sample, int dest_sample)
{
    downsampler(port, src_sample, dest_sample);
    hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_ONLY_L);
    hal_pdm_ctl_rx_ds_enable(port);
    hal_pdm_rx_stereo_enable(port);
    hal_pdm_rx_ch_enable(port);
}
#endif
#endif

static int cal_rate_conv_and_set(drv_pdm_port port, int pdm_clk, int rate)
{
    const int length_approx = 16;
    //const int clk_audio_ref = 160 * 1000;
    int results[length_approx];
    int i = 0;
    for(i = 0; i < length_approx; i++) {
        results[i] = 0;
    }
    //int rg_phase_cycle = (clk_audio_ref) / (pdm_clk);
    int rg_phase_cycle = pdm_clk;
    int rg_target_rate = rate;

    //calculation by integer
    long convert_rate_num = 10000*100;
    long convert_rate_den = (int)(rg_phase_cycle*rg_target_rate*100/1000);
    int rg_rx_resamp_k = convert_rate_num/convert_rate_den;
    convert_rate_num = convert_rate_num - rg_rx_resamp_k*convert_rate_den;
    long approx_num = convert_rate_num;
    long approx_den = convert_rate_den;

    long value_swap = 0;
    int k = 0;
    if(approx_num != 0) {
        for(i = 0; i < length_approx; i++) {
            k++;
            if(approx_den == 0) {
                break;
            } else if(approx_den > approx_num) {
                while(approx_den >= approx_num) {
                    approx_den = approx_den - approx_num;
                    results[i] = results[i] + 1;
                }
            } else {
                value_swap = approx_den;
                approx_den = approx_num;
                approx_num = value_swap;
                while( approx_den >= approx_num ) {
                    approx_den = approx_den - approx_num;
                    results[i] = results[i]+1;
                }
            }
        }
        approx_den = convert_rate_den / approx_num;
        approx_num = convert_rate_num / approx_num;
        if( approx_num > 1023 || approx_den > 2047 ) {
            approx_num = 1;
            approx_den = results[k - 1];
            value_swap = 0;

            for(i = k - 2; i >= 0; i--) {
                approx_num = approx_den * results[i] + approx_num;
                value_swap = approx_num;
                approx_num = approx_den;
                approx_den = value_swap;
                if(approx_num > 1023 || approx_den > 2047) {
                    break;
                }
            }
        }
    } else {
        approx_den = 168;
    }
    //printf("k: %d n: %d m: %d\n", rg_rx_resamp_k, approx_num, approx_den);
    hal_pdm_rx_resamp_k_set(port, rg_rx_resamp_k);
    hal_pdm_rx_resamp_n_set(port, approx_num);
    hal_pdm_rx_resamp_m_set(port, approx_den);
#if (CHIP_SUB_ID == 0)
    printf("debounce up: %ld debounce low: %ld\n", rg_phase_cycle*6/10, rg_phase_cycle*4/10);
    printf("phase_offset: %d\n", rg_phase_cycle*3/4);
    hal_pdm_rx_sel_phase_offset_set(port, (rg_phase_cycle*3/4));
    hal_pdm_rx_debounce_up_thr_set(port, (rg_phase_cycle*6/10));
    hal_pdm_rx_debounce_low_thr_set(port, (rg_phase_cycle*4/10));
#else
    long rg_rx_resamp_inv_m_exp=0;
    long rg_rx_resamp_inv_m_mant=0;

    if( approx_den <= 512 ) {
        for(i=1;i<9;i++){
            if( approx_den*pow(2.0,i) > 512 ) {
                break;
            }
        }
        approx_num = approx_num * pow(2.0, i-1);
        approx_den = approx_den * pow(2.0, i-1);
        rg_rx_resamp_inv_m_exp = 9;
    } else if( approx_den <= 1024 ) {
        rg_rx_resamp_inv_m_exp = 10;
    } else if( approx_den <= 2048 ) {
        rg_rx_resamp_inv_m_exp = 11;
    } else {
        rg_rx_resamp_inv_m_exp = 12;
    }
    rg_rx_resamp_inv_m_mant = pow(2.0, rg_rx_resamp_inv_m_exp+10)/approx_den;
    printf("k: %d n: %d m: %d\n",rg_rx_resamp_k, approx_num, approx_den);    
    printf("m_exp: %d m_mant: %d\n", rg_rx_resamp_inv_m_exp, rg_rx_resamp_inv_m_mant);
    hal_pdm_rx_resamp_n_set(port, approx_num);
    hal_pdm_rx_resamp_m_set(port, approx_den);
    hal_pdm_rx_resamp_inv_m_mant_set(port, rg_rx_resamp_inv_m_mant);
    hal_pdm_rx_resamp_inv_m_exp_set(port, rg_rx_resamp_inv_m_exp);
#endif

    return 0;
}

static int32_t check_chip_id()
{
    #if(CHIP_ID==6020)
        return DRV_PDM_STATUS_OK;
    #else
        printf("6006 not support pdm\n");
        return DRV_PDM_STATUS_ERROR;
    #endif
}

static int32_t check_pdm_port(
    drv_pdm_port port)
{
    if(port >= DRV_PDM_MAX) {
        printf("pdm port number not support: %d\n", port);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }
    return DRV_PDM_STATUS_OK;
}

static int32_t check_pdm_rx_rate(
    pdm_rx_sample_rate_t rate)
{
    if(rate < PDM_Rx_SampleRate_8000HZ || rate >PDM_Rx_SampleRate_48000HZ) {
        printf("not normal use rx rate, please check\n");
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }
    return DRV_PDM_STATUS_OK;
}

static int32_t check_pdm_tx_rate(
    uint32_t rate)
{
    if(rate < 1 || rate >51) {
        printf("not normal use tx rate, please check: %d\n", rate);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }
    return DRV_PDM_STATUS_OK;
}

static int32_t rx_sample_rate_setting(
    drv_pdm_port port,
    pdm_rx_sample_rate_t rate,
    hal_rx_clk clk)
{
    cal_rate_conv_and_set(port, clk, rate);
#if (CHIP_SUB_ID == 0)
    if(clk == PDM_RX_3D20M) {
        if(rate == PDM_Rx_SampleRate_8000HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 1);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 256);
        } else if(rate == PDM_Rx_SampleRate_16000HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 1);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 128);
        } else if(rate == PDM_Rx_SampleRate_22050HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 8);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 1189);
        } else if(rate == PDM_Rx_SampleRate_44100HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 9);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 1189);
        } else if(rate == PDM_Rx_SampleRate_48000HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 9);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 1092);
        } else if(rate == PDM_TONE_GEN) {
            hal_pdm_rx_resamp_k_set(port, 1);
            hal_pdm_rx_resamp_n_set(port, 0);
            hal_pdm_rx_resamp_m_set(port, 1);
        } else {
            printf("not normal use rx rate, can not setting\n");
            return DRV_PDM_STATUS_INVALID_PARAMETER;
        }
        hal_pdm_rx_edge_det_num_set(port, 2);
        hal_pdm_rx_sel_phase_offset_set(port,12);
    } else if (clk == PDM_RX_1D25M) {
        if(rate == PDM_Rx_SampleRate_8000HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 1);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 256);
        } else if(rate == PDM_Rx_SampleRate_16000HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 1);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 128);
        } else if(rate == PDM_Rx_SampleRate_22050HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 8);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 1189);
        } else if(rate == PDM_Rx_SampleRate_44100HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 9);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 1189);
        } else if(rate == PDM_Rx_SampleRate_48000HZ) {
            hal_pdm_rx_resamp_inv_m_exp_set(port, 9);
            hal_pdm_rx_resamp_inv_m_mant_set(port, 1092);
        } else if(rate == PDM_TONE_GEN) {
            hal_pdm_rx_resamp_k_set(port, 1);
            hal_pdm_rx_resamp_n_set(port, 0);
            hal_pdm_rx_resamp_m_set(port, 1);
        } else {
            printf("not normal use rx rate, can not setting\n");
            return DRV_PDM_STATUS_INVALID_PARAMETER;
        }
        hal_pdm_rx_edge_det_num_set(port, 6);
    } else {
        printf("pdm clock: %d need training\n", clk);
    }
#else
    if(rate == PDM_TONE_GEN) {
        hal_pdm_rx_resamp_k_set(port, 1);
        hal_pdm_rx_resamp_n_set(port, 0);
        hal_pdm_rx_resamp_m_set(port, 1);
    }
#endif
    return DRV_PDM_STATUS_OK;
}

#if ((CHIP_SUB_ID !=0))
drv_pdm_status_t drv_pdm_tx_tonegen_enable(
    drv_pdm_port port,
    drv_pdm_tone_t tone)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0)
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    if(port == DRV_PDM_2) {
        printf("pdm tx only support i2s1 interface\n", port);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    } 

    uint16_t value= (tone  * 65536) / 32;

    drv_pdm_rx_enable(port,PDM_TONE_GEN, PDM_RX_STEREO);
    drv_pdm_tx_enable(port,32,PDM_TX_Bit_Depth_16,PDM_TX_STEREO, 0);
    hal_pdm_rx_loopback_enable(port);
    hal_pdm_ctl_tonegen_enable(port, value, 32);
    return DRV_PDM_STATUS_OK;
}

drv_pdm_status_t drv_pdm_tx_tonegen_disable(
    drv_pdm_port port)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0)
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    if(port == DRV_PDM_2) {
        printf("pdm tx only support i2s1 interface\n", port);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }
    hal_pdm_rx_loopback_disable(port);
    hal_pdm_ctl_tonegen_disable(port);
    return DRV_PDM_STATUS_OK;
}
#endif

drv_pdm_status_t drv_pdm_tx_vol(
    drv_pdm_port port,
    int vol)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0)
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    if(port == DRV_PDM_2) {
        printf("pdm tx only support i2s1 interface\n", port);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }

    if(vol < 0 || vol > 64) {
        printf("pdm tx vol set fail: %d\n", vol);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }

    hal_pdm_tx_amp_out_scaling_set(vol);
    return DRV_PDM_STATUS_OK;
}

drv_pdm_status_t drv_pdm_init(
    drv_pdm_port port)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0)
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    hal_i2s_clk_disable(port);
    hal_pdm_tx_mask_enable();
    hal_pdm_rx_mask_enable(port);
    return DRV_PDM_STATUS_OK;
}

drv_pdm_status_t drv_pdm_tx_enable(
    drv_pdm_port port,
    float rate,
    pdm_tx_bit_depth_t depth,
    pdm_tx_mode_t mode,
    bool swapLR)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0 || check_pdm_tx_rate(rate))
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    if(port == DRV_PDM_2) {
        printf("pdm tx only support i2s1 interface\n", port);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }

    hal_i2s_clk_enable(port, 2, mclk_80MHz);//pdm need 40M bit clk
    hal_pdm_tx_out_bw_set(PDM_TX_01D25M);//default
    hal_pdm_tx_resamp_n_set(40 * rate);
    hal_pdm_tx_stereo_disable();
#if ((CHIP_SUB_ID != 0))
    hal_pdm_tx_mono_crtl(HAL_PDM_ONLY_L);
    hal_pdm_tx_swapLR_disable();
    hal_pdm_tx_scaling_leaky_factor_set(PDM_TX_VOL_BW_50K);//defalut value
#endif
    if(mode == PDM_TX_STEREO) {
        hal_pdm_tx_stereo_enable();
#if ((CHIP_SUB_ID !=0))
        if(swapLR == 1) {
            hal_pdm_tx_swapLR_enable();
        }
    } else if (mode == PDM_TX_MONO_ONLY_R) {
        hal_pdm_tx_mono_crtl(HAL_PDM_ONLY_R);
    } else if (mode == PDM_TX_MONO_ONLY_L) {
        hal_pdm_tx_mono_crtl(HAL_PDM_ONLY_L);
    } else if (mode == PDM_TX_MONO_L_AND_COPYTO_R) {
        hal_pdm_tx_mono_crtl(HAL_PDM_L_COPY_TO_R);
    } else if (mode == PDM_TX_MONO_R_AND_COPYTO_L) {
        hal_pdm_tx_mono_crtl(HAL_PDM_R_COPY_TO_L);
#endif
    } else {
        printf("tx not support mode: %d\n", mode);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }
    hal_pdm_tx_amp_out_scaling_set(58);//defalut value
    if(depth >= PDM_TX_Bit_Depth_8 && depth <= PDM_TX_Bit_Depth_24) {
        hal_pdm_tx_bit_res_set(depth);
    } else {
        printf("tx not support depth: %d\n", depth);
    }
    hal_pdm_tx_ch_enable();

    return DRV_PDM_STATUS_OK;
}

drv_pdm_status_t drv_pdm_tx_disable(
    drv_pdm_port port)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0)
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    if(port == DRV_PDM_2) {
        printf("pdm tx only support i2s1 interface\n", port);
        return DRV_PDM_STATUS_INVALID_PARAMETER;
    }

    hal_pdm_tx_ch_disable();
    return DRV_PDM_STATUS_OK;
}

drv_pdm_status_t drv_pdm_rx_enable(
    drv_pdm_port port,
    pdm_rx_sample_rate_t rate,
    pdm_rx_mode_t mode)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < DRV_PDM_STATUS_OK || check_pdm_rx_rate(rate))
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    hal_i2s_clk_enable(port, 2, mclk_80MHz);
    hal_pdm_rx_phase_cycle_set(port, PDM_RX_1D25M);
#if (CHIP_SUB_ID == 0)
    hal_pdm_rx_sync_dly_sel_set(port, PDM_RX_NEAR_1D25M);
#endif
    rx_sample_rate_setting(port, rate, PDM_RX_1D25M);
    hal_pdm_rx_stereo_disable(port);
#if ((CHIP_SUB_ID !=0))
    hal_pdm_rx_lpow_disable(port);
    hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_ONLY_L);
    if(port == DRV_PDM_1) {
        hal_pdm_rx_loopback_disable(port);
    }
    hal_pdm_rx_data_bit_align(port, 1);
    hal_pdm_ctl_rx_ds_disable(port);
    hal_pdm_ctl_tonegen_disable(port);
    hal_pdm_ctl_phase_offset(port, HAL_PDM_OFFSET_6_NSEC);
#else
    hal_pdm_rx_auto_phase_set_enable(port);
    hal_pdm_rx_manual_phase_offset_enable(port);
#endif
    if(mode == PDM_RX_STEREO) {
        hal_pdm_rx_stereo_enable(port);
#if ((CHIP_SUB_ID !=0))
    } else if (mode == PDM_RX_MONO_ONLY_R) {
        hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_ONLY_R);
    } else if (mode == PDM_RX_MONO_ONLY_L) {
        hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_ONLY_L);
    } else if (mode == PDM_RX_MONO_L_AND_COPYTO_R) {
        hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_L_COPY_TO_R);
    } else if (mode == PDM_RX_MONO_R_AND_COPYTO_L) {
        hal_pdm_ctl_rx_mono_ctl(port, HAL_PDM_R_COPY_TO_L);
#endif
    } else {
        printf("rx not support type: %d\n", mode);
    }
    hal_pdm_rx_fir_lpf_ds4x_scale_set(port, 64);//default
#if 0
    printf("echo disable\n");
    hal_pdm_rx_echo_disable(port);
    printf("echo enable\n");
    hal_pdm_rx_echo_enable(port);
#endif
    hal_pdm_rx_ch_enable(port);
        
    return DRV_PDM_STATUS_OK;
}

drv_pdm_status_t drv_pdm_rx_disable(
    drv_pdm_port port)
{
    if(check_chip_id() < DRV_PDM_STATUS_OK)
        return DRV_PDM_STATUS_ERROR;

    if(check_pdm_port(port) < 0)
        return DRV_PDM_STATUS_INVALID_PARAMETER;

    hal_pdm_rx_ch_disable(port);
    return DRV_PDM_STATUS_OK;
}
#endif
