#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_your_token_here" // Put the Ubidots' token here
#define VARIABLE_LABEL "Put_the_variableLabel_here" // Put the variable label here

#define SSID "..." // Network SSID
#define PASSWORD "..." // Wi-Fi Password

Ubidots client(TOKEN);

void setup()
{
  Serial.begin(115200);
  client.wifiConnection(SSID, PASSWORD);
  //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop(){
    float value = analogRead(0);
    unsigned long t = client.ntpUnixTime(); // calculates your actual timestamp in SECONDS

	client.add(VARIABLE_LABEL, value, context);
	client.sendAll();
    delay(5000);
}
