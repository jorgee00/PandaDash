#ifndef WS2812_H
#define WS2812_H

#include "pico/types.h"
#include "hardware/pio.h"

class WS2812 {
    public:
        WS2812(uint pin, uint length, PIO pio, uint sm);
        ~WS2812();

        static uint32_t RGB(uint8_t red, uint8_t green, uint8_t blue) {
            return (uint32_t)(red) << 8 | (uint32_t)(green) << 16 | (uint32_t)(blue);
        };

        void setPixelColor(uint index, uint32_t color);
        void setPixelColor(uint index, uint8_t red, uint8_t green, uint8_t blue);
        void fill(uint32_t color);
        void fill(uint32_t color, uint first);
        void fill(uint32_t color, uint first, uint count);
        void show();

    private:
        uint pin;
        uint length;
        PIO pio;
        uint sm;
        uint32_t *data;

        void initialize(uint pin, uint length, PIO pio, uint sm);

};

#endif