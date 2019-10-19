#include "Timer.h"

Timer::Timer()
{
    state = ready;
    result = false;
}

Timer::~Timer()
{
}

unsigned long Timer::currentTime(){
    return micros();
}

void Timer::start(unsigned long Time)
{
    if (state == ready)
    {
        PT = Time;
        ATime = currentTime();
        state = busy;
    }
}

void Timer::reset()
{
    state = ready;
    result = false;
}

bool Ton::complete()
{
    if (state == busy)
    {
        result = currentTime() - ATime >= PT;
        state = result == true ? ready : busy;
    }
    return result;
}

bool Tof::complete()
{
    if (state == busy)
    {
        result = currentTime() - ATime <= PT;
        state = result == false ? ready : busy;
    }
    return result;
}