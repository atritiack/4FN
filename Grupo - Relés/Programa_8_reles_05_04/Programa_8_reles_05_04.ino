#include <DHT.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define RL1 32
#define RL2 33
#define RL3 25
#define RL4 26
#define RL5 27
#define RL6 14
#define RL7 12
#define RL8 13

#define DHTPIN 15

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(115200);
  
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);
  pinMode(RL5, OUTPUT);
  pinMode(RL6, OUTPUT);
  pinMode(RL7, OUTPUT);
  pinMode(RL8, OUTPUT);
  
  digitalWrite(RL1, HIGH);
  digitalWrite(RL2, HIGH);
  digitalWrite(RL3, HIGH);
  digitalWrite(RL4, HIGH);
  digitalWrite(RL5, HIGH);
  digitalWrite(RL6, HIGH);
  digitalWrite(RL7, HIGH);
  digitalWrite(RL8, HIGH);
  delay(3000);
  digitalWrite(RL1, LOW);
  digitalWrite(RL2, LOW);
  digitalWrite(RL3, LOW);
  digitalWrite(RL4, LOW);
  digitalWrite(RL5, LOW);
  digitalWrite(RL6, LOW);
  digitalWrite(RL7, LOW);
  digitalWrite(RL8, LOW);
  delay(3000);
  digitalWrite(RL1, HIGH);
  digitalWrite(RL2, HIGH);
  digitalWrite(RL3, HIGH);
  digitalWrite(RL4, HIGH);
  digitalWrite(RL5, HIGH);
  digitalWrite(RL6, HIGH);
  digitalWrite(RL7, HIGH);
  digitalWrite(RL8, HIGH);
  
  dht.begin();
  lcd.init();                      
  
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("       4FN      ");
  lcd.setCursor(0,1);
  lcd.print(" ETEC J. STREET ");
  delay(3000);
    
}


void loop()
{
  delay(2000);
  float t = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.println(t);
  float h = dht.readHumidity();
  Serial.print("Umidade: ");
  Serial.println(h);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t,2);
  lcd.print(" C   ");
  lcd.setCursor(0,1);
  lcd.print("Umid: ");
  lcd.print(h,2);
  lcd.print(" %  ");
  lcd.setCursor(0,1);

  if(t > 28)
    {
      digitalWrite(RL1, LOW);
      Serial.println("RELE 01 LIGADO");
      post();
    }
  if(t < 26)
    {
      digitalWrite(RL1, HIGH);
      Serial.println("RELE 01 DESLIGADO");
    }
}
