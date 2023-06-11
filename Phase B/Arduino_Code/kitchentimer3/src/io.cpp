#include "../inc/io.h"

const uint16_t gTable[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};

bool gDisplayStatus = false;
bool gBuzzerStatus = false;
bool gRedStatus = false;
bool gGreenStatus = false;

void ioSetup ()
{
  //Buttons
    pinMode (BUTTON_1, INPUT_PULLUP);
    pinMode (BUTTON_2, INPUT_PULLUP);

  //LEDs
    pinMode (RED_LED, OUTPUT);
    pinMode (GREEN_LED, OUTPUT);

  //Buzzer
    pinMode (BUZZER, OUTPUT);

  //Display Pins
    pinMode (DIGIT_1, OUTPUT);
    pinMode (DIGIT_2, OUTPUT);
    pinMode (DIGIT_3, OUTPUT);
    pinMode (DIGIT_4, OUTPUT);

  //Shift Pins
    pinMode (LATCH, OUTPUT);
    pinMode (CLOCK, OUTPUT);
    pinMode (DATA, OUTPUT);
}

void ioInit ()
{
  //LEDs
    digitalWrite (RED_LED, LOW);
    digitalWrite (GREEN_LED, LOW);

  //Buzzer
    digitalWrite (BUZZER, LOW);

  //Status
    ioDisplay (0);
    ioBuzzer (0);
    ioRed (0);
    ioGreen (0);
}

void ioDisplay (bool state) {
  gDisplayStatus = state;

  digitalWrite (DIGIT_1, state);
  digitalWrite (DIGIT_2, state);
  digitalWrite (DIGIT_3, state);
  digitalWrite (DIGIT_4, state);

  if (!state) ioDisplayDigit (16);
}

void ioDisplayDigit (uint8_t digit)
{
  digitalWrite (LATCH, LOW);
  shiftOut (DATA, CLOCK, MSBFIRST, gTable[digit]);
  digitalWrite (LATCH, HIGH);
}

void ioDisplayTime (uint16_t time)
{
  if (time / 60 > 60) time /= 60; //Convert to hour/minute
  uint16_t seconds = time % 60;
  uint16_t minutes = time / 60;

  digitalWrite (DIGIT_1, LOW);
  ioDisplayDigit (seconds % 10);
  digitalWrite (DIGIT_1, HIGH);

  digitalWrite (DIGIT_4, LOW);
  ioDisplayDigit (seconds / 10);
  digitalWrite (DIGIT_4, HIGH);

  digitalWrite (DIGIT_3, LOW);
  ioDisplayDigit (minutes % 10);
  digitalWrite (DIGIT_3, HIGH);

  digitalWrite (DIGIT_2, LOW);
  ioDisplayDigit (minutes / 10);
  digitalWrite (DIGIT_2, HIGH);
}

void ioBuzzer (bool state)
{
  gBuzzerStatus = state;
  digitalWrite (BUZZER, state);
}

void ioRed (bool state)
{
  gRedStatus = state;
  digitalWrite (RED_LED, state);
}

void ioGreen (bool state)
{
  gGreenStatus = state;
  digitalWrite (GREEN_LED, state);
}

