#include "src/config.hpp"

#include "src/debug.hpp"

#include "src/sensores/ultrasonido.hpp"
#include "src/sensores/piso.hpp"

#include "src/motores/motores.hpp"

#include "src/estrategias/estrategia.hpp"

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
  loopEstrategia(leerUlt(0)->get(), leerUlt(1)->get(), leerUlt(2)->get(), leerPiso(0), leerPiso(1));
  printDebugInfo();
}
