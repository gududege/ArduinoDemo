#include "StepperDriver.h"
#include <Arduino.h>

StepperDriver::StepperDriver(char Apin, char Bpin, char Cpin, char Dpin) : A(Apin), B(Bpin), C(Cpin), D(Dpin)
{
    direction = Null;
    currentPhaseIndex = 0;
}

StepperDriver::~StepperDriver()
{
}

void StepperDriver::setPhaseToDrive(char phase)
{
    bitRead(phase, 1);
    digitalWrite(A, (phase & 0x01) == 0x01);
    digitalWrite(B, (phase & 0x02) == 0x02);
    digitalWrite(C, (phase & 0x04) == 0x04);
    digitalWrite(D, (phase & 0x08) == 0x08);
    delayMicroseconds(currentPhaseCoolDown);
}

void StepperDriver::setSpeed(unsigned int speed)
{
    speedSetPoint = speed;
    if (speed != 0 and speedSetPoint <= driverInfo.maxSpeed)
    {
        actualSpeed = speed;
        currentPhaseCoolDown = microsecondsInAMin / speed / driverInfo.stepPerOutputRevolution;
    }
}

void StepperDriver::setPostion(float circle)
{
    if (actualSpeed > 0)
    {
        if (circle > 0)
        {
            direction = CW;
            step = direction * circle * driverInfo.stepPerOutputRevolution;
        }
        else if (circle < 0)
        {
            direction = CCW;
            step = direction * circle * driverInfo.stepPerOutputRevolution;
        }
        else
        {
            return;
        }
        while (step-- > 0)
        {
            if (direction == CW)
            {
                currentPhaseIndex = (currentPhaseIndex + direction) % driverInfo.beat;
            }
            else if (direction == CCW)
            {
                currentPhaseIndex = (currentPhaseIndex + direction) >= 0 ? currentPhaseIndex + direction : driverInfo.beat - 1;
            }
            setPhaseToDrive(driverInfo.phase[currentPhaseIndex]);
        }
    }
}