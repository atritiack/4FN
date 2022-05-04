#include <WiFi.h>
#include <ThingerESP32.h>

#define USERNAME "williamolever"          //Informações do Thinger.io
#define DEVICE_ID "ESP32TCC"
#define DEVICE_CREDENTIAL "NHdQukqCXD0cPLVP"
#define SSID "casadaIsabella_2G"
#define SSID_PASSWORD "bellabella1302"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int x;

void setup() {
Serial.begin(115200);
thing.add_wifi(SSID, SSID_PASSWORD);
delay(4000);
} 

void loop() {
x = random(1000);
delay(1000);
thing["Valor"] >> outputValue(x);
thing.handle();
delay(2000);
Serial.println(x);
delay(100);
}
