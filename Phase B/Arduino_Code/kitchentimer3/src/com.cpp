#include "../inc/com.h"

bool gCmdFlag = 0;
command gCmd = NULL;
HardwareSerial& gSrl = Serial1;

void comTick ()
{
  if (!gSrl)
    return;

  if (gSrl.available() < MSG_LENGTH + 2)
    return;

  comParse ();
}

void comParse ()
{
  if (gSrl.read() != '$')
    return;
  
  uint8_t j = 0;

  int total = 5;
  char msg[total][MSG_LENGTH + 1] = {"GET", "INC", "NUL", "STP", "STR"}; // length 3 + \0
  bool check[total] = {true};

  while (gSrl.available() && j != MSG_LENGTH + 1)
  {
    char c = gSrl.read();
    for (int i = 0; i < total; i++)
    {
      if (check[i])
        check[i] &= msg[i][j] = c; 
    }
    j++;
  }

  for (int i = 0; i < total; i++)
  {
    if (check[i]) 
      gCmd = i;
      gCmdFlag = 1;
      return;
  }

  gCmd = NUL;
  
}