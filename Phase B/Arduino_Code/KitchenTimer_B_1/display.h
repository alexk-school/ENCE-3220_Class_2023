/**
 * @file display.h
 * @brief All things regarding the 7-segment display (and shift register) for the kitchen timer
 */

#ifndef DISPLAY_H
#define DISPLAY_H


#define DATA      9   
#define LATCH     8  
#define CLOCK     7  

#define DIGIT_4   10
#define DIGIT_3   11
#define DIGIT_2   12
#define DIGIT_1   13

//Macro table to write chars to the display
unsigned char gDisplayTable[] =
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};


void display_setup (void);
void display_on (void);
void display_write (void);
void display_driver (void);


void display_setup ()
{
  // 7-Seg Display
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  // Shift Register Pins
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  display_on();
}


void display_on (void)
{
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
}

/// @brief Uses the shift register to write a single digit number to every enabled digit on the 7seg display
/// @param unsigned_char number
void display_write (unsigned char number)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, gDisplayTable[number]);
  digitalWrite(LATCH, HIGH);
}

/// @brief Uses 'display_write()' to write the leading 4 digits of an unsigned int to the 7seg display
/// @param uint8_t number
void display_driver (uint8_t number) 
{
  digitalWrite(DIGIT_1, LOW);
  Display(number % 10);
  number /= 10;
  digitalWrite(DIGIT_1, HIGH);

  digitalWrite(DIGIT_4, LOW);
  Display(number % 10);
  number /= 10;
  digitalWrite(DIGIT_4, HIGH);

  digitalWrite(DIGIT_3, LOW);
  Display(number % 10);
  number /= 10;
  digitalWrite(DIGIT_3, HIGH);

  digitalWrite(DIGIT_2, LOW);
  Display(number % 10);
  digitalWrite(DIGIT_2, HIGH);
}


#endif