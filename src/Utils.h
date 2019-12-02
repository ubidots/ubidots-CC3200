
#include "UbiTypes.h"

namespace Utils {
/*
* Stores the float type value into the char array input
* @str_value [Mandatory] char payload pointer to store the value.
* @value [Mandatory] Float value to convert
*/
void _floatToChar(char *str_value, float value) {
  char temp_arr[20];
  sprintf(temp_arr, "%17g", value);
  uint8_t j = 0;
  uint8_t k = 0;
  while (j < 20) {
    if (temp_arr[j] != ' ') {
      str_value[k] = temp_arr[j];
      k++;
    }
    if (temp_arr[j] == '\0') {
      str_value[k] = temp_arr[j];
      break;
    }
    j++;
  }
}

/**
* Builds the HTTP payload to send and saves it to the input char pointer.
* @payload [Mandatory] char payload pointer to store the built structure.
* @timestamp_global [Optional] If set, it will be used for any dot without
* timestamp.
*/
void buildHttpPayload(char *payload, Value *_dots, int8_t *_current_value) {
  /* Builds the payload */
  sprintf(payload, "{");

  for (uint8_t i = 0; i < *_current_value;) {
    char str_value[20];
    _floatToChar(str_value, (_dots + i)->dot_value);
    sprintf(payload, "%s\"%s\":{\"value\":%s", payload,
            (_dots + i)->variable_label, str_value);

    // Adds timestamp seconds
    if ((_dots + i)->dot_timestamp_seconds != NULL) {
      sprintf(payload, "%s,\"timestamp\":%lu", payload,
              (_dots + i)->dot_timestamp_seconds);
      // Adds timestamp milliseconds
      if ((_dots + i)->dot_timestamp_millis != NULL) {
        char milliseconds[3];
        int timestamp_millis = (_dots + i)->dot_timestamp_millis;
        uint8_t units = timestamp_millis % 10;
        uint8_t dec = (timestamp_millis / 10) % 10;
        uint8_t hund = (timestamp_millis / 100) % 10;
        sprintf(milliseconds, "%d%d%d", hund, dec, units);
        sprintf(payload, "%s%s", payload, milliseconds);
      } else {
        sprintf(payload, "%s000", payload);
      }
    }

    // Adds dot context
    if ((_dots + i)->dot_context != NULL) {
      sprintf(payload, "%s,\"context\": {%s}", payload,
              (_dots + i)->dot_context);
    }

    sprintf(payload, "%s}", payload);
    i++;

    if (i < *_current_value) {
      sprintf(payload, "%s,", payload);
    } else {
      sprintf(payload, "%s}", payload);
      *_current_value = 0;
    }
  }
}

/**
 * Builds the TCP payload to send and saves it to the input char pointer.
 * @payload [Mandatory] char payload pointer to store the built structure.
 * @timestamp_global [Optional] If set, it will be used for any dot without
 * timestamp.
 */

void buildTcpPayload(char *payload, const char *device_label,
                     const char *device_name, Value *_dots,
                     int8_t *_current_value) {
  sprintf(payload, "");
  sprintf(payload, "%s|POST|%s|", USER_AGENT, _token);
  sprintf(payload, "%s%s:%s", payload, device_label, device_name);

  sprintf(payload, "%s=>", payload);
  for (uint8_t i = 0; i < *_current_value;) {
    char str_value[20];
    _floatToChar(str_value, (_dots + i)->dot_value);
    sprintf(payload, "%s%s:%s", payload, (_dots + i)->variable_label,
            str_value);

    // Adds dot context
    if ((_dots + i)->dot_context != NULL) {
      sprintf(payload, "%s$%s", payload, (_dots + i)->dot_context);
    }

    // Adds timestamp seconds
    if ((_dots + i)->dot_timestamp_seconds != NULL) {
      sprintf(payload, "%s@%lu", payload, (_dots + i)->dot_timestamp_seconds);
      // Adds timestamp milliseconds
      if ((_dots + i)->dot_timestamp_millis != NULL) {
        char milliseconds[3];
        int timestamp_millis = (_dots + i)->dot_timestamp_millis;
        uint8_t units = timestamp_millis % 10;
        uint8_t dec = (timestamp_millis / 10) % 10;
        uint8_t hund = (timestamp_millis / 100) % 10;
        sprintf(milliseconds, "%d%d%d", hund, dec, units);
        sprintf(payload, "%s%s", payload, milliseconds);
      } else {
        sprintf(payload, "%s000", payload);
      }
    }

    i++;

    if (i < *_current_value) {
      sprintf(payload, "%s,", payload);
    } else {
      sprintf(payload, "%s|end", payload);
      *_current_value = 0;
    }
  }
}
}
