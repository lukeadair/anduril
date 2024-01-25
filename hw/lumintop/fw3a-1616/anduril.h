// FW3A config options for Anduril
// Copyright (C) 2018-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "lumintop/fw3a-1616/hwdef.h"

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS

// don't turn on the aux LEDs while main LEDs are on
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V

#define RAMP_SIZE 150

#define PWM1_LEVELS 1,1,2,2,3,3,4,4,5,6,7,8,9,10,12,13,14,15,17,19,20,22,24,26,29,31,34,36,39,42,45,48,51,55,59,62,66,70,75,79,84,89,93,99,104,110,115,121,127,134,140,147,154,161,168,176,184,192,200,209,217,226,236,245,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,13,15,17,19,22,24,26,29,31,34,37,39,42,45,48,51,54,57,60,64,67,70,74,77,81,85,88,92,96,100,104,108,112,116,121,125,130,134,139,143,148,153,158,163,168,173,179,184,189,195,201,206,212,218,224,230,236,243,249,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM3_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,19,31,43,55,67,79,91,104,117,130,143,157,170,184,198,212,226,240,255
#define PWM_TOPS 4096,3831,3570,3314,3063,2817,2577,2342,2115,1894,1682,1477,1281,2237,2005,1784,1576,1380,1196,1111,1026,1442,1348,1215,1091,976,871,774,1031,942,860,784,714,650,591,538,652,602,555,513,473,437,403,372,343,398,370,345,322,299,278,311,292,273,255,278,261,245,263,247,232,246,231,243,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#define MAX_1x7135 65
#define MAX_Nx7135 130

#ifdef USE_DYNAMIC_UNDERCLOCKING
#undef USE_DYNAMIC_UNDERCLOCKING
#endif

#define DEFAULT_LEVEL 50
#define MIN_THERM_STEPDOWN 60


#define RAMP_SMOOTH_FLOOR    3
#define RAMP_SMOOTH_CEIL     120
// 10 28 46 [65] 83 101 120
#define RAMP_DISCRETE_FLOOR  10
#define RAMP_DISCRETE_CEIL   RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS  7

// at Wurkkos's request, reduce the Simple UI ceiling a little bit
// 25 50 [75] 100 125
#define SIMPLE_UI_FLOOR  RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL   100
#define SIMPLE_UI_STEPS  5

// stop panicking at ~50% power
#define THERM_FASTER_LEVEL MAX_Nx7135  // throttle back faster when high

// show each channel while it scroll by in the menu
#define USE_CONFIG_COLORS

// blink numbers on the main LEDs by default
// (so battcheck will be visible while charging)
#define DEFAULT_BLINK_CHANNEL  CM_MAIN
// blink numbers on the aux LEDs by default
//#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT

// use aux red + aux blue for police strobe
#define USE_POLICE_COLOR_STROBE_MODE
#define POLICE_STROBE_USES_AUX
#define POLICE_COLOR_STROBE_CH1        CM_AUXRED
#define POLICE_COLOR_STROBE_CH2        CM_AUXBLU

// don't blink mid-ramp
// #ifdef BLINK_AT_RAMP_MIDDLE
// #undef BLINK_AT_RAMP_MIDDLE
// #endif

