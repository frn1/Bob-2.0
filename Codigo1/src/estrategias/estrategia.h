#include <Arduino.h>

#include "../config.h"

#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

// Usar minusculas para los nombres
#if ESTRATEGIA == STRAT_EMPUJE

#include "empuje/strat.h"

#elif ESTRATEGIA == STRAT_FLANQUEO

#include "flanqueo/strat.h"

#elif ESTRATEGIA == STRAT_PRUEBA

#ifdef DEBUG

#warning Estás usando la estrategia de prueba

#elif

#error Estás usando la estrategia de prueba sin DEBUG

#endif

#include "prueba/strat.h"

#else

#error La estrategia elegida no existe, por favor mire el archivo src/estrategias/estrategia.h para elegir otra en el archivo de configuración src/config.h

#endif

// Setup del codigo de la estrategia
void (*setupEstrategia)() = setupStrat;

// Loop del codigo de la estrategia
void (*loopEstrategia)(uint16_t, uint16_t, uint16_t, uint16_t) = loopStrat;

#endif ESTRATEGIA_H
