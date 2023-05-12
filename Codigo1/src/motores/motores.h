#include <Arduino.h>

#include "../config.h"

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

inline void actualizarMotores(bool lAdel, bool lAtras, bool rAdel, bool rAtras)
{
  digitalWrite(MTR_L_ADELANTE, lAdel);
  digitalWrite(MTR_L_ATRAS, lAtras);
  digitalWrite(MTR_R_ADELANTE, rAdel);
  digitalWrite(MTR_R_ATRAS, rAtras);
}

inline void actualizarMotores(Direccion dir)
{
  Serial.println(dir);
  actualizarMotores(bitRead(dir, 0), bitRead(dir, 1), bitRead(dir, 2), bitRead(dir, 3));
}

inline void actualizarMotores(uint8_t pwmL, uint8_t pwmR)
{
  Serial.print(pwmL);
  Serial.print("\t");
  Serial.print(pwmR);
  Serial.println();
  analogWrite(MTR_L_PWM, pwmL);
  analogWrite(MTR_R_PWM, pwmR);
}

inline void actualizarMotores(uint8_t pwm)
{
  actualizarMotores(pwm, pwm);
}


inline void actualizarMotores(Direccion dir, uint8_t pwm)
{
  actualizarMotores(dir);
  actualizarMotores(pwm);
}

inline void actualizarMotores(Direccion dir, uint8_t pwmL, uint8_t pwmR)
{
  actualizarMotores(dir);
  actualizarMotores(pwmL, pwmR);
}

#endif