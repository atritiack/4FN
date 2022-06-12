// sensor pir com modulo gsm que irar fazer ligaçao 
#include  <SoftwareSerial.h>

// Número do telefone do receptor do alarme com código do país
const String PHONE = "+5511982405573";

// pino RX do módulo GSM para Arduino 3
// pino TX do módulo GSM para Arduino 2
# define  rxPin  2
# define  txPin  3
SoftwareSerial sim800(rxPin,txPin);

// o pino ao qual o sensor pir está conectado
int pir_sensor = 10 ;
int Buzzer = 12;
int sinal = 0;
int led = 13;// led vermelho e azul policia
int vezes = 10;
void alarme();

void  setup() {
  Serial.begin(9600); //Inicializando o serial monitor
   
  pinMode(Buzzer,OUTPUT);
  pinMode (pir_sensor, INPUT);
  pinMode (led, OUTPUT);
  // inicializa o sensor como entrada
  Serial.begin(115200);          // inicializa a série

  sim800.begin(9600);
  Serial.println(" SIM800L software inicializo");

  sim800.println("AT");
  delay(1000);
}

void  loop(){
digitalWrite(Buzzer, HIGH);
////////////////////////////////////////////// _
while(sim800.available()){
  Serial.println (sim800.readString());
}
////////////////////////////////////////////// _
while(Serial.available()) {
  sim800.println(Serial.readString());
}
////////////////////////////////////////////// _
 int val = digitalRead(pir_sensor);
  if (val == HIGH) {                    // verifica se o sensor é HIGH // estado = ALTO;
    Serial. println ("Movimento detectado!");
    Serial. println ("Ligando....");
    delay (1000);
    sim800. println ("ATD"+PHONE+";");
    delay (5000); // atraso de 20 segundos
    vezes = 10;
    alarme();
  }
}
void alarme()
{
    while(vezes != 0)
    {
    delay(1000);
    digitalWrite(Buzzer, LOW);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(led, LOW);
    delay(500);
    vezes--;
    }
    
}
