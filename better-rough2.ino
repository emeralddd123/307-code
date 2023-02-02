#include <DHT.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define HEATER_PIN 9
#define HUMIDIFIER_PIN 8
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 10
#define LCD_D5 7
#define LCD_D6 6
#define LCD_D7 5

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {2, 3, 4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int setTemperature = 25; // set desired temperature in Celsius
int setHumidity = 50;    // set desired humidity in percentage

void setup()
{
    const tolerance = 3;
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(HUMIDIFIER_PIN, OUTPUT);
    Serial.begin(9600);
    dht.begin();
    lcd.begin(16, 2);
}

void loop()
{
    char key = keypad.getKey();

    if (key == '1')
    {
        setTemperature++;
        lcd.clear();
        lcd.print("Temp: ");
        lcd.print(setTemperature);
        lcd.print("°C");
        lcd.clear();
    }
    else if (key == '2')
    {
        setTemperature--;
        lcd.clear();
        lcd.print("Temp: ");
        lcd.print(setTemperature);
        lcd.print("°C");
        lcd.clear();
    }
    else if (key == '3')
    {
        setHumidity++;
        lcd.clear();
        lcd.print("Humid: ");
        lcd.print(setHumidity);
        lcd.print("%");
        lcd.clear();
    }
    }
    else if (key == '4')
    {
        setHumidity--;
        lcd.clear();
        lcd.print("Humid: ");
        lcd.print(setHumidity);
        lcd.print("%");
        lcd.clear();
    }

    float h = dht.readHumidity();
    delay(50);
    float t = dht.readTemperature();
    delay(50);

    if (isnan(h) || isnan(t))
    {
        if (isnan(h))
        {
            lcd.clear();
            lcd.print("Failed to read Humidity");
        }
        else if ((isnan(t)))
        {
            lcd.clear();
            lcd.print("Failed to read Temp");
        }

        return;
    }

    if ((t - tolerance) < setTemperature)
    {
        digitalWrite(HEATER_PIN, HIGH); // turn on heater
    }
    else if ((t + tolerance) > setTemperature)
    {
        digitalWrite(HEATER_PIN, LOW); // turn off heater
    }

    if ((h - tolerance) < setHumidity)
    {
        digitalWrite(HUMIDIFIER_PIN, HIGH); // turn on humidifier
    }
    else if ((h + tolerance) > setHumidity)
    {
        digitalWrite(HUMIDIFIER_PIN, LOW); // turn off humidifier
    }

    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("°C")

    lcd.setCursor(0, 1);
    lcd.print("Humid: ");
    lcd.print(h);
    lcd.print("%")

    delay(1500)
}