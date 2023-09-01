#include "src/gcem/include/gcem.hpp"

constexpr uint8_t MTR_L_ADELANTE = A3;
constexpr uint8_t MTR_L_ATRAS = A0;
constexpr uint8_t MTR_R_ADELANTE = A1;
constexpr uint8_t MTR_R_ATRAS = A2;

constexpr uint8_t TRIG = 3;
constexpr uint8_t ECHO = 6;

constexpr uint8_t TATAMI_L = A9;
constexpr uint8_t TATAMI_R = A10;
constexpr uint8_t BOT_COMIENZO = 12;

constexpr uint8_t LED = LED_BUILTIN;

// Densidad del aire en kg/m^3 (Kilogramp por metro cúbico)
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
constexpr float TEMPERATURA = 283.2;
// La temperatura cuando se midió la presion en K (Kelvins)
// Conversión: °C + 273.15 = K
constexpr float TEMPERATURA_REFERENCIA = 287.15; // 14 °C
// La constante universal del gas en J/(mol K) (Joules por mol kelvin)
constexpr float CONSTANTE_GAS_UNIVERSAL = 0.00831446261815324;
// La presión del aire de referencia en Pa (Pascales)
constexpr float PRESION_REFERENCIA = 101325;
// La presión del aire actual en Pa (Pascaless)
constexpr float PRESION = PRESION_REFERENCIA * gcem::exp(-GRAVEDAD * MASA_MOLAR_AIRE * (ALTITUD - ALTITUD_REFERENCIA) / (CONSTANTE_GAS_UNIVERSAL * TEMPERATURA_REFERENCIA));
// El indice adibatico (7/5 para diatómico, 5/3 para monoatómico)
constexpr float INDICE_ADIBATICO = 7.0 / 5.0;
// La velocidad del sonido en mm/us (milimetros per microsegundos)
constexpr float VELOCIDAD_DEL_SONIDO = gcem::sqrt((INDICE_ADIBATICO * PRESION) / DENSIDAD_AIRE) / 1000;
// Maxima distancia a leer en mm (milimeters)
constexpr float MAX_DIST = 700;
// Tiempo que tarda el sonido en recorer 2 mm (milimetros)
constexpr unsigned long TIEMPO_PARA_2MM = 2.0 / VELOCIDAD_DEL_SONIDO;
// Timeout for a reading in us (microseconds)
constexpr unsigned long TIEMPO_MAX_LECTURA = MAX_DIST * TIEMPO_PARA_2MM * 3;
// Time between readings in ms (milliseconds)
constexpr unsigned long TIEMPO_POR_LECTURA = TIEMPO_MAX_LECTURA / 1000 + 1;

void setup() {
  pinMode(MTR_L_ADELANTE, OUTPUT);
  pinMode(MTR_L_ATRAS, OUTPUT);
  pinMode(MTR_R_ADELANTE, OUTPUT);
  pinMode(MTR_R_ATRAS, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BOT_COMIENZO, INPUT_PULLUP);
  Serial.begin(115200);
  while (BOT_COMIENZO == HIGH) {}
  Serial.println("Vamos en 5!");
  for (uint8_t i = 0; i < 5; i++) {
    Serial.print(5 - i);
    Serial.println("...");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

long ultra(uint8_t trig, uint8_t echo) {
  long t;  //timepo que demora en llegar el eco
  long d;  //distancia en centimetros

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(trig, LOW);

  t = pulseIn(echo, HIGH, TIEMPO_MAX_LECTURA);  //obtenemos el ancho del pulso
  d = (t / TIEMPO_PARA_2MM) / 10;                     //escalamos el tiempo a una distancia en cm
  return d;
}

void loop() {
  Serial.println(analogRead(TATAMI_R));
  if (analogRead(TATAMI_R) < 450) {
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 150);
    analogWrite(MTR_R_ATRAS, 150);
    delay(400);
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 255);
    analogWrite(MTR_L_ATRAS, 120);
    analogWrite(MTR_R_ATRAS, 0);
    delay(200);
  }
  long izq = ultra(TRIG, 4);
  long cen = ultra(TRIG, 5);
  long der = ultra(TRIG, 6);
  if (cen != 0) {
    Serial.println("Adelante");
    analogWrite(MTR_L_ADELANTE, 150);
    analogWrite(MTR_R_ADELANTE, 150);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
  } else if (izq != 0) {
    Serial.println("Izquierda");
    analogWrite(MTR_L_ADELANTE, 150);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
  } else if (der != 0) {
    Serial.println("Derecha");
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 150);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
  } else {
    Serial.println("Ninguno");
    analogWrite(MTR_L_ADELANTE, 135);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 120);
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
