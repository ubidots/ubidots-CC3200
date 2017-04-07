/*
Copyright (c) 2013-2016 Ubidots.

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

Made by Mateo Velez - Metavix for Ubidots Inc

*/

#ifndef _UbidotsCC3200_H_
#define _UbidotsCC3200_H_

#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>


#define SERVER "translate.ubidots.com"
#define TIME_SERVER "pool.ntp.org"
#define USER_AGENT "CC3200"
#define VERSION "1.1"
#define PORT 9012
#define MAX_VALUES 10


typedef struct Value {
  char  *idName;
  char  *contextOne;
  float idValue;
  unsigned long timestamp_val;
} Value;

class Ubidots {
 public:
      bool sendAll();
      bool wifiConnection(char* ssid, char* password);
      float getValue(char* id);
      float getValueWithDatasource(char* dsName, char* idName);
      Ubidots(char* token);
      unsigned long ntpUnixTime();
      void setDataSourceName(char* dsName);
      void setDataSourceLabel(char* dsTag);
      void add(char *variable_id, double value);
      void add(char *variable_id, double value, char *ctext);
      void add(char *variable_id, double value, char *ctext, unsigned long timestamp);
      void setDebug(bool debug);
 

 private:
      bool _debug = false;
      char* _token;
      char* _dsName;
      char* _dsTag;
      uint8_t maxValues;
      uint8_t currentValue;
      Value * val;
      WiFiClient _client;
      WiFiUDP udp;    
};

#endif  // _UbidotsCC3200_H_
