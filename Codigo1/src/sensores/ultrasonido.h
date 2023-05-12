#include <Arduino.h>
#include <NewPing.h>

#include "../config.h"

#ifndef ULT_DEF
#define ULT_DEF

extern uint16_t distanciasUlts[N_ULTS];

extern NewPing sensoresUlts[N_ULTS];

inline void setupUlt(uint8_t n_sensor, uint8_t trig, uint8_t echo)
{
  sensoresUlts[n_sensor] = NewPing(trig, echo, MAX_DIST);
}

inline void setupUlt()
{
  for (size_t i = 0; i < sizeof(ULTS_TRIG); i++)
  {
    setupUlt(i, ULTS_TRIG[i], ULTS_ECHO[i]);
  }
}

inline uint16_t leerUlt(uint8_t numero)
{
  return distanciasUlts[numero];
}

void loopUlt();

#endif
