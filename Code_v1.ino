include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define MQ7#_PIN A0
#define BUZZER_PIN 8

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Threshold for alert (adjust after testing)
int threshold = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);
  display.println("MQ7 Starting...");
  display.display();

  delay(2000);
}

void loop() {
  int sensorValue = analogRead(MQ7_PIN);

  // Serial output
  Serial.print("CO Level: ");
  Serial.println(sensorValue);

  // OLED display
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("CO Monitor");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(sensorValue);

  display.setTextSize(1);
  display.setCursor(0, 50);

  // Alert system
  if (sensorValue > threshold) {
    display.print("Status: DANGER!");
    tone(BUZZER_PIN, 3500);
  } else {
    display.print("Status: SAFE");
    noTone(BUZZER_PIN);
  }

  display.display();

  delay(1000);
}
