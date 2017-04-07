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
Modified by: Maria Carlina Hernandez for Ubidots Inc
*/

#include "UbidotsCC3200.h"
/**
 * Constructor.
 */
Ubidots::Ubidots(char* token) {
    _token = token;
    _dsName = "CC3200";
    _dsTag = "CC3200";
    currentValue = 0;
    val = (Value *)malloc(MAX_VALUES*sizeof(Value));
}

void Ubidots::setDataSourceName(char *dsName) {

    _dsName = dsName;
}

void Ubidots::setDataSourceLabel(char *dsTag) {

    _dsTag = dsTag;
}

/** 
 * This function is to get value from the Ubidots API
 * @arg id the id where you will get the data
 * @return num the data that you get from the Ubidots API
 */
float Ubidots::getValue(char* id) {
    
    String response;
    int timeout = 0;
    float num;
    uint8_t bodyPosinit;
    uint8_t max_retries = 0;
    char* data = (char *) malloc(sizeof(char) * 300);

    sprintf(data, "%s/%s|GET|%s|%s|end", USER_AGENT, VERSION, _token, id);

    _client.connect(SERVER, PORT); // Initial connection

    while(!_client.connected()){

    if(_debug){
        Serial.println("Attemping to connect");
    }
        _client.connect(SERVER, PORT);
        max_retries++;
        if(max_retries>5){
            if(_debug){
                Serial.println("Connection failed");
            }
            free(data);
            return NULL;
        }
        delay(5000);
    }

    if(_debug){
        Serial.println("Getting your variable: ");
        Serial.println(data);
    }
        
    _client.print(data);

    while(!_client.available() && timeout < 5000) {
        timeout++;
        delay(1);
        if(timeout>=5000){
            if(_debug){
                Serial.println("Error, max timeout reached");
            }
            _client.stop();
            delay(5);
            return NULL;
        }
    }

    while (_client.available()) {
        char c = _client.read();
        if (c == -1){
            if(_debug){
                Serial.println("Error reading from server");
            }
            _client.stop();
            delay(5);
            free(data);
            return NULL;
        }
        response += c;
        delay(10);
    }

    if(_debug){
        Serial.println("Response: ");
        Serial.println(response); 
    }

    bodyPosinit = 4 + response.indexOf("\r\n\r\n");    
    response = response.substring(bodyPosinit);
    num = response.toFloat();
    
    if(_debug){
        Serial.println("Value obtained: ");
        Serial.println(num);;
    }
    
    free(data);
    _client.stop();
    delay(5);
    return num;
}

/** 
 * This function is to get value from the Ubidots API
 * @arg id the id where you will get the data
 * @return num the data that you get from the Ubidots API
 */
float Ubidots::getValueWithDatasource(char* dsTag, char* idName) {
  float num;
  int i = 0;
  char* allData = (char *) malloc(sizeof(char) * 300);
  String response;
  uint8_t bodyPosinit;

  sprintf(allData, "%s/%s|LV|%s|%s:%s|end", USER_AGENT, VERSION, _token, dsTag, idName);

  while (!_client.connected() && i < 6) {
        i++;
        _client.connect(SERVER, PORT);
    }
    if (_client.connected()) {  // Connect to the server

        if(_debug){
            Serial.println("Client connected");
            Serial.println(allData);    
        }

        _client.println(allData);
        _client.flush();
    }

    i = 50000;
    while (!_client.available()|| i == 0) {
        i--;
    }
    while (_client.available()) {
        char c = _client.read();
        response += c;
    }
        
    if(_debug){
        Serial.print("response: ");
        Serial.println(response);
    }

    bodyPosinit = 3 + response.indexOf("OK|");
    response = response.substring(bodyPosinit);
    num = response.toFloat();
    
    if(_debug){
        Serial.println("Value obtained: ");
        Serial.println(num);;
    }

    currentValue = 0;
    _client.stop();
    free(allData);
    _client.stop();
    return num;
}
/**
 * Add a value of variable to save
 * @arg variable_id variable id or name to save in a struct
 * @arg value variable value to save in a struct
 * @arg ctext [optional] is the context that you will save, default
 * @arg timestamp_val [optional] is the timestamp for the actual value
 * is NULL
 */

void Ubidots::add(char *variable_id, double value) {
  return add(variable_id, value, NULL, NULL);
}

void Ubidots::add(char *variable_id, double value, char *ctext) {
  return add(variable_id, value, ctext, NULL);
}

void Ubidots::add(char *variable_id, double value, char *ctext, long unsigned timestamp_val) {
  (val+currentValue)->idName = variable_id;
  (val+currentValue)->idValue = value;
  (val+currentValue)->contextOne = ctext;
  (val+currentValue)->timestamp_val = timestamp_val;
  currentValue++;
  if (currentValue > MAX_VALUES) {
        Serial.println(F("You are sending more than the maximum of consecutive variables"));
        currentValue = MAX_VALUES;
  }
}

/**
 * Send all data of all variables that you saved
 * @return true upon success, false upon error.
 */
bool Ubidots::sendAll() {
    int i;
    int timeout = 0;
    String str;
    char* data = (char *) malloc(sizeof(char) * 700);

    sprintf(data, "%s/%s|POST|%s|%s:%s=>", USER_AGENT, VERSION, _token, _dsTag, _dsName);
   
    for (i = 0; i < currentValue;) {
         str = String(((val+i)->idValue), 5);
    
        sprintf(data, "%s%s:%s", data, (val + i)->idName, str.c_str());

        if ((val + i)->timestamp_val != NULL) {
            sprintf(data, "%s@%lu%s", data, (val + i)->timestamp_val, "000");
        }
        if ((val + i)->contextOne != NULL) {
            sprintf(data, "%s$%s", data, (val + i)->contextOne);
        }
        
        i++;

        if (i < currentValue) {
            sprintf(data, "%s,", data);
        } else {
            sprintf(data, "%s|end", data);
            currentValue = 0;
        }
    }
        
    Serial.println("");

    if (_debug){
     Serial.println(data);   
    }
        
    if (_client.connect(SERVER, PORT)) {
        _client.print(data);
    }
    
    while(!_client.available() && timeout < 5000) {
        timeout++;
        delay(1);
    }

    while (_client.available()) {
        char c = _client.read();
        Serial.write(c);
    }

    _client.stop();
    free(data);
}

bool Ubidots::wifiConnection(char* ssid, char* password) {
    WiFi.begin(ssid, password);
    while ( WiFi.status() != WL_CONNECTED) {
        // print dots while we wait to connect
        Serial.print(".");
        delay(300);
    }
    return true;
}

void Ubidots::setDebug(bool debug){
     _debug = debug;
 }

/*
 * © Francesco Potortì 2013 - GPLv3 - Revision: 1.13
 *
 * Send an NTP packet and wait for the response, return the Unix time
 *
 * To lower the memory footprint, no buffers are allocated for sending
 * and receiving the NTP packets.  Four bytes of memory are allocated
 * for transmision, the rest is random garbage collected from the data
 * memory segment, and the received packet is read one byte at a time.
 * The Unix time is returned, that is, seconds from 1970-01-01T00:00.
 */
unsigned long Ubidots::ntpUnixTime () {
    static int udpInited = udp.begin(123); // open socket on arbitrary port

    // Only the first four bytes of an outgoing NTP packet need to be set
    // appropriately, the rest can be whatever.
    const long ntpFirstFourBytes = 0xEC0600E3; // NTP request header

    // Fail if WiFiUdp.begin() could not init a socket
    if (! udpInited)
        return 0;

    // Clear received data from possible stray received packets
    udp.flush();

    // Send an NTP request
    if (! (udp.beginPacket(TIME_SERVER, 123) // 123 is the NTP port
        && udp.write((byte *)&ntpFirstFourBytes, 48) == 48
        && udp.endPacket()))
            return 0;               // sending request failed

    // Wait for response; check every pollIntv ms up to maxPoll times
    const int pollIntv = 150;     // poll every this many ms
    const byte maxPoll = 15;      // poll up to this many times
    int pktLen;               // received packet length
    for (byte i = 0; i < maxPoll; i++) {
        if ((pktLen = udp.parsePacket()) == 48)
            break;
        delay(pollIntv);
    }
    if (pktLen != 48)
        return 0;               // no correct packet received

    // Read and discard the first useless bytes
    // Set useless to 32 for speed; set to 40 for accuracy.
    const byte useless = 40;
    for (byte i = 0; i < useless; ++i)
        udp.read();

    // Read the integer part of sending time
    unsigned long time = udp.read();  // NTP time
    for (byte i = 1; i < 4; i++)
        time = time << 8 | udp.read();

    // Round to the nearest second if we want accuracy
    // The fractionary part is the next byte divided by 256: if it is
    // greater than 500ms we round to the next second; we also account
    // for an assumed network delay of 50ms, and (0.5-0.05)*256=115;
    // additionally, we account for how much we delayed reading the packet
    // since its arrival, which we assume on average to be pollIntv/2.
    time += (udp.read() > 115 - pollIntv/8);
    // Discard the rest of the packet
    udp.flush();
    return time - 2208988800ul;       // convert NTP time to Unix time
}