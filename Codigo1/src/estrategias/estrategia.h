#include <Arduino.h>

#include "../config.h"

#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#if ESTRATEGIA == simple
#include "simple/stratSimple.h"

void (*setupEstrategia)() = setupStrat;
void (*loopEstrategia)(uint16_t, uint16_t, uint16_t, uint16_t) = loopStrat;

#endif


#endif ESTRATEGIA_H
