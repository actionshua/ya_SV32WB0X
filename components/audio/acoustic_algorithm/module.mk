LIB_SRC := webrtc/common_audio/vad/vad_filterbank.c
LIB_SRC += webrtc/common_audio/vad/vad_core.c
LIB_SRC += webrtc/common_audio/vad/vad_gmm.c
LIB_SRC += webrtc/common_audio/vad/vad_sp.c
LIB_SRC += webrtc/common_audio/vad/webrtc_vad.c

LIB_SRC += webrtc/modules/audio_processing/aec/aec_core.c
LIB_SRC += webrtc/modules/audio_processing/aec/aec_rdft.c
LIB_SRC += webrtc/modules/audio_processing/aec/aec_resampler.c
LIB_SRC += webrtc/modules/audio_processing/aec/echo_cancellation.c

LIB_SRC += webrtc/modules/audio_processing/agc/analog_agc.c
LIB_SRC += webrtc/modules/audio_processing/agc/digital_agc.c

LIB_SRC += webrtc/modules/audio_processing/ns/noise_suppression_x.c
LIB_SRC += webrtc/modules/audio_processing/ns/nsx_core.c

LIB_SRC += webrtc/modules/audio_processing/utility/ring_buffer.c
LIB_SRC += webrtc/modules/audio_processing/utility/delay_estimator.c
LIB_SRC += webrtc/modules/audio_processing/utility/delay_estimator_wrapper.c

LIB_SRC += webrtc/common_audio/signal_processing/complex_bit_reverse.c
LIB_SRC += webrtc/common_audio/signal_processing/complex_fft.c
LIB_SRC += webrtc/common_audio/signal_processing/copy_set_operations.c
LIB_SRC += webrtc/common_audio/signal_processing/division_operations.c
LIB_SRC += webrtc/common_audio/signal_processing/energy.c
LIB_SRC += webrtc/common_audio/signal_processing/get_scaling_square.c
LIB_SRC += webrtc/common_audio/signal_processing/min_max_operations.c
LIB_SRC += webrtc/common_audio/signal_processing/real_fft.c
LIB_SRC += webrtc/common_audio/signal_processing/resample_48khz.c
LIB_SRC += webrtc/common_audio/signal_processing/resample_by_2.c
LIB_SRC += webrtc/common_audio/signal_processing/resample_by_2_internal.c
LIB_SRC += webrtc/common_audio/signal_processing/resample_fractional.c
LIB_SRC += webrtc/common_audio/signal_processing/spl_init.c
LIB_SRC += webrtc/common_audio/signal_processing/spl_sqrt.c
LIB_SRC += webrtc/common_audio/signal_processing/spl_sqrt_floor.c
LIB_SRC += webrtc/common_audio/signal_processing/downsample_fast.c
LIB_SRC += webrtc/common_audio/signal_processing/cross_correlation.c
LIB_SRC += webrtc/common_audio/signal_processing/vector_scaling_operations.c
LIB_SRC += webrtc/common_audio/signal_processing/randomization_functions.c

LIB_SRC += speexdsp/libspeexdsp/preprocess.c
LIB_SRC += speexdsp/libspeexdsp/mdf.c
LIB_SRC += speexdsp/libspeexdsp/fftwrap.c
LIB_SRC += speexdsp/libspeexdsp/kiss_fft.c
LIB_SRC += speexdsp/libspeexdsp/kiss_fftr.c
LIB_SRC += speexdsp/libspeexdsp/filterbank.c

LIB_SRC += ml_kws/Source_C/MFCC_C/mfcc.c
LIB_SRC += ml_kws/Source_C/local_NN/arm_avepool_q7_HWC_nonsquare.c
LIB_SRC += ml_kws/Source_C/NN_C/DNN/dnn.c
LIB_SRC += ml_kws/Source_C/NN_C/DS_CNN/ds_cnn.c
LIB_SRC += ml_kws/Source_C/KWS_C/kws.c

LIB_ASRC :=
LIBRARY_NAME := acoustic_algorithm
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/speexdsp/include

LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/ml_kws/Source_C/MFCC_C
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/ml_kws/Source_C/local_NN
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/ml_kws/Source_C/NN_C
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/ml_kws/Source_C/NN_C/DS_CNN
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/ml_kws/Source_C/NN_C/DNN
LOCAL_INC += -I$(TOPDIR)/components/audio/acoustic_algorithm/ml_kws/Source_C/KWS_C
LOCAL_INC += -I$(TOPDIR)/components/audio/CMSIS/porting
LOCAL_INC += -I$(TOPDIR)/components/audio/CMSIS/DSP/Include
LOCAL_INC += -I$(TOPDIR)/components/audio/CMSIS/NN/Include

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))

