#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define HEATER_PIN 9
#define HUMIDIFIER_PIN 8

DHT dht(DHTPIN, DHTTYPE);

int setTemperature = 25; // set desired temperature in Celsius
int setHumidity = 50; // set desired humidity in percentage

void setup() {
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(HUMIDIFIER_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (t < setTemperature) {
    digitalWrite(HEATER_PIN, HIGH); // turn on heater
  } else {
    digitalWrite(HEATER_PIN, LOW); // turn off heater
  }

  if (h < setHumidity) {
    digitalWrite(HUMIDIFIER_PIN, HIGH); // turn on humidifier
  } else {
    digitalWrite(HUMIDIFIER_PIN, LOW); // turn off humidifier
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");
  Serial.println(t < setTemperature ? "Heater on" : "Heater off");
  Serial.println(h < setHumidity ? "Humidifier on" : "Humidifier off");
  
  delay(2000);
}
