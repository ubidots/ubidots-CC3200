# CC3200 - LAUNCHXL

The SimpleLink™ Wi-Fi® CC3200 LaunchPad™ development kit (with QFN-packaged device) is an evaluation development platform for the CC3200 wireless microcontroller (MCU), the industry’s first single-chip programmable MCU with built-in Wi-Fi connectivity. The board features on-board emulation using FTDI and includes sensors for a full out-of-the-box experience.

## Requiremets

* [SimpleLink Wi-Fi CC3200 LaunchPad](http://www.ti.com/tool/cc3200-launchxl)
* [CC3200 Jumper settings](http://energia.nu/cc3200guide/)
* [Energia IDE](http://energia.nu/download/)
* [UbidotsCC3200 Library](https://github.com/ubidots/ubidots-CC3200/archive/master.zip)


## Setup

1. Download Energia IDE [here](http://energia.nu/download/) and install it on your pc.
2. Open **Boards Manager** from **Tools -> Board menu** and install **CC3200** platform
3. Go to **Tools -> Board** and select **CC3200-LAUNCHXL (80MHz)**.
4. Download our library [here](https://github.com/ubidots/ubidots-CC3200/archive/master.zip).
5. Go to **File -> Include Library -> Add .ZIP Library**
6. Select the **.ZIP** file of **Ubidots CC3200-LAUNCHXL** and then "Accept" or "Choose"
7. Close the Energia IDE and open it again.

**IMPORTANT NOTE**: To be able to compile the CC3200 you have establish the [jumpper settings](http://energia.nu/cc3200guide/) properly.

## Change default name

The library will create a new Ubidots device named **"CC3200"**, also assigns the same name as device label. If you desire to assign a different device label, please add to your setup() function the line below:

 
> client.setDeviceLabel("my-new-device")

**NOTE**: To get a better idea of the difference between **Device Label** and **Device Name**, see the following [guide](http://help.ubidots.com/user-guides/how-to-adjust-the-device-name-and-variable-name).

## Send values to Ubidots

**DEPLOYMENT NOTE**: If your are working under **Windows OS** uncomment the line below at the first part of the example codes:

>#define UBI_WIN 1s

### Send one value
To send one value to Ubidots, go to **Sketch -> Examples -> Ubidots CC3200-LAUNCHXL** and select the **"UbidotsSaveValue"** example.

Update your WiFi crendentials, assign your Ubidots [TOKEN](http://help.ubidots.com/user-guides/find-your-token-from-your-ubidots-account) and the variable label where is indicated. Once the parameters are assigned, upload the code. Then, open the Serial monitor to check the results.

**NOTE**: If no response is seen, try unplugging the board and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
/********************************
 * Libraries included
 *******************************/
 #include <SPI.h>
 #include <WiFi.h>
 //#define UBI_WIN 1 // Uncomment if you are using Windows
 #include <UbidotsCC3200.h>

/********************************
 * Constants and objects
 *******************************/
 namespace {
  char SSID_NAME[] = "Assign_your_SSID_name"; // Assign your SSID Name
  char SSID_PASS[] = "Assign_your_SSID_password"; // Assign your SSID Password
  const char * TOKEN = "Assign_your_Ubidots_token"; // Assign your Ubidots TOKEN
  const char * VARIABLE_LABEL= "temperature"; // Assign the Ubidots' Variable label
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
  /* Sending value to Ubidots */
  client.add(VARIABLE_LABEL, value);
  client.sendAll();
  delay(5000);
}
```
The library allow you send just **5 variables** per request. But don't worry for that, if you desire send more than 5 variables, go to **Sketch -> Examples -> Ubidots CC3200-LAUNCHXL** and select the **"UbidotsSaveMultiValues"** example. Don't forget update your WiFi credentials, assign your Ubidots [TOKEN](http://help.ubidots.com/user-guides/find-your-token-from-your-ubidots-account) and variables labels where is indicated.

### Send values with context

The following example is to send one value with context to Ubidots, it will create the variable automatically with the label assign by you into the code.

Add your Ubidots TOKEN where indicated, as well as the WI-FI settings.

```c++
/********************************
 * Libraries included
 *******************************/
 #include <SPI.h>
 #include <WiFi.h>
 //#define UBI_WIN 1 // Uncomment if you are using Windows
 #include <UbidotsCC3200.h>

/********************************
 * Constants and objects
 *******************************/
 namespace {
  char SSID_NAME[] = "Assign_your_SSID_name"; // Assign your SSID Name
  char SSID_PASS[] = "Assign_your_SSID_password"; // Assign your SSID Password
  const char * TOKEN = "Assign_your_Ubidots_token"; // Assign your Ubidots TOKEN
  const char * VARIABLE_LABEL= "position"; // Assign the Ubidots' Variable label
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
  char* context = (char *) malloc(sizeof(char) * 50);
  char *lat  = "1.234";
  char *lng = "132.123";

  /* Build the context to be send */
  sprintf(context, "\"lat\":%s, \"lng\":%s", lat, lng);
  /* Sends latitude and longitude for watching position in a map */
  client.add(VARIABLE_LABEL, 1, context);
  client.sendAll();
  /* free memory */
  free(context);
  delay(5000);
}
```

### Send values with timestamp

The following example is to send one value with timestamp to Ubidots, it will create the variable automatically with the label assign by you into the code.

Add your Ubidots TOKEN where indicated, as well as the WI-FI settings.

```c++
/********************************
 * Libraries included
 *******************************/
 #include <SPI.h>
 #include <WiFi.h>
 //#define UBI_WIN 1 // Uncomment if you are using Windows
 #include <UbidotsCC3200.h>

/********************************
 * Constants and objects
 *******************************/
 namespace {
  char SSID_NAME[] = "Assign_your_SSID_name"; // Assign your SSID Name
  char SSID_PASS[] = "Assign_your_SSID_password"; // Assign your SSID Password
  const char * TOKEN = "Assign_your_Ubidots_token"; // Assign your Ubidots TOKEN
  const char * VARIABLE_LABEL= "temperature"; // Assign the Ubidots' Variable label
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
  /* calculates your actual timestamp in SECONDS */
  unsigned long t = client.ntpUnixTime();
  /* Sends a value with a custom timestamp */
  client.add(VARIABLE_LABEL, value, t-20000);
  client.sendAll();
  delay(5000);
}
```
## Get value from Ubidots

To get the last value of a variable from Ubidots, go to **Sketch -> Examples -> Ubidots CC3200-LAUNCHXL** and select the **"UbidotsGetValue"** example.

Update your WiFi crendentials, assign your Ubidots [TOKEN](http://help.ubidots.com/user-guides/find-your-token-from-your-ubidots-account), the device and variable label from where you desire obtain the value.

Upload the code, open the Serial monitor to check the results.

**NOTE**: If no response is seen, try unplugging the board and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
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
```
## FAQs and Troubleshooting

* If you get the compilation error below remove the `SPI.h` library of the sample code. For more information about this, reference to the [Energia Community](http://energia.nu/getting-help/).

![cc3200_spi_issue](https://ubidots.com/blog/wp-content/uploads/2017/10/cc3200_SPIerror.jpg)

* The issue below reference to a hardware inconvenience (programmer mode utility); to solve it verify the CC3200 [jumper settings](http://energia.nu/cc3200guide/)

![bootloader_issue](https://ubidots.com/blog/wp-content/uploads/2017/10/bootloader_issue.jpg)

* **OS issue:** If the value received at Ubidots is equal to 0 and is not the one that your are sending, please verify if the line below is setup correctly for your operating system:

> #define UBI_WIN 1
