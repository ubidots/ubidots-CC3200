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

**IMPORTANT NOTE**: To be able to compile the CC3200 you have set the [jumpper settings](http://energia.nu/cc3200guide/) properly.

# Documentation

## Constructor
 
### Ubidots

```
Ubidots(const char* token, UbiServer server, IotProtocol iot_protocol)
```

> @token, [Required]. Your Ubidots unique account [TOKEN](http://help.ubidots.com/user-guides/find-your-token-from-your-ubidots-account).  
> @server, [Optional], [Options] = [`UBI_INDUSTRIAL`, `UBI_EDUCATIONAL`], [Default] = `UBI_INDUSTRIAL`. The server to send data, set `UBI_EDUCATIONAL` if your account is educational type.  
> @iot_protocol, [Optional], [Options] = [`UBI_HTTP`, `UBI_TCP`, `UBI_UDP`], [Default] = `UBI_TCP`. The IoT protocol that you will use to send or retrieve data.

Creates an Ubidots instance.

## Methods

```
void add(const char *variable_label, float value, char *context, unsigned long dot_timestamp_seconds, unsigned int dot_timestamp_millis)
```

> @variable_label, [Required]. The label of the variable where the dot will be stored.
> @value, [Required]. The value of the dot.  
> @context, [Optional]. The dot's context.  
> @dot_timestamp_seconds, [Optional]. The dot's timestamp in seconds.  
> @dot_timestamp_millis, [Optional]. The dot's timestamp number of milliseconds. If the timestamp's milliseconds values is not set, the seconds will be multplied by 1000.

Adds a dot with its related value, context and timestamp to be sent to a certain data source, once you use add().

**Important:** The max payload lenght is 700 bytes, if your payload is greater it won't be properly sent. You can see on your serial console the payload to send if you call the `setDebug(bool debug)` method and pass a true value to it.

```
float get(const char* device_label, const char* variable_label)
```

> @device_label, [Required]. The device label which contains the variable to retrieve values from.  
> @variable_label, [Required]. The variable label to retrieve values from.

Returns as float the last value of the dot from the variable.
IotProtocol getCloudProtocol()

```
void addContext(char *key_label, char *key_value)
```

> @key_label, [Required]. The key context label to store values.  
> @key_value, [Required]. The key pair value.

Adds to local memory a new key-value context key. The method inputs must be char pointers. The method allows to store up to 10 key-value pairs.

```
void getContext(char *context)
```

> @context, [Required]. A char pointer where the context will be stored.

Builds the context according to the chosen protocol and stores it in the context char pointer.

```
void setDebug(bool debug)
```

> @debug, [Required]. Boolean type to turn off/on debug messages.

Makes available debug messages through the serial port.

```
bool send(const char* device_label, const char* device_name);
```

> @device_label, [Optional], [Default] = Device's MAC Address. The device label to send data. If not set, the device's MAC address will be used.  
> @device_name, [Optional], [Default] = @device_label. The device name otherwise assigned if the device doesn't already exist in your Ubidots account. If not set, the device label parameter will be used. **NOTE**: Device name is only supported through TCP/UDP, if you use another protocol, the device name will be the same as device label.  

Sends all the data added using the add() method. Returns true if the data was sent.


```
bool wifiConnect(const char* ssid, const char* password)
```

> @ssid, [Optional], [Required]. WiFi SSID to connect to name.  
> @password, [Required]. WiFi password credential.

Attempts to connect to the cloud using WiFi with the specified credentials.

```
bool wifiConnectSettings(IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet)
```

> @ip, [Required]. Static IP to request from the router/gateway
> @dns, [Required]. Custom DNS 
> @gateway, [Required]. Router/Gateway Ip address 
> @subnet, [Required]. Subnet mask to request from the Router/Gateway  

Configure the internal WiFi module to perform a connection to the WiFi with fixed ip, subnet, gateway and dns.

```
bool wifiConnected()
```
Returns true if the device is connected to the cloud using WiFi.

```
bool serverConnected();
```
Returns true if the device has a socket opened with Ubidots.

# Examples

Refer to the ![examples](https://github.com/ubidots/ubidots-CC3200/tree/master/examples) folder
