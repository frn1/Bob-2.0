#include "config.hpp"

#ifdef DEBUG

#include "debug.hpp"

#include "sensores/piso.hpp"
#include "sensores/ultrasonido.hpp"

void printDebugInfo()
{
  dprint("SENSORES PISO: ");
  for (size_t i = 0; i < N_PISO; i++)
  {
    dprint(leerPiso(i));
    dprint(' ');
  }
  dprintln();

  dprint("SENSORES ULTRASONICO: ");
  for (size_t i = 0; i < N_ULTS; i++)
  {
    dprint(leerUlt(i)->get());
    dprint(' ');
  }
  dprintln();
}

#else

void printDebugInfo()
{
  // No estamos en modo DEBUG asi que...
}

#endif