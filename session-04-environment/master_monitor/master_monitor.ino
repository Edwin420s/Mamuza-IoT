#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BUZZER_PIN 18
#define TEMP_THRESHOLD 30.0 

void soundAlarm() {
  tone(BUZZER_PIN, 1000, 150);
  delay(150);
  tone(BUZZER_PIN, 1600, 150);
  delay(150);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED allocation failed!");
    for (;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.println("Initializing System...");
  display.display();
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  display.clearDisplay();
  
  if (isnan(temp) || isnan(hum)) {
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.println("Sensor Read Error!");
    display.display();
    delay(2000);
    return;
  }
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ENVIRONMENT MONITOR");
  display.drawLine(0, 10, 128, 10, WHITE);
  
  display.setCursor(0, 16);
  display.print("Temp: ");
  display.setTextSize(2);
  display.print(temp, 1);
  display.setTextSize(1);
  display.println(" C");
  
  display.setCursor(0, 36);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.print(hum, 1);
  display.setTextSize(1);
  display.println("%");
  
  display.drawLine(0, 52, 128, 52, WHITE);
  display.setCursor(0, 55);
  
  if (temp >= TEMP_THRESHOLD) {
    display.print("STATUS: HIGH TEMP!");
    display.display();
    soundAlarm();
  } else {
    display.print("STATUS: NORMAL");
    display.display();
    delay(2000);
  }
}
