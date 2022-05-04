#include <DHT.h>

//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define RL1 32

#define DHTPIN 15

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(115200);
  pinMode(RL1, OUTPUT);
  digitalWrite(RL1, HIGH);
  dht.begin();
  lcd.init();                      // initialize the lcd 
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("Ywrobot Arduino!");
  delay(2000);
  digitalWrite(RL1, LOW);
  delay(5000);
  digitalWrite(RL1, HIGH);
  
}


void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  Serial.print("Umidade: ");
  Serial.println(h);
  float t = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.println(t);

  
}
