#ifndef __COMMON_H__
#define __COMMON_H__

#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include <WiFi.h>
#include "clientRecv.h"
#include "motorCtrl.h"

uint8_t CheckSum(uint8_t *Buf,uint8_t Len);
#endif