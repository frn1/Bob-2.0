#include "src/config.h"

#include "src/sensores/ultrasonido.h"
#include "src/sensores/piso.h"
#include "src/motores/motores.h"
#include "src/estrategias/estrategia.h"

void setup()
{
  Serial.begin(115200);
  setupEstrategia();
  setupUlt();
}

void loop()
{
  loopUlt();
  loopPiso();
  loopEstrategia(0, leerUlt(0), 0, leerPiso(0));
  // Serial.println(leerSensor(0));
}
