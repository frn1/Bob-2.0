constexpr uint8_t MTR_L_ADELANTE = A3;
constexpr uint8_t MTR_L_ATRAS = A0;
constexpr uint8_t MTR_R_ADELANTE = A1;
constexpr uint8_t MTR_R_ATRAS = A2;


constexpr uint8_t TRIG = 3;
constexpr uint8_t ECHO = 6;

constexpr uint8_t TATAMI_L = 9;
constexpr uint8_t TATAMI_R = 10;
constexpr uint8_t BOT_COMIENZO = 12;

constexpr uint8_t LED = LED_BUILTIN;

constexpr uint8_t VELOCIDAD = 130;

#ifndef ARDUINO_ARCH_AVR
#include "src/gcem/include/gcem.hpp"

// Densidad del aire en kg/m^3 (Kilogramos por metro cúbico)
constexpr float DENSIDAD_AIRE = 1.225;
// Masa molar del aire en kg/mol (Kilogramos por mol)
constexpr float MASA_MOLAR_AIRE = 28.9644 / 1000;
// Aceleración gravitacional en m/s^2 (Metros por segundos cuadrados)
constexpr float GRAVEDAD = 9.79701;
// La altitud actual del robot en m (Metros)
constexpr float ALTITUD = 77;
// La altitud donde se midió la presión en m (Metros)
constexpr float ALTITUD_REFERENCIA = 0;
// La temperatura actual en K (Kelvins)
// Conversión: °C + 273.15 = K
constexpr float TEMPERATURA = 300.15;
// La temperatura cuando se midió la presion en K (Kelvins)
// Conversión: °C + 273.15 = K
constexpr float TEMPERATURA_REFERENCIA = 287.15;  // 14 °C
// La constante universal del gas en J/(mol K) (Joules por mol kelvin)
constexpr float CONSTANTE_GAS_UNIVERSAL = 0.00831446261815324;
// La presión del aire de referencia en Pa (Pascales)
constexpr float PRESION_REFERENCIA = 101325;
// La presión del aire actual en Pa (Pascales)
constexpr float PRESION = PRESION_REFERENCIA * gcem::exp(-GRAVEDAD * MASA_MOLAR_AIRE * (ALTITUD - ALTITUD_REFERENCIA) / (CONSTANTE_GAS_UNIVERSAL * TEMPERATURA_REFERENCIA));
// El indice adibatico (7/5 para diatómico, 5/3 para monoatómico)
constexpr float INDICE_ADIBATICO = 7.0 / 5.0;
// La velocidad del sonido en cm/us (centimetros per microsegundos)
constexpr float VELOCIDAD_DEL_SONIDO = gcem::sqrt((INDICE_ADIBATICO * PRESION) / DENSIDAD_AIRE) / 10000;
#else
// La velocidad del sonido en cm/us (centimetros por microsegundos)
constexpr float VELOCIDAD_DEL_SONIDO = 0.34027 / 10;
#endif
// Maxima distancia a leer en cm (centimetros)
constexpr float MAX_DIST = 40;
// Tiempo que tarda el sonido en recorer 2 cm (centimetros)
constexpr unsigned long TIEMPO_PARA_2CM = (unsigned long)((2.0 / VELOCIDAD_DEL_SONIDO) * 10) % 10 >= 5 ? 2.0 / VELOCIDAD_DEL_SONIDO + 1 : 2.0 / VELOCIDAD_DEL_SONIDO;  // Round the number
// Tiempo máximo para leer en us (microsegundos)
constexpr unsigned long TIEMPO_MAX_LECTURA = MAX_DIST * TIEMPO_PARA_2CM * 3;
// Tiempo entre lecturas en ms (milisegundos)
constexpr unsigned long TIEMPO_POR_LECTURA = TIEMPO_MAX_LECTURA / 1000 + 10;

void setup() {
  Serial.begin(115200);
  pinMode(MTR_L_ADELANTE, OUTPUT);
  pinMode(MTR_L_ATRAS, OUTPUT);
  pinMode(MTR_R_ADELANTE, OUTPUT);
  pinMode(MTR_R_ATRAS, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(TATAMI_L, INPUT);
  pinMode(TATAMI_R, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BOT_COMIENZO, INPUT_PULLUP);

  while (BOT_COMIENZO == HIGH) {}
  while (BOT_COMIENZO == LOW) {}

  Serial.println("Vamos en 5!");
  for (uint8_t i = 0; i < 5; i++) {
    Serial.print(5 - i);
    Serial.println("...");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  analogWrite(MTR_L_ADELANTE, 0);
  analogWrite(MTR_R_ADELANTE, VELOCIDAD);
  analogWrite(MTR_L_ATRAS, 0);
  analogWrite(MTR_R_ATRAS, 0);
}

unsigned long ultra(uint8_t trig, uint8_t echo) {
  unsigned long t;  //timepo que demora en llegar el eco
  unsigned long d;  //distancia en centimetros

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(trig, LOW);

  t = pulseIn(echo, HIGH, TIEMPO_MAX_LECTURA);  //obtenemos el ancho del pulso
  d = t / TIEMPO_PARA_2CM;                      //escalamos el tiempo a una distancia en cm
  return d;
}

void loop() {

  Serial.println(analogRead(TATAMI_R));
  Serial.println(analogRead(TATAMI_L));

  if (analogRead(TATAMI_R) < 450) {
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 255);
    delay(400); 
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 255);
    analogWrite(MTR_L_ATRAS, VELOCIDAD);
    analogWrite(MTR_R_ATRAS, 0);
    delay(10);
  }
  static unsigned long ultima_dist = millis();
  static unsigned long izq = ultra(TRIG, 4);
  static unsigned long cen = ultra(TRIG, 5);
  static unsigned long der = ultra(TRIG, 6);
  if (millis() - ultima_dist > TIEMPO_POR_LECTURA) {
    izq = ultra(TRIG, 4);
    cen = ultra(TRIG, 5);
    der = ultra(TRIG, 6);
    ultima_dist = millis();
  }

  if (cen != 0) {
    Serial.println("Adelante");
    analogWrite(MTR_L_ADELANTE, VELOCIDAD);
    analogWrite(MTR_R_ADELANTE, VELOCIDAD);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
  } else if (izq != 0) {
    Serial.println("Izquierda");
    analogWrite(MTR_L_ADELANTE, VELOCIDAD);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
  } else if (der != 0) {
    Serial.println("Derecha");
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, VELOCIDAD);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
  } else {
    Serial.println("Ninguno");
  }
  // if (ult != 0 && ult <= 60) {

  //   analogWrite(MTR_L_ADELANTE, 255);
  //   analogWrite(MTR_R_ADELANTE, 255);
  //   analogWrite(MTR_L_ATRAS, 0);
  //   analogWrite(MTR_R_ATRAS, 0);
  // } else {
  //   analogWrite(MTR_L_ADELANTE, 255);
  //   analogWrite(MTR_R_ADELANTE, 0);
  //   analogWrite(MTR_L_ATRAS, 0);
  //   analogWrite(MTR_R_ATRAS, 0);
  // }
}
