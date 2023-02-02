#include <DHT.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN A2
#define DHTTYPE DHT11
#define HEATER_PIN 12
#define HUMIDIFIER_PIN 8
#define FAN_PIN 11


LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

const int tolerance = 5;

byte rowPins[ROWS] = { 8,7,6,5 };
byte colPins[COLS] = { 4,3,2 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

DHT dht(DHTPIN, DHTTYPE);

int setTemperature = 36;  // set desired temperature in Celsius
int setHumidity = 50;     // set desired humidity in percentage

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(HUMIDIFIER_PIN, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.print("Test Chamber");
  delay(2000);
  
}

void loop() {
float h = dht.readHumidity();
delay(20);
float t = dht.readTemperature();
delay(20);


if (isnan(h)) {
  lcd.clear();
  lcd.print("Failed to read Humidity");
} else if ((isnan(t))) {
  lcd.clear();
  lcd.print("Failed to read Temp");
}

if ((t + 0.3) > setTemperature) {
  digitalWrite(HEATER_PIN, LOW);  // turn off heater
  digitalWrite(FAN_PIN, HIGH); // FAN PIN 11
} else if ((t-0.3) < setTemperature) {
  digitalWrite(HEATER_PIN, HIGH);
  digitalWrite(FAN_PIN, LOW);  // turn on heater
// } else if (t == setTemperature){
//   digitalWrite(HEATER_PIN, LOW);
}

// if ((h - tolerance) < setHumidity) {
//   digitalWrite(HUMIDIFIER_PIN, HIGH);  // turn on humidifier
// } else if ((h + tolerance) > setHumidity) {
//   digitalWrite(HUMIDIFIER_PIN, LOW);  // turn off humidifier
//   digitalWrite(FAN_PIN, LOW);  // turn off FAN
// }

delay(300);

lcd.clear();
lcd.print("Temp: ");
lcd.print(t);
lcd.print("°C");

lcd.setCursor(0, 1);
lcd.print("Humid: "); 
lcd.print(h);
lcd.print("%");

char key = keypad.getKey();
delay(20);

if (key == '1') {
    setTemperature++;
    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(setTemperature);
    lcd.print("°C");
    delay(100);
   
  } else if (key == '2') {
    setTemperature--;
    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(setTemperature);
    lcd.print("°C");
    delay(100);
    
  } else if (key == '3') {
    setHumidity++;
    lcd.clear();
    lcd.print("Humid: ");
    lcd.print(setHumidity);
    lcd.print("%");
    delay(100);
    
  } else if (key == '4') {
  setHumidity--;
  lcd.clear();
  lcd.print("Humid: ");
  lcd.print(setHumidity);
  lcd.print("%");
  delay(100);

  
}}