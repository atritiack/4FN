#include <WiFi.h>
#include <ThingerESP32.h>

#define USERNAME "williamolever"          //Informações do Thinger.io
#define DEVICE_ID "ESP32TCC"
#define DEVICE_CREDENTIAL "lUS9ZF9dp%sDKxBN"
#define SSID "iPhone de André"
#define SSID_PASSWORD "bellabella1302"
//#define SSID "LG K11+_9730"
//#define SSID_PASSWORD "12345678"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int x;

void setup() {
Serial.begin(115200);
// thing.add_wifi(SSID, SSID_PASSWORD);
delay(4000);
} 

void loop() {
thing.add_wifi(SSID, SSID_PASSWORD);
delay(1500);
x = random(1000);
delay(200);
thing["Valor"] >> outputValue(x);
thing.handle();
delay(50);
Serial.println(x);
delay(100);
}
