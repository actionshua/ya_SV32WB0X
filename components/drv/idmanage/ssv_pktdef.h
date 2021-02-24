#ifndef _SSV_PKTDEF_H_
#define _SSV_PKTDEF_H_
/**
 *  The flag definition for c_type (command type) field of PKTInfo:
 *
 *      @ M0_TXREQ:
 *      @ M1_TXREQ
 *      @ M2_TXREQ
 *      @ M0_RXEVENT
 *      @ M1_RXEVENT
 *      @ HOST_CMD
 *      @ HOST_EVENT
 *
 */
#define M0_TXREQ                            0
#define M1_TXREQ                            1
#define M2_TXREQ                            2
#define M0_RXEVENT                          3
#define M2_RXEVENT                          4
#define HOST_CMD                            5
#define HOST_EVENT                          6
#define RATE_RPT                            7

#define IS_RPT_PKT(_p)       ((_p)->c_type==RATE_RPT)
#define IS_RX_PKT(_p)       ((_p)->c_type==M0_RXEVENT)
#define IS_TX_PKT(_p)       (/*((_p)->c_type>=M0_TXREQ)&&*/((_p)->c_type<=M2_TXREQ))
#endif	/* _SSV_PKTDEF_H_ */

