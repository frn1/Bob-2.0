#include "config.hpp"

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

// Setup debug
inline void setupDebug()
{
  Serial.begin(DEBUG_BAUD_RATE);
}

// Imprimir info de debug
void printDebugInfo();

// Imprimir dato debug
template <typename T>
inline void dprint(T a)
{
  Serial.print(a);
}

// Imprimir línea nueva
inline void dprintln()
{
  Serial.println();
}

// Imprimir dato debug con línea nueva
template <typename T>
inline void dprintln(T a)
{
  Serial.println(a);
}

#else

// Debug está desabilitado
inline void setupDebug() {}

// Debug está desabilitado
void printDebugInfo();

// Debug está desabilitado
template <typename T>
inline void dprint(T a) {}

// Debug está desabilitado
template <typename T>
inline void dprintln(T a) {}

// Debug está desabilitado
inline void dprintln() {}

#endif

#endif