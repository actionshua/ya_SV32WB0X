
#define M_FLASHCTRL             *libsrm_sys.a:*flash.o *libsrm_sys.a:xip.o
#define M_FLASHCTRL_TEXT_RO     *libsrm_sys.a:*flash.o (.text.* .rodata.* .text) *libsrm_sys.a:*xip.o (.text.* .rodata.* .text)
#define M_BOOT                  *libgcc.a:*_udivdi3.o *libgcc.a:*_floatundidf.o *libgcc.a:*_div_df.o *libgcc.a:*_fixunsdfsi.o *libgcc.a:*_si_to_df.o *libc.a:*lib_a-memcpy.o *libgcc.a:*_floatunsisf.o *libgcc.a:*_div_sf.o *libgcc.a:*_compare_sf.o *libgcc.a:*_mul_sf.o *libgcc.a:*_fixunssfsi.o *libgcc.a:*_udivmoddi4.o
#define M_CACHE *libboot.a:*cache.o(.text.* .text)
#define M_BOOT_TEXT_RO          *libgcc.a:*_udivdi3.o (.text.* .rodata.* .text ) *libgcc.a:*_floatundidf.o (.text.* .rodata.* .text ) *libgcc.a:*_div_df.o (.text.* .rodata.* .text ) *libgcc.a:*_fixunsdfsi.o (.text.* .rodata.* .text ) *libgcc.a:*_si_to_df.o (.text.* .rodata.* .text ) *libc.a:*lib_a-memcpy.o(.text.* .rodata.* .text ) *libgcc.a:*_floatunsisf.o(.text.* .rodata.* .text ) *libgcc.a:*_div_sf.o(.text.* .rodata.* .text ) *libgcc.a:*_compare_sf.o(.text.* .rodata.* .text ) *libgcc.a:*_mul_sf.o(.text.* .rodata.* .text ) *libgcc.a:*_fixunssfsi.o(.text.* .rodata.* .text ) *libgcc.a:*_udivmoddi4.o(.text.* .rodata.* .text )

#if defined(MBED_RO_TURN)
#define M_MBEDTLS               *libmbedtls.a:*aes.o *libmbedtls.a:*sha512.o *libmbedtls.a:*bignum.o *libmbedtls.a:*gcm.o
#else
#define M_MBEDTLS
#endif

#define M_MP3                   *polyphase.o *huffman.o *dct32.o *imdct.o *hufftabs.o *trigtabs.o
#define M_MP3_RO                *libhelix.a:*polyphase.o (.text.* .rodata.* .text ) *huffman.o (.text.* .rodata.* .text ) *dct32.o (.text.* .rodata.* .text ) *imdct.o (.text.* .rodata.* .text )  *hufftabs.o (.text.* .rodata.* .text ) *trigtabs.o (.text.* .rodata.* .text ) 


#define M_MP3_3                   *libmp3dec.a:*pv_mp3dec_fxd_op_c_equivalent.o *libmp3dec.a:*pvmp3_alias_reduction.o *libmp3dec.a:*pvmp3_dct_6.o *libmp3dec.a:*pvmp3_dct_9.o *libmp3dec.a:*pvmp3_dct_16.o *libmp3dec.a:*pvmp3_decode_huff_cw.o *libmp3dec.a:*pvmp3_dequantize_sample.o *libmp3dec.a:*pvmp3_equalizer.o *libmp3dec.a:*pvmp3_framedecoder.o *libmp3dec.a:*pvmp3_get_side_info.o *libmp3dec.a:*pvmp3_imdct_synth.o  *libmp3dec.a:*pvmp3_mpeg2_stereo_proc.o
#define M_MP3_3_RO                *libmp3dec.a:*pv_mp3dec_fxd_op_c_equivalent.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_alias_reduction.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_dct_6.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_dct_9.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_dct_16.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_decode_huff_cw.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_dequantize_sample.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_equalizer.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_framedecoder.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_get_side_info.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_imdct_synth.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_mpeg2_stereo_proc.o (.text.* .rodata.* .text ) *libmp3dec.a:*pvmp3_tables.o (.text.* .rodata.* .text )
#define M_MP3_2                   *libpvmp3decoder.a
#define M_MP3_2_RO                *libpvmp3decoder.a:*(.text.* .rodata.* .text)

#if defined(SETTING_THROUGHPUT_HIGH)
#define M_WIFI                  *sys_arch.o *api_msg.o *edca.o *rc80211_minstrel.o *rc80211_minstrel_ht.o
#define M_WIFI_TEXT_RO                  *sys_arch.o(.text.* .rodata.* .text) *api_msg.o(.text.* .rodata.* .text) *edca.o(.text.* .rodata.* .text) *rc80211_minstrel.o(.text.* .rodata.* .text) *rc80211_minstrel_ht.o(.text.* .rodata.* .text)
#define M_OS                    *libfreertos.a:*queue.o *libfreertos.a:*list.o *libfreertos.a:*tasks.o *libfreertos.a:*port.o *libfreertos.a:*portISR.o *osal_freertos.o *heap_5.o *libnds_port.a:*port.o *liblowpower.a:*pmu_6020.o
#define M_OS_TEXT_RO                    *libfreertos.a:*queue.o(.text.* .rodata.* .text) *libfreertos.a:*list.o(.text.* .rodata.* .text) *libfreertos.a:*tasks.o(.text.* .rodata.* .text) *libfreertos.a:*port.o(.text.* .rodata.* .text) *libfreertos.a:*portISR.o(.text.* .rodata.* .text) *osal_freertos.o(.text.* .rodata.* .text) *heap_5.o(.text.* .rodata.* .text) *libnds_port.a:*port.o(.text.* .rodata.* .text) *liblowpower.a:*pmu_6020.o(.text.* .rodata.* .text)
#else
#define M_WIFI                  *edca.o *sys_arch.o *api_msg.o
#define M_WIFI_TEXT_RO                  *edca.o(.text.* .rodata.* .text) *sys_arch.o(.text.* .rodata.* .text) *api_msg.o(.text.* .rodata.* .text)
#define M_OS
#define M_OS_TEXT_RO
#endif
#define M_BLE                  *libble_lestack.a *libble_application.a *libble_bsp.a *libble_lib.a
#define M_BLE_TEXT_RO                  *libble_lestack.a:*(.text.* .rodata.* .text) *libble_application.a:*(.text.* .rodata.* .text) *libble_bsp.a:*(.text.* .rodata.* .text) *libble_lib.a:*(.text.* .rodata.* .text)

#define M_NN					*arm_relu_q7.o *arm_fully_connected_q7.o *arm_q7_to_q15_reordered_no_shift.o *arm_softmax_q7.o *arm_rfft_fast_f32.o 
#define M_NN_TEXT_RO			*arm_relu_q7.o(.text.* .rodata.* .text) *arm_fully_connected_q7.o(.text.* .rodata.* .text) *arm_softmax_q7.o(.text.* .rodata.* .text) *arm_rfft_fast_f32.o(.text.* .rodata.* .text)

#define M_KWS					*mfcc.o *arm_avepool_q7_HWC_nonsquare.o *kws.o
#define M_KWS_TEXT_RO			*mfcc.o(.text.* .rodata.* .text) *arm_avepool_q7_HWC_nonsquare.o(.text.* .rodata.* .text) *kws.o(.text.* .rodata.* .text)

#define M_AEC					*mdf.o *preprocess.o  *kiss_fft.o *kiss_fftr.o *filterbank.o *fftwrap.o *lib_a-pow.o
#define M_AEC_TEXT_RO			*mdf.o(.text.* .rodata.* .text) *preprocess.o(.text.* .rodata.* .text) *kiss_fft.o(.text.* .rodata.* .text) *kiss_fftr.o(.text.* .rodata.* .text) *filterbank.o(.text.* .rodata.* .text) *fftwrap.o(.text.* .rodata.* .text) *lib_a-pow.o(.text.* .rodata.* .text)

#define M_FAST_BOOT             M_BOOT M_FLASHCTRL
#define M_FAST_BOOT_TEXT_RO     M_BOOT_TEXT_RO M_FLASHCTRL_TEXT_RO
#if (BLE_EN == 1)
#define M_ILM                   M_OS M_WIFI M_AEC M_KWS M_NN M_BLE
#define M_ILM_TEXT_RO                   M_OS_TEXT_RO M_WIFI_TEXT_RO M_AEC_TEXT_RO M_KWS_TEXT_RO M_NN_TEXT_RO M_BLE_TEXT_RO
#else
#define M_ILM                   M_OS M_WIFI M_AEC M_KWS M_NN M_MP3
#define M_ILM_TEXT_RO                   M_OS_TEXT_RO M_WIFI_TEXT_RO M_AEC_TEXT_RO M_KWS_TEXT_RO M_NN_TEXT_RO M_MP3_RO
#endif
#define M_ILM_RO                M_OS M_WIFI M_AEC M_KWS M_NN M_MBEDTLS M_MP3

#define M_NORMAL_TEXT_RO
#define M_NORMAL_DATA
#define M_NORMAL_BSS

