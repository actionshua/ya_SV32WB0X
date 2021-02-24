#include <stdint.h>
#include "sa_cfg.h"
#include <string.h>
#include <stdio.h>

#define CFG_ASSERT(cmp) \
    do { \
    } while(!(cmp))

extern const struct sa_cfg g_sa_cfg __attribute__((section(".sa_mp_data")));
const struct sa_cfg g_sa_cfg __attribute__((section(".sa_mp_data"))) = {
    .buf_mp = {
        /* rt_config */
        8, 8, 8, 8, 8, 8, 8, 149, 149, 7, 9, 10, 7, 7, 7, 7, 7, 1,
        /* ht_config */
        12, 12, 12, 12, 12, 12, 12, 180, 180, 7, 9, 10, 7, 7, 7, 7, 7, 1,
        /* lt_config */
        7, 7, 7, 7, 7, 7, 7, 145, 145, 7, 9, 10, 7, 7, 7, 7, 7, 1,
        /* rf_gain */
        4,
        /* rate_gain_b */
        5,
        /* rate_config_g */
        15, 13, 11, 9,
        /* rate_config_20n */
        15, 13, 11, 9,
        /* rate_config_40n */
        15, 13, 11, 9,
        /* low_boundarty */
        15,
        /* high_boundary */
        90,
        /* boot flag*/
        0x00,
        /* work mode */
        0xFF,
        /* rt_5g_config */
        13, 10, 10, 9, 0x4A, 0x92, 0x64, 0x92, 0xCC, 0xB6, 0xDB, 0x96,
        /* ht_5g_config */
        13, 10, 10, 9, 0x4A, 0x92, 0x64, 0x92, 0xCC, 0xB6, 0xDB, 0x96,
        /* lt_5g_config */
        13, 10, 10, 9, 0x4A, 0x92, 0x64, 0x92, 0xCC, 0xB6, 0xDB, 0x96,
        /* band_f0_threshold */
        0x1E,0x14,
        /* band_f1_threshold */
        0x7C,0x15,
        /* band_f2_threshold */
        0x44,0x16,
        /* Signature */
        0x53,0x53,0x56,0x00,
        /* Structure version */
        0x03,0x00,0x00,0x00,
        /* DCDC flag */
        0x01,0x00,0x00,0x00,
        /* external pa settings*/
        0, 0, 1, 8, 0xc, 0xd, 8, 0,
        /* RTC 32K XTAL setting */
        0x00,
        /* Tx lowpower setting */
        0x01,
        /* Ble normal config*/
        14, 14,
        /* Ble high config*/
        14, 14,
        /* Ble low config*/
        14, 14,
}
};

