#include <stdio.h>
#include <stdint.h>
#include <hal_i2cslv.h>
#include "drv_i2cslv.h"
#include <attrs.h>
#include <osal.h>
#include <soc_defs.h>
#include <soc_types.h>
#include <string.h>

#include <logger.h>

#define MAX_FIFO_SIZE           (8)
#define M_I2C_SLV_TX_QUEUE_SIZE (8)
#undef MH_DEBUG

struct i2c_slv_tx_buf {
    int16_t len;
    int16_t idx;
    uint8_t buf[256];
} sg_i2c_slv_sending = {.len = -1}, sg_i2c_slv_waiting, sg_i2c_slv_receiving;

enum i2c_slv_state_machine {
    I2C_SLV_SM_IDLE             = 0,
    I2C_SLV_SM_WAIT_REG         = 1,
    I2C_SLV_SM_RX               = 2,
    I2C_SLV_SM_TX_GET_LEN       = 3,
    I2C_SLV_SM_TX_GET_DATA      = 4,
} sg_i2c_slv_sm[HAL_I2C_MAX];

pfun_i2c_slv_recv_isr sg_drv_i2c_slv_recv_isr = NULL;

void drv_i2c_slv_register_recv_isr(pfun_i2c_slv_recv_isr isr) {
    sg_drv_i2c_slv_recv_isr = isr;
}


pfun_i2c_slv_tx_done_isr sg_drv_i2c_slv_tx_done_isr = NULL;

void drv_i2c_slv_register_tx_done_isr(pfun_i2c_slv_tx_done_isr isr) {
    sg_drv_i2c_slv_tx_done_isr = isr;
}


//static struct ringbuffer_st {
//    uint8_t *buf;
//    uint32_t ridx, widx;
//    uint32_t length;
//    uint32_t data_length;
//} sg_tx_ring_buf[HAL_I2C_MAX];
//uint8_t gu8ReadConfig = 0; // 0: send data length, 1: send data
//uint32_t gu32DataLength = 0;

//uint8_t* pTXbuffer = NULL;
//uint8_t tx_data_counter = 0;

static OsBufQ sg_i2c_slv_tx_buffer_queue[HAL_I2C_MAX];

int32_t drv_i2c_slv_tx_empty_isr(hal_i2c_port port) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_tx_empty_isr(hal_i2c_port port) {
    // for send data burst mode.
#if defined(MH_DEBUG)
    REG32(0xC0000C00) = 'N';
#endif
    return 0;
}

int32_t drv_i2c_slv_read_request_isr(hal_i2c_port port) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_read_request_isr(hal_i2c_port port) {
#if defined(MH_DEBUG)
    REG32(0xC0000C00) = 'R';
#endif
    switch (sg_i2c_slv_sm[port]) {
        case I2C_SLV_SM_IDLE:
        case I2C_SLV_SM_WAIT_REG:
        case I2C_SLV_SM_RX:
            // no data should be send.
            hal_i2c_slv_write_fifo(port, 0);
            break;
        case I2C_SLV_SM_TX_GET_LEN:
            hal_i2c_slv_write_fifo(port, sg_i2c_slv_sending.len);
            sg_i2c_slv_sm[port] = I2C_SLV_SM_WAIT_REG;
            break;
        case I2C_SLV_SM_TX_GET_DATA:
            if ((sg_i2c_slv_sending.idx < sg_i2c_slv_sending.len) && (sg_i2c_slv_sending.idx < 255)) {
                hal_i2c_slv_write_fifo(port, sg_i2c_slv_sending.buf[sg_i2c_slv_sending.idx++]);
            } else {
                hal_i2c_slv_write_fifo(port, 0);
            }
            break;
    }
	//// Write data to CMD_DATA
	//if(gu8ReadConfig){
    //    hal_i2c_slv_write_fifo(port, pTXbuffer[tx_data_counter]);
	//	//sg_i2c_mst[port]->I2CMST_TRX_CMD_DATA = pTXbuffer[tx_data_counter];
	//	tx_data_counter++;
	//}
	//else{	
    //    hal_i2c_slv_write_fifo(port, gu32DataLength);
	//	//sg_i2c_mst[port]->I2CMST_TRX_CMD_DATA = gu32DataLength;
	//}
    return 0;
}

int32_t drv_i2c_slv_master_stop_receive_isr(hal_i2c_port port) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_master_stop_receive_isr(hal_i2c_port port) {
    //tx_data_counter = 0;
#if defined(MH_DEBUG)
    REG32(0xC0000C00) = 'E';
#endif
    switch (sg_i2c_slv_sm[port]) {
        ///case I2C_SLV_SM_IDLE:
        ///case I2C_SLV_SM_WAIT_REG:
        ///case I2C_SLV_SM_RX:
        ///    // no data should be send.
        ///    hal_i2c_slv_write_fifo(port, 0);
        ///    break;
        case I2C_SLV_SM_TX_GET_LEN:
			sg_i2c_slv_sm[port] = I2C_SLV_SM_WAIT_REG;
			break;
        case I2C_SLV_SM_TX_GET_DATA:
            sg_i2c_slv_sm[port] = I2C_SLV_SM_WAIT_REG;

			// check queue is empty or not?
			// empty -> callback to notify app layer
			if(0 == OS_BufQWaitingSize(sg_i2c_slv_tx_buffer_queue[port]))
			{
				if(sg_drv_i2c_slv_tx_done_isr){
					sg_drv_i2c_slv_tx_done_isr(port);	
				}
			}
			
            break;
        case I2C_SLV_SM_WAIT_REG:
        case I2C_SLV_SM_RX:
            break;
        default:
            printf("[%s][%d]should not %d case\n", __func__, __LINE__, sg_i2c_slv_sm[port]);
            break;
    }
    return 0;
}

int32_t drv_i2c_slv_master_abort_receive_isr(hal_i2c_port port) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_master_abort_receive_isr(hal_i2c_port port) {
    // normally clean the fifo.
#if defined(MH_DEBUG)
    REG32(0xC0000C00) = 'A';
#endif
    return 0;
}

int32_t drv_i2c_slv_rx_threshold_isr(hal_i2c_port port) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_rx_threshold_isr(hal_i2c_port port) {
#if defined(MH_DEBUG)
    REG32(0xC0000C00) = 'r';
#endif
    uint8_t data = hal_i2c_slv_read_fifo(port);
    switch (sg_i2c_slv_sm[port]) {
        case I2C_SLV_SM_IDLE:
        case I2C_SLV_SM_WAIT_REG:
            if (0 == data) {
                sg_i2c_slv_sm[port] = I2C_SLV_SM_TX_GET_LEN;
                if (OS_BufQWaitingSize(sg_i2c_slv_tx_buffer_queue[port])) {
                    if (OS_SUCCESS != OS_BufQPop(sg_i2c_slv_tx_buffer_queue[port], &sg_i2c_slv_sending, 1000)) {
                        printf ("[%s][%d] error!!\n", __func__, __LINE__);
                    }
                } else {
                    sg_i2c_slv_sending.len = 0;
                }
            } else if (1 == data) {
                sg_i2c_slv_sm[port] = I2C_SLV_SM_TX_GET_DATA;
            } else if (2 == data) {
                sg_i2c_slv_sm[port] = I2C_SLV_SM_RX;
                sg_i2c_slv_receiving.idx = 0;
            }
            break;
        case I2C_SLV_SM_RX:
            if (sg_i2c_slv_receiving.idx < 255) {
                sg_i2c_slv_receiving.buf[sg_i2c_slv_receiving.idx++] = data;
            } else {
                // overflow error handling
            }
            break;
        default:
            printf("[%s][%d]should not %d case\n", __func__, __LINE__, sg_i2c_slv_sm[port]);
            break;
    }
	// clear RX fifo full interrupt
    //    pRXbuffer[0] = hal_i2c_slv_read_fifo(port);
    //
    ////	// Get 0 -> next read data length
    ////	// Get 1 -> next read data
    //	if(0 == pRXbuffer[0]){
    //		gu8ReadConfig = 0;
    //	}
    //	else{
    //		gu8ReadConfig = 1;
    //	}
    //
    //	RX_Full_cb();
    return 0;
}

int32_t drv_i2c_slv_stop_detect_isr(hal_i2c_port port) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_stop_detect_isr(hal_i2c_port port) {
    // to do write procedure done.
#if defined(MH_DEBUG)
    REG32(0xC0000C00) = 's';
#endif
    switch (sg_i2c_slv_sm[port]) {
        case I2C_SLV_SM_RX:
            sg_i2c_slv_sm[port] = I2C_SLV_SM_WAIT_REG;
            sg_i2c_slv_receiving.buf[sg_i2c_slv_receiving.idx] = 0;
            if (sg_drv_i2c_slv_recv_isr) {
                sg_drv_i2c_slv_recv_isr(port);
            }
            //printf("len = %d, sg_i2c_slv_receiving.buf = %s\n", sg_i2c_slv_receiving.idx, sg_i2c_slv_receiving.buf); // should do a callback.
            break;
        default:
#if defined(MH_DEBUG)
            REG32(0xc0000c00) = 'S'; // for debug.
#endif
            break;
    }
    return 0;
}
int8_t drv_i2c_slv_init(hal_i2c_port port, uint16_t slv_addr)
{
	int8_t ret = 0;
	
    if (OS_SUCCESS != OS_BufQCreate(&(sg_i2c_slv_tx_buffer_queue[port]), M_I2C_SLV_TX_QUEUE_SIZE, sizeof (struct i2c_slv_tx_buf))) {
        return -1; // create queue failed.
    }

    sg_i2c_slv_sm[port] = I2C_SLV_SM_IDLE;
    sg_i2c_slv_receiving.idx = 0;

	ret = hal_i2c_slv_init(port, slv_addr);
    hal_i2c_slv_register_tx_empty_isr(drv_i2c_slv_tx_empty_isr);
    hal_i2c_slv_register_read_request_isr(drv_i2c_slv_read_request_isr);
    hal_i2c_slv_register_master_stop_receive_isr(drv_i2c_slv_master_stop_receive_isr);
    hal_i2c_slv_register_master_abort_receive_isr(drv_i2c_slv_master_abort_receive_isr);
    hal_i2c_slv_register_rx_threshold_isr(drv_i2c_slv_rx_threshold_isr);
    hal_i2c_slv_register_stop_detect_isr(drv_i2c_slv_stop_detect_isr);


	return ret;
}

//int32_t drv_i2c_slv_init_send_buf(hal_i2c_port port, uint8_t *tx_buf, uint32_t length) {
//    sg_tx_ring_buf[port].buf = tx_buf;
//    sg_tx_ring_buf[port].ridx = 0;
//    sg_tx_ring_buf[port].widx = 0;
//    sg_tx_ring_buf[port].length = length;
//    sg_tx_ring_buf[port].data_length = 0;
//
//    return 0;
//}

//int32_t drv_i2c_slv_tx_empty_isr(hal_i2c_port port) {
//    int i;
//    for (int i = 0; i < MAX_FIFO_SIZE; i++) {
//                
//    }
//    return 0;
//}

int32_t drv_i2c_slv_recv(hal_i2c_port port, uint8_t *buf, uint8_t max_len) ATTRIBUTE_SECTION_FAST;
int32_t drv_i2c_slv_recv(hal_i2c_port port, uint8_t *buf, uint8_t max_len) {
    int32_t len = 0;
    memcpy(buf, sg_i2c_slv_receiving.buf, (len = sg_i2c_slv_receiving.idx > max_len? max_len: sg_i2c_slv_receiving.idx));
    //printf("len = %d, sg_i2c_slv_receiving.buf = %s\n", sg_i2c_slv_receiving.idx, sg_i2c_slv_receiving.buf); // should do a callback.
    return len;
}

int32_t drv_i2c_slv_send(hal_i2c_port port, uint8_t *buf, uint8_t len) {
    int i;
    memcpy(sg_i2c_slv_waiting.buf, buf, len);
    sg_i2c_slv_waiting.len = len;
    sg_i2c_slv_waiting.idx = 0;
    if (OS_SUCCESS == OS_BufQPush(sg_i2c_slv_tx_buffer_queue[port], &sg_i2c_slv_waiting)) {
        return 0;
    } else {
        return -1;
    }
//    for (i = 0; i < len; i++) {
//        uint32_t widx = sg_tx_ring_buf[port].widx+1;
//        widx = widx % sg_tx_ring_buf[port].length;
//        if (widx == sg_tx_ring_buf[port].ridx) {
//            return -1; // full.
//        }
//        sg_tx_ring_buf[port].buf[sg_tx_ring_buf[port].widx] = buf[i];
//        sg_tx_ring_buf[port].widx = widx;
//        sg_tx_ring_buf[port].data_length++;
//    }
	//hal_i2c_slv_enable_interrupt(port, INT_R_RD_REQ, 0);
    //return 0;
}

