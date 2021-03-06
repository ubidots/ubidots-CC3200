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

#include "UbiBuilder.h"
#include "UbiHttp.h"
#include "UbiTcp.h"
#include "UbiUdp.h"

UbiBuilder::UbiBuilder(const char *server, const char *token,
                       IotProtocol iot_protocol) {
  _iot_protocol = iot_protocol;
  command_list[UBI_HTTP] = &builderHttp;
  command_list[UBI_UDP] = &builderUdp;
  command_list[UBI_TCP] = &builderTcp;
  _server = server;
  _token = token;
}

UbiProtocol *UbiBuilder::builder() {
  UbiProtocol *ubiBuilder = command_list[_iot_protocol]();
  return ubiBuilder;
}

UbiProtocol *builderTcp() {
  UbiProtocol *tcpInstance =
      new UbiTCP(_server, UBIDOTS_TCP_PORT, USER_AGENT, _token);
  return tcpInstance;
}

UbiProtocol *builderHttp() {
  UbiProtocol *httpInstance =
      new UbiHTTP(_server, UBIDOTS_HTTP_PORT, USER_AGENT, _token);
  return httpInstance;
}

UbiProtocol *builderUdp() {
  UbiProtocol *udpInstance =
      new UbiUDP(_server, UBIDOTS_TCP_PORT, USER_AGENT, _token);
  return udpInstance;
}
