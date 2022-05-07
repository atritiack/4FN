//https://thingspeak.com/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "LG K11+_9730";
const char* password = "12345678";

// #define SSID "iPhone de André"
// #define SSID_PASSWORD "bellabella1302"

const char* serverName = "http://api.thingspeak.com/update";
// Service API Key
String apiKey = "YSLB4HVFWENMA151";

String door1Status, door2Status;

void setup() {
  pinMode(22, INPUT_PULLUP);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Conectando...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado à rede WiFi com o endereço IP: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {
    
    int x = random(1000);
    delay(5000);
           
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
       
      http.begin(client, serverName);
            
      http.addHeader("Content-Type", "application/json");
      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + x + "\"}";           
      int httpResponseCode = http.POST(httpRequestData);
      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println(httpRequestData);
      http.end();
      
    }
    else {
      Serial.println("WiFi Desconectado...");
    }
    
  }





void post(){


  
}
