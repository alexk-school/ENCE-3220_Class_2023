

//Note exact file paths must be specified for compilation
#include <esp.h>
#include <display.h>
#include <main.h>

volatile bool gFlagTimer1 = false

char gMessage_[MESSAGE_LENGTH];

volatile bool gMessageFlag = false;
bool gProccessFlag = false;


#define TIMER_SECOND 65535
#define TIMER_STEP ((float)INTERRUPT_TIME1/65535.0 + 0.5) //0.5 for rounding up
volatile int gTimerFlag = 0;
unsigned int gTimer = 0;
volatile bool gTimerEnable = false;


void setup ()
{
  main_setup();
  esp_setup();
  display_setup();
}

void loop ()
{
  if(gTimerInterrupt > TIMER_SECOND){
    if(gTimerEnable)
    {
      gTimer--;
      gTimerInterrupt -= TIMER_SECOND;
      gTimerInterrupt = gTimerInterrupt < TIMER_STEP ? 0 : gTimerInterrupt; //Prevents overflow but adds inacurracy
	  if(gTimer == 0)
	  {
        gTimerEnable = false
		gTimerInterrupt = 0;
	  }
    }
  }

  if(gMessageFlag)
  {
    if(esp_read()) //will only be called if Serial.available() >= message length
    {
      for(int i = 0; i < MESSAGE_LENGTH; i++) //defined in esp.h
      {
        gMessage_[i] = esp_getMessage(i);
      }
      gProccessFlag = true;
    }
	gMessageFlag = false;
  }

  if(gProccessFlag)
  {
    if(strncmp(gMessage_[], 'STR', 3)) //From string.h
    {
      gTimerEnable = true;
    }
    if(strncmp(gMessage_[], 'STP', 3))
    {
      gTimerEnable = false;
    }
    if(strncmp(gMessage_[], 'INC', 3))
    {
      gTimer++;
    }
    if(strncmp(gMessage_[], 'GET', 3))
    {
      printTimer();
    }
	gProccessFlag = false;
  }

  display_driver(gTimer);
}

/// @brief Serial Prints first 4 digits of timer in format "$xx:xx\\n"
void printTimer ()
{
  char digits[] = //first 4 digits of gTimer
  sprintf(digits, "$%02d:%02d\n", gTimer / 10000); //prints first 4 digits of gTimer formatted as "$00:00\n"
  Serial.printf("%s", digits);
}



ISR (TIMER1_COMPA_vect) // timer compare interrupt service routine
{
  if(Serial.available() >= MESSAGE_LENGTH){ //defined in esp.h
    gMessageFlag = true;
  }

  if(gTimerEnable)
  {
    gTimerFlag += TIMER_STEP; //= TIMER_SECOND at 1s passed
  }
}