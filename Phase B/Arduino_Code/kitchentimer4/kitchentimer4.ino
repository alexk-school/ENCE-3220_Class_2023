#include "inc/main.h"
#include "inc/io.h"
#include "inc/timer.h"
#include "inc/com.h"

volatile bool gTimerISRFlag = 0;
volatile bool gButton1Flag = 0;
volatile bool gButton2Flag = 0;

void setup ()
{
  //Clock Timing
    if (F_CPU == 16000000) clock_prescale_set (clock_div_1);

  //IO
    ioSetup ();

    // Set PWM frequency for pin 6 to 31.25 kHz 
    TCCR0B = TCCR0B & 0b11111000 | 0x01; //Prevents audible whinning noise from buzzer

  //Interupts
    attachInterrupt (digitalPinToInterrupt (BUTTON_1), Button_1_ISR, RISING);
    attachInterrupt (digitalPinToInterrupt (BUTTON_2), Button_2_ISR, RISING);

    noInterrupts ();
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = (uint16_t) (CLOCK_TIME / ISR_SCALE + 0.5); //set in inc/main.h
    TCCR1B |= (1<<WGM12);   // CTC mode
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1<<OCIE1A);  // enable timer compare interrupt
    interrupts ();

  //Inits
    ioInit ();

  //Serial
    Serial1.begin (9600);
    Serial.begin (9600);
    Serial.println ("Begin");
}


void loop ()
{
  if (gTimerISRFlag)
  {
    gTimerISRFlag = 0;
    timerTick();
    comTick();
  }

  if (gButton1Flag)
  {
    for (int i = 0; i < DEBOUNCE_TIME; i++);
    gButton1Flag = 0;
    timerToggle ();
  }

  if (gButton2Flag)
  {
    for (int i = 0; i < DEBOUNCE_TIME; i++);
    gButton2Flag = 0;
    timerInc ();
  }

  if (gCmdFlag)
  {
    Serial.println("Cmd");
    gCmdFlag = 0;

    switch (gCmd) //While I cannot tell you why, moving GET to the front breaks everything.
    {
      Serial.println(gCmd);
      case INC:
        Serial.println("inc"); 
        timerInc ();
        break;
      case STP:
        if (gTimerState)
          timerToggle ();
        break;
      case STR:
        if (!gTimerState)
          timerToggle ();
        break;
      case GET:
        Serial.println("get");
        if (gTimerTime / 60 > 60) 
          gTimerTime /= 60; //Convert to hour/minute
        uint16_t seconds = gTimerTime % 60;
        uint16_t minutes = gTimerTime / 60;
        char time[7]; // Assuming the formatted time will not exceed 6 characters
        sprintf(time, "$%02u:%02u\n", minutes, seconds);
        gSrl.print(time);
        Serial.print(time);
        break;
      case NUL:
        break;
    }
    gCmd = NUL;
  }

  ioDisplayTime (gTimerTime);
  ioBuzzer (gTimerEnd);
  ioRed (gTimerEnd);
  ioGreen (gTimerState);
}

void Button_1_ISR()
{
  gButton1Flag = 1;
  //Serial.println("B1 ISR");
}

void Button_2_ISR()
{ 
  gButton2Flag = 1;
  //Serial.println("B2 ISR");
}

ISR(TIMER1_COMPA_vect)
{
  gTimerISRFlag = 1;
}