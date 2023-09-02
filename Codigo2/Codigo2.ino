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

constexpr uint8_t VELOCIDAD = 130;

// La velocidad del sonido en cm/us (centimetros por microsegundos)
constexpr float VELOCIDAD_DEL_SONIDO = 0.34027 / 10;
// Maxima distancia a leer en cm (centimetros)
constexpr float MAX_DIST = 25;
// Tiempo que tarda el sonido en recorer 2 cm (centimetros)
constexpr unsigned long TIEMPO_PARA_2CM = (unsigned long)((2.0 / VELOCIDAD_DEL_SONIDO) * 10) % 10 >= 5 ? 2.0 / VELOCIDAD_DEL_SONIDO + 1 : 2.0 / VELOCIDAD_DEL_SONIDO;  // Round the number
// Tiempo máximo para leer en us (microsegundos)
constexpr unsigned long TIEMPO_MAX_LECTURA = MAX_DIST * TIEMPO_PARA_2CM * 2;
// Tiempo entre lecturas en ms (milisegundos)
constexpr unsigned long TIEMPO_POR_LECTURA = TIEMPO_MAX_LECTURA / 1000 + 3;

unsigned long ultima_dist;


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
  ultima_dist = millis();
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

  if (analogRead(TATAMI_L) < 450) {
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    delay(2);
    analogWrite(MTR_L_ATRAS, 160);
    analogWrite(MTR_R_ATRAS, 255);
    delay(500);
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 255);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    delay(10);
  }
  if (analogRead(TATAMI_R) < 450) {
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    delay(2);
    analogWrite(MTR_L_ATRAS, 255);
    analogWrite(MTR_R_ATRAS, 160);
    delay(500);
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 255);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    delay(10);
  } else if (analogRead(TATAMI_R) < 450 || analogRead(TATAMI_L) < 450) {
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    delay(2);
    analogWrite(MTR_L_ATRAS, 255);
    analogWrite(MTR_R_ATRAS, 255);
    delay(500);
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, 255);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    delay(10);
  }
  static unsigned long izq = ultra(TRIG, 4);
  static unsigned long cen = ultra(TRIG, 5);
  static unsigned long der = ultra(TRIG, 6);
  if (millis() - ultima_dist > TIEMPO_POR_LECTURA) {
    izq = ultra(TRIG, 4);
    cen = ultra(TRIG, 5);
    der = ultra(TRIG, 6);
    ultima_dist = millis();
  }

  bool girando = false;

  if (cen != 0) {
    Serial.println("Adelante");
    analogWrite(MTR_L_ADELANTE, VELOCIDAD);
    analogWrite(MTR_R_ADELANTE, VELOCIDAD);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    girando = false;
  } else if (izq != 0) {
    Serial.println("Izquierda");
    analogWrite(MTR_L_ADELANTE, VELOCIDAD);
    analogWrite(MTR_R_ADELANTE, 0);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    girando = true;
  } else if (der != 0) {
    Serial.println("Derecha");
    analogWrite(MTR_L_ADELANTE, 0);
    analogWrite(MTR_R_ADELANTE, VELOCIDAD);
    analogWrite(MTR_L_ATRAS, 0);
    analogWrite(MTR_R_ATRAS, 0);
    girando = true;
  } else {
    Serial.println("Ninguno");
    if (girando == false) {
      analogWrite(MTR_L_ADELANTE, 0);
      analogWrite(MTR_R_ADELANTE, VELOCIDAD);
      analogWrite(MTR_L_ATRAS, 0);
      analogWrite(MTR_R_ATRAS, 0);
      girando = true;
    }
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
