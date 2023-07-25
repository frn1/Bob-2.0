#include "../config.hpp"

#include "piso.hpp"

uint16_t lecturasPiso[N_PISO];

void loopPiso()
{
  for (size_t i = 0; i < N_PISO; i++)
  {
    lecturasPiso[i] = analogRead(PISO_PINS[i]);
  }
}
