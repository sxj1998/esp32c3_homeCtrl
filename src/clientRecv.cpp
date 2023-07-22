#include "clientRecv.h"

const char *ssid = "2-517"; //wifi名
const char *password = "11111111";//wifi密码

IPAddress serverIP(192,168,2,100); //欲访问的服务端IP地址
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 2,1);
uint16_t serverPort = 8080;         //服务端口号

WiFiClient client; //声明一个ESP32客户端对象，用于与服务器进行连接
WiFiServer server; //声明服务器对象

void clientInit(void)
{
    WiFi.mode(WIFI_STA);
    // WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    
    if (WiFi.config(serverIP, gateway, subnet, dns, dns) == false) {
        Serial.println("Configuration failed.");
    }

    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    server.begin(8080);

}

void recvHandle(String recvdata)
{
    if(recvdata == "opendoor\r")
    {
        motorstart(1000,1);
        Serial.print("open the door\r\n");
    }else if(recvdata == "closedoor\r")
    {
        motorstart(1000,2);
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
    }
    return 0;
}






