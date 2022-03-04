
#include <stdio.h>

#include "mcp3008.h"
#include "pico/stdlib.h"
int main() {
  stdio_init_all();
  // Create spi device
  struct MCP3008* mcp3008 = init_mcp3008(0, 2, 3, 4, 5, 10000);

  while (true) {
    printf("x %d y %d x %d y %d\n", mcp3008->read(mcp3008, 1),
           mcp3008->read(mcp3008, 0), mcp3008->read(mcp3008, 6),
           mcp3008->read(mcp3008, 7));
    sleep_ms(1000);
  }
}