#include "../../config.h"

#if ESTRATEGIA == STRAT_PRUEBA_TATAMI

#include "../estrategia.h"

#include "../../motores/motores.h"

#include "strat.h"

void setupEstrategia()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPisoL, uint16_t lecturaPisoR)
{
  if (lecturaPisoL < 500 || lecturaPisoR < 500) {
    actualizarMotores(Direccion::Atras, 255);
    delay(100);
  }
  actualizarMotores(Direccion::Adelante, 255);
}

#endif