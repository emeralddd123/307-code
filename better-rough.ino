#include <DHT.h>
#include <Keypad.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define HEATER_PIN 9
#define HUMIDIFIER_PIN 8

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

DHT dht(DHTPIN, DHTTYPE);

int setTemperature = 25; // set desired temperature in Celsius
int setHumidity = 50;    // set desired humidity in percentage

void setup()
{
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(HUMIDIFIER_PIN, OUTPUT);
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
    char key = keypad.getKey();

    if (key == 'A')
    {
        setTemperature++;
    }
    else if (key == 'B')
    {
        setTemperature--;
    }
    else if (key == 'C')
    {
        setHumidity++;
    }
    else if (key == 'D')
    {
        setHumidity--;
    }

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    if (t < setTemperature)
    {
        digitalWrite(HEATER_PIN, HIGH); // turn on heater
    }
    else
    {
        digitalWrite(HEATER_PIN, LOW); // turn off heater
    }

    if (h < setHumidity)
    {
        digitalWrite(HUMIDIFIER_PIN, HIGH); // turn on humidifier
    }
    else
    {
        digitalWrite(HUMIDIFIER_PIN, LOW); // turn off humidifier
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("°C");
    Serial.print("Desired Temperature: ");
    Serial.print(setTemperature);
    Serial.println("°C");
    Serial.print("Desired Humidity: ");
    Serial.print(setHumidity);
    Serial.println("%");
    delay(2000);
}
