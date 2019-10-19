#ifndef ARDUINO_SENSOR_H
#define ARDUINO_SENSOR_H
#include <Arduino.h>
#include "Tools/GeneralStruct.h"

//Use for led in pwm pin
class Led
{
private:
    char pin;
    char breathingStep;
    unsigned char lightValue;
public:
    Led(char p, int initvalue);
    ~Led();
    void setPin(char p);
    void setBreathingStep(char step);
    void setLightValue(unsigned char value);
    unsigned char getLightValue();
    void setValueToBoard();
    void breathing(unsigned char minimumvalue, unsigned char maximumvalue);
};

//Use for HC-SR04
class UltrasonicSensor
{
private:
    char triggerpin;
    char echopin;
    //trigger 10us
    const char triggertime = 15;
    //in millimeters
    unsigned short int result;
    const short int sonicspeedinseconds = 340;
    SensorStatus status;

public:
    UltrasonicSensor(char trigpin, char echopin);
    ~UltrasonicSensor();
    void startSingleTrigger();
    unsigned short int getResult();
    // void startCycleTrigger();
    // void endCycleTrigger();
    // int processResult();
};

//Use for dht11
class TemperatureAndHumiditySensor
{
private:
    char datapin;
    char data[6];
    const float errorTemp = 999.9;
    const float errorHum = 999.9;
    float resultTemp;
    float resultHum;
    SensorStatus status;
    void initSensor();
    bool readBit();
    char readByte();    
public:
    TemperatureAndHumiditySensor(char pin);
    ~TemperatureAndHumiditySensor();
    void startSingleTrigger();
    void getResult(float& temp, float& hum);
};

class RotartEncoder
{
private:
    const char Apin;
    const char Bpin;
    const char Zpin;
    const unsigned short int stepPerRevolution;
    bool prevAValue;
    Dir direction;
    unsigned int rpm;
    unsigned short int pps;
    void updatePulse();
public:
    RotartEncoder(unsigned short int stepPerCircle, char A, char B, char Z);
    ~RotartEncoder();
    unsigned short int getPulsePerSecond();
    Dir getDir();
};
#endif
