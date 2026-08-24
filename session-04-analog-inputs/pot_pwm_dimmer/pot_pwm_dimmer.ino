#define POT_PIN 34
#define LED_PIN 25

const int pwmFreq = 5000;
const int pwmResolution = 8;

void setup() {
  Serial.begin(115200);
  
  ledcAttach(LED_PIN, pwmFreq, pwmResolution);
  
  pinMode(POT_PIN, INPUT);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  
  int pwmValue = map(potValue, 0, 4095, 0, 255);
  
  ledcWrite(LED_PIN, pwmValue);
  
  Serial.println(pwmValue);
  
  delay(15);
}
