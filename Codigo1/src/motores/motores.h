#include <Arduino.h>

#include "../config.h"
#include "../debug.h"

#ifndef MOTORES_H
#define MOTORES_H

inline void setupMotores()
{
  pinMode(MTR_L_ADELANTE, OUTPUT);
  pinMode(MTR_L_ATRAS, OUTPUT);
  pinMode(MTR_R_ADELANTE, OUTPUT);
  pinMode(MTR_R_ATRAS, OUTPUT);
}

enum Direccion
{
  Nada = 0b0000,
  Derecha = 0b0010,
  Izquierda = 0b1000,
  Adelante = 0b1010,
  Atras = 0b0101,
  // Freno = 0b1111
};

extern bool lAdelSt, lAtrasSt;
extern bool rAdelSt, rAtrasSt;

extern uint8_t pwmLSt, pwmRSt;

// Actualizar los motores
inline void actualizarMotores() {
  if (lAdelSt) {
    analogWrite(pwmLSt, MTR_L_ADELANTE);
  } else {
    analogWrite(0, MTR_L_ADELANTE);
  }

  if (lAtrasSt) {
    analogWrite(pwmLSt, MTR_L_ATRAS);
  } else {
    analogWrite(0, MTR_L_ATRAS);
  }

  if (lAdelSt) {
    analogWrite(pwmLSt, MTR_L_ADELANTE);
  } else {
    analogWrite(0, MTR_L_ADELANTE);
  }

  if (lAtrasSt) {
    analogWrite(pwmLSt, MTR_L_ATRAS);
  } else {
    analogWrite(0, MTR_L_ATRAS);
  }

  // Listo :)
}

// Actualizar la dirección de los motores
inline void actualizarMotores(bool lAdel, bool lAtras, bool rAdel, bool rAtras)
{
  dprint("CAMBIO DE DIRECCION (lAdel, lAtras, rAdel, rAtras): ");
  dprint(lAdel ? "ALTO" : "bajo");
  dprint(' ');
  dprint(lAtras ? "ALTO" : "bajo");
  dprint(' ');
  dprint(rAdel ? "ALTO" : "bajo");
  dprint(' ');
  dprint(rAtras ? "ALTO" : "bajo");
  dprintln();

  lAdelSt = map(lAdel, 0, 255, 140, 255);
  lAtrasSt = map(lAtras, 0, 255, 140, 255);
  rAdelSt = map(rAdel, 0, 255, 100, 255);
  rAtrasSt = map(rAtras, 0, 255, 100, 255);

  actualizarMotores();
}

// Actualizar la dirección de los motores con el Enum
inline void actualizarMotores(Direccion dir)
{
  // Serial.println(dir);
  actualizarMotores(bitRead(dir, 0), bitRead(dir, 1), bitRead(dir, 2), bitRead(dir, 3));
}

// Actualizar la fuerza de cada motor individualmente
inline void actualizarMotores(uint8_t pwmL, uint8_t pwmR)
{
  // Serial.print(pwmL);
  // Serial.print("\t");
  // Serial.print(pwmR);
  // Serial.println();

  dprint("CAMBIO DE PWM (pwmL, pwmR): ");
  dprint(pwmL);
  dprint(' ');
  dprint(pwmR);
  dprintln();

  pwmLSt = pwmL;
  pwmRSt = pwmL;
  actualizarMotores();
}

// Actualizar la fuerza ambos motores
inline void actualizarMotores(uint8_t pwm)
{
  actualizarMotores(pwm, pwm);
}

// Actualizar la fuerza de ambos motores y la dirección
inline void actualizarMotores(Direccion dir, uint8_t pwm)
{
  actualizarMotores(dir);
  actualizarMotores(pwm);
}

// Actualizar la fuerza de cada motore y su dirección
inline void actualizarMotores(Direccion dir, uint8_t pwmL, uint8_t pwmR)
{
  actualizarMotores(dir);
  actualizarMotores(pwmL, pwmR);
}

#endif