#ifndef _MAC_COMMON_H_
#define _MAC_COMMON_H_


#define WLAN_MAX_STA                    (9)

#define SOFTAP_CLIENT_MAX WLAN_MAX_STA - 1
#define SOFTAP_CLIENT_DEFAULT 4

typedef enum {
    IF_STA = 0,
    IF_AP,
    IF_NONE,
} IF_MODE;

#endif//_MAC_COMMON_H_
