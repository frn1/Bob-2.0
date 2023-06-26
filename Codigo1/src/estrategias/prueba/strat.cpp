#include "../../config.h"

#if ESTRATEGIA == STRAT_PRUEBA

#include "../estrategia.h"

#include "../../motores/motores.h"

#include "strat.h"

void setupEstrategia()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void testMotores(Direccion dir) {
  actualizarMotores(dir, 255);
  delay(250);
  actualizarMotores(dir, 255 / 3);
  delay(250);
}

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPiso)
{
  dprintln("STRAT DE PRUEBA");
  digitalWrite(LED_BUILTIN, HIGH);
  actualizarMotores(Direccion::Adelante, 255);
  // testMotores(Direccion::Adelante);
  // testMotores(Direccion::Izquierda);
  // testMotores(Direccion::Derecha);
  // testMotores(Direccion::Atras);
}

#endif