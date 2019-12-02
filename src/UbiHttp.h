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

#ifndef _UbiHttp_H_
#define _UbiHttp_H_

#include "UbiProtocol.h"

#include <WiFi.h>

#include <time.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic pop

class UbiHTTP : public UbiProtocol {

private:
  bool _debug = false;
  int _timeout = 5000;
  uint8_t _maxReconnectAttempts = 5;
  unsigned long _timerToSync = millis();

  UbiServer _server;
  UbiAgent _user_agent;
  UbiToken _token;
  UbiPort _port;
  WiFiClient _client_http_ubi;

  bool waitServerAnswer();
  void reconnect(const char *server, int port);
  float parseHttpAnswer(const char *request_type, char *data);
  void readServerAnswer(char *response);

public:
  UbiHTTP(const char *server, const int port, const char *user_agent,
          const char *token);

  ~UbiHTTP();

  bool sendData(const char *device_label, const char *device_name,
                char *payload);

  float get(const char *device_label, const char *variable_label);

  void setDebug(bool debug);

  bool serverConnected();
};

#endif
