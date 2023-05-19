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

  pinMode(MTR_R_PWM, OUTPUT);
  pinMode(MTR_L_PWM, OUTPUT);
}

enum Direccion
{
  Nada = 0b0000,
  Derecha = 0b0010,
  Izquierda = 0b1000,
  Adelante = 0b1010,
  Atras = 0b0101,
  Freno = 0b1111
};

// Actualizar la dirección de los motores
inline void actualizarMotores(bool lAdel, bool lAtras, bool rAdel, bool rAtras)
{
  dprint("CAMBIO DE MOTOR (lAdel, lAtras, rAdel, rAtras): ");
  dprint(lAdel ? "HIGH" : "low");
  dprint('\t');
  dprint(lAtras ? "HIGH" : "low");
  dprint('\t');
  dprint(rAdel ? "HIGH" : "low");
  dprint('\t');
  dprint(rAtras ? "HIGH" : "low");
  dprintln();

  digitalWrite(MTR_L_ADELANTE, lAdel);
  digitalWrite(MTR_L_ATRAS, lAtras);
  digitalWrite(MTR_R_ADELANTE, rAdel);
  digitalWrite(MTR_R_ATRAS, rAtras);
}

// Actualizar la dirección de los motores con el Enum
inline void actualizarMotores(Direccion dir)
{
  actualizarMotores(bitRead(dir, 0), bitRead(dir, 1), bitRead(dir, 2), bitRead(dir, 3));
}

// Actualizar la fuerza de cada motor individualmente
inline void actualizarMotores(uint8_t pwmL, uint8_t pwmR)
{
  dprint("CAMBIO DE MOTOR (pwmL, pwmR): ");
  dprint(pwmL);
  dprint('\t');
  dprint(pwmR);
  dprintln();

  analogWrite(MTR_L_PWM, pwmL);
  analogWrite(MTR_R_PWM, pwmR);
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