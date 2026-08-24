#define SOIL_ANALOG_PIN 34 
#define ONBOARD_LED     2  

void setup() {
    Serial.begin(115200);
    pinMode(ONBOARD_LED, OUTPUT);
}

float readFilteredSoilVWC() {
    const int totalSamples = 11; // Odd tracking matrix window size
    int samples[totalSamples];
    
    // 1. Array sample gathering
    for(int i = 0; i < totalSamples; i++) {
        samples[i] = analogRead(SOIL_ANALOG_PIN);
        delay(15);
    }
    
    // 2. Clear transient circuit spikes using a simple bubble sort filter
    for(int i = 0; i < totalSamples-1; i++) {
        for(int j = 0; j < totalSamples-i-1; j++) {
            if(samples[j] > samples[j+1]) {
                int temp = samples[j];
                samples[j] = samples[j+1];
                samples[j+1] = temp;
            }
        }
    }
    
    int medianRaw = samples[totalSamples / 2];
    
    // 3. Translate raw output directly into Volumetric Water Content percentage curves
    float vwcPercentage = map(medianRaw, 3400, 1200, 0, 100);
    return constrain(vwcPercentage, 0.0, 100.0);
}

void loop() {
    float soilMoisture = readFilteredSoilVWC();
    Serial.print("AGRI_DATA | VWC: ");
    Serial.print(soilMoisture);
    Serial.println("%");
    
    digitalWrite(ONBOARD_LED, HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED, LOW);
    delay(1900);
}
