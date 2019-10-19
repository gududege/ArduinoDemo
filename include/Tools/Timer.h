#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
protected:
    unsigned long ATime;
    unsigned long PT;
    unsigned long currentTime();
    bool result;
    enum TimerState
    {
        ready,
        busy
    } state;

public:
    Timer();
    ~Timer();
    unsigned long ET;
    //bu us
    void start(unsigned long Time);
    virtual bool complete();
    void reset();
};

class Ton : public Timer
{
public:
    bool complete() final;
};

class Tof : public Timer
{
public:
    bool complete() final;
};

#endif
