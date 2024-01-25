// BLF/TLF FW3A driver layout
// Copyright (C) 2018-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

/* FW3A driver layout using the Attiny1616

Driver pinout:
 * eSwitch:    PA5
 * Aux RED:    PC1
 * Aux GREEN:  PC2
 * Aux BLUE:   PC3
 * PWM FET:    PB5 (TCA0 WO5)
 * PWM 1x7135: PB1 (TCA0 WO1)
 * PWM 7x7135: PB0 (TCA0 WO0)
 * Voltage:    VCC

*/

#define HWDEF_C  lumintop/fw3a-1616/2ch/hwdef.c

// allow using aux LEDs as extra channel modes
#include "fsm/chan-rgbaux.h"

// channel modes:
// * 0. channel 1 only
// * 1. channel 2 only
// * 2. both channels, tied together, max "200%" power
// * 3. both channels, manual blend, max "100%" power
// * 4. both channels, auto blend, reversible
#define NUM_CHANNEL_MODES   (5 + NUM_RGB_AUX_CHANNEL_MODES)
enum channel_modes_e {
    CM_CH1 = 0,
    CM_CH2,
    CM_BOTH,
    CM_BLEND,
    CM_AUTO,
    RGB_AUX_ENUMS
};

// right-most bit first, modes are in fedcba9876543210 order
#define CHANNEL_MODES_ENABLED 0b0000000000011111
#define USE_CHANNEL_MODE_ARGS
// _, _, _, 128=middle CCT, 0=warm-to-cool
#define CHANNEL_MODE_ARGS     0,0,0,128,0,RGB_AUX_CM_ARGS

// can use some of the common handlers
#define USE_CALC_2CH_BLEND

#define PWM_CHANNELS 3  // old, remove this

#define PWM_BITS      16     // 0 to 16383 at variable Hz, not 0 to 255 at 16 kHz
#define PWM_GET       PWM_GET8
#define PWM_DATATYPE  uint16_t  // is used for PWM_TOPS (which goes way over 255)
#define PWM_DATATYPE2 uint16_t  // only needs 32-bit if ramp values go over 255
#define PWM1_DATATYPE uint8_t   // 1x7135 part of 1x7135+FET ramp
#define PWM2_DATATYPE uint8_t   // DD FET part of 1x7135+FET ramp
#define PWM3_DATATYPE uint16_t  // 1x7135+FET ramp tops
#define PWM4_DATATYPE uint8_t   // 7x7135-only ramp
#define PWM5_DATATYPE uint16_t  // 7x7135-only ramp tops


// PWM parameters of both channels are tied together because they share a counter
#define PWM_TOP TCA0.SINGLE.PERBUF   // holds the TOP value for for variable-resolution PWM
#define PWM_TOP_INIT  255    // highest value used in top half of ramp
// not necessary when double-buffered "BUF" registers are used
#define PWM_CNT TCA0.SINGLE.CNT   // for resetting phase after each TOP adjustment

// 1x7135 channel
#define CH1_PIN  PB1
#define CH1_PWM  TCA0.SINGLE.CMP1BUF  // CMP1 is the output compare register for PB1

// 7x7135 channel
#define CH2_PIN  PB0
#define CH2_PWM  TCA0.SINGLE.CMP0BUF  // CMP0 is the output compare register for PB1

// DD FET channel
#define CH3_PIN  PB5
#define CH3_PWM  TCA0.SINGLE.CMP2BUF  // CMP2 is the output compare register for PB0

// e-switch
#define SWITCH_PIN      PIN5_bp
#define SWITCH_PORT     VPORTA.IN
#define SWITCH_ISC_REG  PORTA.PIN2CTRL
#define SWITCH_VECT     PORTA_PORT_vect
#define SWITCH_INTFLG   VPORTA.INTFLAGS

// average drop across diode on this hardware
#ifndef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V
#endif

// this driver allows for aux LEDs under the optic
#define AUXLED_R_PIN    PIN1_bp    // pin 1
#define AUXLED_G_PIN    PIN2_bp    // pin 2
#define AUXLED_B_PIN    PIN3_bp    // pin 3
#define AUXLED_RGB_PORT PORTC  // PORTA or PORTB or PORTC

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS


inline void hwdef_setup() {

    // set up the system clock to run at 10 MHz instead of the default 3.33 MHz
    _PROTECTED_WRITE( CLKCTRL.MCLKCTRLB,
                      CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm );

    // enable pwm on PB5
    PORTMUX.CTRLC = PORTMUX_TCA02_ALTERNATE_gc;

    //VPORTA.DIR = ...;
    // Outputs: PWMs
    VPORTB.DIR = PIN0_bm
               | PIN1_bm
               | PIN5_bm;
    // RGB aux LEDs
    VPORTC.DIR = PIN1_bm
               | PIN2_bm
               | PIN3_bm;

    // enable pullups on the unused pins to reduce power
    PORTA.PIN0CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;  // eSwitch
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;

    //PORTB.PIN0CTRL = PORT_PULLUPEN_bm; // 7x7135 channel
    //PORTB.PIN1CTRL = PORT_PULLUPEN_bm; // 1x7135 channel
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTB.PIN4CTRL = PORT_PULLUPEN_bm;
    //PORTB.PIN5CTRL = PORT_PULLUPEN_bm; // FET channel

    PORTC.PIN0CTRL = PORT_PULLUPEN_bm;
    //PORTC.PIN1CTRL = PORT_PULLUPEN_bm; // RGB Aux
    //PORTC.PIN2CTRL = PORT_PULLUPEN_bm; // RGB Aux
    //PORTC.PIN3CTRL = PORT_PULLUPEN_bm; // RGB Aux

    // set up the PWM
    // https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny1614-16-17-DataSheet-DS40002204A.pdf
    // PB0 is TCA0:WO0, use TCA_SINGLE_CMP0EN_bm
    // PB1 is TCA0:WO1, use TCA_SINGLE_CMP1EN_bm
    // PB2 is TCA0:WO2, use TCA_SINGLE_CMP2EN_bm
    // For Fast (Single Slope) PWM use TCA_SINGLE_WGMODE_SINGLESLOPE_gc
    // For Phase Correct (Dual Slope) PWM use TCA_SINGLE_WGMODE_DSBOTTOM_gc
    // See the manual for other pins, clocks, configs, portmux, etc
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm
                      | TCA_SINGLE_CMP1EN_bm
                      | TCA_SINGLE_CMP2EN_bm
                      | TCA_SINGLE_WGMODE_DSBOTTOM_gc;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc
                      | TCA_SINGLE_ENABLE_bm;

    PWM_TOP = PWM_TOP_INIT;

}


#define LAYOUT_DEFINED

