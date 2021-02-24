#ifndef ECCP_MICRO_
#define ECCP_MICRO_

#define ECCP_FUNC_COMMIT                       0x0
#define ECCP_FUNC_PEER                         0x6
#define ECCP_FUNC_XPOW                         0x22
#define ECCP_FUNC_XPOW_INIT                    0x28
#define ECCP_FUNC_XPOW_FP1                     0x2c
#define ECCP_FUNC_XPOW_FP2                     0x2e
#define ECCP_FUNC_ATOPNTOM                     0x30
#define ECCP_FUNC_ECPINIT                      0x35
#define ECCP_FUNC_ECPADD                       0x3a
#define ECCP_FUNC_ECPDOUBLE                    0x59
#define ECCP_FUNC_ECCDOT                       0x74
#define ECCP_FUNC_PTOAMTON                     0x79
#define ECCP_FUNC_MMI                          0x81
#define ECCP_FUNC_MMI_INIT                     0x88
#define ECCP_FUNC_MMI_ADD                      0x8a
#define ECCP_FUNC_MMI_DOUBLE                   0x8c

#define ECCP_const_1_ADDR                    0x200
#define ECCP_p_ADDR                          0x208
#define ECCP_a_ADDR                          0x210
#define ECCP_r2modp_ADDR                     0x218
#define ECCP_rmodp_ADDR                      0x220
#define ECCP_rand_ADDR                       0x228
#define ECCP_pwe_x_ADDR                      0x230
#define ECCP_pwe_y_ADDR                      0x238
#define ECCP_mask_ADDR                       0x240
#define ECCP_peer_x_ADDR                     0x248
#define ECCP_peer_y_ADDR                     0x250
#define ECCP_result_x_ADDR                   0x298
#define ECCP_result_y_ADDR                   0x2A0

const u32 ecc_code[] = { 
0x38c00000,
0x39d00000,
0x39e40000,
0x19613000,
0x19814000,
0x40000000,
0x38c00000,
0x39d00000,
0x39e40000,
0x19613000,
0x19814000,
0x19606000,
0x19807000,
0x38c00000,
0x1960f000,
0x19810000,
0x19a11000,
0x19c12000,
0x19206000,
0x19407000,
0x38c00000,
0x38e80000,
0x39e40000,
0x19613000,
0x19814000,
0x19606000,
0x19807000,
0x18a08000,
0x38c00000,
0x39d00000,
0x39e40000,
0x19613000,
0x19814000,
0x40000000,
0x30000028,
0x3004002c,
0x3008002e,
0x7ae00042,
0x4aa000a8,
0x40000000,
0x18815000,
0x4ac030b0,
0x4aa160a8,
0x40000000,
0x4aa160a8,
0x40000000,
0x4ac160b0,
0x40000000,
0x48c03058,
0x48e03060,
0x48003068,
0x48403070,
0x40000000,
0x1960f000,
0x19810000,
0x19a11000,
0x19c12000,
0x40000000,
0x4a2110a8,
0x49a0d0c8,
0x496150b0,
0x49e190c0,
0x4aa110a8,
0xe30160b8,
0x498150a8,
0x4b20d0c8,
0x4ae170c0,
0x4a0190c8,
0x4ac180b0,
0xe32150c8,
0x4b0170c0,
0x62c160d0,
0x49a110e8,
0x6301a0d0,
0x4ba170e8,
0x4b2190b8,
0x4aa180a8,
0xe2e1a0d8,
0x4ba1d0f0,
0xe2c1b0b0,
0x4b2160b8,
0x4bc1e0f0,
0xe2e150e0,
0x4841e0f0,
0x1b60f000,
0x1b810000,
0x1ba11000,
0x1bc12000,
0x40000000,
0x4980c0a8,
0x6160b0b0,
0x4aa150b8,
0x62c160b0,
0x4ac150a8,
0x62e170b8,
0x4960b0b0,
0x62e170b8,
0x4980d0c0,
0x62e170b8,
0x4ae0e0c8,
0x62c160d0,
0x634160b0,
0x62c0e0b0,
0x4ac160d0,
0x630180e8,
0x62a150c0,
0xe34180d8,
0xe2a1b0a8,
0x4ac150b0,
0x632190f0,
0xe2c170e0,
0x1b60b000,
0x1b80c000,
0x1ba0d000,
0x1bc0e000,
0x40000000,
0x30000035,
0x3004003a,
0x30080059,
0x79000042,
0x40000000,
0x3a040000,
0x49c0e090,
0x49e12058,
0x49c120f0,
0x4a01e060,
0x49600058,
0x49800060,
0x40000000,
0xa8200040,
0xa9000040,
0x30000088,
0x3004008a,
0x3008008c,
0x79000042,
0x40000000,
0x48811070,
0x40000000,
0x49c11070,
0x40000000,
0x4a211088,
0x40000000,
};

#endif
