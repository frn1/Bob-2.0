#include <Arduino.h>

#ifndef CONFIG_H
#define CONFIG_H

// Pines para la dirección de los motores
constexpr uint8_t MTR_L_ADELANTE = NOT_A_PIN;
constexpr uint8_t MTR_L_ATRAS = NOT_A_PIN;
constexpr uint8_t MTR_R_ADELANTE = NOT_A_PIN;
constexpr uint8_t MTR_R_ATRAS = NOT_A_PIN;

// Los pines de PWM para los motores
constexpr uint8_t MTR_R_PWM = NOT_A_PIN;
constexpr uint8_t MTR_L_PWM = NOT_A_PIN;

// La cantidad de sensores de piso
constexpr uint8_t N_PISO = 1;

// Los pines para los sensores del piso
constexpr uint8_t PISO_PINS[N_PISO] = {A0};

// La cantidad de ultrasonicos
constexpr uint8_t N_ULTS = 1;

// Los pines para los ultrasonidos
// 
// El primero es de la izquierda, el segundo el del frente y
// el tercero el de la derecha
constexpr uint8_t ULTS_TRIG[N_ULTS] = {3};
constexpr uint8_t ULTS_ECHO[N_ULTS] = {4};

// Distancia máxima para cada sensor ultrasonido en cm
constexpr uint16_t MAX_DIST = 175;

// El intervalo del ping para cada ultrasonido en ms
constexpr int PING_INTERVALO = 20;

// La estrategia a utilizar
//
// Escribir en minuscula el nombre
//
#define ESTRATEGIA simple

#endif