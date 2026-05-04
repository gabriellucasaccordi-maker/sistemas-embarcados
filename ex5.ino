int leds[3]  = {9, 10, 11};       
int intervalo[3] = {2000, 1000, 3000}; 

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], HIGH);
    delay(intervalo[i]);
    digitalWrite(leds[i], LOW);
  }
}