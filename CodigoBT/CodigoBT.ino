#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3);
// #define BT Serial1

constexpr uint8_t MTR_L_ADELANTE = A3;
constexpr uint8_t MTR_L_ATRAS = A0;
constexpr uint8_t MTR_R_ADELANTE = A1;
constexpr uint8_t MTR_R_ATRAS = A2;

// Tiempo máximo que tiene para enviar un latido
constexpr unsigned long MAX_TIEMPO_LATIDO = 2000;
// Tiempo por latido
constexpr unsigned long INTERVALO_LATIDO = 5000;

void setup() {
  Serial.begin(115200);
  BT.begin(9600);
  BT.setTimeout(5);
  pinMode(MTR_L_ADELANTE, OUTPUT);
  pinMode(MTR_L_ATRAS, OUTPUT);
  pinMode(MTR_R_ADELANTE, OUTPUT);
  pinMode(MTR_R_ATRAS, OUTPUT);
}

// bool esperando_latido = false;
// unsigned long comienzo_check_latido;
// unsigned long ultimo_latido = millis();

void loop() {
  // 
  // if (millis() - ultimo_latido > INTERVALO_LATIDO) {
  //   Serial.println("Estas vivo?");
  //   BT.println("_");
  //   esperando_latido = true;
  //   ultimo_latido = millis();
  //   comienzo_check_latido = millis();
  // }
  // // 
  // if (esperando_latido) {
  //   if (millis() - comienzo_check_latido > MAX_TIEMPO_LATIDO) {
  //     // No se respondió, nos vamos
  //     analogWrite(MTR_L_ADELANTE, 0);
  //     analogWrite(MTR_L_ATRAS, 0);
  //     analogWrite(MTR_R_ADELANTE, 0);
  //     analogWrite(MTR_R_ATRAS, 0);
  //     // (void)BT.readString();
  //     Serial.println("No respondes >:(");
  //     esperando_latido = false;
  //   }
  // }
  // 
  if (BT.available() != 0) {
    // if (esperando_latido) {
    //   
    //   esperando_latido = false;
    //   Serial.println("Gracias :)");
    // }

    
    int16_t motorL_raw = BT.parseInt();
    bool adelanteL = motorL_raw > 0;                             // Si se mueve adelante o atras
    uint8_t motorL = motorL_raw < 0 ? -motorL_raw : motorL_raw;  // Sacarle el signo a motorL
    if (BT.read() != ',') {
      Serial.println("Que me enviaste????");
      return;
    }

    
    int16_t motorR_raw = BT.parseInt();
    bool adelanteR = motorR_raw > 0;                             // Si se mueve adelante o atras
    uint8_t motorR = motorR_raw < 0 ? -motorR_raw : motorR_raw;  // Sacarle el signo a motorR
    if (BT.read() != '\n') {
      Serial.println("Que me enviaste????");
      return;
    }

    
    if (adelanteL) {
      Serial.print("Adelante ");
      analogWrite(MTR_L_ADELANTE, motorL);
      analogWrite(MTR_L_ATRAS, 0);
    } else {
      Serial.print("Atras ");
      analogWrite(MTR_L_ADELANTE, 0);
      analogWrite(MTR_L_ATRAS, motorL);
    }
    Serial.print(motorL);
    Serial.print(' ');
    Serial.print(motorR);
    if (adelanteR) {
      Serial.println(" Adelante");
      analogWrite(MTR_R_ADELANTE, motorR);
      analogWrite(MTR_R_ATRAS, 0);
    } else {
      Serial.println(" Atras");
      analogWrite(MTR_R_ADELANTE, 0);
      analogWrite(MTR_R_ATRAS, motorR);
    }
    // (void)Serial.readStringUntil('\n');
  }
}
