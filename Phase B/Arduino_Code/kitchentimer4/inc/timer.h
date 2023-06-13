#ifndef TIMER_H
#define TIMER_H

#include "../inc/main.h"

#define TIMER_SKIP (uint16_t) 0
#define TIMER_TICKS (uint16_t) (ISR_SCALE / (TIMER_SKIP + 1) + 0.5)

extern uint16_t gTimerTime;
extern uint16_t gTimerSkip;
extern uint16_t gTimerTicks; //Number of ticks to make a 

extern bool gTimerState;
extern bool gTimerEnd;

void timerInc (void);
void timerToggle (void);
void timerTick (void);


#endif