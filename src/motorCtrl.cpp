#include "motorCtrl.h"
#include "common.h"

int t = 100; 
int channel_PWM = 3;  //使用3号通道 定时器1  总共16个通道 
// 舵机频率，那么周期也就是1/50，也就是20ms ，PWM⼀共有16个通道，0-7位⾼速通道由80Mhz时钟驱动，后⾯8个为低速通道由1Mhz
int freq_PWM = 50;  //50HZ pwm波
// PWM分辨率，取值为 0-20 之间  ，这⾥填写为10，那么后⾯的ledcWrite 这个⾥⾯填写的pwm值就在 0 - 2的10次⽅ 之间 也就是 0-1024，如果是要求不⾼的东西你可以直接拿1000去算了
int res_PWM = 10;  //分辨率  0-1024  共1025
const int  PWM_PIN = 9; //使用9号引脚

void setupMotor(void)
{
    ledcSetup(channel_PWM,freq_PWM,res_PWM);  //设置通道
    ledcAttachPin(PWM_PIN,channel_PWM);  //将引脚绑定到通道上
}

//startTimes 延时时间 moveWay 转动方向
void motorstart(uint16_t startTimes,uint8_t moveWay)
{
    Serial.printf("start move\r\n");
    setupMotor();
    if(moveWay == 1)
    {
        ledcWrite(channel_PWM,60); //20ms⾼电平为1ms左右 ，也就是1/20*1024 = 52，此时360度舵机正传5秒
    }else if(moveWay == 2)
    {
        ledcWrite(channel_PWM,91); 
    }
    
    delay(startTimes);
    ledcDetachPin(PWM_PIN);  //这个是解除IO⼝的pwm输出功能模式
}

void disableMotor(void)
{
    ledcDetachPin(PWM_PIN);  //这个是解除IO⼝的pwm输出功能模式
}