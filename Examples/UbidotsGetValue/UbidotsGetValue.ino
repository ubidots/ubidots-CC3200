#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_your_token_here" // Put your Ubidots' token here
#define ID "Put_your_variableID_here" // Put the variable ID here

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
    float value = client.getValue(ID);
    Serial.print("value: ");
    Serial.println(value);
    delay(5000);
}