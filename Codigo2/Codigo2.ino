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

  t = pulseIn(echo, HIGH, 5000);  //obtenemos el ancho del pulso
  d = t / 59;                     //escalamos el tiempo a una distancia en cm
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
