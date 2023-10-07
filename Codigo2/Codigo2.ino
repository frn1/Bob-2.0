#include <FastGPIO.h>  // https://github.com/pololu/fastgpio-arduino
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
  FastGPIO::Pin<MTR_L_ADELANTE>::setOutput(false);
  FastGPIO::Pin<MTR_R_ADELANTE>::setOutput(false);
  FastGPIO::Pin<MTR_L_ATRAS>::setOutput(false);
  FastGPIO::Pin<MTR_R_ATRAS>::setOutput(false);
  // pinMode(MTR_L_ADELANTE, OUTPUT);
  // pinMode(MTR_L_ATRAS, OUTPUT);
  // pinMode(MTR_R_ADELANTE, OUTPUT);
  // pinMode(MTR_R_ATRAS, OUTPUT);

  parar();
}

/*****ULTRASONICOS****/

#define HABILITAR_CNYL
#define HABILITAR_CNYR

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
  FastGPIO::Pin<TRIG>::setOutputLow();
  FastGPIO::Pin<ECHO_L>::setInput();
  FastGPIO::Pin<ECHO_C>::setInput();
  FastGPIO::Pin<ECHO_R>::setInput();
  // pinMode(ECHO_L, INPUT);
  // pinMode(ECHO_C, INPUT);
  // pinMode(ECHO_R, INPUT);

  izq = ultra<TRIG, ECHO_L>();
  cen = ultra<TRIG, ECHO_C>();
  der = ultra<TRIG, ECHO_R>();
}

// Medir distancia del ultrasonido
template<uint8_t trig, uint8_t echo>
unsigned long ultra() {
  unsigned long t;  //timepo que demora en llegar el eco
  unsigned long d;  //distancia en centimetros

  FastGPIO::Pin<trig>::setOutputHigh();
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  FastGPIO::Pin<trig>::setOutputLow();

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

// Estrategias disponibles:
// * ```ESTRATEGIA_2```: En desarrollo
// * ```ESTRATEGIA_1_MIRKO```: La original pero Mirko >:(
// * ```ESTRATEGIA_1```: La original
// La versión Mirko me hizo enojar >:(
#define ESTRATEGIA_1

// Boton para inciar el código
// No está implementado por ahora
constexpr uint8_t BOT_COMIENZO = 12;
// Led para lo que quieras
constexpr uint8_t LED = 7;

void setup() {
  // Serial.begin(115200);
  setupMotor();
  setupUltra();
  setupPiso();
  FastGPIO::Pin<LED>::setOutputHigh();
  FastGPIO::Pin<BOT_COMIENZO>::setInputPulledUp();

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

  // Inicializar timer de los ultrasonidos
  ultima_medicion_dist = millis();

  delay(5000);
}

// Código para evitar que se caiga
// TODO: Hacerlo más lindo
void evitarBlanco() {
#ifdef HABILITAR_CNYL
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
  } else
#endif
#ifdef HABILITAR_CNYR
    if (analogRead(CNY_R) < 450) {
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
  } else
#endif
    if (
#ifdef HABILITAR_CNYR
      analogRead(CNY_R) < 450
#ifdef HABILITAR_CNYL
      ||
#endif
#endif
#ifdef HABILITAR_CNYL
      analogRead(CNY_L) < 450
#endif
    ) {
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
  evitarBlanco();

  if (millis() - ultima_medicion_dist > TIEMPO_POR_LECTURA) {
    izq = ultra<TRIG, ECHO_L>();
    cen = ultra<TRIG, ECHO_C>();
    der = ultra<TRIG, ECHO_R>();
    ultima_medicion_dist = millis();
  }


#ifdef ESTRATEGIA_2

#elif ESTRATEGIA_1_MIRKO
  static enum Estados {
    GirandoR,
    GirandoL,
    Matando,
  } estado;

  switch (estado) {
    case GirandoR:
      if (cen != 0) {
        estado = Estados::Matando;
      } else if (izq != 0) {
        estado = Estados::GirandoL;
      }
      derecha();
      break;
    case GirandoL:
      if (cen != 0) {
        estado = Estados::Matando;
      } else if (der != 0) {
        estado = Estados::GirandoR;
      }
      izquierda();
      break;
    case Matando:
      if (izq != 0) {
        estado = Estados::GirandoL;
      } else if (der != 0) {
        estado = Estados::GirandoR;
      }
      adelante();
  }
#else
  static bool girando = false;

  if (cen != 0) {
    // Serial.println("Adelante");
    adelante();
    girando = false;
  } else if (izq != 0) {
    // Serial.println("Izquierda");
    izquierda();
    girando = true;
  } else if (der != 0) {
    // Serial.println("Derecha");
    derecha();
    girando = true;
  } else {
    // Serial.println("Ninguno");
    if (girando == false) {
      derecha();
      girando = true;
    }
  }
#endif
}