#include <WiFi.h>
#include "common.h"



void setup()
{
    Serial.begin(115200);
    Serial.println();
    clientInit();
    setupMotor();

}

void loop()
{
    RecvAscillData(&server);
    // motorstart(1000,1);
    // delay(1000);
    // motorstart(1000,2);
    // delay(1000);
}

