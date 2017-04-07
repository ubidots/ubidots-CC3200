#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_your_token_here" // Put the Ubidots' token here
#define VARIABLE_LABEL_1 "Put_the_variableLabel_here" // Put the variable label here
#define VARIABLE_LABEL_2 "Put_the_variableLabel_here"
#define VARIABLE_LABEL_3 "Put_the_variableLabel_here"

#define SSID "..." // Network SSID
#define PASSWORD "..." // Wi-Fi Password

Ubidots client(TOKEN);

void setup()
{
  Serial.begin(115200);
  client.wifiConnection(SSID, PASSWORD);
  //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop()
{
  float value1 = analogRead(A0);
  float value2 = analogRead(A1);
  float value3 = analogRead(A2);
  
  client.add(VARIABLE_LABEL_1, value1);
  client.add(VARIABLE_LABEL_2, value2);
  client.add(VARIABLE_LABEL_3, value3);
  client.sendAll();
  delay(5000);
}