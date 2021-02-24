#ifndef _L2CAP_COMPOSER_H_
#define _L2CAP_COMPOSER_H_



#include "l2cap_def.h"



typedef enum
{
    L2CAP_RECOMBINE_STATUS_ONGOING,
    L2CAP_RECOMBINE_STATUS_COMPLETED,
    L2CAP_RECOMBINE_STATUS_ERROR,

} L2CAP_RECOMBINE_STATUS;



u8 l2cap_composer_recombine(L2CAP_ID id, l2cap_sdu_st *sdu);



#endif  /// end of _L2CAP_COMPOSER_H_
