/********************************
 * Libraries included
 *******************************/
 #include <SPI.h>
 #include <WiFi.h>
 #include <UbidotsCC3200.h>

/********************************
 * Constants and objects
 *******************************/
 namespace {
  char SSID_NAME[] = "Assign_your_SSID_name"; // Assign your SSID Name
  char SSID_PASS[] = "Assign_your_SSID_password"; // Assign your SSID Password
  const char * TOKEN = "Assign_your_Ubidots_token"; // Assign your Ubidots TOKEN
  const char * VARIABLE_LABEL_1 = "temperature"; // Assign the Ubidots' Variable label
  const char * VARIABLE_LABEL_2 = "humidity"; // Assign the Ubidots' Variable label
  const char * VARIABLE_LABEL_3 = "pressure"; // Assign the Ubidots' Variable label
  const char * VARIABLE_LABEL_4 = "current"; // Assign the Ubidots' Variable label
  const char * VARIABLE_LABEL_5 = "voltage"; // Assign the Ubidots' Variable label
}

/* initialize the instance */
Ubidots client(TOKEN);

/********************************
 * Main Functions
 *******************************/
void setup() {
  Serial.begin(115200);
  client.wifiConnection(SSID_NAME, SSID_PASS);
  //client.setDeviceLabel("my-new-device"); // Uncomment this line to change the default device name
  //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() {
  /* Sensors readings */
  float value = analogRead(2);
  /* Sending values to Ubidots */
  client.add(VARIABLE_LABEL_1,value);
  client.add(VARIABLE_LABEL_2,value);
  client.sendAll();
  /* Sending more than 5 variables */
  client.add(VARIABLE_LABEL_3,value);
  client.add(VARIABLE_LABEL_4,value);
  client.add(VARIABLE_LABEL_5,value);
  client.sendAll();
  delay(5000);
}
