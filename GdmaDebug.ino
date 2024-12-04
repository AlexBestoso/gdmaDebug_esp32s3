#include <Arduino.h>
#include <cstdint>
#include <src/GdmaDebug.h>

GdmaDebug gdbg;
void setup() {
  Serial.begin(115200);
  Serial.printf("Running the thing....\n");
  delay(2000);
  gdbg.channel = 0;
  gdbg.init();
}

void loop() {
  gdbg.print(false);
  gdbg.refresh();
  delay(6000);
}
