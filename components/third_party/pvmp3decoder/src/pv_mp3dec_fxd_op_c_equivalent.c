
#include "pv_mp3dec_fxd_op_c_equivalent.h"

inline int32 pv_abs(int32 a)
{
    int32 b = (a < 0) ? -a : a;
    return b;
}

inline Int32 fxp_mul32_Q30(const Int32 a, const Int32 b)
{
    return (Int32)(((int64)(a) * b) >> 30);
}

inline Int32 fxp_mac32_Q30(const Int32 a, const Int32 b, Int32 L_add)
{
    return (L_add + (Int32)(((int64)(a) * b) >> 30));
}

inline Int32 fxp_mul32_Q32(const Int32 a, const Int32 b)
{
    return (Int32)(((int64)(a) * b) >> 32);
}

inline Int32 fxp_mul32_Q28(const Int32 a, const Int32 b)
{
    return (Int32)(((int64)(a) * b) >> 28);
}

inline Int32 fxp_mul32_Q27(const Int32 a, const Int32 b)
{
    return (Int32)(((int64)(a) * b) >> 27);
}

inline Int32 fxp_mul32_Q26(const Int32 a, const Int32 b)
{
    return (Int32)(((int64)(a) * b) >> 26);
}

inline Int32 fxp_mac32_Q32(Int32 L_add, const Int32 a, const Int32 b)
{
    return (L_add + (Int32)(((int64)(a) * b) >> 32));
}

inline Int32 fxp_msb32_Q32(Int32 L_sub, const Int32 a, const Int32 b)
{
    return (L_sub - ((Int32)(((int64)(a) * b) >> 32)));
}

inline Int32 fxp_mul32_Q29(const Int32 a, const Int32 b)
{
    return (Int32)(((int64)(a) * b) >> 29);
}
