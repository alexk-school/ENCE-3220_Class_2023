/*
 * @Note This will not work unless serial/serial1 are declared
 */
#ifndef COM_H
#define COM_H

#include "../inc/main.h"

#define MSG_LENGTH 3 //No padding

extern bool gCmdFlag;
extern command gCmd;
extern HardwareSerial& gSrl;

void comTick (void);
void comParse (void);

#endif