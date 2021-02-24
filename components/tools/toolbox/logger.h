#ifndef __LOGGER_H__
#define __LOGGER_H__


#define LOG_FILTER_LEVEL LOG_DEBUG
#define LOG_DEFAULG_TAG_LEVEL LOG_INFO
#define CONFIG_LOG_COLORS 0
#define CONFIG_LOG_TIMESTAMP 0

// Tag definitions
typedef enum 
{
    LOG_TAG_NONE        = 0,
    /* [S] for wifi system [S] */
    LOG_TAG_OS          = 1,
    LOG_TAG_PHY         = 2,                    // for PHY and RF
    LOG_TAG_LP          = 3,                     // for low power
    LOG_TAG_HWMAC       = 4,                     // for low power
    /* [E] for wifi system [E] */
    LOG_TAG_WIFI        = 5,

    /* [S] for driver [S] */
    LOG_TAG_DRV_I2S     = 10,
    LOG_TAG_DRV_SPIMST  = 11,
    LOG_TAG_DRV_I2CMST  = 12,
    LOG_TAG_DRV_SPISLV  = 13,

    /* [E] for driver [E] */

    /* [S] for middle ware [S] */
    LOG_TAG_CMD         = 15,
    LOG_TAG_ATCMD       = 16,
    LOG_TAG_JOYLINK     = 17,
    LOG_TAG_AIRKISS     = 18,
    LOG_TAG_RTLINK      = 19,
    LOG_TAG_CJSON       = 20,
    LOG_TAG_HTTPC       = 21,
    LOG_TAG_IPERF2      = 22,
    LOG_TAG_IPERF3      = 23,
    LOG_TAG_PING        = 24,
    LOG_TAG_TFTP        = 25,
    LOG_TAG_MBEDTLS     = 26,
    LOG_TAG_FOTA        = 27,
    LOG_TAG_MQTT        = 28,
    LOG_TAG_ADK         = 29,
    LOG_TAG_AP          = 30,
    LOG_TAG_FS          = 31,
    /* [E] for middle ware [E] */

    LOG_TAG_MAX = 32,
} log_tag_t;

typedef enum 
{
	LOG_CRIT = 1,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_VERBOSE,
} log_level_t;

#define LOG_ERR LOG_ERROR
#define LOG_DBG LOG_DEBUG

uint32_t log_timestamp(void);      

#if 1
int log_print(log_level_t level, log_tag_t tag, const char* format, ...);
int get_tag_level(log_tag_t tag, log_level_t* level);
int set_tag_level(log_tag_t tag, log_level_t level);
int show_tag_level_list();
int clean_tag_level_list();
#else
int log_print(log_level_t level, const char* tag, const char* format, ...);
int get_tag_level(const char* tag, log_level_t* level);
int set_tag_level(const char* tag, log_level_t level);
int show_tag_level_list();
int clean_tag_level_list();
#endif


#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D       LOG_COLOR(LOG_COLOR_BLUE)
#define LOG_COLOR_V
#else 
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif //CONFIG_LOG_COLORS


#if CONFIG_LOG_TIMESTAMP
#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter "[%08d] " format LOG_RESET_COLOR 
#else
#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter "" format LOG_RESET_COLOR 
#endif

#if (LOG_FILTER_LEVEL >= LOG_ERROR)
#if CONFIG_LOG_TIMESTAMP
#define  log_e(tag, format, ...)  log_print(LOG_ERROR, tag, LOG_FORMAT(W, format), log_timestamp(), ##__VA_ARGS__)
#else
#define log_e(tag, format, ...)  log_print(LOG_ERROR, tag, LOG_FORMAT(E, format), ##__VA_ARGS__)
#endif
#else
#define log_e(tag, format, ...) 
#endif

#if (LOG_FILTER_LEVEL >= LOG_WARN)
#if CONFIG_LOG_TIMESTAMP
#define  log_w(tag, format, ...)  log_print(LOG_WARN, tag, LOG_FORMAT(W, format), log_timestamp(), ##__VA_ARGS__)
#else
#define  log_w(tag, format, ...)   log_print(LOG_WARN, tag, LOG_FORMAT(W, format), ##__VA_ARGS__)
#endif
#else
#define log_w(tag, format, ...) 
#endif

#if (LOG_FILTER_LEVEL >= LOG_INFO)
#if CONFIG_LOG_TIMESTAMP
#define log_i(tag, format, ...)   log_print(LOG_INFO, tag, LOG_FORMAT(I, format), log_timestamp(), ##__VA_ARGS__)
#else
#define log_i(tag, format, ...)   log_print(LOG_INFO, tag, LOG_FORMAT(I, format), ##__VA_ARGS__)
#endif
#else
#define log_i(tag, format, ...) 
#endif

#if (LOG_FILTER_LEVEL >= LOG_DEBUG)
#if CONFIG_LOG_TIMESTAMP
#define log_d(tag, format, ...)   log_print(LOG_DEBUG, tag, LOG_FORMAT(D, format), log_timestamp(), ##__VA_ARGS__)
#else
#define log_d(tag, format, ...)   log_print(LOG_DEBUG, tag, LOG_FORMAT(D, format), ##__VA_ARGS__)
#endif
#else
#define log_d(tag, format, ...) 
#endif

#if (LOG_FILTER_LEVEL >= LOG_VERBOSE)
#if CONFIG_LOG_TIMESTAMP
#define log_v(tag, format, ...)   log_print(LOG_VERBOSE, tag, LOG_FORMAT(V, format), log_timestamp(), ##__VA_ARGS__)
#else
#define log_v(tag, format, ...)  log_print(LOG_VERBOSE, tag, LOG_FORMAT(V, format), ##__VA_ARGS__)
#endif
#else
#define log_v(tag, format, ...) 
#endif

#endif // __LOGGER_H__
