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

#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#include "SSV_cJSON.h"

#define PRINT_CJSON_TAG LOG_TAG_CJSON

/* project version */
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 5
#define CJSON_VERSION_PATCH 8

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7) /* raw json */

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512


#define cJSON SSV_cJSON
#define cJSON_Hooks SSV_cJSON_Hooks
#define cJSON_bool SSV_cJSON_bool

#define cJSON_Version SSV_cJSON_Version

#define cJSON_InitHooks(hooks) SSV_cJSON_InitHooks(hooks)

#define cJSON_Parse(value) SSV_cJSON_Parse(value)

#define cJSON_ParseWithOpts(value, return_parse_end, require_null_terminated) SSV_cJSON_ParseWithOpts(value, return_parse_end, require_null_terminated)

#define cJSON_Print(item) SSV_cJSON_Print(item)

#define cJSON_PrintUnformatted(item) SSV_cJSON_PrintUnformatted(item)

#define cJSON_PrintBuffered(item, prebuffer, fmt) SSV_cJSON_PrintBuffered(item, prebuffer, fmt)

#define cJSON_PrintPreallocated(item, buffer, length, format) SSV_cJSON_PrintPreallocated(item, buffer, length, format)

#define cJSON_Delete(c) SSV_cJSON_Delete(c)

#define cJSON_GetArraySize(array) SSV_cJSON_GetArraySize(array)

#define cJSON_GetArrayItem(array, index) SSV_cJSON_GetArrayItem(array, index)

#define cJSON_GetObjectItem(object, string) SSV_cJSON_GetObjectItem(object, string)

#define cJSON_GetObjectItemCaseSensitive(object, string) SSV_cJSON_GetObjectItemCaseSensitive(object, string)

#define cJSON_HasObjectItem(object, string) SSV_cJSON_HasObjectItem(object, string)

#define cJSON_GetErrorPtr SSV_cJSON_GetErrorPtr

#define cJSON_IsInvalid(item) SSV_cJSON_IsInvalid(item)

#define cJSON_IsFalse(item) SSV_cJSON_IsFalse(item)

#define cJSON_IsTrue(item) SSV_cJSON_IsTrue(item)

#define cJSON_IsBool SSV_cJSON_IsBool

#define cJSON_IsNull(item) SSV_cJSON_IsNull(item)

#define cJSON_IsNumber(item) SSV_cJSON_IsNumber(item)

#define cJSON_IsString(item) SSV_cJSON_IsString(item)

#define cJSON_IsArray(item) SSV_cJSON_IsArray(item)

#define cJSON_IsObject(item) SSV_cJSON_IsObject(item)

#define cJSON_IsRaw(item) SSV_cJSON_IsRaw(item)

#define cJSON_CreateNull SSV_cJSON_CreateNull

#define cJSON_CreateTrue SSV_cJSON_CreateTrue

#define cJSON_CreateFalse SSV_cJSON_CreateFalse

#define cJSON_CreateBool(boolean) SSV_cJSON_CreateBool(boolean)

#define cJSON_CreateNumber(num) SSV_cJSON_CreateNumber(num)

#define cJSON_CreateString(string) SSV_cJSON_CreateString(string)

#define cJSON_CreateRaw(raw) SSV_cJSON_CreateRaw(raw)

#define cJSON_CreateArray SSV_cJSON_CreateArray

#define cJSON_CreateObject SSV_cJSON_CreateObject

#define cJSON_CreateIntArray(numbers, count) SSV_cJSON_CreateIntArray(numbers, count)

#define cJSON_CreateFloatArray(numbers, count) SSV_cJSON_CreateFloatArray(numbers, count)

#define cJSON_CreateDoubleArray(numbers, count) SSV_cJSON_CreateDoubleArray(numbers, count)

#define cJSON_CreateStringArray(strings, count) SSV_cJSON_CreateStringArray(strings, count)

#define cJSON_AddItemToArray(array, item) SSV_cJSON_AddItemToArray(array, item)

#define cJSON_AddItemToObject(object, string, item) SSV_cJSON_AddItemToObject(object, string, item)

#define cJSON_AddItemToObjectCS(object, string, item) SSV_cJSON_AddItemToObjectCS(object, string, item)

#define cJSON_AddItemReferenceToArray(object, item) SSV_cJSON_AddItemReferenceToArray(object, item)

#define cJSON_AddItemReferenceToObject(object, string, item) SSV_cJSON_AddItemReferenceToObject(object, string, item)

#define cJSON_DetachItemViaPointer(parent, item) SSV_cJSON_DetachItemViaPointer(parent, item)

#define cJSON_DetachItemFromArray(array, which) SSV_cJSON_DetachItemFromArray(array, which)

#define cJSON_DeleteItemFromArray(array, which) SSV_cJSON_DeleteItemFromArray(array, which)

#define cJSON_DetachItemFromObject(object, which) SSV_cJSON_DetachItemFromObject(object, which)

#define cJSON_DetachItemFromObjectCaseSensitive(object, string) SSV_cJSON_DetachItemFromObjectCaseSensitive(object, string)

#define cJSON_DeleteItemFromObject(object, string) SSV_cJSON_DeleteItemFromObject(object, string)

#define cJSON_DeleteItemFromObjectCaseSensitive(object, string) SSV_cJSON_DeleteItemFromObjectCaseSensitive(object, string)

#define cJSON_InsertItemInArray(array, which, newitem) SSV_cJSON_InsertItemInArray(array, which, newitem)

#define cJSON_ReplaceItemViaPointer(parent, item, replacement) SSV_cJSON_ReplaceItemViaPointer(parent, item, replacement)

#define cJSON_ReplaceItemInArray(array, which, newitem) SSV_cJSON_ReplaceItemInArray(array, which, newitem)

#define cJSON_ReplaceItemInObject(object, string, newitem) SSV_cJSON_ReplaceItemInObject(object, string, newitem)

#define cJSON_ReplaceItemInObjectCaseSensitive(object, string, newitem) SSV_cJSON_ReplaceItemInObjectCaseSensitive(object, string, newitem)

#define cJSON_Duplicate(item, recurse) SSV_cJSON_Duplicate(item, recurse)

#define cJSON_Compare(a, b, case_sensitive) SSV_cJSON_Compare(a, b, case_sensitive)

#define cJSON_Minify(json) SSV_cJSON_Minify(json)

/* Macros for creating things quickly. */
#define cJSON_AddNullToObject(object,name) cJSON_AddItemToObject(object, name, cJSON_CreateNull())
#define cJSON_AddTrueToObject(object,name) cJSON_AddItemToObject(object, name, cJSON_CreateTrue())
#define cJSON_AddFalseToObject(object,name) cJSON_AddItemToObject(object, name, cJSON_CreateFalse())
#define cJSON_AddBoolToObject(object,name,b) cJSON_AddItemToObject(object, name, cJSON_CreateBool(b))
#define cJSON_AddNumberToObject(object,name,n) cJSON_AddItemToObject(object, name, cJSON_CreateNumber(n))
#define cJSON_AddStringToObject(object,name,s) cJSON_AddItemToObject(object, name, cJSON_CreateString(s))
#define cJSON_AddRawToObject(object,name,s) cJSON_AddItemToObject(object, name, cJSON_CreateRaw(s))

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))

#define cJSON_SetNumberHelper(object, number) SSV_cJSON_SetNumberHelper(object, number)

#define cJSON_SetNumberValue(object, number) ((object != NULL) ? cJSON_SetNumberHelper(object, (double)number) : (number))

/* Macro for iterating over an array or object */
#define cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

#define cJSON_malloc(size) SSV_cJSON_malloc(size)
#define cJSON_free(object) SSV_cJSON_free(object)

#ifdef __cplusplus
}
#endif

#endif
