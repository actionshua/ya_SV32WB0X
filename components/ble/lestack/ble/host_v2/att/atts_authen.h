#ifndef _ATTS_AUTHEN_H_
#define _ATTS_AUTHEN_H_



#include "atts_def.h"
#include "atts_core.h"



ATTS_AUTHEN_STATE atts_authen_get_authentication(u16 conn_hdl, u16 security_level, u8 *error_code);
void atts_authen_clear_authentication(u16 conn_hdl);



#endif  /// end of _ATTS_AUTHEN_H_

