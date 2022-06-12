#include  <SoftwareSerial.h>

//*****************************************************************
// Parâmetros do Sensor Biométrico
//*****************************************************************
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(7, 8); 
// Pinos do Sensor Biométrico
// Arduino -->  Sensor
//    8    -->   RX
//    7   -->    TX 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;
//******************************************************************

// Número do telefone do receptor do alarme com código do país
const String PHONE = "+5511982405573";

// pino RX do módulo GSM para Arduino 3
// pino TX do módulo GSM para Arduino 2
# define  rxPin  2
# define  txPin  3
SoftwareSerial sim800(rxPin,txPin);

// Definição dos pinos:
#define TRAVA 4
#define MODO 5
#define PIR 8
#define BUZZER 12
#define LED 13

bool statusModo = 0;
// Se o pino 5 estiver em HIGH, modo Normal. (Lê biometria e abre trava)
// Se o pino 5 estiver em LOW, modo Alarme. (Aguarda PIR e aciona LED e BUZZER, conforme função "Alarme")

bool valorPIR;

int sinal = 0;
int vezes = 10;

void  setup() {
  Serial.begin(9600); //Inicializando o serial monitor
  delay(50);
  
  finger.begin(57600);
  delay(50);

  Serial.println("");
  Serial.println("Inicializando!!");
  Serial.println("");
  delay(3000);
  
  inicializaBiometria();
  delay(1500);
   
  // inicializa o sensor como entrada
  
  sim800.begin(9600);
  Serial.println("SIM800L software inicializado");

  sim800.println("AT");
  delay(1000);
  
  pinMode(MODO, INPUT_PULLUP);
  pinMode(TRAVA, OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);

  // Trava desligada em HIGH
  digitalWrite(TRAVA, HIGH);
}

void inicializaBiometria(){

  if (finger.verifyPassword()) {
    Serial.println("Sensor biométrico encontrado!");
  } else {
    Serial.println("Sensor biométrico não encontrado... :(");
    while (1) { delay(1); }
  }
  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }

}


void  loop(){
  statusModo = digitalRead(MODO);
  if(statusModo == HIGH) modoNormal();
  else modoAlarme();
}

void modoNormal(){
  Serial.println("Modo Normal, aguardando biometria");
  getFingerprintID();
  int idEncontrado = finger.fingerID;
  if(idEncontrado == 100){
    Serial.println("Liberado :-) !!!!");
    delay(2000);
    Serial.println("");
    Serial.println("Trava ativada por um segundo...");
    digitalWrite(TRAVA, LOW);
    delay(1000);
    digitalWrite(TRAVA, HIGH);
    Serial.println("");
    Serial.println("Feito!");
    Serial.println("");
    idEncontrado = 0;
    finger.fingerID = 0;
    Serial.println("Aguarde...");
    Serial.println("");
    delay(2000);
  }
  delay(50);
}

void modoAlarme()
{
////////////////////////////////////////////// _
while(sim800.available()){
  Serial.println(sim800.readString());
}
////////////////////////////////////////////// _
while(Serial.available()) {
  sim800.println(Serial.readString());
}
////////////////////////////////////////////// _
 int valorPIR = digitalRead(PIR);
  if (valorPIR == HIGH) { // verifica se o sensor é HIGH // estado = ALTO;
    Serial.println ("Movimento detectado!");
    Serial.println ("Ligando....");
    delay (1000);
    sim800.println ("ATD"+PHONE+";");
    delay (5000); 
    vezes = 10;
    alarme();
    }
  else Serial.println("PIR desativado...");
}    

void alarme(){
    Serial.println("Entrando no loop do alarme...");
    delay(1000);
    while(vezes != 0)
    {
    
    Serial.print("vezes = ");
    Serial.println(vezes);
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, HIGH);
    Serial.println("Buzzer OFF / LED ON");
    delay(500);
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, LOW);
    Serial.println("Buzzer ON / LED OFF");
    delay(500);
    vezes--;
    }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  delay(1000);
  // Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
