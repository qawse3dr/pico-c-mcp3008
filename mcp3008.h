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

// This code was adapted from python to C from
// http://blog.rareschool.com/2021/02/raspberry-pi-pico-project-2-mcp3008.html

#ifndef QAWSE3DR_MCP3008_H_
#define QAWSE3DR_MCP3008_H_

#include "hardware/spi.h"
#include "pico.h"
#include "pico/stdlib.h"

struct MCP3008 {
  // Can't do differential cause I don't need that and don't know how
  int (*read)(struct MCP3008*, int);
  spi_inst_t* spi_;
  int cs_;
};
/**
 * @brief Init mcp3008 to get it ready for reading
 *
 * @param channel what spi channel you are using normally 0
 * @param sck What spi clock you are using I used 2 on pico
 * @param mosi What master input you are using I used 3 on pico
 * @param miso what master output you are using I used 4 on pico
 * @param cs what cs you are going to use. I used 5 on pico
 * @param baudrate 10000 works fine for me
 *
 * @return MCP3008 object to read from
 */
struct MCP3008* init_mcp3008(int channel, int sck, int mosi, int miso, int cs,
                             long baudrate);

/**
 * @brief frees the mcp3008 object and de_init spi
 * @param mcp3008 ptr to mcp3008 object will be set to NULL
 * when finished
 */
void free_mcp3008(struct MCP3008** mcp3008);

#endif  // QAWSE3DR_MCP3008_H_