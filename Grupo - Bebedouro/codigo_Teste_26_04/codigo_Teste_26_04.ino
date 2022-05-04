#define SENSOR 2
#define RELE 11
#define LED 10

bool statusSensor, flag;

void setup() {
Serial.begin(9600);
pinMode(SENSOR, INPUT);
pinMode(RELE, OUTPUT);  
pinMode(LED, OUTPUT);  
digitalWrite(RELE, HIGH); // RELÉ DESLIGADO NA INICIALIZAÇÃO.
}

void loop() {
Serial.println("Estamos no loop");
statusSensor = digitalRead(SENSOR); // LÊ O ESTADO DO PINO DO SENSOR

if(statusSensor == 1 && flag == 0){
  flag = 1;
}
if(statusSensor == 0 && flag == 1){
  flag = 0;
  digitalWrite(RELE, LOW);
  for(int i = 0; i <= 50; i++){
    Serial.print("i = ");
    Serial.println(i);
    delay(200);
    statusSensor = digitalRead(SENSOR);
    if(statusSensor == 1)  
    {
    digitalWrite(RELE, HIGH);
    return;
    }
      
  }
  digitalWrite(RELE, HIGH);
}


  
/*
if(statusSensor == 0){  // SENSOR ÓPTICO ATIVADO (NÍVEL 0)
  digitalWrite(RELE, LOW);        // LIGA O RELÉ
  digitalWrite(LED, HIGH);        // LIGA O LED
  Serial.println("Relé ligado");
  delay(500);
}
else {                  //  SENSOR ÓPTICO DESATIVADO (NÍVEL 0)
  digitalWrite(RELE, HIGH);      // DESLIGA O RELÉ
  digitalWrite(LED, LOW);        // DESLIGA O LED
  Serial.println("Relé desligado");
  delay(500);
 */


  

}
