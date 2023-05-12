#include "../config.h"

#ifndef PISO_H
#define PISO_H

extern uint16_t lecturasPiso[N_PISO];

inline void setupPiso(uint8_t n_sensor, uint8_t pin)
{
  pinMode(pin, INPUT);
  lecturasPiso[n_sensor] = 0;
}

inline void setupPiso()
{
  for (size_t i = 0; i < N_PISO; i++)
  {
    setupPiso(i, PISO_PINS[i]);
  }
}

void loopPiso();

inline uint16_t leerPiso(uint8_t n_sensor) {
  return lecturasPiso[n_sensor];
}

#endif