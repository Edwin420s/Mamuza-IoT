#define BUZZER_PIN 18

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  tone(BUZZER_PIN, 262, 200);
  delay(250);
  tone(BUZZER_PIN, 330, 200);
  delay(250);
  tone(BUZZER_PIN, 392, 200);
  delay(250);
  tone(BUZZER_PIN, 523, 400);
  delay(1000);
}
