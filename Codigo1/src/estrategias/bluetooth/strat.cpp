#include "../../config.hpp"

#if ESTRATEGIA == STRAT_BLUETOOTH

#include "../estrategia.hpp"

#include "../../motores/motores.hpp"

#include "strat.hpp"

#define BT Serial

void setupEstrategia()
{
  BT.begin(115200);
}

uint8_t porcentaje = 0;

void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPisoL, uint16_t lecturaPisoR)
{
  switch (BT.read())
  {
  case 'G': // Adelante Izq.
    actualizarMotores(Direccion::Adelante, map(porcentaje, 0, 10, 0, 127), map(porcentaje, 0, 10, 0, 255));
    break;
  case 'F': // Adelante
    actualizarMotores(Direccion::Adelante, map(porcentaje, 0, 10, 0, 255));
    break;
  case 'I': // Adelante Der.
    actualizarMotores(Direccion::Adelante, map(porcentaje, 0, 10, 0, 255), map(porcentaje, 0, 10, 0, 127));
    break;
  case 'H': // Atras Izq.
    actualizarMotores(Direccion::Atras, map(porcentaje, 0, 10, 0, 127), map(porcentaje, 0, 10, 0, 255));
    break;
  case 'B': // Atras
    actualizarMotores(Direccion::Atras, map(porcentaje, 0, 10, 0, 255));
    break;
  case 'J': // Atras Der.
    actualizarMotores(Direccion::Atras, map(porcentaje, 0, 10, 0, 255), map(porcentaje, 0, 10, 0, 127));
    break;
  case 'L': // Izquierda
    actualizarMotores(Direccion::Izquierda, map(porcentaje, 0, 10, 0, 255));
    break;
  case 'R': // Derecha
    actualizarMotores(Direccion::Derecha, map(porcentaje, 0, 10, 0, 255));
    break;
  case 'S': // Parar
    actualizarMotores(Direccion::Nada);
    break;
  case '0':
    porcentaje = 0;
    break;
  case '1':
    porcentaje = 1;
    break;
  case '2':
    porcentaje = 2;
    break;
  case '3':
    porcentaje = 3;
    break;
  case '4':
    porcentaje = 4;
    break;
  case '5':
    porcentaje = 5;
    break;
  case '6':
    porcentaje = 6;
    break;
  case '7':
    porcentaje = 7;
    break;
  case '8':
    porcentaje = 8;
    break;
  case '9':
    porcentaje = 9;
    break;
  case 'q':
    porcentaje = 10;
    break;
  default:
    break;
  }
}

#endif