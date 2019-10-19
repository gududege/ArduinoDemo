#include <Arduino.h>
#include <Driver/StepperDriver.h>


const char A = 3;
const char B = 5;
const char C = 6;
const char D = 9;

StepperDriver driver(A, B, C, D);

void setup()
{
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    for (int i = 16; i < 21; i++)
    {
        driver.setSpeed(i);
        Serial.println(i);        
        driver.setPostion((i % 2 == 0) ? 1 : -1);
        delay(1000);
    }
}