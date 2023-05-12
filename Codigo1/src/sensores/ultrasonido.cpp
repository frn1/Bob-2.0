#include <Arduino.h>
#include <NewPing.h>

#include "../config.h"

#include "ultrasonido.h"

NewPing sensoresUlts[N_ULTS] = {NewPing(NOT_A_PIN, NOT_A_PIN)};

uint16_t distanciasUlts[N_ULTS] = {0};

unsigned long pingTimer[N_ULTS];

uint8_t currentSensor = 0;

void checkEcho()
{
  if (sensoresUlts[currentSensor].check_timer())
    distanciasUlts[currentSensor] = sensoresUlts[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void loopUlt()
{
  for (uint8_t i = 0; i < N_ULTS; i++)
  {
    if (millis() >= pingTimer[i])
    {
      pingTimer[i] += PING_INTERVALO * N_ULTS;
      sensoresUlts[currentSensor].timer_stop();
      currentSensor = i;
      distanciasUlts[currentSensor] = 0;
      sensoresUlts[currentSensor].ping_timer(checkEcho);
    }
  }
}