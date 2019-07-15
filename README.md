# Wifi Camera Light
This code was used and tested on a NodeMCU but should work with any board that uses the ESP8266 Wifi chip

# Cable Connections
*  The 5v lead can be run on the NodeMCU's 3.3v pin
*  The Ground lead is connected to the ground pin
*  And the Led lead is connect to pin 4 (D2 on NodeMCU)

# Required Libarys
*  ESP8266WiFi
*  WiFiClient
*  ESP8266WebServer
*  Adafruit_NeoPixel

# Wifi Setup
The Wifi SSID is set here: `#define APSSID "Camera Light"`
<br/>
And the Wifi's Password is set here: `#define APSSID "Camera Light"`

# Notes
To find the webpage type `http://192.168.4.1`, into a web browser when connected to the Wifi Network
<br/><br/>
Brightness changes happen on the change after the brightness was changed
<br/>
E.G. Change to green and 50% brightness, this will keep the brightness at 100% until the next command is sent
