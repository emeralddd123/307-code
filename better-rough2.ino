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
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int setTemperature = 25; // set desired temperature in Celsius
int setHumidity = 50;    // set desired humidity in percentage

void setup()
{
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(HUMIDIFIER_PIN, OUTPUT);
    Serial.begin(9600);
    dht.begin();
    lcd.begin(16, 2);
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
        lcd.clear();
        lcd.print("Failed to read");
        lcd.setCursor(0, 1);
        lcd.print("DHT sensor!");
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

    lcd.clear();
    lcd.print("Humidity: ");
    lcd.print(h);
    
    lcd
