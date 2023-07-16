#include "clientRecv.h"


uint8_t recvBuf[200] = {0};
uint16_t recvIndex = 0;
uint8_t frameData[200] = {0};
uint16_t frameIndex = 0;
framme_t frame;
/*
    包头        55AA
    长度        xx
    数据{

    }
    crc         xx
    包尾        AA55
*/

/*
    数据段
    {
    id          xx
    }
*/

/* 解析收到的数据
data 数据源
length 数据总长度
usefulData 有效数据
*/
void dataHandle(void)
{
    if(frameIndex)
    {
        memcpy(&frame,frameData,frameIndex);
        Serial.printf("frame length %x\r\n",frameIndex);
        for(int i=0; i<frameIndex; i++)
            Serial.printf("%x ",frameData[i]);
        Serial.printf("\r\n");
        Serial.printf("id %x\r\n",frame.id);
        Serial.printf("code %x\r\n",frame.code);

        if(frameData[0] == 1)
            motorstart();

        memset(frameData,0,200);
        frameIndex = 0;
    }
}

int8_t packetRecv(uint8_t* data,uint16_t length,uint8_t* usefulData)
{
    uint8_t crc = 0;
    uint8_t frameLength = 0;
    if((data[0] == 0x55) && (data[1] == 0xAA))
    {
        crc = CheckSum(data,length-3);
        // Serial.printf("crc: %x\r\n",crc);
        // Serial.printf("framecrc: %x\r\n",data[length-3]);
        if(crc == data[length-3])
        {
            frameIndex = data[2];
            memcpy(frameData,&data[3],frameIndex);
        
            for(int i=0; i<length; i++)
                Serial.printf("%x ",data[i]);
            Serial.printf("\r\n");
            
            return 1;
        }else{
            return -1;
        }
    }
    return 0;
}

int8_t RecvData(WiFiServer* server)
{
    WiFiClient client = server->available(); //尝试建立客户对象
    if (client) //如果当前客户可用
    {
        Serial.println("[Client connected]");
        String readBuff;
        while (client.connected()) //如果客户端处于连接状态
        {
            if (client.available()) //如果有可读数据
            {
                uint8_t c = client.read(); //读取一个字节
                                        //也可以用readLine()等其他方法
                recvBuf[recvIndex] = c;
                recvIndex++;
                Serial.printf("c: %x\r\n",c); //从串口打印
                Serial.printf("recvIndex: %d\r\n",recvIndex); //从串口打印
                if((recvBuf[recvIndex-1] == 0x55) && (recvBuf[recvIndex-2] == 0xAA)) 
                {
                    // client.print("Received: " + readBuff); //向客户端发送
                    // Serial.println("Received: " + readBuff); //从串口打印
                    client.printf("get a frame\r\n");
                    if(packetRecv(recvBuf,recvIndex,frameData) == 1)
                    {
                        dataHandle();
                        memset(recvBuf,0,recvIndex);
                        recvIndex = 0;
                    }

                }
            }
        }
        // client.stop(); //结束当前连接:
        // Serial.println("[Client disconnected]");
    }
    return 0;
}

void recvHandle(String recvdata)
{
    if(recvdata == "opendoor\r")
    {
        Serial.print("open the door\r\n");
    }else if(recvdata == "closedoor\r")
    {
        Serial.print("close the door\r\n");
    }
}


int8_t RecvAscillData(WiFiServer* server)
{
    WiFiClient client = server->available(); //尝试建立客户对象
    if (client) //如果当前客户可用
    {
        Serial.println("[Client connected]");
        String readBuff;
        while (client.connected()) //如果客户端处于连接状态
        {
            if (client.available()) //如果有可读数据
            {
                String line = client.readStringUntil('\n'); //读取数据到换行符
                Serial.print("读取到数据：");
                Serial.println(line);
                recvHandle(line);

            }
        }
        // client.stop(); //结束当前连接:
        // Serial.println("[Client disconnected]");
    }
    return 0;
}






