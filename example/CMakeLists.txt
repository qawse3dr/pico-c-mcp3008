cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)



project(mcp3008_example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )


# compile src

add_executable(mcp3008_example)

target_sources(mcp3008_example PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/test.c
        ${CMAKE_CURRENT_LIST_DIR}/../mcp3008.c
        )

target_include_directories(mcp3008_example PUBLIC
         ${CMAKE_CURRENT_LIST_DIR}/..)

target_link_libraries(mcp3008_example PUBLIC pico_stdlib  hardware_spi)

# Enable usb output, disable uart output
pico_enable_stdio_usb(mcp3008_example 1)
# pico_enable_stdio_uart(mcp3008_example 0)

pico_add_extra_outputs(mcp3008_example)
