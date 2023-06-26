#include <Arduino.h>
#include <NewPing.h>

#include "../config.h"

#include "ultrasonido.h"

NewPing sensoresUlts[N_ULTS] = {
    NewPing(NOT_A_PIN, NOT_A_PIN),
    NewPing(NOT_A_PIN, NOT_A_PIN),
    NewPing(NOT_A_PIN, NOT_A_PIN)
};

uint16_t distanciasUlts[N_ULTS];

unsigned long ultimoCheck = millis();

void loopUlt()
{
  if (millis() - ultimoCheck >= PING_INTERVALO)
  {
    for (uint8_t i = 0; i < N_ULTS; i++)
    {
      distanciasUlts[i] = sensoresUlts[i].ping_cm(MAX_DIST);
    }
  }
}