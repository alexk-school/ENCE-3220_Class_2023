#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <avr/power.h>
#include <stdint.h>

#define CLOCK_TIME (uint16_t) (16000000 / 256 - 1)  // 16M / 256 - 1
#define ISR_SCALE (uint16_t) 1000  // CLOCK_TIME / 1000

#define DEBOUNCE_TIME 30000 //10k

typedef enum {GET, INC, NUL, STP, STR} command;

#endif 