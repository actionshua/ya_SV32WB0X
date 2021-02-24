
/*
 * 
 * Author: Tim Li
 *
 */
 
#ifndef _OTA_API_H_
#define _OTA_API_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HTTP = 0, ///< HTTP 
    TFTP = 1, ///< TFTP
    RAW = 2 ///< RAW
} OTA_PROTOCOL_TYPE;

typedef enum {
    OTA_SUCCESS = 0,  ///< OTA success.
    OTA_FAIL = 1      ///< OTA fail.
} OTA_STATUS;

typedef enum {
    OT_ERROR = -3, /// < Task fail
    OA_ERROR = -2, /// < Alloc fail
    OP_ERROR = -1, ///<Parameters fail
    O_SUCCESS = 0,
} OTA_RET_TYPE;

typedef enum {
    OTA_STATE_INIT = 0,
    OTA_STATE_GET_HDR,
    OTA_STATE_BURN,
    OTA_STATE_VERIFY,
    OTA_STATE_RETRY,
    OTA_STATE_DONE,
    OTA_STATE_FAIL,
    OTA_STATE_NONE
} OTA_STATE_TYPE;

/**
 * Stop OTA upadte procedure.
 * @retval  OTA_RET_TYPE.
 *   
 */
OTA_RET_TYPE ota_stop(void);

/**
 * Start OTA upadte procedure.
 * @retval  OTA_RET_TYPE.
 */
OTA_RET_TYPE ota_update(void);

/**
 * Set OTA server parameter.
 * @param  nProtocol        OTA protocal mode, 0 : HTTP, 1 : TFTP 2 : RAW.
 * @param  pIP                OTA Server addrass.
 * @param  port               OTA Server port.
 * @retval OTA_RET_TYPE.
 */
OTA_RET_TYPE ota_set_server(OTA_PROTOCOL_TYPE nProtocol, char *pIP, unsigned short port);

/**
 * Set OTA file parameter.
 * @param  filename                    OTA file name.
 * @param  filepath                     OTA file path.
 * @retval OTA_RET_TYPE.
 */
OTA_RET_TYPE ota_set_parameter(char* filename, char* filepath);


/**
 * Register OTA progress callback function.
 * @param  ota_progress_cbfn                    OTA progress callback function indicator OTA update success.
 * @retval OTA_RET_TYPE.
 */
OTA_RET_TYPE ota_register_progress_callback(void (*ota_progress_cbfn)(int));

/**
 * Register OTA status callback function.
 * @param  ota_status_cbfn                    OTA status callback function indicator OTA update success.
 * @retval OTA_RET_TYPE.
 */
OTA_RET_TYPE ota_register_status_callback(void (*ota_status_cbfn)(OTA_STATUS));

/**
 * Register OTA state callback function.
 * @param ota_state_cbfn                      OTA state callback function.
 * @retval  OTA_RET_TYPE
 */
OTA_RET_TYPE ota_register_state_callback(void (*ota_state_cbfn)(OTA_STATE_TYPE));

/**
 * Apply OTA update flag and  reboot system.
  * @retval OTA_RET_TYPE.
 */
OTA_RET_TYPE ota_reboot(void);

#ifdef __cplusplus
}
#endif

#endif //_OTA_API_H_

