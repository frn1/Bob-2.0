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

// Gas density in kg/m^3 (Kilogram per meter cubed)
constexpr float DENSIDAD_AIRE = 1.225;
// Molar mass of air in kg/mol (Kilograms per mole)
constexpr float MASA_MOLAR_AIRE = 28.9644 / 1000;
// Gravity   in m/s^2 (Meters per second squared)
constexpr float GRAVEDAD = 9.79701;
// The ALTITUD the robots currently at in m (Meters)
constexpr float ALTITUD = 77;
// The ALTITUD where the reference was measured in m (Meters)
constexpr float ALTITUD_REFERENCIA = 0;
// The current temperature the robots is currently in K (Kelvins)
constexpr float TEMPERATURE = 283.2;  // 10 °C
// The temperature at the place the reference was measured in K (Kelvins)
constexpr float TEMPERATURE_REFERENCE = 287.15;  // 14 °C
// The Universal Gas Constant in J/(mol K) (Joules per mole kelvin)
constexpr float UNIVERSAL_GAS_CONSTANT = 0.00831446261815324;
// Gas pressure at the place where the reference was measured in Pa (Pascals)
constexpr float PRESSURE_REFERENCE = 101325;
// Gas pressure at current height in Pa (Pascals)
constexpr float PRESSURE = PRESSURE_REFERENCE * gcem::exp(-GRAVEDAD * MASA_MOLAR_AIRE * (ALTITUD - ALTITUD_REFERENCIA) / (UNIVERSAL_GAS_CONSTANT * TEMPERATURE_REFERENCE));
// Gas adibatic index (7/5 for diatomic, 5/3 for monatomic)
constexpr float ADIBATIC_INDEX = 7.0 / 5.0;
// The speed of sound in mm/us (millimeters per microseconds)
constexpr float SPEED_OF_SOUND = gcem::sqrt((ADIBATIC_INDEX * PRESSURE) / DENSIDAD_AIRE) / 1000;
// Maximum distance to read in mm (millimeters)
constexpr float MAX_DIST = 700;
// Time it takes for sound to move 2 mm (millimeters)
constexpr unsigned long TIME_PER_MM = 2.0 / SPEED_OF_SOUND;
// Timeout for a reading in us (microseconds)
constexpr unsigned long TIMEOUT_DIST = MAX_DIST * TIME_PER_MM * 3;
// Time between readings in ms (milliseconds)
constexpr unsigned long TIME_PER_READING_DIST = TIMEOUT_DIST / 1000 + 1;

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

  t = pulseIn(echo, HIGH, TIMEOUT_DIST);  //obtenemos el ancho del pulso
  d = t / TIME_PER_MM;                     //escalamos el tiempo a una distancia en cm
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
