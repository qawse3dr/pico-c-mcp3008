/*
 * (C) Copyright 2021 Larry Milne (https://www.larrycloud.ca)
 *
 * This code is distributed on "AS IS" BASIS,
 * WITHOUT WARRANTINES OR CONDITIONS OF ANY KIND.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author: qawse3dr a.k.a Larry Milne
 */

#include "mcp3008.h"

#include <stdio.h>
#include <stdlib.h>

#include "hardware/spi.h"
#include "pico/stdlib.h"

static int read_mcp3008(struct MCP3008* mcp3008, int channel) {
  // Create Message always single mode
  uint8_t buf_in[3] = {0, 0, 0};
  uint8_t buf_out[3] = {0, 0, 0};

  buf_out[0] = 0b00000001;
  buf_out[1] = 0b10000000 | (channel << 4);

  // Start writing and read back info
  gpio_put(mcp3008->cs_, 0);
  for (int i = 0; i < 3; i++) {
    spi_write_read_blocking(mcp3008->spi_, &buf_out[i], &buf_in[i], 1);
  }

  // finish writing
  gpio_put(mcp3008->cs_, 1);

  // return value
  return ((buf_in[1] & 0x03) << 8) | buf_in[2];
}

struct MCP3008* init_mcp3008(int channel, int sck, int mosi, int miso, int cs,
                             long baudrate) {
  struct MCP3008* mcp3008 = malloc(sizeof(struct MCP3008));
  // Init pins
  mcp3008->cs_ = cs;
  gpio_init(mcp3008->cs_);
  gpio_set_dir(mcp3008->cs_, GPIO_OUT);

  // set reading function
  mcp3008->read = read_mcp3008;

  // Init spi
  switch (channel) {
    case 0:
      mcp3008->spi_ = spi0;
      break;
    case 1:
      mcp3008->spi_ = spi1;
      break;
  }

  spi_init(mcp3008->spi_, baudrate);
  spi_set_format(
      mcp3008->spi_,  // SPI
      8,  // bits per transfer (8 bits not 10 because mcp3008 deals in 8 bits)
      0,  // Polarity
      0,  // Phase
      SPI_MSB_FIRST);
  // set cs to high
  gpio_put(mcp3008->cs_, 1);

  // Initialize SPI pins
  gpio_set_function(sck, GPIO_FUNC_SPI);
  gpio_set_function(mosi, GPIO_FUNC_SPI);
  gpio_set_function(miso, GPIO_FUNC_SPI);

  // throw away read to make sck idle high (someone said this is a problem)
  // with pico but I don't really know tbh.
  read_mcp3008(mcp3008, 0);

  return mcp3008;
}

void free_mcp3008(struct MCP3008** mcp3008) {
  if (mcp3008 && *mcp3008) {
    spi_deinit((*mcp3008)->spi_);
    free(*mcp3008);
    *mcp3008 = NULL;
  }
}
