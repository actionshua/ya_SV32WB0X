/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef SSV_cJSON__h
#define SSV_cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

/* project version */
#define SSV_cJSON_VERSION_MAJOR 1
#define SSV_cJSON_VERSION_MINOR 5
#define SSV_cJSON_VERSION_PATCH 8

#include <stddef.h>
#include "osal.h"

/* SSV_cJSON Types: */
#define SSV_cJSON_Invalid (0)
#define SSV_cJSON_False  (1 << 0)
#define SSV_cJSON_True   (1 << 1)
#define SSV_cJSON_NULL   (1 << 2)
#define SSV_cJSON_Number (1 << 3)
#define SSV_cJSON_String (1 << 4)
#define SSV_cJSON_Array  (1 << 5)
#define SSV_cJSON_Object (1 << 6)
#define SSV_cJSON_Raw    (1 << 7) /* raw json */

#define SSV_cJSON_IsReference 256
#define SSV_cJSON_StringIsConst 512

/* The SSV_cJSON structure: */
typedef struct SSV_cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct SSV_cJSON *next;
    struct SSV_cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
    struct SSV_cJSON *child;

    /* The type of the item, as above. */
    int type;

    /* The item's string, if type==SSV_cJSON_String  and type == SSV_cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use SSV_cJSON_SetNumberValue instead */
    int valueint;
    /* The item's number, if type==SSV_cJSON_Number */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    char *string;
} SSV_cJSON;

typedef struct SSV_cJSON_Hooks
{
      void *(*malloc_fn)(size_t sz);
      void (*free_fn)(void *ptr);
} SSV_cJSON_Hooks;

typedef int SSV_cJSON_bool;

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif
#ifdef __WINDOWS__

/* When compiling for windows, we specify a specific calling convention to avoid issues where we are being called from a project with a different default calling convention.  For windows you have 2 define options:

SSV_cJSON_HIDE_SYMBOLS - Define this in the case where you don't want to ever dllexport symbols
SSV_cJSON_EXPORT_SYMBOLS - Define this on library build when you want to dllexport symbols (default)
SSV_cJSON_IMPORT_SYMBOLS - Define this if you want to dllimport symbol

For *nix builds that support visibility attribute, you can define similar behavior by

setting default visibility to hidden by adding
-fvisibility=hidden (for gcc)
or
-xldscope=hidden (for sun cc)
to CFLAGS

then using the SSV_cJSON_API_VISIBILITY flag to "export" the same symbols the way SSV_cJSON_EXPORT_SYMBOLS does

*/

/* export symbols by default, this is necessary for copy pasting the C and header file */
#if !defined(SSV_cJSON_HIDE_SYMBOLS) && !defined(SSV_cJSON_IMPORT_SYMBOLS) && !defined(SSV_cJSON_EXPORT_SYMBOLS)
#define SSV_cJSON_EXPORT_SYMBOLS
#endif

#if defined(SSV_cJSON_HIDE_SYMBOLS)
#define SSV_cJSON_PUBLIC(type)   type __stdcall
#elif defined(SSV_cJSON_EXPORT_SYMBOLS)
#define SSV_cJSON_PUBLIC(type)   __declspec(dllexport) type __stdcall
#elif defined(SSV_cJSON_IMPORT_SYMBOLS)
#define SSV_cJSON_PUBLIC(type)   __declspec(dllimport) type __stdcall
#endif
#else /* !WIN32 */
#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(SSV_cJSON_API_VISIBILITY)
#define SSV_cJSON_PUBLIC(type)   __attribute__((visibility("default"))) type
#else
#define SSV_cJSON_PUBLIC(type) type
#endif
#endif

/* Limits how deeply nested arrays/objects can be before SSV_cJSON rejects to parse them.
 * This is to prevent stack overflows. */
#ifndef SSV_cJSON_NESTING_LIMIT
#define SSV_cJSON_NESTING_LIMIT 1000
#endif

/* returns the version of SSV_cJSON as a string */
SSV_cJSON_PUBLIC(const char*) SSV_cJSON_Version(void);

/* Supply malloc, realloc and free functions to SSV_cJSON */
SSV_cJSON_PUBLIC(void) SSV_cJSON_InitHooks(SSV_cJSON_Hooks* hooks);

/* Memory Management: the caller is always responsible to free the results from all variants of SSV_cJSON_Parse (with SSV_cJSON_Delete) and SSV_cJSON_Print (with stdlib free, SSV_cJSON_Hooks.free_fn, or SSV_cJSON_free as appropriate). The exception is SSV_cJSON_PrintPreallocated, where the caller has full responsibility of the buffer. */
/* Supply a block of JSON, and this returns a SSV_cJSON object you can interrogate. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_Parse(const char *value);
/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
/* If you supply a ptr in return_parse_end and parsing fails, then return_parse_end will contain a pointer to the error. If not, then SSV_cJSON_GetErrorPtr() does the job. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_ParseWithOpts(const char *value, const char **return_parse_end, SSV_cJSON_bool require_null_terminated);

/* Render a SSV_cJSON entity to text for transfer/storage. */
SSV_cJSON_PUBLIC(char *) SSV_cJSON_Print(const SSV_cJSON *item);
/* Render a SSV_cJSON entity to text for transfer/storage without any formatting. */
SSV_cJSON_PUBLIC(char *) SSV_cJSON_PrintUnformatted(const SSV_cJSON *item);
/* Render a SSV_cJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
SSV_cJSON_PUBLIC(char *) SSV_cJSON_PrintBuffered(const SSV_cJSON *item, int prebuffer, SSV_cJSON_bool fmt);
/* Render a SSV_cJSON entity to text using a buffer already allocated in memory with given length. Returns 1 on success and 0 on failure. */
/* NOTE: SSV_cJSON is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need */
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_PrintPreallocated(SSV_cJSON *item, char *buffer, const int length, const SSV_cJSON_bool format);
/* Delete a SSV_cJSON entity and all subentities. */
SSV_cJSON_PUBLIC(void) SSV_cJSON_Delete(SSV_cJSON *c);

/* Returns the number of items in an array (or object). */
SSV_cJSON_PUBLIC(int) SSV_cJSON_GetArraySize(const SSV_cJSON *array);
/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_GetArrayItem(const SSV_cJSON *array, int index);
/* Get item "string" from object. Case insensitive. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_GetObjectItem(const SSV_cJSON * const object, const char * const string);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_GetObjectItemCaseSensitive(const SSV_cJSON * const object, const char * const string);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_HasObjectItem(const SSV_cJSON *object, const char *string);
/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when SSV_cJSON_Parse() returns 0. 0 when SSV_cJSON_Parse() succeeds. */
SSV_cJSON_PUBLIC(const char *) SSV_cJSON_GetErrorPtr(void);

/* These functions check the type of an item */
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsInvalid(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsFalse(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsTrue(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsBool(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsNull(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsNumber(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsString(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsArray(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsObject(const SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_IsRaw(const SSV_cJSON * const item);

/* These calls create a SSV_cJSON item of the appropriate type. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateNull(void);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateTrue(void);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateFalse(void);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateBool(SSV_cJSON_bool boolean);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateNumber(double num);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateString(const char *string);
/* raw json */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateRaw(const char *raw);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateArray(void);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateObject(void);

/* These utilities create an Array of count items. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateIntArray(const int *numbers, int count);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateFloatArray(const float *numbers, int count);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateDoubleArray(const double *numbers, int count);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_CreateStringArray(const char **strings, int count);

/* Append item to the specified array/object. */
SSV_cJSON_PUBLIC(void) SSV_cJSON_AddItemToArray(SSV_cJSON *array, SSV_cJSON *item);
SSV_cJSON_PUBLIC(void) SSV_cJSON_AddItemToObject(SSV_cJSON *object, const char *string, SSV_cJSON *item);
/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the SSV_cJSON object.
 * WARNING: When this function was used, make sure to always check that (item->type & SSV_cJSON_StringIsConst) is zero before
 * writing to `item->string` */
SSV_cJSON_PUBLIC(void) SSV_cJSON_AddItemToObjectCS(SSV_cJSON *object, const char *string, SSV_cJSON *item);
/* Append reference to item to the specified array/object. Use this when you want to add an existing SSV_cJSON to a new SSV_cJSON, but don't want to corrupt your existing SSV_cJSON. */
SSV_cJSON_PUBLIC(void) SSV_cJSON_AddItemReferenceToArray(SSV_cJSON *array, SSV_cJSON *item);
SSV_cJSON_PUBLIC(void) SSV_cJSON_AddItemReferenceToObject(SSV_cJSON *object, const char *string, SSV_cJSON *item);

/* Remove/Detatch items from Arrays/Objects. */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_DetachItemViaPointer(SSV_cJSON *parent, SSV_cJSON * const item);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_DetachItemFromArray(SSV_cJSON *array, int which);
SSV_cJSON_PUBLIC(void) SSV_cJSON_DeleteItemFromArray(SSV_cJSON *array, int which);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_DetachItemFromObject(SSV_cJSON *object, const char *string);
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_DetachItemFromObjectCaseSensitive(SSV_cJSON *object, const char *string);
SSV_cJSON_PUBLIC(void) SSV_cJSON_DeleteItemFromObject(SSV_cJSON *object, const char *string);
SSV_cJSON_PUBLIC(void) SSV_cJSON_DeleteItemFromObjectCaseSensitive(SSV_cJSON *object, const char *string);

/* Update array items. */
SSV_cJSON_PUBLIC(void) SSV_cJSON_InsertItemInArray(SSV_cJSON *array, int which, SSV_cJSON *newitem); /* Shifts pre-existing items to the right. */
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_ReplaceItemViaPointer(SSV_cJSON * const parent, SSV_cJSON * const item, SSV_cJSON * replacement);
SSV_cJSON_PUBLIC(void) SSV_cJSON_ReplaceItemInArray(SSV_cJSON *array, int which, SSV_cJSON *newitem);
SSV_cJSON_PUBLIC(void) SSV_cJSON_ReplaceItemInObject(SSV_cJSON *object,const char *string,SSV_cJSON *newitem);
SSV_cJSON_PUBLIC(void) SSV_cJSON_ReplaceItemInObjectCaseSensitive(SSV_cJSON *object,const char *string,SSV_cJSON *newitem);

/* Duplicate a SSV_cJSON item */
SSV_cJSON_PUBLIC(SSV_cJSON *) SSV_cJSON_Duplicate(const SSV_cJSON *item, SSV_cJSON_bool recurse);
/* Duplicate will create a new, identical SSV_cJSON item to the one you pass, in new memory that will
need to be released. With recurse!=0, it will duplicate any children connected to the item.
The item->next and ->prev pointers are always zero on return from Duplicate. */
/* Recursively compare two SSV_cJSON items for equality. If either a or b is NULL or invalid, they will be considered unequal.
 * case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0) */
SSV_cJSON_PUBLIC(SSV_cJSON_bool) SSV_cJSON_Compare(const SSV_cJSON * const a, const SSV_cJSON * const b, const SSV_cJSON_bool case_sensitive);


SSV_cJSON_PUBLIC(void) SSV_cJSON_Minify(char *json);

/* Macros for creating things quickly. */
#define SSV_cJSON_AddNullToObject(object,name) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateNull())
#define SSV_cJSON_AddTrueToObject(object,name) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateTrue())
#define SSV_cJSON_AddFalseToObject(object,name) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateFalse())
#define SSV_cJSON_AddBoolToObject(object,name,b) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateBool(b))
#define SSV_cJSON_AddNumberToObject(object,name,n) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateNumber(n))
#define SSV_cJSON_AddStringToObject(object,name,s) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateString(s))
#define SSV_cJSON_AddRawToObject(object,name,s) SSV_cJSON_AddItemToObject(object, name, SSV_cJSON_CreateRaw(s))

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define SSV_cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))
/* helper for the SSV_cJSON_SetNumberValue macro */
SSV_cJSON_PUBLIC(double) SSV_cJSON_SetNumberHelper(SSV_cJSON *object, double number);
#define SSV_cJSON_SetNumberValue(object, number) ((object != NULL) ? SSV_cJSON_SetNumberHelper(object, (double)number) : (number))

/* Macro for iterating over an array or object */
#define SSV_cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

/* malloc/free objects using the malloc/free functions that have been set with SSV_cJSON_InitHooks */
SSV_cJSON_PUBLIC(void *) SSV_cJSON_malloc(size_t size);
SSV_cJSON_PUBLIC(void) SSV_cJSON_free(void *object);

#ifdef __cplusplus
}
#endif

#endif
