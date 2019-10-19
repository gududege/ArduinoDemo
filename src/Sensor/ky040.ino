#include "ArduinoSensor.h"

RotartEncoder ky040(20, 4, 3, 2);

void setup(){
    Serial.begin(9600);
}

void loop(){
    ky040.getPulsePerSecond();
    int i = ky040.getPulsePerSecond();
    Serial.println(i);
    Serial.println(ky040.getDir());
    Serial.println("next");
}