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
  const char * DEVICE_LABEL = "Assign_device_label"; // Assign the Ubidots' Device label
  const char * VARIABLE_LABEL = "Assign_variable_label"; // Assign the Ubidots' Variable label
}

/* initialize the instance */
Ubidots client(TOKEN);

/********************************
 * Main Functions
 *******************************/
void setup() {
  Serial.begin(115200);
  client.wifiConnection(SSID_NAME, SSID_PASS);
  //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() {
  /* Getting the last value from a variable */
  float value = client.getValue(DEVICE_LABEL, VARIABLE_LABEL);
  /* Print the value obtained */
  Serial.print("The value obteined is: ");
  Serial.println(value);
  delay(5000);
}
