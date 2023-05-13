#include <Arduino.h>

#include "../config.h"

#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#if ESTRATEGIA == simple
#include "simple/stratSimple.h"

#else

#error La estrategia elegida no existe, por favor mire el archivo src/estrategias/estrategia.h para elegir otra en el archivo de configuración src/config.h

#endif

// Setup del codigo de la estrategia
void (*setupEstrategia)() = setupStrat;

// Loop del codigo de la estrategia
void (*loopEstrategia)(uint16_t, uint16_t, uint16_t, uint16_t) = loopStrat;

#endif ESTRATEGIA_H
