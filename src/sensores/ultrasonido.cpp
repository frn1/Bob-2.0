#include <Arduino.h>

#include "src/config.h"

#include "ultrasonido.h"

inline void setupUlt(uint8_t izq, uint8_t adel, uint8_t der) {
    pinMode(izq, INPUT);
    pinMode(adel, INPUT);
    pinMode(der, INPUT);
}

inline void setupUlt() {
    setupUlt(ULT_I, ULT_A, ULT_D);
}