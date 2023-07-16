#include "common.h"
#include "stdio.h"

uint8_t CheckSum(uint8_t *Buf,uint8_t Len)
{
  uint8_t i =0;
  uint8_t sum =0;
  uint8_t checksum =0;
  
  for(i=0; i<Len; i++)
  {
    sum += *Buf++;
  }
  checksum = sum &0xff;
  return checksum;
}
