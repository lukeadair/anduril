// BLF/TLF FW3A PWM helper functions
// Copyright (C) 2019-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "fsm/chan-rgbaux.c"

void set_level_zero();

void set_level_main(uint8_t level);
bool gradual_tick_main(uint8_t gt);


Channel channels[] = {
    { // channel 1 only
        .set_level    = set_level_main,
        .gradual_tick = gradual_tick_main
    },
    RGB_AUX_CHANNELS
};


void set_level_zero() {
    CH1_PWM = 0;
    CH2_PWM = 0;
    #ifdef CH3_PIN
        CH3_PWM = 0;
    #endif
    PWM_CNT = 0;  // reset phase
}

// single set of LEDs with 3 stacked power channels, FET+N+1
// (or just use N+1 on the no-FET model or FET+1 model)
void set_level_main(uint8_t level) {
    PWM_DATATYPE ch1_pwm = PWM_GET(pwm1_levels, level);
    PWM_DATATYPE ch2_pwm = PWM_GET(pwm2_levels, level);
    #ifdef CH3_PIN
        PWM_DATATYPE ch3_pwm = PWM_GET(pwm3_levels, level);
    #endif
    // pulse frequency modulation, a.k.a. dynamic PWM
    uint16_t top = PWM_GET16(pwm_tops, level);

    CH1_PWM = ch1_pwm;
    CH2_PWM = ch2_pwm;
    #ifdef CH3_PIN
        CH3_PWM = ch3_pwm;
    #endif
    // wait to sync the counter and avoid flashes
    // (unnecessary w/ buffered registers)
    //while(actual_level && (PWM_CNT > (top - 32))) {}
    PWM_TOP = top;
    // force reset phase when turning on from zero
    // (because otherwise the initial response is inconsistent)
    if (! actual_level) PWM_CNT = 0;
}

bool gradual_tick_main(uint8_t gt) {
    PWM_DATATYPE pwm1 = PWM_GET(pwm1_levels, gt);
    PWM_DATATYPE pwm2 = PWM_GET(pwm2_levels, gt);
    #ifdef CH3_PIN
        PWM_DATATYPE pwm3 = PWM_GET(pwm3_levels, gt);
    #endif

    GRADUAL_ADJUST_STACKED(pwm1, CH1_PWM, PWM_TOP_INIT);
    #ifdef CH3_PIN
        GRADUAL_ADJUST_STACKED(pwm2, CH2_PWM, PWM_TOP_INIT);
        GRADUAL_ADJUST_SIMPLE (pwm3, CH3_PWM);
    #else
        GRADUAL_ADJUST_SIMPLE (pwm2, CH2_PWM);
    #endif

    if (   (pwm1 == CH1_PWM)
        && (pwm2 == CH2_PWM)
        #ifdef CH3_PIN
            && (pwm3 == CH3_PWM)
        #endif
       ) {
        return true;  // done
    }
    return false;  // not done yet
}

