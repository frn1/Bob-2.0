#include "../../config.h"

#if ESTRATEGIA == STRAT_EMPUJE

#include "../estrategia.h"

#include "../../motores/motores.h"

#include "strat.h"

void setupEstrategia()
{
  // Nada...
}

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPiso)
{
  dprintln("STRAT DE BUSCAR Y MATAR >:(");
  if (lecturaPiso > 500)
  {
    actualizarMotores(Direccion::Atras, 255);
    delay(300);
  }
  
  if (distanciaAdelante < 150 && distanciaAdelante != 0)
  {
    actualizarMotores(Direccion::Adelante, 255);
  }
  else
  {
    actualizarMotores(Direccion::Derecha, 255);
  }
}

#endif