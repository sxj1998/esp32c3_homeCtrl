#ifndef __CLIENTRECV_H__
#define __CLIENTRECV_H__

#include "common.h"
#include "stdio.h"

#define HeadP   0x55AA
#define TailP   0xAA55

typedef struct{
    uint8_t id;
    uint8_t code;
    uint8_t reserve;
}framme_t;

typedef enum{
    CLIENT_CONNECT = 0,
    DATA_RECV,
    DATA_HANDLE
}RECV_STAGE_E;

int8_t RecvData(WiFiServer* server);
void dataHandle(void);
int8_t RecvAscillData(WiFiServer* server);

#endif