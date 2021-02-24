
/*
 * 
 * Author: Tim Li
 *
 */

#ifndef __FOTA_HTTP_H__
#define __FOTA_HTTP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "fota_common.h"
#include "httpclient.h"
#include "fota_md5.h"

//http status code
#define RESPONSE_CODES 103
#define HTTP_CONTINUE                        100
#define HTTP_SWITCHING_PROTOCOLS             101
#define HTTP_PROCESSING                      102
#define HTTP_OK                              200
#define HTTP_CREATED                         201
#define HTTP_ACCEPTED                        202
#define HTTP_NON_AUTHORITATIVE               203
#define HTTP_NO_CONTENT                      204
#define HTTP_RESET_CONTENT                   205
#define HTTP_PARTIAL_CONTENT                 206
#define HTTP_MULTI_STATUS                    207
#define HTTP_ALREADY_REPORTED                208
#define HTTP_IM_USED                         226
#define HTTP_MULTIPLE_CHOICES                300
#define HTTP_MOVED_PERMANENTLY               301
#define HTTP_MOVED_TEMPORARILY               302
#define HTTP_SEE_OTHER                       303
#define HTTP_NOT_MODIFIED                    304
#define HTTP_USE_PROXY                       305
#define HTTP_TEMPORARY_REDIRECT              307
#define HTTP_PERMANENT_REDIRECT              308
#define HTTP_BAD_REQUEST                     400
#define HTTP_UNAUTHORIZED                    401
#define HTTP_PAYMENT_REQUIRED                402
#define HTTP_FORBIDDEN                       403
#define HTTP_NOT_FOUND                       404
#define HTTP_METHOD_NOT_ALLOWED              405
#define HTTP_NOT_ACCEPTABLE                  406
#define HTTP_PROXY_AUTHENTICATION_REQUIRED   407
#define HTTP_REQUEST_TIME_OUT                408
#define HTTP_CONFLICT                        409
#define HTTP_GONE                            410
#define HTTP_LENGTH_REQUIRED                 411
#define HTTP_PRECONDITION_FAILED             412
#define HTTP_REQUEST_ENTITY_TOO_LARGE        413
#define HTTP_REQUEST_URI_TOO_LARGE           414
#define HTTP_UNSUPPORTED_MEDIA_TYPE          415
#define HTTP_RANGE_NOT_SATISFIABLE           416
#define HTTP_EXPECTATION_FAILED              417
#define HTTP_IM_A_TEAPOT                     418
#define HTTP_MISDIRECTED_REQUEST             421
#define HTTP_UNPROCESSABLE_ENTITY            422
#define HTTP_LOCKED                          423
#define HTTP_FAILED_DEPENDENCY               424
#define HTTP_TOO_EARLY                       425
#define HTTP_UPGRADE_REQUIRED                426
#define HTTP_PRECONDITION_REQUIRED           428
#define HTTP_TOO_MANY_REQUESTS               429
#define HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE 431
#define HTTP_UNAVAILABLE_FOR_LEGAL_REASONS   451
#define HTTP_INTERNAL_SERVER_ERROR           500
#define HTTP_NOT_IMPLEMENTED                 501
#define HTTP_BAD_GATEWAY                     502
#define HTTP_SERVICE_UNAVAILABLE             503
#define HTTP_GATEWAY_TIME_OUT                504
#define HTTP_VERSION_NOT_SUPPORTED           505
#define HTTP_VARIANT_ALSO_VARIES             506
#define HTTP_INSUFFICIENT_STORAGE            507
#define HTTP_LOOP_DETECTED                   508
#define HTTP_NOT_EXTENDED                    510
#define HTTP_NETWORK_AUTHENTICATION_REQUIRED 511

#ifdef __cplusplus
}
#endif

#endif  /* __FOTA_HTTP_H__ */