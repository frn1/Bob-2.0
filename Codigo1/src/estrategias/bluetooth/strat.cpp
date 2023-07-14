#include "../../config.h"

#if ESTRATEGIA == STRAT_BLUETOOTH

#include "../estrategia.h"

#include "../../motores/motores.h"

#include "strat.h"

void setupEstrategia()
{
  Serial.begin(115200);
}

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPisoL, uint16_t lecturaPisoR)
{
  Serial.println("HOLA");
  switch (Serial.read())
  {
  case 'F':
    actualizarMotores(Direccion::Adelante);
    break;
  case 'B':
    actualizarMotores(Direccion::Atras);
    break;
  case 'L':
    actualizarMotores(Direccion::Izquierda);
    break;
  case 'R':
    actualizarMotores(Direccion::Derecha);
    break;
  case 'S':
    actualizarMotores(Direccion::Nada);
    break;
  case '0':
    actualizarMotores(0);
    break;
  case '1':
    actualizarMotores(0.1*255);
    break;
  case '2':
    actualizarMotores(0.2*255);
    break;
  case '3':
    actualizarMotores(0.3*255);
    break;
  case '4':
    actualizarMotores(0.4*255);
    break;
  case '5':
    actualizarMotores(0.5*255);
    break;
  case '6':
    actualizarMotores(0.6*255);
    break;
  case '7':
    actualizarMotores(0.7*255);
    break;
  case '8':
    actualizarMotores(0.8*255);
    break;
  case '9':
    actualizarMotores(0.9*255);
    break;
  case 'q':
    actualizarMotores(255);
    break;
  default:
    break;
  }
}

#endif