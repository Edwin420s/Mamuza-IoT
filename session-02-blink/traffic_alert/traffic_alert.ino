#define RED_PIN 25
#define GREEN_PIN 26

void cycleLights() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(RED_PIN, HIGH);
    delay(500);
    digitalWrite(RED_PIN, LOW);
    delay(500);
  }
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);
  digitalWrite(GREEN_PIN, LOW);
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  cycleLights();
}
