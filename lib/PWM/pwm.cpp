/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pwm.hpp"
#include "generated/pwm.pio.h"

PWM::PWM(uint32_t period, uint pin, PIO pio, uint sm) {
    initialize(period,pin,pio,sm);
}

PWM::~PWM() {
}

void PWM::initialize(uint32_t period, uint pin, PIO pio, uint sm) {
    this->period = period;
    this->pin = pin;
    this->pio = pio;
    this->sm = sm;
    this->value = 0;
    uint offset = pio_add_program(pio, &pwm_program);
    pwm_program_init(pio, sm, offset, PICO_DEFAULT_LED_PIN);
    pio_pwm_set_period(pio, sm, (1u << 16) - 1);

}
// Write `period` to the input shift register
void PWM::pio_pwm_set_period(PIO pio, uint sm, uint32_t period) {
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_put_blocking(pio, sm, period);
    pio_sm_exec(pio, sm, pio_encode_pull(false, false));
    pio_sm_exec(pio, sm, pio_encode_out(pio_isr, 32));
    pio_sm_set_enabled(pio, sm, true);
}

// Write `level` to TX FIFO. State machine will copy this into X.
void PWM::setValue(uint32_t value) {
    pio_sm_put_blocking(pio, sm, value);
}
