#include "../../config.h"

#if ESTRATEGIA == STRAT_EMPUJE

#include "../../motores/motores.h"

#include "strat.h"

void setupStrat()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loopStrat(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPiso)
{
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
    actualizarMotores(Direccion::Adelante, 255, 140);
  }
}

#endif