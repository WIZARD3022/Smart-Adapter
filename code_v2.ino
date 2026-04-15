#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ESP32 Pins
#define MQ7_PIN 34
#define BUZZER_PIN 25
#define RELAY_PIN 26

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Thresholds
int SAFE_LIMIT = 1200;
int WARNING_LIMIT = 2000;
int DANGER_LIMIT = 3000;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF initially
  digitalWrite(RELAY_PIN, HIGH);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);
  display.println("MQ7 Warming...");
  display.display();

  delay(20000);
}

void loop() {
  // Smooth reading
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(MQ7_PIN);
    delay(10);
  }
  int sensorValue = sum / 10;

  Serial.print("CO Value: ");
  Serial.println(sensorValue);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("CO Monitor");

  display.setTextSize(2);
  display.setCursor(0, 18);
  display.print(sensorValue);

  display.setTextSize(1);
  display.setCursor(0, 50);

  // 🚨 Alert Logic
  if (sensorValue > DANGER_LIMIT) {
    display.print("DANGER!");

    // Buzzer fast beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);

    // 🔴 Relay ON (activate device)
    digitalWrite(RELAY_PIN, LOW);
  } 
  else if (sensorValue > WARNING_LIMIT) {
    display.print("WARNING");

    // Buzzer slow beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);

    // 🟡 Relay ON (optional)
    digitalWrite(RELAY_PIN, LOW);
  } 
  else {
    display.print("SAFE");

    digitalWrite(BUZZER_PIN, LOW);

    // 🟢 Relay OFF
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
  }

  display.display();
}
