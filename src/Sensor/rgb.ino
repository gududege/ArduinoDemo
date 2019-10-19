#include <ArduinoSensor.h>
#include <ArduinoJson.h>

const char R_PIN = 9;
const char G_PIN = 10;
const char B_PIN = 11;
String status = "R_PIN: ";
Led rLed = Led(R_PIN, 0);
Led gLed = Led(G_PIN, 50);
Led bLed = Led(B_PIN, 100);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    static String json;
    static boolean flash = false;
    boolean newresult = false;
    if (Serial.available())
    {
        json = "";
        newresult = true;
    }

    while (Serial.available())
    {
        json += Serial.readString();
    }
    //json messgae like {"flash": false, "values": [0, 100, 200], "step": 2}
    if (newresult)
    {
        StaticJsonDocument<300> doc;
        if (!deserializeJson(doc, json))
        {
            flash = doc["flash"];
            rLed.setLightValue(doc["values"][0]);
            gLed.setLightValue(doc["values"][1]);
            bLed.setLightValue(doc["values"][2]);
            rLed.setBreathingStep(doc["step"]);
            gLed.setBreathingStep(doc["step"]);
            bLed.setBreathingStep(doc["step"]);
        }
    }
    if (flash)
    {
        rLed.breathing(0, 200);
        gLed.breathing(0, 200);
        bLed.breathing(0, 200);
    }
    Serial.println(status + rLed.getLightValue() + "; G_PIN: " + gLed.getLightValue() + "; B: " + bLed.getLightValue());
    delay(30);
}