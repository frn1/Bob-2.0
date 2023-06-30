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
  setupMotores();
}

void loop()
{
  loopUlt();
  loopPiso();
  loopEstrategia(leerUlt(0)->get(), leerUlt(1)->get(), leerUlt(2)->get(), leerPiso(0));
  // printDebugInfo();
}
