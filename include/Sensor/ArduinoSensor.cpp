#include "ArduinoSensor.h"

float intToFloat(int integer, int decimals)
{
  if (decimals != 0){
    float d = decimals / pow(10, ceil(log10(decimals)));
    return integer + d;
  }else{
    return integer + 0.0;
  }
}

Led::Led(char p, int initValue)
{
    pin = p;
    pinMode(pin, OUTPUT);
    lightValue = initValue;
    breathingStep = 2;
    setValueToBoard();
}

Led::~Led()
{
    lightValue = 0;
    setValueToBoard();
    pinMode(pin, INPUT);
}

void Led::setPin(char p)
{
    pin = p;
}
void Led::setBreathingStep(char step)
{
    breathingStep = step;
}
void Led::setLightValue(unsigned char value)
{
    lightValue = value;
    setValueToBoard();
}

unsigned char Led::getLightValue()
{
    return lightValue;
}

void Led::breathing(unsigned char minimumValue, unsigned char maximumValue)
{
    lightValue = max(lightValue, minimumValue);
    lightValue = min(lightValue, maximumValue);
    setValueToBoard();
    lightValue = lightValue + breathingStep;
    if (lightValue <= minimumValue || lightValue >= maximumValue)
    {
        breathingStep = -breathingStep;
    }
}

void Led::setValueToBoard()
{
    analogWrite(pin, lightValue);
}

UltrasonicSensor::UltrasonicSensor(char tpin, char epin)
{
    triggerpin = tpin;
    echopin = epin;
    pinMode(triggerpin, OUTPUT);
    pinMode(echopin, INPUT);
    status = ready;
}

UltrasonicSensor::~UltrasonicSensor()
{
    digitalWrite(triggerpin, LOW);
    pinMode(triggerpin, INPUT);
    pinMode(echopin, INPUT);
}

void UltrasonicSensor::startSingleTrigger()
{
    if (status == ready)
    {
        status = busy;
        digitalWrite(triggerpin, LOW);
        digitalWrite(echopin, LOW);
        delayMicroseconds(5);
        digitalWrite(triggerpin, HIGH);
        delayMicroseconds(triggertime);
        digitalWrite(triggerpin, LOW);
        unsigned int scaletime = pulseIn(echopin, HIGH, 1000000);
        result = (scaletime * sonicspeedinseconds / 2000);
        status = done;
    }
    else
    {
        result = -1;
    }
}

unsigned short int UltrasonicSensor::getResult()
{
    if (status == done)
    {
        status = ready;
        return result;
    }
    return 0;
}

TemperatureAndHumiditySensor ::TemperatureAndHumiditySensor(char pin)
{
    datapin = pin;
    pinMode(datapin, OUTPUT);
    digitalWrite(datapin, HIGH);
    status = error;
}

TemperatureAndHumiditySensor::~TemperatureAndHumiditySensor() {}

void TemperatureAndHumiditySensor::initSensor()
{
    if (status != busy or status != done)
    {
        status = busy;
        digitalWrite(datapin, LOW);
        delay(20);
        digitalWrite(datapin, HIGH);
        pinMode(datapin, INPUT);
        char count = 0;
        while (count <= 50)
        {
            if (digitalRead(datapin) == LOW)
                break;
            delayMicroseconds(2);
            count++;
        }
        if (digitalRead(datapin) == HIGH)
        {
            status = timeouterror;
            return;
        }
        delayMicroseconds(80);
        count = 0;
        while (count <= 50)
        {
            if (digitalRead(datapin) == HIGH)
                break;
            delayMicroseconds(2);
            count++;
        }
        if (digitalRead(datapin) == LOW)
        {
            status = timeouterror;
            return;
        }
    }
}

bool TemperatureAndHumiditySensor::readBit()
{
    char count = 0;
    while (count <= 20)
    {
        if (digitalRead(datapin) == LOW)
        {
            unsigned short int hightime = pulseIn(datapin, HIGH, 1000);
            if (hightime == 0)
            {
                status = timeouterror;
                return 0;
            }
            else
            {
                //low: 23-27us, high: 68-74us
                return hightime >= 40 ? 1 : 0;
            }
        }
        count++;
        delayMicroseconds(2);
    }
    status = timeouterror;
    return 0;
}

char TemperatureAndHumiditySensor::readByte()
{
    char c = 0;
    bool b;
    char j;
    for (j = 0; j < 8; j++)
    {

        b = readBit();
        if (status == busy)
        {
            c = c << 1;
            c |= b;           
        }
        else
        {
            return 0;
        }
    }
    return c;
}

void TemperatureAndHumiditySensor::startSingleTrigger()
{
    //init dht11
    initSensor();
    //read data from wire
    if (status != busy)
    {
        return;
    }
    short int i;
    for (i = 0; i < 5; i++)
    {
        if (status == busy)
        {
            data[i] = readByte();
        }
        else
        {
            return;
        }
    }
    //check sum
    if (data[4] == data[0] + data[1] + data[2] + data[3])
    {
        resultHum = intToFloat((int)data[0], (int)data[1]);
        resultTemp = intToFloat((int)data[2], (int)data[3]);      
        status = done;
    }
    else
    {
        status = dataerror;
        return;
    }
}

void TemperatureAndHumiditySensor::getResult(float& temp, float& hum)
{
    if (status == done)
    {
        temp = resultTemp;
        hum = resultHum;
        status = ready;
    }
    else
    {
        temp = errorTemp;
        hum = errorHum;
    }
    pinMode(datapin, OUTPUT);
    digitalWrite(datapin, HIGH);
}

RotartEncoder::RotartEncoder(unsigned short int stepPerCircle, char A, char B, char Z):Apin(A),Bpin(B),Zpin(Z),stepPerRevolution(stepPerCircle)
{
    direction = Null;
    pps = 0;
    pinMode(Apin, INPUT);
    pinMode(Bpin, INPUT);
    pinMode(Zpin, INPUT);
}

RotartEncoder::~RotartEncoder()
{
}

void RotartEncoder::updatePulse(){
    bool aVal = digitalRead(Apin);
    if (aVal != prevAValue and aVal)
    {
        direction = digitalRead(Bpin) == false ? CW : CCW;
        pps ++;
    }
    prevAValue = aVal;
}

unsigned short int RotartEncoder::getPulsePerSecond(){
    unsigned long prevTime = millis();
    pps = 0;
    while (millis() - prevTime <= 1000)
    {
        updatePulse();        
    }
    return pps;
}

Dir RotartEncoder::getDir(){
    return direction;
}
