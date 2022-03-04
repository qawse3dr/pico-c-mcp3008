# pico-C-mcp3008

C spi drivers for adafruit mcp3008 10 bit adc.

## Why I made this
Ada fruit seems to not supply any spi drivers for the pico or any other microcomputer
only circutpython drivers.... well I needed some drivers for C for a game controller 
and there doesn't seem to be any online so here we are... 

## Limitations
This driver will only do single-end reading as thats all I needed and to be honest
I am not even sure why you would want differntial. but it shouldn't be to hard to implement
if anyone needs it in the future (just change the first bit from a 1 to a zero). If anyone
ends up implementing it feel free to create a PR and I'll try and merge it in.

## Usage
pretty basic use init_mcp3008() to create the mcp3008 object, then from there use
mcp3008->read(mcp3008, channel) to get the reading. and free_mcp3008(&mcp3008) to dealloc
the memory

## Example
I have included an example on how to use it in example/main.c
