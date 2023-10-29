/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "../lib/WS2812/WS2812.hpp"
#include "../lib/PWM/pwm.hpp"

#define IS_RGBW true

#define WS2812_PIN 26
#define NUM_LEDS 5

int main() {
    WS2812 ledStrip(
            WS2812_PIN,            // Data line is connected to pin 0. (GP0)
            NUM_LEDS,         // Strip is 6 LEDs long.
            pio0,               // Use PIO 0 for creating the state machine.
            0
    );
    PWM pwm{
            (1u << 16) - 1,
            25,
            pio1,
            0
    };
    stdio_init_all();
    printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);


    for(uint32_t value = 0; value < 255; value++){
        pwm.setValue(value*value);
        ledStrip.setPixelColor(0,value,value,value);
        ledStrip.show();
        sleep_ms(10);
    }
}
