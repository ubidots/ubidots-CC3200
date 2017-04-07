#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_your_token_here" // Put your Ubidots' token here
#define DEVICE_LABEL "Put_your_deviceLabel_here" // Put the device label  here
#define VARIABLE_LABEL "Put_your_variableLabel_here" // Put the variable label here

#define SSID "..." // Network SSID
#define PASSWORD "..." // Wi-Fi Password


Ubidots client(TOKEN);

void setup()
{
  Serial.begin(115200);
  client.wifiConnection(SSID, PASSWORD);
  //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() {
    float value = client.getValueWithDatasource(DEVICE_LABEL, VARIABLE_LABEL);
    Serial.print("value: ");
    Serial.println(value);
    delay(5000);
}