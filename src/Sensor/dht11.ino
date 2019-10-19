#include "ArduinoSensor.h"

const char pin = 5;
TemperatureAndHumiditySensor dht11 = TemperatureAndHumiditySensor(pin);
float t = 0;
float h = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    dht11.startSingleTrigger();
    dht11.getResult(t, h);
    Serial.println(t);
    Serial.println(h);
    delay(2000);
}