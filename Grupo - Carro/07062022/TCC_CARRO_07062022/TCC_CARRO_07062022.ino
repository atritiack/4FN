
// sensor pir com modulo gsm que irar fazer ligaçao 
#include  <SoftwareSerial.h>

// Número do telefone do receptor do alarme com código do país
const String PHONE = "+5511960721996";

// pino RX do módulo GSM para Arduino 3
// pino TX do módulo GSM para Arduino 2
# define  rxPin  2
# define  txPin  3
SoftwareSerial sim800(rxPin,txPin);

// o pino ao qual o sensor pir está conectado
int pir_sensor = 10 ;

void  setup() {
  pinMode (pir_sensor, INPUT);    // inicializa o sensor como entrada
  Serial.begin(115200);          // inicializa a série

  sim800.begin(9600);
  Serial.println(" SIM800L software inicializo");

  sim800.println("AT");
  delay(1000);
}

void  loop(){

////////////////////////////////////////////// _
while(sim800.available()){
  Serial.println (sim800.readString());
}
////////////////////////////////////////////// _
while(Serial.available()) {
  sim800.println(Serial.readString());
}
////////////////////////////////////////////// _
  int val = digitalRead(pir_sensor);  // lê o valor do sensor
  if (val == HIGH) {                    // verifica se o sensor é HIGH
    // estado = ALTO;
    Serial. println ("Movimento detectado!");
    Serial. println ("Ligando....");
    delay (1000);
    sim800. println ("ATD"+PHONE+";");
    delay (10000); // atraso de 20 segundos
  }
}
