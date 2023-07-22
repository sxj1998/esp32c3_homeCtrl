#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__
#include "stdint.h"

void setupMotor(void);
void motorstart(uint16_t startTimes,uint8_t moveWay);

#endif