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

#include "UbiTcp.h"

/**************************************************************************
 * Overloaded constructors
 ***************************************************************************/

/**
 * @brief Construct a new UbiTCP object and power up the module
 *
 * @param server Server addres
 * @param port Server port
 * @param user_agent Reference from the device being connected
 * @param token Users token
 */
UbiTCP::UbiTCP(const char *server, const int port, const char *user_agent,
               const char *token) {
  _server = server;
  _user_agent = user_agent;
  _token = token;
  _port = port;
}

/**************************************************************************
 * Destructor
 ***************************************************************************/

UbiTCP::~UbiTCP() {
  delete[] _server;
  delete[] _user_agent;
  delete[] _token;
}

/**************************************************************************
 * Cloud Functions
 ***************************************************************************/
/**
 * @brief Post new data to ubidots server
 *
 * @param device_label Label of the device to be set or update in the ubidots
 * platform
 * @param device_name Device name to be published
 * @param payload Body to be processed by the Ubidot server
 * @return true The data was succesfully published
 * @return false Something went wrong with the sending.
 */
bool UbiTCP::sendData(char *payload, const char *device_label,
                      const char *device_name, Value *_dots,
                      int8_t *_current_value, UbiToken _token) {
  buildTcpPayload(payload, device_label, device_name, _dots,
                         _current_value, _token);
  /* Connecting the client */
  _client_tcp_ubi.connect(_server, UBIDOTS_TCP_PORT);
  reconnect(_server, UBIDOTS_TCP_PORT);

  /* Sends data to Ubidots */
  if (_client_tcp_ubi.connected()) {
    if (_debug) {
      Serial.println("TCP Payload being sent");
      Serial.println(payload);
      _client_tcp_ubi.print(payload);
    }
  } else {
    if (_debug) {
      Serial.println("[ERROR] Could not connect to the host");
    }
    _client_tcp_ubi.stop();
    return false;
  }

  /* Waits for the host's answer */
  if (!waitServerAnswer()) {
    if (_debug) {
      Serial.println("[ERROR] Could not read server's response");
    }
    _client_tcp_ubi.stop();
    return false;
  }

  /* Parses the host answer, returns true if it is 'Ok' */
  char *response = (char *)malloc(sizeof(char) * 100);

  float value = parseTCPAnswer("POST", response);
  free(response);
  if (value != ERROR_VALUE) {
    _client_tcp_ubi.stop();
    return true;
  }

  _client_tcp_ubi.stop();
  return false;
}

/**
 * @brief Get request over TCP to Ubidots server
 *
 * @param device_label device label of the device
 * @param variable_label variable label to be fetched
 * @return float Response value from the server
 */
float UbiTCP::get(const char *device_label, const char *variable_label) {
  /* Connecting the client */
  _client_tcp_ubi.connect(_server, UBIDOTS_TCP_PORT);
  reconnect(_server, UBIDOTS_TCP_PORT);

  if (_client_tcp_ubi.connected()) {
    /* Builds the request POST - Please reference this link to know all the
     * request's structures https://ubidots.com/docs/api/ */
    _client_tcp_ubi.print(_user_agent);
    _client_tcp_ubi.print("|LV|");
    _client_tcp_ubi.print(_token);
    _client_tcp_ubi.print("|");
    _client_tcp_ubi.print(device_label);
    _client_tcp_ubi.print(":");
    _client_tcp_ubi.print(variable_label);
    _client_tcp_ubi.print("|end");

    if (_debug) {
      Serial.println("----");
      Serial.println("Payload for request:");
      Serial.print(_user_agent);
      Serial.print("|LV|");
      Serial.print(_token);
      Serial.print("|");
      Serial.print(device_label);
      Serial.print(":");
      Serial.print(variable_label);
      Serial.print("|end");
      Serial.println("\n----");
    }

    /* Waits for the host's answer */
    if (!waitServerAnswer()) {
      _client_tcp_ubi.stop();
      return ERROR_VALUE;
    }

    /* Reads the response from the server */
    char *response = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
    float value = parseTCPAnswer("LV", response);
    _client_tcp_ubi.stop();
    free(response);
    return value;
  }

  if (_debug) {
    Serial.println("ERROR could not connect to the server");
  }

  _client_tcp_ubi.stop();
  return ERROR_VALUE;
}

/**************************************************************************
 * Auxiliar
 ***************************************************************************/

/**
 * Reconnects to the server
 * @return true once the host answer buffer length is greater than zero,
 *         false if timeout is reached.
 */

void UbiTCP::reconnect(const char *server, const int port) {
  uint8_t attempts = 0;
  while (!_client_tcp_ubi.status() && attempts < 5) {
    if (_debug) {
      Serial.print("Trying to connect to ");
      Serial.print(server);
      Serial.print(" , attempt number: ");
      Serial.println(attempts);
    }
    _client_tcp_ubi.stop();
    _client_tcp_ubi.connect(server, port);
    attempts += 1;
    delay(1000);
  }
}

/**
 * Function to wait for the host answer up to the already set _timeout.
 * @return true once the host answer buffer length is greater than zero,
 *         false if timeout is reached.
 */

bool UbiTCP::waitServerAnswer() {
  int timeout = 0;
  while (!_client_tcp_ubi.available() && timeout < _timeout) {
    timeout++;
    delay(1);
    if (timeout > _timeout - 1) {
      if (_debug) {
        Serial.println("timeout, could not read any response from the host");
      }
      return false;
    }
  }
  return true;
}

/**
 * Parse the TCP host answer and saves it to the input char pointer.
 * @payload [Mandatory] char payload pointer to store the host answer.
 * @return true if there is an 'Ok' in the answer, false if not.
 */

float UbiTCP::parseTCPAnswer(const char *request_type, char *response) {
  int j = 0;

  if (_debug) {
    Serial.println("----------");
    Serial.println("Server's response:");
  }

  while (_client_tcp_ubi.available()) {
    char c = _client_tcp_ubi.read();
    if (_debug) {
      Serial.write(c);
    }
    response[j] = c;
    j++;
    if (j >= MAX_BUFFER_SIZE - 1) {
      break;
    }
  }

  if (_debug) {
    Serial.println("\n----------");
  }

  response[j] = '\0';
  float result = ERROR_VALUE;

  // POST
  if (request_type == "POST") {
    char *pch = strstr(response, "OK");
    if (pch != NULL) {
      result = 1;
    }
    return result;
  }

  // LV
  char *pch = strchr(response, '|');
  if (pch != NULL) {
    result = atof(pch + 1);
  }

  return result;
}

/**
 * Makes available debug traces
 */

void UbiTCP::setDebug(bool debug) { _debug = debug; }

/*
 * Checks if the socket is still opened with the Ubidots Server
 */

bool UbiTCP::serverConnected() { return _client_tcp_ubi.connected(); }
