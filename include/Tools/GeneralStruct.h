#ifndef GENERALSTRUCT_H
#define GENERALSTRUCT_H

enum SensorStatus
{   
    ready,
    busy,
    done,
    error,
    timeouterror,
    dataerror
};

enum Dir
{
    CCW = -1,
    Null = 0,
    CW = 1
};

#endif