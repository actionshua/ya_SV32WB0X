LIB_SRC := src/pvmp3_alias_reduction.c
LIB_SRC += src/pvmp3_crc.c
LIB_SRC += src/pvmp3_dct_16.c
LIB_SRC += src/pvmp3_dct_6.c
LIB_SRC += src/pvmp3_dct_9.c
LIB_SRC += src/pvmp3_decode_header.c
LIB_SRC += src/pvmp3_decode_huff_cw.c
LIB_SRC += src/pvmp3_dequantize_sample.c
LIB_SRC += src/pvmp3_equalizer.c
LIB_SRC += src/pvmp3_framedecoder.c
LIB_SRC += src/pvmp3_getbits.c
LIB_SRC += src/pvmp3_get_main_data_size.c
LIB_SRC += src/pvmp3_get_scale_factors.c
LIB_SRC += src/pvmp3_get_side_info.c
LIB_SRC += src/pvmp3_huffman_decoding.c
LIB_SRC += src/pvmp3_huffman_parsing.c
LIB_SRC += src/pvmp3_imdct_synth.c
LIB_SRC += src/pvmp3_mdct_18.c
LIB_SRC += src/pvmp3_mdct_6.c
LIB_SRC += src/pvmp3_mpeg2_get_scale_data.c
LIB_SRC += src/pvmp3_mpeg2_get_scale_factors.c
LIB_SRC += src/pvmp3_mpeg2_stereo_proc.c
LIB_SRC += src/pvmp3_normalize.c
LIB_SRC += src/pvmp3_polyphase_filter_window.c
LIB_SRC += src/pvmp3_poly_phase_synthesis.c
LIB_SRC += src/pvmp3_reorder.c
LIB_SRC += src/pvmp3_seek_synch.c
LIB_SRC += src/pvmp3_stereo_proc.c
LIB_SRC += src/pvmp3_tables.c
LIB_SRC += src/pv_mp3dec_fxd_op_c_equivalent.c

#LIB_SRC += test/mp3dec_test.c
LIB_SRC += test/mp3reader.c

LIB_ASRC :=
LIBRARY_NAME := pvmp3decoder
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/pvmp3decoder/src
LOCAL_INC += -I$(TOPDIR)/components/third_party/pvmp3decoder/include
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))