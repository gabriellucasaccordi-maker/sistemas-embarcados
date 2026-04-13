const int botaoA = 2;    
const int botaoB = 3;    
const int led1   = 9;    

const unsigned long TEMPO_ACESO = 5000; 

bool ledAtivo              = false;
unsigned long tempoInicio  = 0;

bool estadoAnteriorBotaoA  = HIGH;
bool estadoAnteriorBotaoB  = HIGH;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);

  Serial.begin(9600);
  Serial.println("Sistema pronto.");
}

void loop() {
  bool estadoA = digitalRead(botaoA);
  bool estadoB = digitalRead(botaoB);
  unsigned long agora = millis();

 
  if (estadoA == LOW && estadoAnteriorBotaoA == HIGH) {
    delay(50); // Debounce
    if (digitalRead(botaoA) == LOW) {
      ledAtivo     = true;
      tempoInicio  = millis();
      digitalWrite(led1, HIGH);

      Serial.println("LED aceso por 5 segundos.");
    }
  }

 
  if (estadoB == LOW && estadoAnteriorBotaoB == HIGH) {
    delay(50); // Debounce
    if (digitalRead(botaoB) == LOW) {
      if (ledAtivo) {
        ledAtivo = false;
        digitalWrite(led1, LOW);

        unsigned long decorrido = (agora - tempoInicio) / 1000;
        Serial.print("LED cancelado após ");
        Serial.print(decorrido);
        Serial.println("s.");
      }
    }
  }


  if (ledAtivo && (agora - tempoInicio >= TEMPO_ACESO)) {
    ledAtivo = false;
    digitalWrite(led1, LOW);
    Serial.println("LED apagado automaticamente.");
  }

  estadoAnteriorBotaoA = estadoA;
  estadoAnteriorBotaoB = estadoB;
}
