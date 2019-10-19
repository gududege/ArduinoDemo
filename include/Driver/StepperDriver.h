#ifndef STEPPERDRIVER_H
#define STEPPERDRIVER_H

#include <Tools/GeneralStruct.h>
#include <Arduino.h>

#define microsecondsInAMin 60 * 1E6
#define secondInMin 60

struct DriverInfo
{
    //by us
    const unsigned char minPhaseCoolDown = 100;
    const unsigned char beat = 8;
    //CW
    const char phase[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08};
    const unsigned char stepPerRevolution = 64;
    //internal gear
    const unsigned char gear = 64;
    const unsigned short int stepPerOutputRevolution = stepPerRevolution * gear;
    //In motor manual,  550 pps
    const unsigned short int maxStartSpeed = 55 * secondInMin / beat / (stepPerOutputRevolution / 10);
    //rpm
    const unsigned short int maxSpeed = microsecondsInAMin / minPhaseCoolDown / stepPerOutputRevolution;
};

class StepperDriver
{
private:
    DriverInfo driverInfo;
    unsigned short int speedSetPoint = 0;
    unsigned short int actualSpeed = 0;
    char currentPhaseIndex;
    unsigned char currentPhaseCoolDown;
    double step;
    Dir direction;
    const char A;
    const char B;
    const char C;
    const char D;
    void setPhaseToDrive(char phase);
public:
    StepperDriver(char Apin, char Bpin, char Cpin, char Dpin);
    ~StepperDriver();
    //by rpm
    //For 28BYJ-48 should be set range 2 to 20
    void setSpeed(unsigned int speed);
    //by circle
    void setPostion(float circle);
};

#endif