/**
 * @file esp.h
 * @brief All things regarding the esp for the kitchen timer
 */

#ifndef ESP_H
#define ESP_H

#define MESSAGE_LENGTH 4 //Expecting 3 chars and '\\n'
char gMessage[MESSAGE_LENGTH];
uint8_t gMessageIndex = 0;

//Main code
void esp_setup (void);
bool esp_read (void);
void esp_clear (void);

//Getters
uint8_t esp_getMaxSize ();
uint8_t esp_getMessageSize ();
char esp_getMessage (uint8_t index);


void esp_setup ()
{
  Serial.begin(9600);
}


/// @brief Reads what the ESP sends to the arduino with a WHILE LOOP. Use 'esp_getMessage()' to retrive data
/// @param None 
/// @return Successful reading of data returns TRUE
///
bool esp_read ()
{
  char incomingChar = Serial.read();
  if(incomingChar != '$')
  {
    return false;
  }
  esp_clear();

  incomingChar = Serial.read();
  while((incomingChar != '\n') && (gMessageIndex < MESSAGE_LENGTH - 1)) //Stops before last index for '/n'
  {
    gBuffer[gMessageIndex++] = incomingChar;
  }

  if(incomingChar != '\n') //Message Overlapped; Read failed
  {
    return false;
  }

  gBuffer[gMessageIndex] = '\n';
  return true;
}


/// @brief Clear Message
void esp_clear ()
{
  for(int i = 0; i < BUFFER_SIZE; i++)
  {
    gMessage[i] = 0;
  }
  gMessageIndex = 0;
}


/// @brief Message size getter
/// @param None 
/// @return Message size
uint8_t esp_getMessageSize ()
{
  return gMessageIndex + 1;
}


/// @brief Max message size getter
/// @param None 
/// @return Max message size
uint8_t esp_getMaxSize ()
{
  return MESSAGE_LENGTH
}


/// @brief Message getter
/// @param uint8_t index 
/// @return gMessage[index]
char esp_getMessage (uint8_t index)
{
  return index > MESSAGE_LENGTH - 1 ? -1: gMessage[index];
}


#endif