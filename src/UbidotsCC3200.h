/*
Copyright (c) 2017, Ubidots.
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
Original Maker: Mateo Velez - Metavix for Ubidots Inc
Modified and Maintened by: María Carlina Hernández ---- Developer at Ubidots Inc
                           https://github.com/mariacarlinahernandez
                           Jose Garcia ---- Developer at Ubidots Inc
                           https://github.com/jotathebest
*/

#ifndef _UbidotsCC3200_H_
#define _UbidotsCC3200_H_

#ifndef __CC3200R1M1RGC__
#include <SPI.h>
#endif
#include <WiFi.h>

namespace {
  const char * DEFAULT_DEVICE_LABEL = "cc3200";
  const char * TIME_SERVER = "pool.ntp.org";
  const char * SERVER = "things.ubidots.com";
  const char * USER_AGENT = "CC3200-LAUNCHXL";
  const char * VERSION = "2.0";
  const int PORT = 80;
  const float ERROR_VALUE = -3.4028235E+5;
}

typedef struct Value {
  const char *varLabel;
  char *context;
  float varValue;
  unsigned long timestamp_val;
} Value;

class Ubidots {
  private:
    bool _debug = false;
    const char * _deviceLabel;
    const char * _token;
    const char* _server;
    #if defined(UBI_WIN)
    float _value;
    #endif
    int dataLen(char* variable);
    uint8_t _maxValues;
    uint8_t _currentValue;
    Value * val;
    WiFiClient _client;
    WiFiUDP udp;

  public:
    bool sendAll();
    explicit Ubidots(const char * token, const char * server = SERVER);
    float getValue(const char * device_label, const char * variable_label);
    unsigned long ntpUnixTime();
    void add(const char * variable_label, float value);
    void add(const char * variable_label, float value, char* ctext);
    void add(const char * variable_label, float value, unsigned long timestamp_val);
    void add(const char * variable_label, float value, char* ctext, unsigned long timestamp_val);
    void setDebug(bool debug);
    void setDeviceLabel(const char * new_device_label);
    void wifiConnection(char* ssid, char* password);
};

#endif  // _UbidotsCC3200_H_
