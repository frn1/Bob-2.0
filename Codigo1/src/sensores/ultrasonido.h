#include <Arduino.h>
#include <NewPing.h>
#include <Smoothed.h>

#include "../config.h"

#ifndef ULT_DEF
#define ULT_DEF

// La distancia leida en cada ultrasonido
extern Smoothed<uint16_t> distanciasUlts[N_ULTS];

extern NewPing sensoresUlts[N_ULTS];

// Setup un sensor ultrasonido
inline void setupUlt(uint8_t n_sensor, uint8_t trig, uint8_t echo)
{
  distanciasUlts[n_sensor] = Smoothed<uint16_t>();
  distanciasUlts[n_sensor].begin(SMOOTHED_EXPONENTIAL, 6);
  sensoresUlts[n_sensor] = NewPing(trig, echo, MAX_DIST);
}

// Setup todos los sensores ultrasonido
inline void setupUlt()
{
  for (size_t i = 0; i < N_ULTS; i++)
  {
    setupUlt(i, ULTS_TRIG[i], ULTS_ECHO[i]);
  }
}

// Leer la distancia de ese ultrasonido
inline Smoothed<uint16_t> *leerUlt(uint8_t numero)
{
  return &distanciasUlts[numero];
}

void loopUlt();

#endif
