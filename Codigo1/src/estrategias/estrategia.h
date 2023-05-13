#include <Arduino.h>

#include "../config.h"

#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#if ESTRATEGIA == simple
#include "simple/stratSimple.h"

// Setup del codigo de la estrategia
void (*setupEstrategia)() = setupStrat;

// Loop del codigo de la estrategia
void (*loopEstrategia)(uint16_t, uint16_t, uint16_t, uint16_t) = loopStrat;

#endif


#endif ESTRATEGIA_H
