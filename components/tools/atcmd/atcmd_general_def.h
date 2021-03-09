/**
 *
 * @page ATCMD AT Command Manual V2.0
 *
 * @section ATCMD_general General AT Command
 *
 * @subsection ATCMD_general_1 List all AT Command
 *
 * | command     | AT+H |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  |  AT+H=OK               |
 * | example       | AT+H |
 *
 * @subsection ATCMD_general_2 System Reboot
 *
 * | command     | AT+REBOOT|
 * |---------------|-------------------|
 * | param         | none        |
 * | return value  | AT+REBOOT=OK               |
 * | example       | AT+REBOOT |
 *
 * @subsection ATCMD_general_3 Get Firmware Version
 * | command     | AT+VERSION=?|
 * |---------------|-------------------|
 * | param         | none       |
 * | return value  | +VERSION:<number>              |
 * | example       | AT+VERSION=? |
 *
 * @subsection ATCMD_general_4 Get Manufacture Information
 * | command     | AT+MF_INFO=?|
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | +MF_INFO:<manufacture>               |
 * | example       | AT+MF_INFO=? |
 *
 *
 * @subsection ATCMD_general_5 Write MAC1 address to Flash
 * | command     | AT+RF_WRITE_MAC1=<mac1_address> |
 * |---------------|-------------------|
 * | param         | <mac1_address>: xx:xx:xx:xx:xx:xx         |
 * | return value  | AT+RF_WRITE_MAC1=OK               |
 * | example       | AT+RF_WRITE_MAC1=00:23:45:67:89:15 |
 *
 * @subsection ATCMD_general_6 Read MAC1 address from flash
 * | command     | AT+RF_READ_MAC1=? |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+RF_READ_MAC1=00:23:45:67:89:15               |
 * | example       | AT+RF_READ_MAC1=? |
 *
 * @subsection ATCMD_general_7 Write MAC2 address to Flash
 * | command     | AT+RF_WRITE_MAC2=<mac2_address> |
 * |---------------|-------------------|
 * | param         | <mac2_address>: xx:xx:xx:xx:xx:xx          |
 * | return value  | AT+RF_WRITE_MAC2=OK               |
 * | example       | AT+RF_WRITE_MAC2=00:23:45:67:89:15 |
 *
 * @subsection ATCMD_general_8 Read MAC2 address from flash
 * | command     | AT+RF_READ_MAC2=?  |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+RF_READ_MAC2=00:23:45:67:89:15              |
 * | example       | AT+RF_READ_MAC2=> |
 *
 * @subsection ATCMD_general_9 Enable Efuse Write function
 * | command     | AT+EFUSE_ENABLE_WRITE  |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+EFUSE_ENABLE_WRITE=OK               |
 * | example       | AT+EFUSE_ENABLE_WRITE  |
 *
 * @subsection ATCMD_general_10 Write MAC address to Efuse
 * | command     | AT+EFUSE_WRITE_MAC=<mac_address>    |
 * |---------------|-------------------|
 * | param         | <mac_address>: xx:xx:xx:xx:xx:xx:xx         |
 * | return value  | AT+EFUSE_WRITE_MAC=OK               |
 * | example       | AT+EFUSE_WRITE_MAC=00:11:22:33:44:55  |
 *
 * @subsection ATCMD_general_11 Read MAC address from Efuse
 * | command     | AT+EFUSE_READ_MAC=?   |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+EFUSE_READ_MAC=00:11:22:33:44:55               |
 * | example       | AT+EFUSE_READ_MAC=? |
 *
 * @subsection ATCMD_general_12 Dump Efuse Context
 * | command     | AT+EFUSE_DUMP   |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+EFUSE_DUMP=OK               |
 * | example       | AT+EFUSE_DUMP |
 *
 * @subsection ATCMD_general_13 Configure Debug UART
 * | command     | AT+UART_CONFIG=<uartnum>,<baudrate>,<databits>,<stopbits>,<parity>    |
 * |---------------|-------------------|
 * | param         | <uartnum>: 0:debug uart, 1:data uart <br><baudrate>: uart bard rate <br>[<databits>]: 0: 5 bits, 1: 6 bits, 2: 7 bits, 3: 8 bits <br>[<stopbits>]: 0: one bit, 1: two bits <br>[<parity>]: 0: none, 1: odd, 3: even      |
 * | return value  | AT+UART_CONFIG=OK               |
 * | example       | AT+UART_CONFIG=0,921600,3,0,0  |
 *
 * @subsection ATCMD_general_14 Dormant mode
 * @description System enter dormant mode, it means only rtc & gpio can wake system up.
 * | command     | AT+DORMANT=<seconds>,<micro-seconds>    |
 * |---------------|-------------------|
 * | param         | <second>: 0~134217 <br><micro-seconds>: 0~1000000      |
 * | return value  | time=<time>               |
 * | example       | AT+DORMANT=60,0  |
 */

#ifndef ATCMD_GENERAL_DEF_H__
#define ATCMD_GENERAL_DEF_H__

//### following AT CMD, has doc ###
//general atcmd
#define ATCMD_LIST                      "AT+H"
#define ATCMD_REBOOT                "AT+REBOOT"
#define ATCMD_VERSION               "AT+VERSION"
#define ATCMD_MINFO                 "AT+MF_INFO"
#define ATCMD_RADIO_WRITE_MAC1		"AT+RF_WRITE_MAC1"
#define ATCMD_RADIO_READ_MAC1			"AT+RF_READ_MAC1"
#define ATCMD_RADIO_WRITE_MAC2		"AT+RF_WRITE_MAC2"
#define ATCMD_RADIO_READ_MAC2			"AT+RF_READ_MAC2"
#if BLE_EN
#define ATCMD_RADIO_WRITE_MAC3 ("AT+RF_WRITE_MAC3")
#define ATCMD_RADIO_READ_MAC3  ("AT+RF_READ_MAC3")
#endif
//efuse atcmd
#define ATCMD_EFUSE_ENABLE_WRITE		"AT+EFUSE_ENABLE_WRITE"
#define ATCMD_EFUSE_WRITE_MAC		"AT+EFUSE_WRITE_MAC"
#define ATCMD_EFUSE_READ_MAC	        	"AT+EFUSE_READ_MAC"
#define ATCMD_EFUSE_DUMP	        	"AT+EFUSE_DUMP"
//confurate for debug uart
#define ATCMD_UART_CONFIG                        "AT+UART_CONFIG"
//read/write data with user raw section
#define ATCMD_USER_RAW_CONFIG                        "AT+USER_RAW"
//### following AT CMD, no doc ###
#define ATCMD_POWERSAVE             "AT+POWERSAVE"

//### following are not AT CMD,they are for debugging ###
#define ATCMD_CFGPARSER             ("AT+CFGPARSER")
#define ATCMD_CFG_TESTER            ("AT+CFG_TESTER")
#define ATCMD_CFG_MAC_TESTER        ("AT+CFG_MAC_TESTER")
#define ATCMD_USER_FLASH	"AT+USER_FLASH"
#define ATCMD_TEST_PERIPHERAL       "testp"
#define ATCMD_SYSINFO				"sysinfo"
#define ATCMD_ILOG_LEVEL            "_l"
#define ATCMD_ILOG_TSAK             "_t"
#define ATCMD_FSINFO				"fsinfo"
#define ATCMD_FSINFO_PERSONAL		"fsinfo_p"
#define ATCMD_FSRESET				"fsreset"
#define ATCMD_MEMINFO				"meminfo"
#define ATCMD_MEMDUMP				"md"
#define ATCMD_WRITE_REG             "regw"
#define ATCMD_READ_REG              "regr"

#define ATCMD_GPIO_WAKEUP           ("AT+GPIO_WAKEUP")
#define ATCMD_POWERMODE             ("AT+POWERMODE")
#define ATCMD_POWERCONF             ("AT+POWERCONF")
#define ATCMD_SETDTIMPERIOD         ("AT+SETDTIMPERIOD")
#define ATCMD_DORMANT               ("AT+DORMANT")
#if BLE_GAP_ATCMD_EN
#define ATCMD_BLEINIT               ("AT+bleinit")
#define ATCMD_BLESETSCANPARAMS      ("AT+blesetscanparams")
#define ATCMD_BLESTARTSCAN          ("AT+blestartscan")
#define ATCMD_BLEADVSTART           ("AT+bleADV")
#define ATCMD_BLEDISCONNECT      ("AT+bledisconnect")
#endif

#define ATCMD_BLE_UART_START        ("AT+ble_uart_start")
#define ATCMD_BLE_UART_TX           ("AT+ble_uart_send")

#if BLE_GATTS_ATCMD_EN
#define ATCMD_BLEADDSERVICE         ("AT+bleaddservice")
#define ATCMD_BLESENDINDICATION     ("AT+blesendindication")
#endif
#if BLE_GAP_ATCMD_EN
#define ATCMD_BLEGATTCOPEN          ("AT+blegattcopen")
#define ATCMD_BLEGATTCWRITECHAR     ("AT+blegattcwritechar")
#endif

#if MESH_BLE_EN
#define ATCMD_BMREG          ("AT+bmreg")
#define ATCMD_BMOOB          ("AT+bmoob")
#define ATCMD_BMINIT         ("AT+bminit")
#define ATCMD_BMTXPOWER      ("AT+bmtxpower")
#define ATCMD_BMTPCVM        ("AT+bmtpcvm")
#define ATCMD_BMGOCM         ("AT+bmgocm")
#define ATCMD_BMVMCM         ("AT+bmvmcm")
#define ATCMD_BMPDEV         ("AT+bmpdev")
#define ATCMD_BMNBEARER      ("AT+bmnbearer")
#define ATCMD_BMSTCORELOAD      ("AT+bmstcoreload") //settings_core_load
#define ATCMD_BMSTCORECOMMIT      ("AT+bmstcoreci")//settings_core_commit
#define ATCMD_BMLOGLVL      ("AT+bmloglvl")//mesh log level
#define ATCMD_BMPRIMARYADDR      ("AT+bmprimaryaddr")//mesh primary address
#define ATCMD_BMSETSCANWIN      ("AT+bmsetscanwin")//mesh set BLE scan window and interval
#if CONFIG_BLE_MESH_PROVISIONER
#define ATCMD_BMPBEARER      ("AT+bmpbearer")
#define ATCMD_BMPGETN        ("AT+bmpgetn")
#define ATCMD_BMPADDN        ("AT+bmpaddn")
#define ATCMD_BMPBIND        ("AT+bmpbind")
#define ATCMD_BMPKEY         ("AT+bmpkey")
#endif//CONFIG_BLE_MESH_PROVISIONER
#define ATCMD_BMCCM          ("AT+bmccm")
#define ATCMD_BMNRESET       ("AT+bmnreset")
#define ATCMD_BMNSUSPEND      ("AT+bmnsuspend")
#define ATCMD_BMNRESUME       ("AT+bmnresume")
#define ATCMD_BMSPERF        ("AT+bmsperf")//ble mesh server: performance statistics
#define ATCMD_BMNNWK         ("AT+bmnnwk")//ble mesh node: auto join network
#define ATCMD_BMGETPUBLISHACK ("AT+bmgetpublishack")
#define ATCMD_BMGPIO          ("AT+bmgpio")
#endif
#define ATCMD_BLEMODE         ("AT+BLE")
#define ATCMD_ENBLEMODE       ("AT+EnBLEMode")
//garbage code
//#define ATCMD_REMOVE_CONF           "AT+REMOVE_CONF"
//#define ATCMD_BENCH_FLASH_READ      "bflashr"
//#define ATCMD_BENCH_FLASH_WRITE     "bflashw"
//#define ATCMD_FLASH_WRITE           "flashw"
//#define ATCMD_FLASH_READ            "flashr"
//#define ATCMD_FLASH_ERASE           "flashe"
//#define ATCMD_FLASH_ERASE32K        "flash32ke"

#endif
