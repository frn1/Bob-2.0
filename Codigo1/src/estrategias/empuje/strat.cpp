#include "../../config.h"

#if ESTRATEGIA == STRAT_EMPUJE

#include "../estrategia.h"

#include "../../motores/motores.h"

#include "strat.h"

void setupEstrategia()
{
  // Nada...
}

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPisoL, uint16_t lecturaPisoR)
{
  dprintln("STRAT DE BUSCAR Y MATAR >:(");
  if (lecturaPisoL < 500 || lecturaPisoR < 500)
  {
    actualizarMotores(Direccion::Atras, 200);
    delay(200);
  }
  
  if (distanciaAdelante < 100 && distanciaAdelante != 0)
  {
    actualizarMotores(Direccion::Adelante, 140);
  }
  else
  {
    actualizarMotores(Direccion::Derecha, 130);
  }
}

#endif