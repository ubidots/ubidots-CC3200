# CC3200 - LAUNCHXL


The SimpleLink™ Wi-Fi® CC3200 LaunchPad™ development kit (with QFN-packaged device) is an evaluation development platform for the CC3200 wireless microcontroller (MCU), the industry’s first single-chip programmable MCU with built-in Wi-Fi connectivity. The board features on-board emulation using FTDI and includes sensors for a full out-of-the-box experience.

## Requiremets

* [SimpleLink Wi-Fi CC3200 LaunchPad](http://www.ti.com/tool/cc3200-launchxl)
* [Energia IDE](http://energia.nu/download/)
* [UbidotsCC3200 Library](https://github.com/ubidots/ubidots-CC3200/archive/master.zip)

## Setup

1. Download Energia IDE [here](http://energia.nu/download/) and install it on your pc.
2. Open **Boards Manager** from Tools -> Board menu and install **CC3200** platform 
3. Go to **Tools -> Board** and select LaunchPad w/ cc3200 (80MHz).
4. Download our library [here](https://github.com/ubidots/ubidots-CC3200/archive/master.zip).
5. Now, click on **File -> Include Library -> Add .ZIP Library**
6. Select the .ZIP file of UbidotsCC3200 and then "Accept" or "Choose"
7. Close the Energia IDE and open it again.

**Note**: The library will create a new Ubidots data source named "**CC32000**. If you desire assign a different device name and label, you can add the add to your code the following lines:

* To change the Device Name:

```
client.setDataSourceName("New_name");
```

* To change the Device label:

``` 
client.setDataSourceLabel("New_label"); 
```

   
## Send values to Ubidots 

You can send values using the variable label, also you can send values with timestamp and context. 


### Send values using the variable label 

The following example is to send one value to Ubidots, it will create the variable automatically with the label assign by you on the code. If you desire send more than one value just add this line ```client.add("variable_name", value);``` to your code with the parameters needed. 

Also, you can find the example on the library examples. Go to **Sketch -> Examples -> UbidotsCC3200 library** and select the **"UbidotsSaveValue"** example.

Add your Ubidots TOKEN where indicated, as well as the WI-FI settings.

```c++
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

void loop()
{
  float value = analogRead(A0);
  client.add(VARIABLE_LABEL, value);
  client.sendAll();
  delay(5000);
}
```

### Send values with timestamp

The following example is to send one value with timestamp to Ubidots, it will create the variable automatically with the label assign by you on the code.

Add your Ubidots TOKEN where indicated, as well as the WI-FI settings.

```c++
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
```

### Send values with context

The following example is to send one value with context to Ubidots, it will create the variable automatically with the label assign by you on the code.

Add your Ubidots TOKEN where indicated, as well as the WI-FI settings.

```c++
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
  char context[25];
  sprintf(context, "lat=1.2343$lng=132.1233"); //Sends latitude and longitude for watching position in a map

  client.add(VARIABLE_LABEL, value, context);
  client.sendAll();
  delay(5000);
}
```

## Get value from Ubidots

To get the last value of a variable from Ubidots you can use two different functions:

+ client.getValue(ID)
+ client.getValueWithDatasource(DEVICE_LABEL, VARIABLE_LABEL)

On the example folder you'll find all the examples codes. Go to **Sketch -> Examples ->  UbidotsCC3200 library** and select the one that you need "**UbidotsGetValue**";**UbidotsGetValueWithDatasource**".

### client.getValue(ID)

This function let you get de last value of a variable using the variable ID.

Add your Ubidots TOKEN and variable ID where indicated, as well as the WI-FI settings.

```c++
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
```

### client.getValueWithDatasource(DEVICE_LABEL, VARIABLE_LABEL)

This function let you get de last value of a variable using the device and variable labels.

Add your Ubidots TOKEN, device label, and variable label where indicated, as well as the WI-FI settings.

```c++
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
```
