#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define PIN 12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  pixels.begin();
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  //float hi = dht.computeHeatIndex(f, h);
  if (h < 75) {
    pixels.setPixelColor(1, pixels.Color(250,0,20));
    pixels.show();
    digitalWrite(8, LOW);
  }
  else if (h > 85) {
    pixels.setPixelColor(1, pixels.Color(255,255,0));
    pixels.show();
  }
  else {
    pixels.setPixelColor(1, pixels.Color(20,150,0));
    pixels.show();
    digitalWrite(8, HIGH);
  }
  
  if (f < 72) {
    pixels.setPixelColor(0, pixels.Color(239,40,22));
    pixels.show();
    digitalWrite(8, LOW);
  }
  else if (f > 85) {
    pixels.setPixelColor(0, pixels.Color(51,255,51));
    pixels.show();
    digitalWrite(9,LOW);
  }
  else {
    pixels.setPixelColor(0, pixels.Color(0,150,20));
    pixels.show();
    digitalWrite(9, HIGH);
  }
}    
