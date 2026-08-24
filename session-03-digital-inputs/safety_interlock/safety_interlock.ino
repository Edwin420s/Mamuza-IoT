#define BUTTON_PIN 18
#define TOUCH_PIN 4
#define LED_PIN 2
#define BUZZER_PIN 13

bool wasActive = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  int touchState = digitalRead(TOUCH_PIN);

  if (buttonState == LOW && touchState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    wasActive = true;
  } else {
    digitalWrite(LED_PIN, LOW);
    if (wasActive) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      wasActive = false;
    }
  }
}
