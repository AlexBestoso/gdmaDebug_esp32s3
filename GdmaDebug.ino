#include <Arduino.h>
#include <cstdint>
#include <src/GdmaDebug.h>

GdmaDebug gdbg;

void setup() {
  Serial.begin(115200);
  Serial.printf("Running the thing....\n");
  delay(2000);

  gdbg.channel = 0;

  gdbg.init_date();
  gdbg.print_date(false);

  gdbg.date.gdma_date = 0x1234;
  gdbg.print_date(false);

  gdbg.patch_date(true);
  

}

void loop() {
  gdbg.refresh();
  gdbg.print_date(false);
  delay(60000);
}
