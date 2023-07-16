#include <WiFi.h>
#include "common.h"

const char *ssid = "2-517"; //wifi名
const char *password = "11111111";//wifi密码

const IPAddress serverIP(192,168,2,7); //欲访问的服务端IP地址
uint16_t serverPort = 8080;         //服务端口号

WiFiClient client; //声明一个ESP32客户端对象，用于与服务器进行连接
WiFiServer server; //声明服务器对象

int t = 100; 
int channel_PWM = 3;  //使用3号通道 定时器1  总共16个通道 
// 舵机频率，那么周期也就是1/50，也就是20ms ，PWM⼀共有16个通道，0-7位⾼速通道由80Mhz时钟驱动，后⾯8个为低速通道由1Mhz
int freq_PWM = 50;  //50HZ pwm波
// PWM分辨率，取值为 0-20 之间  ，这⾥填写为10，那么后⾯的ledcWrite 这个⾥⾯填写的pwm值就在 0 - 2的10次⽅ 之间 也就是 0-1024，如果是要求不⾼的东西你可以直接拿1000去算了
int res_PWM = 10;  //分辨率  0-1024  共1025
const int  PWM_PIN = 9; //使用4号引脚

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
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


    ledcSetup(channel_PWM,freq_PWM,res_PWM);  //设置通道
    ledcAttachPin(PWM_PIN,channel_PWM);  //将引脚绑定到通道上
}

void loop()
{
    // RecvAscillData(&server);
    ledcWrite(channel_PWM,52); //20ms⾼电平为1ms左右 ，也就是1/20*1024 = 52，此时360度舵机正传5秒
    delay(1000);
    ledcDetachPin(PWM_PIN);  //这个是解除IO⼝的pwm输出功能模式
}





// //正传t秒 停止t秒 反转t秒 停止t秒 循环...
// void loop() {

// //   delay(t);
// //   ledcWrite(channel_PWM, 77);  //20ms⾼电平为1.5ms左右 ，也就是1.5/20*1024 = 77，此时360度舵机⼏乎停转
// //   delay(t);
// //   ledcWrite(channel_PWM, 102);  //20ms⾼电平为2ms左右 ，也就是2/20*1024 = 102，此时360度舵机反转
// //   delay(t);
// //   ledcWrite(channel_PWM, 77);  //20ms⾼电平为1.5ms左右 ，也就是1.5/20*1024 = 77，此时360度舵机⼏乎停转
// //   delay(t);
//   //ledcDetachPin(PWM_Pin);  //这个是解除IO⼝的pwm输出功能模式

// }