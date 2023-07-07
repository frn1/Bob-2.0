#include "../config.h"

#include "piso.h"

Smoothed<uint16_t> lecturasPiso[N_PISO];

void loopPiso()
{
  for (size_t i = 0; i < N_PISO; i++)
  {
    lecturasPiso[i].add(analogRead(PISO_PINS[i]));
  }
}
