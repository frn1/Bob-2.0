#include "src/config.h"

#include "src/debug.h"

#include "src/sensores/ultrasonido.h"
#include "src/sensores/piso.h"

#include "src/motores/motores.h"

#include "src/estrategias/estrategia.h"

void setup()
{
  setupDebug();
  setupEstrategia();
  setupUlt();
  setupPiso();
}

void loop()
{
  loopUlt();
  loopPiso();
  loopEstrategia(leerUlt(0), leerUlt(1), leerUlt(2), leerPiso(0));
  printDebugInfo();
}
