#define THINGER_SERIAL_DEBUG
#include <ThingerESP8266AT.h>
#include "arduino_secrets.h"

// Emulate Serial1 on pins 10/11 if HW is not present (use interrupt pins for better performance)
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(10,11); // RX, TX
#endif

ThingerESP8266AT thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL, Serial1);

void setup() {
  // open serial for debugging
  Serial.begin(115200);

  /* Notice: initialize serial for ESP8266 at your ESP8266 baud rate
   * You can change the baud rate of ESP8266 sending a command like "AT+UART_DEF=9600,8,1,0,0\r\n"
   * Test with different rates, and use the higher one that works with your setup.
   */
  Serial1.begin(9600);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  pinMode(LED_BUILTIN, OUTPUT);
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}