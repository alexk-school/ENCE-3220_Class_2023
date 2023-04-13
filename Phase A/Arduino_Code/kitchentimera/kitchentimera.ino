#include <kitchentimera.h> //Arduino Doesnt like headers; This will need the exact file path

#define debounce 10000
#define mul 10 //Debounce is multiplied by this value, having debounce simply be 100_000 caused runtime errors
#define max 9999
#define timeInc 1000 //This is used to track the timer, a higher value will give more acurate time between pauses (enabling/disabling).

volatile unsigned int counter = 0;
volatile unsigned int timerCheck = timeInc;
volatile unsigned long clearLED = false;
volatile boolean timer = false, buzzer = false; //Timer and buzzer control the state of the timer and buzzer

void setup() {
    pinSetup();

    //Timer ISR time
    OCR1A = (int)(62500/timeInc); //overriden from header; also disabled in header   
    intSetup();
    disp_on();

    // Set PWM frequency for pin 6 to 31.25 kHz 
    TCCR0B = TCCR0B & 0b11111000 | 0x01; //The buzzer makes an audible whinning noise without this at all times
}

void Button_1_ISR() //Increment button
{   
    for(int i = 0; i < debounce*mul; i++){} //Debounce
    counter++;
    counter = counter == max ? 0 : counter; //reset
    clearLED = debounce*.005; //briefly pusle red led
}

void Button_2_ISR() //Start/Stop; Note this also disables the buzzer after the timer goes to 0
{   
    for(int i = 0; i < debounce*mul; i++){} //Debounce
    timer = !timer; //Toggle timer state
    if(counter == 0){ //Disable timer and buzzer if time is 0
      timer = false; 
      buzzer = false;
    }  
}

ISR(TIMER1_COMPA_vect) // Timer ISR
{
    if(timer){
        //This provides more accuracy between pauses
        if(timerCheck == 0){ 
            incTimer(); //This function is so small enough to not cause noticable timing problems
        }
        timerCheck = timerCheck == timeInc ? 0 : timerCheck + 1; //reset and Increment
    }
}

void incTimer() {
    if(counter == 0){ //Stops timer and enables buzzer
      timer = false;
      buzzer = true;
      return;
    }
    counter--;
}

void loop() {
    displayDriver(counter); //Displays counter in seconds
    digitalWrite(GREEN_LED, timer ? HIGH : LOW); //Green led shows timer status
    digitalWrite(RED_LED, clearLED > 0 ? HIGH : LOW); //Red led pulses on increment button
    clearLED -= clearLED > 0 ? 1 : 0;
    if(counter == 0 && buzzer){ //Enable Buzzer
        Active_Buzzer();
    }
}