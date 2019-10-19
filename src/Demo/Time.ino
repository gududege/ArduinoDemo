#include <Tools/Timer.h>

Ton t1 = Ton();

void setup(){
    Serial.begin(9600);
}

void loop(){
    t1.start(5000 * 1000L);
    if (t1.complete())
    {
        Serial.println(String(micros()));
    }
}
