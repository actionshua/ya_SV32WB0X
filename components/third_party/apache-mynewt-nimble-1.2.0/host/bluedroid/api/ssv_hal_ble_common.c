#include "ssv_hal_ble_common.h"
#include "ssv_gap_ble_api.h"
#include "btc/btc_task.h"
#define SSV_HAL_COMM_TAG "SSV_HAL_COMM_TAG"

extern void app_ble_init(void);
int ssv_hal_ble_common_init(void)
{
	int rc = 0;
	app_ble_init();

    rc = btc_init();
    if (rc != 0) {
        SSV_LOGE(SSV_HAL_COMM_TAG,"%s btc_init err %d\n", __func__, rc);
    }
	
	return rc;
}