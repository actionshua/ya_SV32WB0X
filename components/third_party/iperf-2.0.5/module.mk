 LIB_SRC := src/Client.c
 LIB_SRC += src/gnu_getopt.c
 LIB_SRC += src/gnu_getopt_long.c
 LIB_SRC += src/iperf_main.c
 LIB_SRC += src/Launch.c
 LIB_SRC += src/List.c
 LIB_SRC +=  src/Listener.c
 LIB_SRC += src/Locale.c
 LIB_SRC += src/PerfSocket.c
 LIB_SRC += src/ReportDefault.c
 LIB_SRC += src/Reporter.c
 LIB_SRC += src/Server.c
 LIB_SRC += src/service.c
 LIB_SRC += src/Settings.c
 LIB_SRC += src/SocketAddr.c
 LIB_SRC += src/sockets.c
 LIB_SRC += src/stdio.c
 LIB_SRC += src/tcp_window_size.c
 LIB_SRC += src/Timestamp.c
 LIB_SRC += compat/delay.c
 LIB_SRC += compat/error.c
 LIB_SRC += compat/inet_ntop.c
 LIB_SRC += compat/inet_pton.c
 LIB_SRC += compat/signal.c
 LIB_SRC += compat/snprintf.c
 LIB_SRC += compat/string.c
 LIB_SRC += compat/Thread.c

LIB_ASRC :=
LIBRARY_NAME := iperf
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/drv/$(CHIP_NAME)
LOCAL_INC += -Icomponents/netstack_wrapper
LOCAL_INC += -Icomponents/net/tcpip/$(LWIP_PATH)/ports/icomm/include
LOCAL_INC += -Icomponents/net/tcpip/$(LWIP_PATH)/src/include
LOCAL_INC += -Icomponents/net/tcpip/$(LWIP_PATH)/src/include/ipv4
LOCAL_INC += -Icomponents/net/tcpip/$(LWIP_PATH)/src/netif/ppp
LOCAL_INC += -I$(MYDIR)/include

RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
