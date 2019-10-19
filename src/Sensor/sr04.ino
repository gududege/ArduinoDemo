#include <ArduinoSensor.h>

const char trigpin = 2;
const char echopin = 3;
UltrasonicSensor us = UltrasonicSensor(trigpin, echopin);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    us.startSingleTrigger();
    Serial.println(us.getResult());
    delay(3000);
}