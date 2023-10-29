/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef PWM_H
#define PWM_H

#include "pico/types.h"
#include "hardware/pio.h"

class PWM {
    public:
        PWM(uint32_t period, uint pin, PIO pio, uint sm);
        ~PWM();

        void setValue(uint32_t value);


    private:
        uint pin;
        PIO pio;
        uint sm;
        uint32_t period;
        uint32_t value;
        void initialize(uint32_t period, uint pin, PIO pio, uint sm);
        void pio_pwm_set_period(PIO pio, uint sm, uint32_t period);

};

#endif

