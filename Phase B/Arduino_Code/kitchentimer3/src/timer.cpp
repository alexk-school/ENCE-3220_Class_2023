#include "../inc/timer.h"

uint16_t gTimerTime = 0;
uint16_t gTimerSkip = 0;
uint16_t gTimerTicks = 0;

bool gTimerState = false;
bool gTimerEnd = false;

void timerInc ()
{
  gTimerEnd = false;
  gTimerTime++;
  Serial.println("INC");
}

void timerToggle ()
{
  if (!gTimerTime == 0)
  {
    gTimerState = !gTimerState;
  }

  gTimerEnd = false;
}

void timerTick ()
{
  if (!gTimerState) 
    return;

  if (gTimerSkip++ != TIMER_SKIP)
    return;
  gTimerSkip = 0;

  Serial.println((unsigned long) TIMER_TICKS);
  if (gTimerTicks++ != TIMER_TICKS) 
    return;
  Serial.println("T4");

  gTimerTicks = 0;
  gTimerTime--;

  gTimerEnd = gTimerTime == 0;
  gTimerState = !gTimerEnd;
  Serial.println("T5");
}