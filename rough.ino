#include <SoftwareSerial.h>

#include <Wire.h>

#include <Adafruit_SH1106.h>

#define OLED_ADDRESS 0x3C

#define OLED_RESET -1

Adafruit_SH1106 display(OLED_RESET);

#include "DHT.h"

DHT dht;

int humidity = 0;

void setup()

{

    Serial.begin(9600);

    dht.setup(2);

    pinMode(6, OUTPUT);

    pinMode(11, OUTPUT);

    display.begin(SH1106_SWITCHCAPVCC, OLED_ADDRESS);

    display.clearDisplay();
}

void loop()

{

    delay(dht.getMinimumSamplingPeriod());

    humidity = dht.getHumidity();

    display.setTextSize(1);

    display.setTextColor(WHITE);

    display.setCursor(27, 2);

    display.print("CIRCUIT DIGEST");

    display.setTextSize(1);

    display.setCursor(35, 20);

    display.print("HUMIDITY(%)");

    display.display();

    display.setTextSize(2);

    display.setCursor(55, 40);

    display.print(humidity);

    display.display();

    delay(50);

    display.clearDisplay();

    if (humidity < 85)

    {

        digitalWrite(6, HIGH);

        digitalWrite(11, HIGH);
    }

    else

    {

        digitalWrite(6, LOW);

        digitalWrite(11, LOW);
    }
}
