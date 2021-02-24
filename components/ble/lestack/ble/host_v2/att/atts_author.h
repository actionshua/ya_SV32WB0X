#ifndef _ATTS_AUTHOR_H_
#define _ATTS_AUTHOR_H_



#include "atts_def.h"
#include "atts_core.h"



ATTS_AUTHOR_STATE atts_author_get_rd_author(u16 conn_hdl, u16 attr_hdl, u16 value_offset, u8 *response_with_value, attr_value_st *response_attr_value, u8 *err_code);
void atts_author_clear_rd_author(u16 conn_hdl, u16 attr_hdl);
ATTS_AUTHOR_STATE atts_author_get_wr_author(u16 conn_hdl, u16 attr_hdl, u8 *value, u16 value_len, u8 *response_with_value, u8 *err_code);
void atts_author_clear_wr_author(u16 conn_hdl, u16 attr_hdl);
ATTS_AUTHOR_STATE atts_author_get_prep_wr_author(u16 conn_hdl, u16 attr_hdl, u16 value_offset, u16 value_len, u8* value, u8 *err_code);
void atts_author_clear_prep_wr_author(u16 conn_hdl, u16 attr_hdl);
ATTS_AUTHOR_STATE atts_author_get_exec_wr_author(u16 conn_hdl, u8 flags, u8 *err_code);
void atts_author_clear_exec_wr_author(u16 conn_hdl);
u8 atts_author_send_write_sync(u16 conn_hdl, u16 attr_hdl, u16 value_len, u8 *value);
u8 atts_author_send_write_sync_with_cb(u16 conn_hdl, u16 attr_hdl, u16 value_len, u8 *value, l2cap_sdu_st *sdu);



#endif  /// end of _ATTS_AUTHOR_H_

