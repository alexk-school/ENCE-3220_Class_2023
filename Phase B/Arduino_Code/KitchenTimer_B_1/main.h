/**
 * @file main.h
 * @brief Main header file for kitchen timer, contains interupts and small macro for io
 */

#ifndef MAIN_H
#define MAIN_H


#include <string.h> //for strncmp(char a[],char b[],int num_bytes);


#define INTERRUPT_TIME1 100 // 0.4 ms; Max 65535 == 1 sec

void main_setup ()
{
  // Initialize Timer1 (16bit) -> Used for Serial Comms
  // Speed of Timer1 = 16MHz/64 = 250 KHz
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = INTERRUPT_TIME1;            // max value 2^16 - 1 = 65535
  TCCR1A |= (1<<WGM11);
  TCCR1B = (1<<CS11) | (1<<CS10);   // 64 prescaler
  TIMSK1 |= (1<<OCIE1A);
  interrupts();
}


#endif