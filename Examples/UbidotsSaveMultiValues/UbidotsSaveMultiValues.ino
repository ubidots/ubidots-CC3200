/*
ISC License

Copyright (c) 2016, Mateo Velez Rodriguez - Metavix

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Made by Mateo Velez - Metavix for Ubidots Inc
*/

#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_Your_Token_Here"
#define VARIABLE_NAME1 "Put_Your_Variable_Name_Here"
#define VARIABLE_NAME2 "Put_Your_Variable_Name_Here"
#define VARIABLE_NAME3 "Put_Your_Variable_Name_Here"

#define SSID "Put_Here_Your_WiFi_SSID"
#define PASSWORD "Put_Here_Your_WiFi_PASSWORD"

Ubidots client(TOKEN);

void setup()
{
  client.wifiConnection(SSID, PASSWORD);
  
}

void loop()
{
  float value1 = analogRead(A0);
  float value2 = analogRead(A1);
  float value3 = analogRead(A2);
  client.add(VARIABLE_NAME1, value1);
  client.add(VARIABLE_NAME1, value2);  
  client.add(VARIABLE_NAME1, value3);
  client.sendAll();
}