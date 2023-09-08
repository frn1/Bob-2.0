/***MOTORES***/
//Inicializacion de pines

// Velocidad de los motores
//! MINIMO 130!!! SI NO NO SE MUEVE!!!
constexpr uint8_t VELOCIDAD = 130;

// Motor Izq. Adelante
constexpr uint8_t MTR_L_ADELANTE = A3;
// Motor Izq. Atras
constexpr uint8_t MTR_L_ATRAS = A0;
// Motor Der. Adelante
constexpr uint8_t MTR_R_ADELANTE = A1;
// Motor Der. Atras
constexpr uint8_t MTR_R_ATRAS = A2;

// Mover Adelante
void adelante() {
  analogWrite(MTR_L_ADELANTE, VELOCIDAD);
  analogWrite(MTR_R_ADELANTE, VELOCIDAD);
  analogWrite(MTR_L_ATRAS, 0);
  analogWrite(MTR_R_ATRAS, 0);
}

// Girar Izq.
void izquierda() {
  analogWrite(MTR_L_ADELANTE, VELOCIDAD);
  analogWrite(MTR_R_ADELANTE, 0);
  analogWrite(MTR_L_ATRAS, 0);
  analogWrite(MTR_R_ATRAS, 0);
}

// Girar Der.
void derecha() {
  analogWrite(MTR_L_ADELANTE, 0);
  analogWrite(MTR_R_ADELANTE, VELOCIDAD);
  analogWrite(MTR_L_ATRAS, 0);
  analogWrite(MTR_R_ATRAS, 0);
}

// Mover Atras
void atras() {
  analogWrite(MTR_L_ADELANTE, 0);
  analogWrite(MTR_R_ADELANTE, 0);
  analogWrite(MTR_L_ATRAS, VELOCIDAD);
  analogWrite(MTR_R_ATRAS, VELOCIDAD);
}

// Parar
void parar() {
  analogWrite(MTR_L_ADELANTE, 0);
  analogWrite(MTR_R_ADELANTE, 0);
  analogWrite(MTR_L_ATRAS, 0);
  analogWrite(MTR_R_ATRAS, 0);
}

// Setup los motores
void setupMotor() {
  pinMode(MTR_L_ADELANTE, OUTPUT);
  pinMode(MTR_L_ATRAS, OUTPUT);
  pinMode(MTR_R_ADELANTE, OUTPUT);
  pinMode(MTR_R_ATRAS, OUTPUT);

  parar();
}

/*****ULTRASONICOS****/

constexpr uint8_t TRIG = 3;
constexpr uint8_t ECHO_L = 4;
constexpr uint8_t ECHO_C = 5;
constexpr uint8_t ECHO_R = 6;

// La velocidad del sonido en cm/us (centimetros por microsegundos)
constexpr float VELOCIDAD_DEL_SONIDO = 0.34027 / 10;
// Maxima distancia a leer en cm (centimetros)
constexpr float MAX_DIST = 25;
// Tiempo que tarda el sonido en recorer 2 cm (centimetros)
constexpr unsigned long TIEMPO_PARA_2CM = (unsigned long)((2.0 / VELOCIDAD_DEL_SONIDO) * 10) % 10 >= 5 ? 2.0 / VELOCIDAD_DEL_SONIDO + 1 : 2.0 / VELOCIDAD_DEL_SONIDO;  // Redondeo
// Tiempo máximo para leer en us (microsegundos)
constexpr unsigned long TIEMPO_MAX_LECTURA = MAX_DIST * TIEMPO_PARA_2CM * 2;
// Tiempo entre lecturas en ms (milisegundos)
constexpr unsigned long TIEMPO_POR_LECTURA = TIEMPO_MAX_LECTURA / 1000 + 3;

// Ultimo tiempo de medicion de los ultrasonicos
unsigned long ultima_medicion_dist;
// Distancia del ultrasónico de la izquierda
unsigned long izq;
// Distancia del ultrasónico del centro
unsigned long cen;
// Distancia del ultrasónico de la derecha
unsigned long der;

// Setup ultrasonicos
void setupUltra() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(ECHO_C, INPUT);
  pinMode(ECHO_R, INPUT);

  izq = ultra(TRIG, ECHO_L);
  cen = ultra(TRIG, ECHO_C);
  der = ultra(TRIG, ECHO_R);
}

// Medir distancia del ultrasonido
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

/***SENSORES DE PISO***/

// CNY de piso izquierdo
constexpr uint8_t CNY_L = A9;
// CNY de piso derecho
constexpr uint8_t CNY_R = A10;

// Setup sensores de piso
void setupPiso() {
  pinMode(CNY_L, INPUT);
  pinMode(CNY_R, INPUT);
}

/***MISC.***/

// Boton para inciar el código
// No está implementado por ahora
constexpr uint8_t BOT_COMIENZO = 12;
// Led para lo que quieras
constexpr uint8_t LED = 7;

void setup() {
  Serial.begin(115200);
  setupMotor();
  setupUltra();
  setupPiso();
  pinMode(LED, OUTPUT);
  pinMode(BOT_COMIENZO, INPUT_PULLUP);

  // Esperar 5 segundos antes de prender el robot
  // Serial.println("Vamos en 5!");
  // for (uint8_t i = 0; i < 5; i++) {
  //   Serial.print(5 - i);
  //   Serial.println("...");
  //   // Prender y apagar led
  //   digitalWrite(LED, HIGH);
  //   delay(500);
  //   digitalWrite(LED, LOW);
  //   delay(500);
  // }
  delay(5000);

  // Inicializar timer de los ultrasonidos
  ultima_medicion_dist = millis();
}

// Código para evitar que se caiga
// TODO: Hacerlo más lindo
void evitarBlanco() {
  if (analogRead(CNY_L) < 450) {
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
  } else /* if (analogRead(CNY_R) < 450) {
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
  } else */
    if (/* analogRead(CNY_R) < 450 || */ analogRead(CNY_L) < 450) {
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
}

void loop() {
  Serial.println(analogRead(CNY_R));
  Serial.println(analogRead(CNY_L));

  evitarBlanco();

  if (millis() - ultima_medicion_dist > TIEMPO_POR_LECTURA) {
    izq = ultra(TRIG, ECHO_L);
    cen = ultra(TRIG, ECHO_C);
    der = ultra(TRIG, ECHO_R);
    ultima_medicion_dist = millis();
  }

  bool girando = false;

  if (cen != 0) {
    Serial.println("Adelante");
    adelante();
    girando = false;
  } else if (izq != 0) {
    Serial.println("Izquierda");
    izquierda();
    girando = true;
  } else if (der != 0) {
    Serial.println("Derecha");
    derecha();
    girando = true;
  } else {
    Serial.println("Ninguno");
    if (girando == false) {
      derecha();
      girando = true;
    }
  }
}