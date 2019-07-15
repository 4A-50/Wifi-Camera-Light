#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

#ifndef APSSID
#define APSSID "Camera Light"
#define APPSK  "cameralight"
#endif

#define N_PIXELS  24  // Number of pixels you are using
#define LED_PIN    4  // NeoPixel LED strand is connected to GPIO #4

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);
Adafruit_NeoPixel  strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

/* Go to http://192.168.4.1 in a web browser */

const char MAIN_page[] PROGMEM = R"=====(
<html>
<head>
  <title>Camera Light</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>

<style>
div{
  margin-left: auto;
  margin-right: auto;
  text-align: center;
}
</style>

<body>
  <div>
    <h1>Select The Light Options</h1>
    <form action='http://192.168.4.1' method='POST'>
      <h2>Color:</h2>
      <input type='color' name='color' value='#00ff00'>
      <h2>Brightness:</h2>
      <input type="range" name='brightness' min="0" max="255" value="255"><br/><br/>
      <input type='submit' value='Submit' style='color: #fff; background: #42a5f5; border:0px; border-radius:3px; padding:10px;'>
    </form>
  </div>
</body>
</html>
)=====";

String webCol;
String brightnessStr;
int brightness;

void handleRoot() {
  String webpage = MAIN_page;
  server.send(200, "text/html", webpage);

  if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "brightness") {
        brightnessStr = server.arg(i);
        brightness = brightnessStr.toInt();
        strip.setBrightness(brightness);
      }
      
      if (server.argName(i) == "color") {
        webCol = server.arg(i);
        
        // Get rid of '#' and convert it to integer
        int number = (int) strtol( &webCol[1], NULL, 16);
        
        // Split them up into r, g, b values
        int r = number >> 16;
        int g = number >> 8 & 0xFF;
        int b = number & 0xFF;

        colorWipe(strip.Color(r, g, b));
      }
    }
  }
}

void setup() {
  delay(1000);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.begin();

  strip.begin();
  strip.show();
}

void loop() {
  server.handleClient();
}

void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
