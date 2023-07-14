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
  if (lecturaPisoL < 550 || lecturaPisoR < 550) {
    actualizarMotores(Direccion::Atras, 130);
    delay(300);
  }
  actualizarMotores(Direccion::Adelante, 100);
}

#endif