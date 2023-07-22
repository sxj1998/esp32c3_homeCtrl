#ifndef __CLIENTRECV_H__
#define __CLIENTRECV_H__

#include "common.h"
#include "stdio.h"

extern WiFiClient client; //声明一个ESP32客户端对象，用于与服务器进行连接
extern WiFiServer server; //声明服务器对象

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

int8_t RecvAscillData(WiFiServer* server);
void clientInit(void);


#endif