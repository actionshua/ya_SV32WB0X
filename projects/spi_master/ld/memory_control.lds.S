
#define M_FLASHCTRL             *libsrm_sys.a:*flash.o *libsrm_sys.a:xip.o
#define M_FLASHCTRL_TEXT_RO     *libsrm_sys.a:*flash.o (.text.* .rodata.* .text) *libsrm_sys.a:*xip.o (.text.* .rodata.* .text)
#define M_BOOT                  *libc.a:*lib_a-memcpy.o
#define M_CACHE *libboot.a:*cache.o(.text.* .text)
#define M_BOOT_TEXT_RO          *libc.a:*lib_a-memcpy.o(.text.* .rodata.* .text )

#if defined(MBED_RO_TURN)
#define M_MBEDTLS               *libmbedtls.a:*aes.o *libmbedtls.a:*sha512.o *libmbedtls.a:*bignum.o *libmbedtls.a:*gcm.o
#else
#define M_MBEDTLS
#endif

#if defined(SETTING_THROUGHPUT_HIGH)
#define M_WIFI                  *sys_arch.o *api_msg.o *edca.o *rc80211_minstrel.o *rc80211_minstrel_ht.o
#define M_WIFI_TEXT_RO          *sys_arch.o(.text.* .rodata.* .text) *api_msg.o(.text.* .rodata.* .text) *edca.o(.text.* .rodata.* .text) *rc80211_minstrel.o(.text.* .rodata.* .text) *rc80211_minstrel_ht.o(.text.* .rodata.* .text)
#define M_OS                    *libfreertos.a:*queue.o *libfreertos.a:*list.o *libfreertos.a:*tasks.o *libfreertos.a:*port.o *libfreertos.a:*portISR.o *osal_freertos.o *heap_5.o *libnds_port.a:*port.o *liblowpower.a:*pmu_6020.o
#define M_OS_TEXT_RO            *libfreertos.a:*queue.o(.text.* .rodata.* .text) *libfreertos.a:*list.o(.text.* .rodata.* .text) *libfreertos.a:*tasks.o(.text.* .rodata.* .text) *libfreertos.a:*port.o(.text.* .rodata.* .text) *libfreertos.a:*portISR.o(.text.* .rodata.* .text) *osal_freertos.o(.text.* .rodata.* .text) *heap_5.o(.text.* .rodata.* .text) *libnds_port.a:*port.o(.text.* .rodata.* .text) *liblowpower.a:*pmu_6020.o(.text.* .rodata.* .text)
#else
#define M_WIFI                  *edca.o *sys_arch.o *api_msg.o
#define M_WIFI_TEXT_RO          *edca.o(.text.* .rodata.* .text) *sys_arch.o(.text.* .rodata.* .text) *api_msg.o(.text.* .rodata.* .text)
#define M_OS
#define M_OS_TEXT_RO
#endif
#define M_BLE                  *libble_lestack.a *libble_application.a *libble_bsp.a *libble_lib.a
#define M_BLE_TEXT_RO          *libble_lestack.a:*(.text.* .rodata.* .text) *libble_application.a:*(.text.* .rodata.* .text) *libble_bsp.a:*(.text.* .rodata.* .text) *libble_lib.a:*(.text.* .rodata.* .text)

#define M_FAST_BOOT             M_BOOT M_FLASHCTRL
#define M_FAST_BOOT_TEXT_RO     M_BOOT_TEXT_RO M_FLASHCTRL_TEXT_RO
#if (BLE_EN == 1)
#define M_ILM                   M_OS M_WIFI M_BLE
#define M_ILM_TEXT_RO           M_OS_TEXT_RO M_WIFI_TEXT_RO M_BLE_TEXT_RO
#else
#define M_ILM                   M_OS M_WIFI
#define M_ILM_TEXT_RO           M_OS_TEXT_RO M_WIFI_TEXT_RO
#endif
#define M_ILM_RO                M_OS M_WIFI M_MBEDTLS

#define M_NORMAL_TEXT_RO
#define M_NORMAL_DATA
#define M_NORMAL_BSS

