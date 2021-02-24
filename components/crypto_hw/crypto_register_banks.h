/*
 * crypto_register_banks.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_REGISTER_BANKS_H_
#define INCLUDE_CRYPTO_CRYPTO_REGISTER_BANKS_H_

/*
 * 190430.001: first draft
 * 190501.001: define SHA modes, little/big endian
 * 190517.001: define DBG, ECCP base address
 * 190531.001: define APB DBG base address, busy cycles cnts
 * 190611.001: define COP_TRAP reasons, fix typo
 */
#define COP_VERSION             "COP.190611.001"

#define COP_SHA_LE              (0x1 << 5)
#define COP_SHA_BE              (0x0 << 5)
#define COP_SHA1_MODE           (COP_SHA_LE + (0x1))
#define COP_SHA224_MODE         (COP_SHA_LE + (0x2))
#define COP_SHA256_MODE         (COP_SHA_LE + (0x3))
#define COP_SHA384_MODE         (COP_SHA_LE + (0x4))
#define COP_SHA512_MODE         (COP_SHA_LE + (0x5))
#define COP_TRNG_ENABLE         (0x2)
#define COP_TRNG_DISABLE        (0x0)
#define COP_AES_KEY128          (0x0 << 1)
#define COP_AES_KEY192          (0x1 << 1)
#define COP_AES_KEY256          (0x2 << 1)
#define COP_AES_ENC             (0x0 << 3)
#define COP_AES_DEC             (0x1 << 3)
#define COP_AES_ENABLE          (0x1)
#define COP_AES_DISABLE         (0x0)
#define COP_AES_KEY128_ENC      (COP_AES_KEY128 | COP_AES_ENC | COP_AES_ENABLE)
#define COP_AES_KEY128_DEC      (COP_AES_KEY128 | COP_AES_DEC | COP_AES_ENABLE)
#define COP_AES_KEY192_ENC      (COP_AES_KEY192 | COP_AES_ENC | COP_AES_ENABLE)
#define COP_AES_KEY192_DEC      (COP_AES_KEY192 | COP_AES_DEC | COP_AES_ENABLE)
#define COP_AES_KEY256_ENC      (COP_AES_KEY256 | COP_AES_ENC | COP_AES_ENABLE)
#define COP_AES_KEY256_DEC      (COP_AES_KEY256 | COP_AES_DEC | COP_AES_ENABLE)
#define COP_TRAP_NMI            (0x8)
#define COP_TRAP_INVALID_ADDR   (0x4)
#define COP_TRAP_INVALID_CMD    (0x2)
#define COP_TRAP_BUSY_TIMEOUT   (0x1)
#define COP_TRAP_DEFAULT        (COP_TRAP_NMI | COP_TRAP_INVALID_ADDR | COP_TRAP_INVALID_CMD)

#define COPE_RESET              (0x0)
#define COPE_SET_BASEADDR       (0x01 << 14)
#define COPE_CHECK_BUSY         (0x02 << 14)
#define COPE_BUSY_CYCLE_CNT     (0x03 << 14)
#define COPE_AES_KICK           (0x04 << 14)
#define COPE_AES_RESET          (0x05 << 14)
#define COPE_MUL_KICK           (0x06 << 14)
#define COPE_SHA_KICK           (0x07 << 14)
#define COPE_SHA_LOAD           (0x08 << 14)
#define COPE_SHA_RESET          (0x09 << 14)
#define COPE_AES_GEN_KEY        (0x0a << 14)
#define COPE_MUL_RESET          (0x0b << 14)
#define COPE_SEED_SAMPLE        (0x0c << 14)
#define COPE_LFSR_EN_E          (0x0d << 14)
#define COPE_LFSR_NEXT_E        (0x0e << 14)
#define COPE_ECP_START          (0x0f << 14)
#define COPE_ECP_RESTART        (0x10 << 14)
#define COPE_ECP_RESET          (0x11 << 14)
#define COPE_ECP_MEM_KICK       (0x12 << 14)

#define COP_BUSY_CYCLE_0        ((COPE_BUSY_CYCLE_CNT) + 0x0)
#define COP_BUSY_CYCLE_9        ((COPE_BUSY_CYCLE_CNT) + 0x9)
#define COP_BUSY_CYCLE_32       ((COPE_BUSY_CYCLE_CNT) + 0x20)

/*
 * COP DBG
 */
#define COP_DBG_APB_BASE        (0xCA100000)
#define COP_DBG_CUR_COP_INST    (COP_DBG_APB_BASE + 0x1E0)
#define COP_DBG_LAST_COP_INST   (COP_DBG_APB_BASE + 0x1E4)
#define COP_DBG_VER_CODE        (COP_DBG_APB_BASE + 0x1EC)
#define COP_DBG_TIMEOUT_VALUE   (COP_DBG_APB_BASE + 0x280) 
#define COP_DBG_BASE_ADDR       (COP_DBG_APB_BASE + 0x284)
#define COP_DBG_ERR_STATUS      (COP_DBG_APB_BASE + 0x288)
#define COP_DBG_TRAP_EN         (COP_DBG_APB_BASE + 0x28C)

/*
 * SHA base address
 */
#define COP_ADDR_SHA_MSG0            (COPE_SET_BASEADDR + (0x0000 >> 2))
#define COP_ADDR_SHA_MSG1            (COPE_SET_BASEADDR + (0x0004 >> 2))
#define COP_ADDR_SHA_MSG2            (COPE_SET_BASEADDR + (0x0008 >> 2))
#define COP_ADDR_SHA_MSG3            (COPE_SET_BASEADDR + (0x000C >> 2))
#define COP_ADDR_SHA_MSG4            (COPE_SET_BASEADDR + (0x0010 >> 2))
#define COP_ADDR_SHA_MSG5            (COPE_SET_BASEADDR + (0x0014 >> 2))
#define COP_ADDR_SHA_MSG6            (COPE_SET_BASEADDR + (0x0018 >> 2))
#define COP_ADDR_SHA_MSG7            (COPE_SET_BASEADDR + (0x001C >> 2))
#define COP_ADDR_SHA_MSG8            (COPE_SET_BASEADDR + (0x0020 >> 2))
#define COP_ADDR_SHA_MSG9            (COPE_SET_BASEADDR + (0x0024 >> 2))
#define COP_ADDR_SHA_MSG10           (COPE_SET_BASEADDR + (0x0028 >> 2))
#define COP_ADDR_SHA_MSG11           (COPE_SET_BASEADDR + (0x002C >> 2))
#define COP_ADDR_SHA_MSG12           (COPE_SET_BASEADDR + (0x0030 >> 2))
#define COP_ADDR_SHA_MSG13           (COPE_SET_BASEADDR + (0x0034 >> 2))
#define COP_ADDR_SHA_MSG14           (COPE_SET_BASEADDR + (0x0038 >> 2))
#define COP_ADDR_SHA_MSG15           (COPE_SET_BASEADDR + (0x003C >> 2))
#define COP_ADDR_SHA_MSG0H           (COPE_SET_BASEADDR + (0x0040 >> 2))
#define COP_ADDR_SHA_MSG1H           (COPE_SET_BASEADDR + (0x0044 >> 2))
#define COP_ADDR_SHA_MSG2H           (COPE_SET_BASEADDR + (0x0048 >> 2))
#define COP_ADDR_SHA_MSG3H           (COPE_SET_BASEADDR + (0x004C >> 2))
#define COP_ADDR_SHA_MSG4H           (COPE_SET_BASEADDR + (0x0050 >> 2))
#define COP_ADDR_SHA_MSG5H           (COPE_SET_BASEADDR + (0x0054 >> 2))
#define COP_ADDR_SHA_MSG6H           (COPE_SET_BASEADDR + (0x0058 >> 2))
#define COP_ADDR_SHA_MSG7H           (COPE_SET_BASEADDR + (0x005C >> 2))
#define COP_ADDR_SHA_MSG8H           (COPE_SET_BASEADDR + (0x0060 >> 2))
#define COP_ADDR_SHA_MSG9H           (COPE_SET_BASEADDR + (0x0064 >> 2))
#define COP_ADDR_SHA_MSG10H          (COPE_SET_BASEADDR + (0x0068 >> 2))
#define COP_ADDR_SHA_MSG11H          (COPE_SET_BASEADDR + (0x006C >> 2))
#define COP_ADDR_SHA_MSG12H          (COPE_SET_BASEADDR + (0x0070 >> 2))
#define COP_ADDR_SHA_MSG13H          (COPE_SET_BASEADDR + (0x0074 >> 2))
#define COP_ADDR_SHA_MSG14H          (COPE_SET_BASEADDR + (0x0078 >> 2))
#define COP_ADDR_SHA_MSG15H          (COPE_SET_BASEADDR + (0x007C >> 2))
#define COP_ADDR_SHA_COEF_A          (COPE_SET_BASEADDR + (0x0080 >> 2))
#define COP_ADDR_SHA_COEF_B          (COPE_SET_BASEADDR + (0x0084 >> 2))
#define COP_ADDR_SHA_COEF_C          (COPE_SET_BASEADDR + (0x0088 >> 2))
#define COP_ADDR_SHA_COEF_D          (COPE_SET_BASEADDR + (0x008C >> 2))
#define COP_ADDR_SHA_COEF_E          (COPE_SET_BASEADDR + (0x0090 >> 2))
#define COP_ADDR_SHA_COEF_F          (COPE_SET_BASEADDR + (0x0094 >> 2))
#define COP_ADDR_SHA_COEF_G          (COPE_SET_BASEADDR + (0x0098 >> 2))
#define COP_ADDR_SHA_COEF_H          (COPE_SET_BASEADDR + (0x009C >> 2))
#define COP_ADDR_SHA_COEF_AH         (COPE_SET_BASEADDR + (0x00A0 >> 2))
#define COP_ADDR_SHA_COEF_BH         (COPE_SET_BASEADDR + (0x00A4 >> 2))
#define COP_ADDR_SHA_COEF_CH         (COPE_SET_BASEADDR + (0x00A8 >> 2))
#define COP_ADDR_SHA_COEF_DH         (COPE_SET_BASEADDR + (0x00AC >> 2))
#define COP_ADDR_SHA_COEF_EH         (COPE_SET_BASEADDR + (0x00B0 >> 2))
#define COP_ADDR_SHA_COEF_FH         (COPE_SET_BASEADDR + (0x00B4 >> 2))
#define COP_ADDR_SHA_COEF_GH         (COPE_SET_BASEADDR + (0x00B8 >> 2))
#define COP_ADDR_SHA_COEF_HH         (COPE_SET_BASEADDR + (0x00BC >> 2))
#define COP_ADDR_SHA_CTL             (COPE_SET_BASEADDR + (0x00C0 >> 2))
#define COP_ADDR_SHA_CMD             (COPE_SET_BASEADDR + (0x00C4 >> 2))

/*
 * AES & GF128MUL base address
 */
#define COP_ADDR_AES_CTRL            (COPE_SET_BASEADDR + (0x0100 >> 2))
#define COP_ADDR_AES_MUX_SEL         (COPE_SET_BASEADDR + (0x0104 >> 2))
#define COP_ADDR_AES_CMD             (COPE_SET_BASEADDR + (0x0108 >> 2))
#define COP_ADDR_AES_KEY_0           (COPE_SET_BASEADDR + (0x0110 >> 2))
#define COP_ADDR_AES_KEY_1           (COPE_SET_BASEADDR + (0x0114 >> 2))
#define COP_ADDR_AES_KEY_2           (COPE_SET_BASEADDR + (0x0118 >> 2))
#define COP_ADDR_AES_KEY_3           (COPE_SET_BASEADDR + (0x011c >> 2))
#define COP_ADDR_AES_KEY_4           (COPE_SET_BASEADDR + (0x0120 >> 2))
#define COP_ADDR_AES_KEY_5           (COPE_SET_BASEADDR + (0x0124 >> 2))
#define COP_ADDR_AES_KEY_6           (COPE_SET_BASEADDR + (0x0128 >> 2))
#define COP_ADDR_AES_KEY_7           (COPE_SET_BASEADDR + (0x012c >> 2))
#define COP_ADDR_AES_IV_0            (COPE_SET_BASEADDR + (0x0130 >> 2))
#define COP_ADDR_AES_IV_1            (COPE_SET_BASEADDR + (0x0134 >> 2))
#define COP_ADDR_AES_IV_2            (COPE_SET_BASEADDR + (0x0138 >> 2))
#define COP_ADDR_AES_IV_3            (COPE_SET_BASEADDR + (0x013C >> 2))
#define COP_ADDR_AES_DIN_0           (COPE_SET_BASEADDR + (0x0150 >> 2))
#define COP_ADDR_AES_DIN_1           (COPE_SET_BASEADDR + (0x0154 >> 2))
#define COP_ADDR_AES_DIN_2           (COPE_SET_BASEADDR + (0x0158 >> 2))
#define COP_ADDR_AES_DIN_3           (COPE_SET_BASEADDR + (0x015c >> 2))
#define COP_ADDR_AES_DOUT_0          (COPE_SET_BASEADDR + (0x0160 >> 2))
#define COP_ADDR_AES_DOUT_1          (COPE_SET_BASEADDR + (0x0164 >> 2))
#define COP_ADDR_AES_DOUT_2          (COPE_SET_BASEADDR + (0x0168 >> 2))
#define COP_ADDR_AES_DOUT_3          (COPE_SET_BASEADDR + (0x016c >> 2))
#define COP_ADDR_MUL_DIN0_0          (COPE_SET_BASEADDR + (0x0170 >> 2))
#define COP_ADDR_MUL_DIN0_1          (COPE_SET_BASEADDR + (0x0174 >> 2))
#define COP_ADDR_MUL_DIN0_2          (COPE_SET_BASEADDR + (0x0178 >> 2))
#define COP_ADDR_MUL_DIN0_3          (COPE_SET_BASEADDR + (0x017c >> 2))
#define COP_ADDR_MUL_DIN1_0          (COPE_SET_BASEADDR + (0x0180 >> 2))
#define COP_ADDR_MUL_DIN1_1          (COPE_SET_BASEADDR + (0x0184 >> 2))
#define COP_ADDR_MUL_DIN1_2          (COPE_SET_BASEADDR + (0x0188 >> 2))
#define COP_ADDR_MUL_DIN1_3          (COPE_SET_BASEADDR + (0x018c >> 2))
#define COP_ADDR_MUL_DOUT_0          (COPE_SET_BASEADDR + (0x0190 >> 2))
#define COP_ADDR_MUL_DOUT_1          (COPE_SET_BASEADDR + (0x0194 >> 2))
#define COP_ADDR_MUL_DOUT_2          (COPE_SET_BASEADDR + (0x0198 >> 2))
#define COP_ADDR_MUL_DOUT_3          (COPE_SET_BASEADDR + (0x019c >> 2))
#define COP_ADDR_MUL_CMD             (COPE_SET_BASEADDR + (0x01a0 >> 2))

/*
 * TRNG base address
 */
#define COP_ADDR_TRNG_CTRL           (COPE_SET_BASEADDR + (0x0200 >> 2))
#define COP_ADDR_TRNG_KICK           (COPE_SET_BASEADDR + (0x0204 >> 2))
#define COP_ADDR_SAMPLE_SEED         (COPE_SET_BASEADDR + (0x0208 >> 2))
#define COP_ADDR_SEED_STATUS         (COPE_SET_BASEADDR + (0x020C >> 2))
#define COP_ADDR_LFSR_CTRL           (COPE_SET_BASEADDR + (0x0210 >> 2))
#define COP_ADDR_LFSR_EN             (COPE_SET_BASEADDR + (0x0214 >> 2))
#define COP_ADDR_LFSR_NEXT           (COPE_SET_BASEADDR + (0x0218 >> 2))
#define COP_ADDR_RANDOM_VALUE        (COPE_SET_BASEADDR + (0x021C >> 2))


/*
 * Debug base address
 */
#define COP_ADDR_COPIF_TIMEOUT_VALUE (COPE_SET_BASEADDR + (0x0280 >> 2))
#define COP_ADDR_COPIF_BASE_ADDR     (COPE_SET_BASEADDR + (0x0284 >> 2))
#define COP_ADDR_COPIF_ERR_STATUS    (COPE_SET_BASEADDR + (0x0288 >> 2))
#define COP_ADDR_COPIF_TRAP_EN       (COPE_SET_BASEADDR + (0x028C >> 2))
#define COP_ADDR_CUR_COP_INST        (COPE_SET_BASEADDR + (0x01E0 >> 2))
#define COP_ADDR_LAST_COP_INST       (COPE_SET_BASEADDR + (0x01E4 >> 2))
#define COP_ADDR_SETKEY_CNT          (COPE_SET_BASEADDR + (0x01E8 >> 2))


/*
 * ECCP base address
 */
#define COP_ADDR_ECCP_CTRL           (COPE_SET_BASEADDR + (0x0300 >> 2))
#define COP_ADDR_ECCP_MEM_OP         (COPE_SET_BASEADDR + (0x0304 >> 2))
#define COP_ADDR_ECCP_WDATA          (COPE_SET_BASEADDR + (0x0308 >> 2))
#define COP_ADDR_ECCP_RDATA          (COPE_SET_BASEADDR + (0x030C >> 2))
#define COP_ADDR_ECCP_FSM            (COPE_SET_BASEADDR + (0x0310 >> 2))
#define COP_ADDR_ECC_ROUND           (COPE_SET_BASEADDR + (0x0314 >> 2))
#define COP_ADDR_ECCP_PN_0           (COPE_SET_BASEADDR + (0x0320 >> 2))
#define COP_ADDR_ECCP_PN_1           (COPE_SET_BASEADDR + (0x0324 >> 2))
#define COP_ADDR_ECCP_PN_2           (COPE_SET_BASEADDR + (0x0328 >> 2))
#define COP_ADDR_ECCP_PN_3           (COPE_SET_BASEADDR + (0x032c >> 2))
#define COP_ADDR_ECCP_PN_4           (COPE_SET_BASEADDR + (0x0330 >> 2))
#define COP_ADDR_ECCP_PN_5           (COPE_SET_BASEADDR + (0x0334 >> 2))
#define COP_ADDR_ECCP_PN_6           (COPE_SET_BASEADDR + (0x0338 >> 2))
#define COP_ADDR_ECCP_PN_7           (COPE_SET_BASEADDR + (0x033c >> 2))
#define COP_ADDR_ECCP_INT            (COPE_SET_BASEADDR + (0x0340 >> 2))

#endif /* INCLUDE_CRYPTO_CRYPTO_REGISTER_BANKS_H_ */
