# CC3200 - LAUNCHXL


The SimpleLink™ Wi-Fi® CC3200 LaunchPad™ development kit (with QFN-packaged device) is an evaluation development platform for the CC3200 wireless microcontroller (MCU), the industry’s first single-chip programmable MCU with built-in Wi-Fi connectivity. The board features on-board emulation using FTDI and includes sensors for a full out-of-the-box experience.

## Requiremets

* [SimpleLink Wi-Fi CC3200 LaunchPad](http://www.ti.com/tool/cc3200-launchxl)
* [Energia IDE](http://energia.nu/download/)
* [UbidotsCC3200 Library](https://github.com/ubidots/ubidots-CC3200/archive/master.zip)

## Setup

1. Download Energia IDE [here](http://energia.nu/download/) and install it on your pc.
2. Go to **Tools -> Board** and select LaunchPad w/ cc3200 (80MHz).
3. Download our library [here](https://github.com/ubidots/ubidots-CC3200/archive/master.zip).
4. Now, click on **File -> Include Library -> Add .ZIP Library**
5. Select the .ZIP file of UbidotsCC3200 and then "Accept" or "Choose"
6. Close the Energia IDE and open it again.

<aside class="notice">
To use this library don't forget to put your token.
</aside>
    
## Send one value to Ubidots

To send a value to Ubidots, go to **File -> Examples -> UbidotsCC3200 library** and select the "saveValue" example.


```c++
#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_Your_Token_Here"
#define VARIABLE_NAME1 "Put_Your_Variable_Name_Here"

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
  client.add(VARIABLE_NAME1, value1);
  client.sendAll();
}
```


## Get one value from Ubidots

To send multiple values to Ubidots, go to **File -> Examples -> UbidotsCC3200 library** and select the "saveValues" example.

```c++
#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

#define TOKEN "Put_Your_Token_Here"
#define VARIABLE_NAME1 "Put_Your_Variable_Name_Here"

#define SSID "Put_Here_Your_WiFi_SSID"
#define PASSWORD "Put_Here_Your_WiFi_PASSWORD"

Ubidots client(TOKEN);

void setup()
{
  client.wifiConnection(SSID, PASSWORD);
  
}

void loop() {
    float value = client.getValue(ID);
}
```

## Send multiple values to Ubidots 

To send multiple values to Ubidots, go to **File -> Examples -> UbidotsCC3200 library** and select the "saveValues" example.

```c++
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
```