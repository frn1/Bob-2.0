#include "../../config.h"

#include "../../motores/motores.h"

#if ESTRATEGIA == simple
void setupStrat()
{
  pinMode(LED_BUILTIN, OUTPUT);
  actualizarMotores(255);
}

void loopStrat(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPiso)
{
  if (lecturaPiso > 500)
  {
    actualizarMotores(Direccion::Atras);
    delay(300);
  }
  
  if (distanciaAdelante < 150 && distanciaAdelante != 0)
  {
    actualizarMotores(Direccion::Adelante);
  }
  else
  {
    actualizarMotores(Direccion::Derecha);
  }
}
#endif