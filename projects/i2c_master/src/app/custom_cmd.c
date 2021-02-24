
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include <drv_i2cslv.h>
#include <drv_i2cmst.h>
#include <drv_pinmux.h>

#include "logger.h"

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)


typedef enum
{
    i2c_w = 0,
    i2c_r = 1
} i2c_control;

#define AH_DEVICE_VERSION                         0x00  // R
#define AH_FIRMWARE_VERSON                        0x01  // R
#define AH_AUTHENTICATION_PROTOCOL_MAJOR_VERSION  0x02  // R
#define AH_AUTHENTICATION_PROTOCOL_MINOR_VERSION  0x03  // R 
#define AH_DEVICE_ID                              0x04  // R
#define AH_IPOD_CERTIFICATE_DATA_LENGTH           0x50  // RW


#define AH_DEVICE_VERSION_LEN                         0x01  //
#define AH_FIRMWARE_VERSON_LEN                        0x01  // 
#define AH_AUTHENTICATION_PROTOCOL_MAJOR_VERSION_LEN  0x01  // 
#define AH_AUTHENTICATION_PROTOCOL_MINOR_VERSION_LEN  0x01  // 
#define AH_DEVICE_ID_LEN                              0x04  // 
#define AH_IPOD_CERTIFICATE_DATA_LENGTH_LEN           0x02  // 

#define I2C_SLAVE_RW_SIZE       (16)
#define I2C_SLAVE_ADDR          (0x50)
#define I2C_SLAVE_ADDR_WAC      (0x10)

#define MST_RX_BUFFER_SIZE	256
static uint8_t sg_mst_rx_buffer[MST_RX_BUFFER_SIZE] = {0};

int Cmd_i2c_master_rw_wac(s32 argc, char *argv[])
{
    printf("run i2C Master example with wac start...%s %s\n" , __DATE__ , __TIME__);

    uint8_t write_buf[I2C_SLAVE_RW_SIZE] ={0};
    uint8_t read_buf[I2C_SLAVE_RW_SIZE]  ={0};
    uint8_t read_addr[1] ;

    uint16_t i2cmaster_clk = 0;
    uint16_t i2cmaster_id = 0;

    i2cmaster_id = strtoul(argv[1], NULL, 10);
    i2cmaster_clk = strtoul(argv[2], NULL, 10);

    if ((argc != 3) || (i2cmaster_id < 0) || (i2cmaster_id > 1) || (i2cmaster_clk < 1) || (i2cmaster_clk > 1000)) {
        printf("Usage           : i2c_master_rw_wac <id> <clk_KHz>\n");
        printf("<id>            : i2c master id. 0:I2C_0 ; 1:I2C_1\n");
        printf("<clk_Hz>        : clk speed(1K-1000K)\n");
        return -1;
    }

    if(0 != drv_i2c_mst_init_ex(i2cmaster_id, i2cmaster_clk)){
        printf("init fail!\n");
        return -1;
    }

    printf("===== READ MFi info ===== \n");
    read_addr[0] = AH_DEVICE_VERSION ;
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
        
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_buf, AH_DEVICE_VERSION_LEN, 1, 1)){
        printf("read fail!\n");
        return -1;
    }
        
    printf("MFi device version: %d\n", read_buf[0]);

    read_addr[0] = AH_FIRMWARE_VERSON ;
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_buf, AH_FIRMWARE_VERSON_LEN, 1, 1)){
        printf("read fail!\n");
        return -1;
    }
    printf("MFi fw version: %d\n", read_buf[0]);

    read_addr[0] = AH_AUTHENTICATION_PROTOCOL_MAJOR_VERSION ;
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_buf, AH_AUTHENTICATION_PROTOCOL_MAJOR_VERSION_LEN, 1, 1)){
        printf("read fail!\n");
        return -1;
    }
    printf("MFi major version: %d\n", read_buf[0]);

    read_addr[0] = AH_AUTHENTICATION_PROTOCOL_MINOR_VERSION ;
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_buf, AH_AUTHENTICATION_PROTOCOL_MINOR_VERSION_LEN, 1, 1)){
        printf("read fail!\n");
        return -1;
    }
    printf("MFi minor version: %d\n", read_buf[0]);

    read_addr[0] = AH_DEVICE_ID;
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_buf, AH_DEVICE_ID_LEN, 1, 1)){
        printf("read fail!\n");
        return -1;
    }
    printf("MFi device id: %02d%02d%02d%02d\n", read_buf[0], read_buf[1], read_buf[2], read_buf[3]);

    printf("===== R/W MFi info ===== \n");
    write_buf[0] = AH_IPOD_CERTIFICATE_DATA_LENGTH;

    uint16_t certificate_data_len = 777;
    write_buf[1] = certificate_data_len >> 8;
    write_buf[2] = certificate_data_len & 0xFF;

    printf("write MFi certificate data len: %d\n", certificate_data_len);    
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, write_buf, AH_IPOD_CERTIFICATE_DATA_LENGTH_LEN + 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
    
    read_addr[0] = AH_IPOD_CERTIFICATE_DATA_LENGTH;
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR_WAC, read_buf, AH_IPOD_CERTIFICATE_DATA_LENGTH_LEN, 1, 1)){
        printf("read fail!\n");
        return -1;
    }

    printf("read  MFi certificate data len: %d\n", (uint16_t)(read_buf[0] << 8) + read_buf[1]);

    return 0;

}

int Cmd_i2c_master_w(s32 argc, char *argv[])
{
    printf("run i2C Master w example start...%s %s\n" , __DATE__ , __TIME__);
	
    uint16_t i2cmaster_clk = 0;
	uint16_t i2cdeviceaddr = 0;
	char *inputstr = NULL;
	uint16_t i2cstrlength = 0;

    i2cmaster_clk = strtoul(argv[1], NULL, 10);
	i2cdeviceaddr = strtoul(argv[2], NULL, 10);
	inputstr = argv[3];
	i2cstrlength = strlen(inputstr);

	printf(" input str = %s, length = %d\n", inputstr, i2cstrlength);

    if ((argc != 4) || (i2cmaster_clk < 1) || (i2cmaster_clk > 1000) || (i2cdeviceaddr == 0) || (inputstr == NULL)) {
        printf("Usage           : i2c_master_w <clk_KHz> <device address> <input string>\n");
        printf("<clk_KHz>       : clk speed(1K-1000K)\n");
		printf("<device address>: decive address\n");
		printf("<input string>  : input string\n");
        return -1;
    }

    if(0 != drv_i2c_mst_init(i2cmaster_clk)){
        printf("init fail!\n");
        return -1;
    }

    printf("===== Write %s to 0x%X===== \n", inputstr , i2cdeviceaddr);

    uint8_t send_cmd = 2;
    if(0 != drv_i2c_mst_write(i2cdeviceaddr, (uint8_t* )&send_cmd, 1, 1, 0)){
        printf("write fail!\n");
        return -1;
    }
    if(0 != drv_i2c_mst_write(i2cdeviceaddr, (uint8_t* )inputstr, i2cstrlength , 0, 1)){
        printf("write fail!\n");
        return -1;
    }

	return 0;
}

uint32_t g_i2cdeviceaddr;

void tmr_i2c_polling(OsTimer tmr) {
	uint8_t w_data[4] = {0};
	uint32_t i2cdatalength = 0;
	// ----------- Read length ------------
	w_data[0] = 0;
    if(0 != drv_i2c_mst_write(g_i2cdeviceaddr, w_data, 1, 1, 1)){
        printf("write fail!\n");
        return;
    }

    if(0 != drv_i2c_mst_read(g_i2cdeviceaddr, w_data , 1 , 1, 1)){
        printf("read fail!\n");
        return;

    }
	i2cdatalength = (uint32_t)w_data[0];
	// -----------------------------------
    if (i2cdatalength == 0) {
        return;
    }
	// ----------- Read Data ------------
	w_data[0] = 1;
    if(0 != drv_i2c_mst_write(g_i2cdeviceaddr, w_data, 1, 1, 1)){
        printf("write fail!\n");
        return;
    }

    if(0 != drv_i2c_mst_read(g_i2cdeviceaddr, sg_mst_rx_buffer, i2cdatalength , 1, 1)){
        printf("read fail!\n");
        return;
    }
    sg_mst_rx_buffer[i2cdatalength] = 0;
    printf("%s\n", sg_mst_rx_buffer);
}

int Cmd_i2c_master_polling(s32 argc, char *argv[])
{
    OsTimer tmr;
    uint32_t i2cmaster_clk = strtoul(argv[1], NULL, 10);
	uint32_t i2cdeviceaddr = strtoul(argv[2], NULL, 10);
    g_i2cdeviceaddr = i2cdeviceaddr;
    if(0 != drv_i2c_mst_init(i2cmaster_clk)){
        printf("init fail!\n");
        return -1;
    }
    OS_TimerCreate(&tmr, 50, 1, NULL, tmr_i2c_polling);
    OS_TimerStart(tmr);
	return 0;
}

int Cmd_i2c_master_r(s32 argc, char *argv[])
{
    printf("run i2C Master example r start...%s %s\n" , __DATE__ , __TIME__);
	
	uint32_t i = 0;
    uint32_t i2cmaster_clk = 0;
	uint32_t i2cdeviceaddr = 0;
	uint32_t i2cdatalength = 0;

	uint8_t w_data[4] = {0};

    i2cmaster_clk = strtoul(argv[1], NULL, 10);
	i2cdeviceaddr = strtoul(argv[2], NULL, 10);
	
    if ((argc != 3) || (i2cmaster_clk < 1) || (i2cmaster_clk > 1000) || (i2cdeviceaddr == 0)) {
        printf("Usage             : i2c_master_r <clk_KHz> <device address>\n");
        printf("<clk_Hz>          : clk speed(1K-1000K)\n");
		printf("<device address>  : decive address\n");
        return -1;
    }

    if(0 != drv_i2c_mst_init(i2cmaster_clk)){
        printf("init fail!\n");
        return -1;
    }

	// ----------- Read length ------------
	w_data[0] = 0;
    if(0 != drv_i2c_mst_write(i2cdeviceaddr, w_data, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }

    if(0 != drv_i2c_mst_read(i2cdeviceaddr, w_data , 1 , 1, 1)){
        printf("read fail!\n");
        return -1;

    }
	i2cdatalength = (uint32_t)w_data[0];
	printf("Length = %d\n",i2cdatalength);
    if (i2cdatalength == 0) {
        return -1;
    }
	// -----------------------------------

	
	// ----------- Read Data ------------
	w_data[0] = 1;
    if(0 != drv_i2c_mst_write(i2cdeviceaddr, w_data, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }

    if(0 != drv_i2c_mst_read(i2cdeviceaddr, sg_mst_rx_buffer , i2cdatalength , 1, 1)){
        printf("read fail!\n");
        return -1;
    }

	// print read data
	for(i=0; i < i2cdatalength; i++)
	{
		printf("%c", sg_mst_rx_buffer[i]);
	}
	// reset rx buffer
	for(i=0; i < MST_RX_BUFFER_SIZE; i++)
	{
		sg_mst_rx_buffer[i] = 0;
	}

	return 0;
}

int Cmd_i2c_master_rw(s32 argc, char *argv[])
{
    printf("run i2C Master example start...%s %s\n" , __DATE__ , __TIME__);

    uint8_t write_buf[I2C_SLAVE_RW_SIZE];
    uint8_t read_buf[I2C_SLAVE_RW_SIZE];
    uint8_t data_start_addr = 0;

    uint8_t i = 0;
    for(i = 0; i < I2C_SLAVE_RW_SIZE; i ++) {
        write_buf[i] = 0x20 + i;
        read_buf[i] = 0x0;
    }

    write_buf[0] = data_start_addr ;

    uint16_t i2cmaster_clk = 0;
    uint16_t i2cmaster_id = 0;

    i2cmaster_id = strtoul(argv[1], NULL, 10);
    i2cmaster_clk = strtoul(argv[2], NULL, 10);

    if ((argc != 3) || (i2cmaster_id < 0) || (i2cmaster_id > 1) || (i2cmaster_clk < 1) || (i2cmaster_clk > 1000)) {
        printf("Usage           : i2c_master_rw <id> <clk_KHz>\n");
        printf("<id>            : i2c master id. 0:I2C_0 ; 1:I2C_1\n");
        printf("<clk_Hz>        : clk speed(1K-1000K)\n");
        return -1;
    }
 
    if(0 != drv_i2c_mst_init_ex(i2cmaster_id, i2cmaster_clk)){
        printf("init fail!\n");
        return -1;
    }
    
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR, write_buf, I2C_SLAVE_RW_SIZE, 1, 1)){
        printf("write fail!\n");
        return -1;
    }

    printf("data read from addr[%d]\n", data_start_addr);
    
    if(0 != drv_i2c_mst_write_ex(i2cmaster_id, I2C_SLAVE_ADDR, &data_start_addr, 1, 1, 1)){
        printf("write fail!\n");
        return -1;
    }

    
    if(0 != drv_i2c_mst_read_ex(i2cmaster_id, I2C_SLAVE_ADDR, read_buf, I2C_SLAVE_RW_SIZE, 1, 1)){
        printf("read fail!\n");
        return -1;
    }
    
    
    for(i = 0; i < I2C_SLAVE_RW_SIZE-1 ; i ++) {
        printf("read_buf[%d] = 0x%x\n",i , read_buf[i]);
    }

    if(0 != memcmp(write_buf+1, read_buf, I2C_SLAVE_RW_SIZE-1)){
        printf("\n[compare r/w data fail!]\n");
        printf("\n[I2C Master Test : FAIL!]\n");
    }else{
        printf("\n[compare r/w data success!]\n");
        printf("\n[I2C Master Test : PASS!]\n");
    }
    
    drv_i2c_mst_deinit_ex(i2cmaster_id);

    return 0;
}

int Cmd_help (int32_t argc, char *argv[])
{
    printf ("\n*************************************************************************\n");
    printf ("Test I2C Target : \n");
    printf ("WB02 PINOUT: \n");
    printf ("               I2C_0 :\n");
    printf ("                   GPIO_04 : I2C_M_SCL\n");
    printf ("                   GPIO_06 : I2C_M_SDA\n");
    printf ("               I2C_1 :\n");
    printf ("                   GPIO_23 : I2C_M_SCL\n");
    printf ("                   GPIO_24 : I2C_M_SDA\n");
    
    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       i2c_master_rw <i2c_id> <clk_Hz>\n");
    printf ("Brief:\n");
    printf ("       This function can test the I2C master to write & read EEPROM data.\n");
    printf ("Note:\n");
    printf ("       None\n");
    printf ("Options:\n");
    printf ("<i2c_id>               The I2C master id. 0:I2C_0 ; 1:I2C_1\n");
    printf ("<clk_Hz>               The I2C master clk speed(1-1000)kHz.\n");
    /*
    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       i2c_master_rw_wac  <clk_Hz>\n");
    printf ("Brief:\n");
    printf ("       This function can test the I2C master to get Mfi inf.\n");
    printf ("Note:\n");
    printf ("       None\n");
    printf ("Options:\n");
    printf ("<clk_Hz>                       The I2C master clk speed(1-1000)kHz.\n");
    */

    return 0;
}

uint8_t sg_local_buffer[256];

int32_t i2c_rx_get_callback(hal_i2c_port port)
{
    drv_i2c_slv_recv(port, sg_local_buffer, 255);
    printf("get data!\n%s\n", sg_local_buffer);
    return 0;
}

int32_t i2c_tx_done_callback(hal_i2c_port port)
{
	// slave tx done cb
	printf("slave tx done\n");
	return 0;
}

int Cmd_i2c_slave_init(s32 argc, char *argv[])
{
    printf("run i2C Slave init example start...%s %s\n" , __DATE__ , __TIME__);
	
	drv_i2c_slv_init(DRV_I2C_DEFAULT, 0x55);
    drv_i2c_slv_register_recv_isr(i2c_rx_get_callback);
	drv_i2c_slv_register_tx_done_isr(i2c_tx_done_callback);
	
    return 0;
}


int Cmd_i2c_slave_add_str(s32 argc, char *argv[])
{
	printf("run i2C Slave example start...%s %s\n" , __DATE__ , __TIME__);
	char *inputstr = NULL;
	uint32_t i2cstrlength = 0;
	uint32_t i = 0;

	inputstr = argv[1];
	i2cstrlength = strlen(inputstr);
	
	printf("input str = %s, length = %d\n", inputstr, i2cstrlength);

    if ((argc != 2) || (inputstr == NULL)) {
        printf("Usage           : i2c_slave_add_str <input string> \n");
		printf("<input string>  : input string\n");
        return -1;
    }

    drv_i2c_slv_send(DRV_I2C_DEFAULT, (uint8_t *)inputstr, i2cstrlength);
		
	
    return 0;
}


/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "help",               Cmd_help,                   "i2C Master test help"          	},
    { "i2c_master_rw",      Cmd_i2c_master_rw,          "i2c_master_rw <i2c_id> <clk_Hz>"   },
    { "i2c_master_rw_wac",  Cmd_i2c_master_rw_wac,      "i2c_master_rw_wac <clk_Hz>"},
	{ "i2c_slave_init", 	Cmd_i2c_slave_init, 		"i2c slave init"},
	{ "i2c_slave_add_str",  Cmd_i2c_slave_add_str, 		"i2c_slave_add_str <input string>"},
	{ "i2c_master_w",		Cmd_i2c_master_w,			"i2c_master_w <clk_KHz> <device address> <input string>"},
	{ "i2c_master_r",		Cmd_i2c_master_r,			"i2c_master_r <clk_KHz> <device address>"},
	{ "i2c_master_p",		Cmd_i2c_master_polling,     "i2c_master_p <clk_KHz> <device address>, do polling rx"},
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


