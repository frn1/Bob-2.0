#include "src/config.hpp"

#include "src/debug.hpp"

#include "src/sensores/ultrasonido.hpp"
#include "src/sensores/piso.hpp"

#include "src/motores/motores.hpp"

#include "src/estrategias/estrategia.hpp"

void setup() {
  setupDebug();
  setupEstrategia();
  setupUlt();
  setupPiso();
  setupMotores();
}

void loop() {
#if ESTRATEGIA==STRAT_BLUETOOTH
  loopEstrategia(0, 0, 0, 0, 0);
#else
  if (millis() >= 5000) {
    loopEstrategia(0, leerUlt(0)->get(), 0, leerPiso(0), leerPiso(1));
  }
  if (millis() >= 3000) {
    loopUlt();
    loopPiso();
  }
#endif
  printDebugInfo();
}
