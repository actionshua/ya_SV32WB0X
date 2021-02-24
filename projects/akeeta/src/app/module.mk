#CONFIG_AKEETA_EXAMPLE:=light_yusing
CONFIG_AKEETA_EXAMPLE:=light_tospo
LIB_SRC := main.c
LIB_SRC += custom_cmd.c

LIB_SRC += akeeta/hal/src/ya_hal_flash.c
LIB_SRC += akeeta/hal/src/ya_hal_net.c
LIB_SRC += akeeta/hal/src/ya_hal_os.c
LIB_SRC += akeeta/hal/src/ya_hal_timer.c
LIB_SRC += akeeta/hal/src/ya_hal_wdt.c
LIB_SRC += akeeta/hal/src/ya_hal_wlan.c
LIB_SRC += akeeta/hal/src/ya_hal_ble.c
LIB_SRC += akeeta/app/src/ya_ble_app.c
LIB_SRC += akeeta/app/src/internal_hal/ya_hardware_timer_hal.c
LIB_SRC += akeeta/app/src/internal_hal/ya_ota_hal.c
LIB_SRC += akeeta/app/src/ya_hardware_app.c
LIB_SRC += akeeta/app/src/ya_hardware_translate.c
LIB_SRC += akeeta/app/src/ya_common_func.c
LIB_SRC += akeeta/app/src/ya_app_main.c
LIB_SRC += akeeta/app/src/ya_atcmd.c
LIB_SRC += akeeta/app/src/ya_aes_md5.c
LIB_SRC += akeeta/app/src/ya_softap_update.c
LIB_SRC += akeeta/app/src/wifi_80211.c
LIB_SRC += akeeta/app/src/cloud.c
LIB_SRC += akeeta/app/src/ya_aliyun_cloud.c
LIB_SRC += akeeta/app/src/ya_aws_cloud.c
LIB_SRC += akeeta/app/src/ya_emq_cloud.c
LIB_SRC += akeeta/app/src/ya_cert_flash_api.c
LIB_SRC += akeeta/app/src/ya_flash.c
LIB_SRC += akeeta/app/src/ya_hardware_timer.c
LIB_SRC += akeeta/app/src/ya_ota.c
LIB_SRC += akeeta/app/src/ya_smartconfig.c
LIB_SRC += akeeta/app/src/ya_sniffer_broadcast.c
LIB_SRC += akeeta/app/src/ya_uart_app.c
LIB_SRC += akeeta/csdk3.0.1/eng/certs/root_ca.c
LIB_SRC += akeeta/csdk3.0.1/eng/dev_sign/dev_sign_mqtt.c 
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_compat.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_defs.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_log.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_net.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_prt_nwk_payload.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_report.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_sha256.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_string.c
LIB_SRC += akeeta/csdk3.0.1/eng/infra/infra_timer.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/iotx_mqtt_client.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/mqtt_api.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/MQTTConnectClient.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/MQTTDeserializePublish.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/MQTTPacket.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/MQTTSerializePublish.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/MQTTSubscribeClient.c
LIB_SRC += akeeta/csdk3.0.1/eng/mqtt/MQTTUnsubscribeClient.c
LIB_SRC += akeeta/csdk3.0.1/eng/wrappers/HAL_TLS_mbedtls.c
LIB_SRC += akeeta/csdk3.0.1/eng/wrappers/wrapper.c
LIB_SRC += akeeta/AWS/src/aws_iot_json_utils.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client_common_internal.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client_connect.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client_publish.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client_subscribe.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client_unsubscribe.c
LIB_SRC += akeeta/AWS/src/aws_iot_mqtt_client_yield.c
LIB_SRC += akeeta/AWS/external_libs/jsmn/jsmn.c
LIB_SRC += akeeta/AWS/platform/freertos/aws_iot_timer.c
LIB_SRC += akeeta/AWS/platform/freertos/network_mbedtls_wrapper.c
LIB_SRC += akeeta/AWS/platform/freertos/threads_mutex_wrapper.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTConnectClient.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTConnectServer.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTDeserializePublish.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTFormat.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTPacket.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTSerializePublish.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTSubscribeClient.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTSubscribeServer.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTUnsubscribeClient.c
LIB_SRC += akeeta/emq/MQTTPacket/src/MQTTUnsubscribeServer.c
LIB_SRC += akeeta/emq/MQTTClient-C/src/MQTTClient.c
LIB_SRC += akeeta/emq/MQTTClient-C/src/MQTTFreeRTOS.c

LIB_SRC += test_example/common/ya_hal_button.c
LIB_SRC += test_example/common/ya_hal_pwm.c
LIB_SRC += test_example/common/ya_hal_gpio.c
LIB_SRC += test_example/common/ya_hal_uart.c

ifeq ($(CONFIG_AKEETA_EXAMPLE),light_yusing)
LIB_SRC += test_example/light_yusing/ya_example.c
LIB_SRC += test_example/light_yusing/app/hls_rgb.c
LIB_SRC += test_example/light_yusing/app/ya_light_io.c
LIB_SRC += test_example/light_yusing/app/ya_light_product_test.c
LIB_SRC += test_example/light_yusing/app/ya_stripLights_display.c
LIB_SRC += test_example/light_yusing/app/ya_light_app.c
LIB_SRC += test_example/light_yusing/app/ya_light_example.c
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),light_tospo)
LIB_SRC += test_example/light_tospo/ya_example.c
LIB_SRC += test_example/light_tospo/app/hls_rgb.c
LIB_SRC += test_example/light_tospo/app/ya_light_io.c
LIB_SRC += test_example/light_tospo/app/ya_light_product_test.c
LIB_SRC += test_example/light_tospo/app/ya_stripLights_display.c
LIB_SRC += test_example/light_tospo/app/ya_light_app.c
LIB_SRC += test_example/light_tospo/app/ya_light_example.c
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),light)
LIB_SRC += test_example/light/ya_example.c
LIB_SRC += test_example/light/app/hls_rgb.c
LIB_SRC += test_example/light/app/ya_light_io.c
LIB_SRC += test_example/light/app/ya_light_product_test.c
LIB_SRC += test_example/light/app/ya_stripLights_display.c
LIB_SRC += test_example/light/app/ya_light_app.c
LIB_SRC += test_example/light/app/ya_light_example.c
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),light_scene)
LIB_SRC += test_example/light_scene/ya_example.c
LIB_SRC += test_example/light_scene/app/hls_rgb.c
LIB_SRC += test_example/light_scene/app/ya_light_io.c
LIB_SRC += test_example/light_scene/app/ya_light_product_test.c
LIB_SRC += test_example/light_scene/app/ya_stripLights_display.c
LIB_SRC += test_example/light_scene/app/ya_stripLights_app.c
LIB_SRC += test_example/light_scene/app/ya_stripLights_example.c
LIB_SRC += test_example/light_scene/app/ya_melody_broadcast.c
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),stripLights_without_mic)
LIB_SRC += test_example/stripLights_without_mic/app/hls_rgb.c
LIB_SRC += test_example/stripLights_without_mic/app/ya_stripLights_display.c
LIB_SRC += test_example/stripLights_without_mic/app/ya_stripLights_app.c
LIB_SRC += test_example/stripLights_without_mic/app/ya_stripLights_example.c
LIB_SRC += test_example/stripLights_without_mic/app/ya_ir_app.c
LIB_SRC += test_example/stripLights_without_mic/app/ya_melody_broadcast.c
endif

LIB_ASRC :=
LIBRARY_NAME := application
LOCAL_CFLAGS := -w
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/bsp
LOCAL_INC := -I$(TOPDIR)/components/inc/bsp
LOCAL_INC := -I$(TOPDIR)/components/sys
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/softmac
LOCAL_INC += -I$(TOPDIR)/components/iotapi
LOCAL_INC += -I$(TOPDIR)/components/netstack_wrapper
LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/libAACdec/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/libSYS/include
LOCAL_INC += -I$(TOPDIR)/components/inc/tiramisu
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/lwip-1.4.0/src/include
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/lwip-1.4.0/src/include/ipv4
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/lwip-1.4.0/ports/icomm/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/cJSON
LOCAL_INC += -I$(TOPDIR)/components/tools/utility/SSV_cJSON
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/lowpower
LOCAL_INC += -I$(TOPDIR)/components/tools/fota_api

LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/user
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/hal/inc
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/app/inc
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/app/src/internal_include 
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/csdk3.0.1/eng
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/csdk3.0.1/eng/include
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/AWS/include
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/AWS/external_libs/jsmn
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/AWS/platform/freertos
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/emq/MQTTPacket
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/akeeta/emq/MQTTClient-C/src

ifeq ($(CONFIG_AKEETA_EXAMPLE),light_yusing)
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light_yusing/io
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light_yusing/app
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),light_tospo)
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light_tospo/io
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light_tospo/app
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),light)
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light/io
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light/app
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),light_scene)
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light_scene/io
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/light_scene/app
endif

ifeq ($(CONFIG_AKEETA_EXAMPLE),stripLights_without_mic)
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/stripLights_without_mic/io
LOCAL_INC += -I$(TOPDIR)/projects/akeeta/src/app/test_example/stripLights_without_mic/app
endif

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
