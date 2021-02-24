#ifndef _APPL_LOG_H_
#define _APPL_LOG_H_


#include <stdint.h>
#include "ssv_types.h"
#include "ilog.h"



#define APPL_LOG(str, ...) do { ILOG_DBG(str, ##__VA_ARGS__);} while (0)
#define APPL_LOG_ARRAY(array, len) do { IDUMP(LOG_INFO, array, len);} while (0)



#endif  /// end of _APPL_LOG_H_
