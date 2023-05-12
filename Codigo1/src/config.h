#include <Arduino.h>

#ifndef CONFIG_H
#define CONFIG_H

constexpr uint8_t MTR_L_ADELANTE = NOT_A_PIN;
constexpr uint8_t MTR_L_ATRAS = NOT_A_PIN;
constexpr uint8_t MTR_R_ADELANTE = NOT_A_PIN;
constexpr uint8_t MTR_R_ATRAS = NOT_A_PIN;

constexpr uint8_t MTR_R_PWM = NOT_A_PIN;
constexpr uint8_t MTR_L_PWM = NOT_A_PIN;

constexpr uint8_t N_ULTS = 1;

constexpr uint8_t N_PISO = 1;
constexpr uint8_t PISO_PINS[N_ULTS] = {A0};

// Los pines para los ultrasonidos
// 
// El primero es de la izquierda, el segundo el del frente y
// el tercero el de la derecha
constexpr uint8_t ULTS_TRIG[N_ULTS] = {3};
constexpr uint8_t ULTS_ECHO[N_ULTS] = {4};

// Distancia máxima para cada sensor en cm
constexpr uint16_t MAX_DIST = 200;
constexpr int PING_INTERVALO = 20;

#define ESTRATEGIA simple

#endif