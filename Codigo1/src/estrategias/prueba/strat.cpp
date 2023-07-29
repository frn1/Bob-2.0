#include "../../config.hpp"

#if ESTRATEGIA == STRAT_PRUEBA

#include "../estrategia.hpp"

#include "../../motores/motores.hpp"

#include "strat.hpp"

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

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPisoL, uint16_t lecturaPisoR)
{
  dprintln("STRAT DE PRUEBA");
  digitalWrite(LED_BUILTIN, HIGH);
  testMotores(Direccion::Adelante);
  //testMotores(Direccion::Izquierda);
  //testMotores(Direccion::Derecha);
  //testMotores(Direccion::Atras);
}

#endif
