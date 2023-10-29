cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PandaDash C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add blink example
add_executable(PandaDash
        src/main.cpp
        lib/WS2812/WS2812.cpp
        lib/PWM/pwm.cpp
)
pico_generate_pio_header(PandaDash ${CMAKE_CURRENT_LIST_DIR}/lib/WS2812/WS2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/WS2812/generated)
pico_generate_pio_header(PandaDash ${CMAKE_CURRENT_LIST_DIR}/lib/PWM/pwm.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/PWM/generated)
target_link_libraries(PandaDash PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(PandaDash)


add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()