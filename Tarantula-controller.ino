#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define PIN 12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(8, OUTPUT); //relay 1 - heater
  pinMode(9, OUTPUT); //relay 2 - exhaust fan
  /* for debugging
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  */
  dht.begin();
  pixels.begin();
  
  digitalWrite(8, HIGH); //set relays to OFF
  digitalWrite(9, HIGH); //set relays to OFF
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

  if (h < 75) {
    pixels.setPixelColor(1, pixels.Color(250,0,20));
    pixels.show();
    digitalWrite(8, LOW); //turn heater relay ON
  }
  else if (h > 85) {
    pixels.setPixelColor(1, pixels.Color(255,255,0));
    pixels.show();
    digitalWrite(9, LOW); //turn fan relay ON
  }
  else {
    pixels.setPixelColor(1, pixels.Color(20,150,0));
    pixels.show();
    digitalWrite(8, HIGH); //turn heater relay OFF (humidity is fine!)
    // the next conditional may turn the heater back on, though.
  }
  
  if (f < 72) {
    pixels.setPixelColor(0, pixels.Color(239,40,22));
    pixels.show();
    digitalWrite(8, LOW); //turn heater on
  }
  else if (f > 85) {
    pixels.setPixelColor(0, pixels.Color(51,255,51));
    pixels.show();
    digitalWrite(9,LOW); //Too hot, turn fan on
    digitalWrite(8, HIGH); //too hot turn heater off
  }
  else {
    pixels.setPixelColor(0, pixels.Color(0,150,20));
    pixels.show();
    digitalWrite(9, HIGH); //temp is fine, shut fan off
  }

  /* debugging
    Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  */
}
