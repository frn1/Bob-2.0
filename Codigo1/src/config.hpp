#include <Arduino.h>

#ifndef CONFIG_H
#define CONFIG_H

// #define DEBUG

// La velocidad en baudios para debug por serial
constexpr auto DEBUG_BAUD_RATE = 115200U;

// Pines para la dirección de los motores

constexpr uint8_t MTR_L_ADELANTE = A3;
constexpr uint8_t MTR_L_ATRAS = A0;
constexpr uint8_t MTR_R_ADELANTE = A1;
constexpr uint8_t MTR_R_ATRAS = A2;

// La cantidad de sensores de piso
constexpr uint8_t N_PISO = 2;

// Los pines para los sensores del piso
constexpr uint8_t PISO_PINS[N_PISO] = {A9, A10};

// La cantidad de ultrasonicos
constexpr uint8_t N_ULTS = 1;

// Los pines para los ultrasonidos
// 
// El primero es de la izquierda, el segundo el del frente y
// el tercero el de la derecha

// Los pines TRIG del los ultrasonidos
constexpr uint8_t ULTS_TRIG[N_ULTS] = {3};

// Los pines ECHO del los ultrasonidos
constexpr uint8_t ULTS_ECHO[N_ULTS] = {5};

// Distancia máxima para cada sensor ultrasonido en cm
constexpr auto MAX_DIST = 65U;

// El intervalo del ping para cada ultrasonido en ms
constexpr auto PING_INTERVALO = 1000U/15U;

#define STRAT_PRUEBA_TATAMI -2
#define STRAT_PRUEBA -1
#define STRAT_NADA 0
#define STRAT_EMPUJE 1
#define STRAT_FLANQUEO 2
#define STRAT_BLUETOOTH 3

// La estrategia a utilizar
#define ESTRATEGIA STRAT_BLUETOOTH

#endif
