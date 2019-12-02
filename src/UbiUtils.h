
#ifndef _UBI_UTILS_
#define _UBI_UTILS_

#include "UbiConstants.h"
#include "stddef.h"
#include "stdio.h"

/*
* Stores the float type value into the char array input
* @str_value [Mandatory] char payload pointer to store the value.
* @value [Mandatory] Float value to convert
*/
void _floatToChar(char *str_value, float value);

/**
* Builds the HTTP payload to send and saves it to the input char pointer.
* @payload [Mandatory] char payload pointer to store the built structure.
* @timestamp_global [Optional] If set, it will be used for any dot without
* timestamp.
*/
void buildHttpPayload(char *payload, Value *_dots, int8_t *_current_value);

/**
 * Builds the TCP payload to send and saves it to the input char pointer.
 * @payload [Mandatory] char payload pointer to store the built structure.
 * @timestamp_global [Optional] If set, it will be used for any dot without
 * timestamp.
 */

void buildTcpPayload(char *payload, const char *device_label,
                     const char *device_name, Value *_dots,
                     int8_t *_current_value, UbiToken _token);

#endif