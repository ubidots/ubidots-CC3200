/*
Copyright (c) 2013-2018 Ubidots.
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Developed and maintained by Jose Garcia and Cristian Arrieta for Ubidots
@jotathebest at github: https://github.com/jotathebest
@crisap94 at github: https://github.com/crisap94
*/

#include "UbiProtocolHandler.h"
/**************************************************************************
 * Overloaded constructors
 ***************************************************************************/

UbiProtocolHandler::UbiProtocolHandler(UbiToken token,
                                       IotProtocol iot_protocol) {
  _builder(token, UBI_INDUSTRIAL, iot_protocol);
}

UbiProtocolHandler::UbiProtocolHandler(UbiToken token, UbiServer server,
                                       IotProtocol iot_protocol) {
  _builder(token, server, iot_protocol);
}

void UbiProtocolHandler::_builder(UbiToken token, UbiServer server,
                                  IotProtocol iot_protocol) {
  _iot_protocol = iot_protocol;
  UbiBuilder builder(server, token, _iot_protocol);
  _dots = (Value *)malloc(MAX_VALUES * sizeof(Value));
  _ubiProtocol = builder.builder();
  _token = token;
  _current_value = 0;
}

/**************************************************************************
 * Overloaded destructor
 ***************************************************************************/

UbiProtocolHandler::~UbiProtocolHandler() {
  free(_dots);
  delete _ubiProtocol;
}

/***************************************************************************
FUNCTIONS TO SEND DATA
***************************************************************************/

/**
 * Add a value of variable to save
 * @arg variable_label [Mandatory] variable label where the dot will be stored
 * @arg value [Mandatory] Dot value
 * @arg context [optional] Dot context to store. Default NULL
 * @arg dot_timestamp_seconds [optional] Dot timestamp in seconds, usefull for
 * datalogger. Default NULL
 * @arg dot_timestamp_millis [optional] Dot timestamp in millis to add to
 * dot_timestamp_seconds, usefull for datalogger.
 */

void UbiProtocolHandler::add(const char *variable_label, float value,
                             char *context, unsigned long dot_timestamp_seconds,
                             unsigned int dot_timestamp_millis) {
  (_dots + _current_value)->variable_label = variable_label;
  (_dots + _current_value)->dot_value = value;
  (_dots + _current_value)->dot_context = context;
  (_dots + _current_value)->dot_timestamp_seconds = dot_timestamp_seconds;
  (_dots + _current_value)->dot_timestamp_millis = dot_timestamp_millis;
  _current_value++;
  if (_current_value > MAX_VALUES) {
    if (_debug) {
      Serial.println(
          F("You are sending more than the maximum of consecutive variables"));
    }
    _current_value = MAX_VALUES;
  }
}

/**
 * Sends data to Ubidots
 * @arg device_label [Mandatory] device label where the dot will be stored
 * @arg device_name [optional] Name of the device to be created (supported only
 * for TCP/UDP)
 */

bool UbiProtocolHandler::send(const char *device_label,
                              const char *device_name) {
  // Builds the payload
  char *payload = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);

  // Sends data
  if (_debug) {
    Serial.println("Sending data...");
  }

  bool result = _ubiProtocol->sendData(payload, device_label, device_name,
                                       _dots, &_current_value, _token);
  if (_debug) {
    Serial.println("----------");
    Serial.println("payload:");
    Serial.println(payload);
    Serial.println("----------");
    Serial.println("");
  }

  free(payload);
  _current_value = 0;
  return result;
}

float UbiProtocolHandler::get(const char *device_label,
                              const char *variable_label) {
  if (_iot_protocol == UBI_UDP) {
    Serial.println(
        "ERROR, data retrieval is only supported using TCP or HTTP protocols");
    return ERROR_VALUE;
  }

  float value = ERROR_VALUE;

  value = _ubiProtocol->get(device_label, variable_label);

  return value;
}

/*
  Makes debug messages available
*/

void UbiProtocolHandler::setDebug(bool debug) {
  _debug = debug;
  _ubiProtocol->setDebug(debug);
}

bool UbiProtocolHandler::serverConnected() {
  return _ubiProtocol->serverConnected();
}
