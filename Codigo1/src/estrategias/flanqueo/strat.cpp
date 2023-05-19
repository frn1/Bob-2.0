#include "../../config.h"

#if ESTRATEGIA == STRAT_FLANQUEO

#include "../../motores/motores.h"

#include "strat.h"

void setupStrat()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

enum EstadoStrat
{
  Buscando,
  Flanqueando
} estado;

uint32_t comienzoFlanqueo = 0;

void loopStrat(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPiso)
{
  if (lecturaPiso > 500)
  {
    actualizarMotores(Direccion::Atras, 255);
    delay(100);
  }

  switch (estado)
  {
  case Buscando:
    actualizarMotores(Direccion::Derecha, 255);
    if (distanciaAdelante < 150 && distanciaAdelante != 0)
    {
      comienzoFlanqueo = millis();
      estado = EstadoStrat::Flanqueando;
    }
    break;
  case Flanqueando:
    if (millis() - comienzoFlanqueo < 20) {
      actualizarMotores(Direccion::Adelante);
    }
    if (millis() - comienzoFlanqueo > 730)
    {
      estado = EstadoStrat::Buscando;
    }

    if (distanciaAdelante < MAX_DIST && distanciaAdelante != 0)
    {
      actualizarMotores(255);
    }
    else if (distanciaIzquierda < MAX_DIST && distanciaIzquierda != 0)
    {
      actualizarMotores(255, 100);
    }
    else if (distanciaDerecha < MAX_DIST && distanciaDerecha != 0)
    {
      actualizarMotores(100, 255);
    }
    else
    {
      actualizarMotores(255, 140); // Ir curvando a la izq
    }
    break;

  default:
    break;
  }

  if (distanciaAdelante < 150 && distanciaAdelante != 0)
  {
    actualizarMotores(Direccion::Adelante, 255);
  }
  else
  {
  }
}

#endif