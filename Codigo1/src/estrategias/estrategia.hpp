#include <Arduino.h>

#include "../config.hpp"

#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

// Usar minusculas para los nombres
#if ESTRATEGIA == STRAT_NADA

void setupStrat() {
    // Nada...
}

void loopStrat(uint16_t _, uint16_t __, uint16_t ___, uint16_t ____, uint16_t _____) {
    // Nada...
}

#else

// Setup del codigo de la estrategia
void setupEstrategia();

void loopEstrategia(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);

#endif

#endif ESTRATEGIA_H
