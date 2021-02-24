#ifndef _SVC_DEF_N7_H_
#define _SVC_DEF_N7_H_


#if defined(__SSV_LINUX_SIM__)

#define DEF_SVC(num, ret_type, func) ret_type func

#elif defined(__GNUC__)

#if !defined(__NO_PRE_SVC__)
#define DEF_SVC(num, ret_type, func) ret_type func __attribute__((optimize("Os")))
#else
#define DEF_SVC(num, ret_type, func)
#endif
#endif



#endif  /// end of _SVC_DEF_N7_H_
