const int leds[] = {2, 3, 4, 5}; // pinos dos LEDs
const int totalLeds = 4;

unsigned long intervalo = 200; // 200 ms
unsigned long tempoAnterior = 0;

int ledAtual = 0;

void setup() {
  for (int i = 0; i < totalLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;

    
    for (int i = 0; i < totalLeds; i++) {
      digitalWrite(leds[i], LOW);
    }

   
    digitalWrite(leds[ledAtual], HIGH);

   
    ledAtual++;

   
    if (ledAtual >= totalLeds) {
      ledAtual = 0;
    }
  }
}
