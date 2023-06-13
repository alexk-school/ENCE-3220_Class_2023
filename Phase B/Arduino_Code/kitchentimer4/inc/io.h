#ifndef IO_H
#define IO_H

#include "../inc/main.h"

#define BUTTON_1  2
#define BUTTON_2  3
#define RED_LED   4
#define GREEN_LED 5
#define BUZZER    6

#define CLOCK     7 
#define LATCH     8  
#define DATA      9   

#define DIGIT_4   10
#define DIGIT_3   11
#define DIGIT_2   12
#define DIGIT_1   13

extern const uint16_t gTablep[];

extern bool gDisplayStatus;
extern bool gBuzzerStatus;
extern bool gRedStatus;
extern bool gGreenStatus;

void ioSetup (void);
void ioInit (void);
void ioDisplay (bool state);
void ioDisplayDigit (uint8_t digit);
void ioDisplayTime (uint16_t time);
void ioBuzzer (bool state);
void ioRed (bool state);
void ioGreen (bool state);

#endif