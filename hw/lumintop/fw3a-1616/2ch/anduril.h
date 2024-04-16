// Emisar 2-channel generic (plus FET) config options for Anduril (based on Noctigon K9.3)
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "lumintop/fw3a-1616/2ch/hwdef.h"

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS

// don't turn on the aux LEDs while main LEDs are on
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V

// channel modes...
// CM_CH1, CM_CH2, CM_BOTH, CM_BLEND, CM_AUTO
// enable max brightness out of the box
#define DEFAULT_CHANNEL_MODE           CM_CH1

#define USE_CONFIG_COLORS

// blink numbers on the main LEDs by default (but allow user to change it)
#define DEFAULT_BLINK_CHANNEL  CM_BOTH

#define POLICE_COLOR_STROBE_CH1        CM_CH1
#define POLICE_COLOR_STROBE_CH2        CM_CH2

// how much to increase total brightness at middle tint
// (0 = 100% brightness, 64 = 200% brightness)
#define TINT_RAMPING_CORRECTION 0  // none, linear regulator doesn't need it


// channel 1 / main LEDs (w/ DD FET)
//   output: unknown, 1750 lm?
//   FET: unknown, 3000 lm?
// channel 2
//   output: unknown, 1750 lm?
// combined: 4000 to 5000 lm?
#define RAMP_SIZE 150

// linear+FET ramp: maxreg at 140/150
// level_calc.py 5.01 2 150 7135 1 0.1 1924 FET 1 10 2600 --pwm dyn:68:4096:255:3 --clock 8:16:0
// linear segment
#define PWM1_LEVELS 1,1,1,2,2,2,2,3,3,3,4,4,5,6,6,7,8,8,9,10,11,12,13,14,16,17,18,20,21,23,25,26,28,30,32,34,36,39,41,44,46,49,52,55,58,61,64,67,71,74,78,82,86,90,94,98,103,107,112,117,122,127,132,138,143,149,155,161,167,173,180,186,193,200,207,215,222,230,238,246,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
// DD FET segment
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,8,10,11,13,15,17,19,21,23,25,28,30,32,34,37,39,41,44,46,49,52,54,57,60,62,65,68,71,74,77,80,83,86,89,93,96,99,103,106,110,113,117,121,124,128,132,136,140,144,148,152,156,160,165,169,173,178,182,187,192,196,201,206,211,216,221,226
// PWM TOPS values
#define PWM3_LEVELS 4096,3831,3570,3314,3063,2817,2577,2342,2115,1894,1682,1477,1281,2237,2005,1784,1576,1380,1196,1111,1026,1442,1348,1215,1091,976,871,774,1031,942,860,784,714,650,591,538,652,602,555,513,473,437,403,372,343,398,370,345,322,299,278,311,292,273,255,278,261,245,263,247,232,246,231,243,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

// linear-only ramp
// level_calc.py 3.11 1 150 7135 1 0.1 1750 --pwm dyn:64:4096:255:3 --clock 8:16:0
#define PWM4_LEVELS 1,1,1,1,2,2,3,3,4,4,5,5,6,6,7,8,8,9,9,10,11,11,12,13,13,14,15,15,16,17,18,19,20,21,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,43,44,45,46,48,49,50,51,53,54,56,57,58,60,61,63,64,66,67,69,70,72,74,75,77,79,80,82,84,85,87,89,91,93,95,97,98,100,102,104,106,108,111,113,115,117,119,121,124,126,128,130,133,135,137,140,142,145,147,150,152,155,157,160,163,165,168,171,173,176,179,182,185,188,190,193,196,199,202,205,209,212,215,218,221,224,228,231,234,238,241,245,248,251,255
// PWM_TOPS values for linear-only ramp
#define PWM5_LEVELS 4096,3681,3247,2794,2328,1856,2937,2393,1860,2690,2273,1875,2281,1959,1658,1893,1646,1774,1569,1381,1466,1309,1166,1224,1104,996,1033,942,858,882,810,746,687,634,586,604,561,522,487,454,425,397,409,385,362,341,321,302,311,295,279,286,271,257,263,250,255,258,246,249,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

#define DEFAULT_LEVEL      50
#define MAX_1x7135         81
#define MAX_Nx7135         150

#ifdef USE_DYNAMIC_UNDERCLOCKING
#undef USE_DYNAMIC_UNDERCLOCKING
#endif

#define RAMP_SMOOTH_FLOOR  3  // level 1 is unreliable (?)
#define RAMP_SMOOTH_CEIL   120
// 10, 31, 53, [75], 96, 118, [140]
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// safe limit highest regulated power (no FET or turbo)
// 10, 42, [75], 107, 140
#define SIMPLE_UI_FLOOR  RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL   RAMP_DISCRETE_CEIL
#define SIMPLE_UI_STEPS  5

// stop panicking at ~1500 lm
#define THERM_FASTER_LEVEL 130
#define MIN_THERM_STEPDOWN 65  // should be above highest dyn_pwm level

#define USE_POLICE_COLOR_STROBE_MODE
#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 140,30,(RAMP_SIZE+3)  // high, low, police strobe

// use the brightest setting for strobe
#define STROBE_BRIGHTNESS MAX_LEVEL
// slow down party strobe; this driver can't pulse for 1ms or less

// TODO: change speed per channel mode
// (the FET is really fast, but the regulator is not)
//#undef PARTY_STROBE_ONTIME

// the default of 26 looks a bit flat, so increase it
#define CANDLE_AMPLITUDE 33

// the power regulator is a bit slow, so push it harder for a quick response from off
#define DEFAULT_JUMP_START_LEVEL 40
#define BLINK_BRIGHTNESS 45
#define BLINK_ONCE_TIME 12  // longer blink, since main LEDs are slow

#define THERM_CAL_OFFSET 5

// don't blink while ramping
#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif

// can't reset the normal way because power is connected before the button
#define USE_SOFT_FACTORY_RESET

