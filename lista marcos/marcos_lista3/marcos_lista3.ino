const int potPin = A0;

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  int leitura = analogRead(potPin);
  // Apaga todos os LEDs
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  
  if (leitura >= 256 && leitura < 512) { 
    digitalWrite(led1, HIGH);
  }
  else if (leitura >= 512 && leitura < 768) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else if (leitura >= 768 && leitura < 920) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  else if (leitura >= 920) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }
