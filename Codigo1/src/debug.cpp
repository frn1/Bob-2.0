#include "config.h"

#ifdef DEBUG

#include "debug.h"

#include "sensores/piso.h"
#include "sensores/ultrasonido.h"

void printDebugInfo()
{
  dprint("SENSORES PISO: ");
  for (size_t i = 0; i < N_PISO; i++)
  {
    dprint(leerPiso(i));
    dprint('\t');
  }
  dprintln();

  dprint("SENSORES ULTRASONICO: ");
  for (size_t i = 0; i < N_PISO; i++)
  {
    dprint(leerUlt(i));
    dprint('\t');
  }
  dprintln();
}

#else

inline void printDebugInfo()
{
  // No estamos en modo DEBUG asi que...
}

#endif