const int botaoA = 12;
const int botaoB = 13;
const int ledPrensa = 2; 
const int ledErro = 5;   
unsigned long tempoPrimeiroClique = 0;
bool esperandoSegundoBotao = false;
bool comandoFinalizado = false; 

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(ledPrensa, OUTPUT);
  pinMode(ledErro, OUTPUT);
}

void loop() {
  bool estadoA = !digitalRead(botaoA);
  bool estadoB = !digitalRead(botaoB);
  unsigned long agora = millis();

  
  if ((estadoA || estadoB) && !esperandoSegundoBotao && !comandoFinalizado) {
    tempoPrimeiroClique = agora;
    esperandoSegundoBotao = true;
  }

  
  if (esperandoSegundoBotao && !comandoFinalizado) {
    
   
    if (estadoA && estadoB) {
      if (agora - tempoPrimeiroClique <= 500) {
        digitalWrite(ledPrensa, HIGH);
        digitalWrite(ledErro, LOW);
      } else {
        digitalWrite(ledPrensa, LOW);
        digitalWrite(ledErro, HIGH);
      }
      comandoFinalizado = true; 
    }

    
    if (agora - tempoPrimeiroClique > 500 && !comandoFinalizado) {
      digitalWrite(ledErro, HIGH);
      digitalWrite(ledPrensa, LOW);
      comandoFinalizado = true; 
    }
  }

  
  if (!estadoA && !estadoB) {
    digitalWrite(ledPrensa, LOW);
    digitalWrite(ledErro, LOW);
    esperandoSegundoBotao = false;
    comandoFinalizado = false;
  }
}