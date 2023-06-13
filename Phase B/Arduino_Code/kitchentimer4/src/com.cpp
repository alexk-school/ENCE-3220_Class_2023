#include "../inc/com.h"

bool gCmdFlag = 0;
command gCmd = NUL;
HardwareSerial& gSrl = Serial1;

void comTick ()
{
  if (!gSrl)
    return;

  if (gSrl.available() < MSG_LENGTH + 2)
    return;
  //Serial.println("Parse Start");
  comParse ();
  //Serial.println("Parse Done");
}

void comParse ()
{
  if (gSrl.read() != '$')
    return;
  
  uint8_t j = 0;

  const int total = 5;
  char msg[total][MSG_LENGTH + 1] = {"GET", "INC", "NUL", "STP", "STR"}; // length 3 + \0
  char m[4] = {"123"};
  bool check[total] = {true,true,true,true,true};

  while (gSrl.available() && j != MSG_LENGTH)
  {
    char c = gSrl.read();
    m[j] = c;
    for (int i = 0; i < total; i++)
    {
      if (check[i])
        check[i] &= msg[i][j] == c; 
    }
    j++;
  }
  //Serial.println(m);
  //Serial.println("Parse Middle");
  for (int i = 0; i < total; i++)
  {
    if (check[i])
    { 
      gCmd = (command) i;
      gCmdFlag = 1;
      Serial.print("Parse Success\t");
	    Serial.print(i);
	    Serial.println();
      return;
    }
  }
  Serial.println("Parse Fail");
  gCmd = NUL;
}

void comPrint (char c[])
{ 
  if (gSrl && c != NULL)
    gSrl.print(c);
}