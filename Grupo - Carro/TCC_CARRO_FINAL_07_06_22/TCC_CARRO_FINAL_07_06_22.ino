/*
 * ALARME VEICULAR , TRAVA ELETROMECANICA PARA ABRIR CAPO ATRAVES DO SENSOR BIOMETRICO
 */
// INCLUSÃO DAS BIBLIOTECAS
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <PushButton.h>

// Número do telefone do receptor do alarme com código do país
const String PHONE = "+5511960721996";

// pino RX do módulo GSM para Arduino 3
// pino TX do módulo GSM para Arduino 2
# define  rxPin  2
# define  txPin  3
SoftwareSerial sim800(rxPin,txPin);

// DEFINIÇÃO DO PINO DA CHAVE DE SELEÇÃO
#define posAlarme 5

// DEFINIÇÃO DO PINO DO BOTÃO
#define pinBot 11

// DEFINIÇÃO DO PINO DA TRAVA
#define pinTrava 4

#define Sensor 10 //definição do pino de saída do sensor PIR 
#define Buzzer 12//definição do pino de entrada do Buzzer
#define led 13// led vermelho e azul policia

bool sinal = 0;

// INSTANCIANDO OBJETOS
SoftwareSerial mySerial(7, 8);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
PushButton botao(pinBot);

// DECLARAÇÃO DAS VARIÁVEIS E FUNCOES
uint8_t numID = 1;
bool gravar=false;

uint8_t modoGravacaoID(uint8_t IDgravar);

void setup() {
  //abaixo vamos configurar cada um dos pinos como entrada ou saída de dados
  
  pinMode(posAlarme, INPUT_PULLUP);
  pinMode(Sensor, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  
  pinMode(pinTrava, OUTPUT);
  digitalWrite(pinTrava, HIGH);
  
  Serial.begin(9600);
  finger.begin(57600);
  sim800.begin(9600);
  Serial.println(" SIM800L software serial inicializado");
  sim800.println("AT");
  delay(2000);

  
  if(finger.verifyPassword()){
    Serial.println("Sensor biometrico encontrado!");
    delay(1000);
  } else {
    Serial.println("Sensor biometrico não encontrado! Verifique a conexão e reinicie o sistema");
    while(true) { 
      delay(1); 
      }
  }
  Serial.println("Fim do Setup!");
  delay(2000);
}

void loop() {
  bool y = digitalRead(posAlarme);
  
  if(y == LOW){
    Serial.println("Modo Alarme");
    modoAlarme();
  }
  else
    Serial.println("Modo Normal");
    modoNormal();
}

uint8_t modoGravacaoID(uint8_t IDgravar) {

  int p = -1;
  Serial.print("Esperando uma leitura válida para gravar #"); Serial.println(IDgravar);
  delay(2000);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Leitura concluída");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      delay(200);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro comunicação");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Erro de leitura");
      break;
    default:
      Serial.println("Erro desconhecido");
      break;
    }
  }

  // OK successo!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Leitura convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Leitura suja");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro de comunicação");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Não foi possível encontrar propriedade da digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Não foi possível encontrar propriedade da digital");
      return p;
    default:
      Serial.println("Erro desconhecido");
      return p;
  }
  
  Serial.println("Remova o dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(IDgravar);
  p = -1;
  Serial.println("Coloque o Mesmo dedo novamente");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Leitura concluída");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      delay(200);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro de comunicação");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Erro de Leitura");
      break;
    default:
      Serial.println("Erro desconhecido");
      break;
    }
  }

  // OK successo!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Leitura convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Leitura suja");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro de comunicação");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Não foi possível encontrar as propriedades da digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Não foi possível encontrar as propriedades da digital");
      return p;
    default:
      Serial.println("Erro desconhecido");
      return p;
  }
  
  // OK convertido!
  Serial.print("Criando modelo para #");  Serial.println(IDgravar);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("As digitais batem!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro de comunicação");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("As digitais não batem");
    return p;
  } else {
    Serial.println("Erro desconhecido");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(IDgravar);
  p = finger.storeModel(IDgravar);
  if (p == FINGERPRINT_OK) {
    Serial.println("Armazenado!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro de comunicação");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Não foi possível gravar neste local da memória");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Erro durante escrita na memória flash");
    return p;
  } else {
    Serial.println("Erro desconhecido");
    return p;
  }   
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  //Encontrou uma digital!
  if (finger.fingerID == 0) {
     Serial.print("Modo Administrador!");
     
     numID++;
     modoGravacaoID(numID);
     return 0; 
  
  } else {

     digitalWrite(pinTrava, LOW);
     Serial.print("ID encontrado #"); Serial.print(finger.fingerID); 
     Serial.print(" com confiança de "); Serial.println(finger.confidence);
     delay(500);
     digitalWrite(pinTrava, HIGH);
     return finger.fingerID;
  } 
}

void modoAlarme(){
  //faz a leitura do sensor de presença (retorna HIGH ou LOW)
  sinal = digitalRead(Sensor); 
  // botao.button_loop();
  if(sinal == HIGH)
    {
    // estado = ALTO;
    Serial.println ("Movimento detectado!");
    Serial.println ("Ligando....");
    delay(1000);
    sim800. println ("ATD"+PHONE+";");
    // delay(10000);
    for(int i = 0; i > 20; i++){
      Serial.print("i = ");
      Serial.println(i);
      //aciona o Buzzer
      digitalWrite(Buzzer, HIGH);
      digitalWrite(led, HIGH);
      delay(500);      
      digitalWrite(Buzzer, LOW);
      digitalWrite(led, LOW);
      delay(500);
    }
    // fim do laço for...
    }
  //LOW : nenhum movimento detectado
  else
    {
    //desativa o buzzer
    digitalWrite(Buzzer, LOW);
    digitalWrite(led, LOW);
    }
}

void modoNormal(){
  getFingerprintIDez();
}
