#include <Arduino.h>
#include <NewPing.h>
#include <Smoothed.h>

#include "../config.hpp"

#include "ultrasonido.hpp"

Ultrasonido sensoresUlts[N_ULTS];

Smoothed<uint16_t> distanciasUlts[N_ULTS];

unsigned long ultimoCheck = millis();

void loopUlt()
{
  if (millis() - ultimoCheck >= PING_INTERVALO)
  {
    for (uint8_t i = 0; i < N_ULTS; i++)
    {
      distanciasUlts[i].add(sensoresUlts[i].ping_cm(MAX_DIST));
    }
  }
}