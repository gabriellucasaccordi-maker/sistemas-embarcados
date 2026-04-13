const int botaoA = 2;    
const int led1   = 9;     


const int niveis[]  = {0, 64, 128, 191, 255};
const int totalNiveis = 5;

int  nivelAtual          = 0;
bool estadoAnteriorBotao = HIGH;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  analogWrite(led1, niveis[nivelAtual]);

  Serial.begin(9600);
  Serial.println("Brilho: 0%");
}

void loop() {
  bool estadoAtual = digitalRead(botaoA);

  
  if (estadoAtual == LOW && estadoAnteriorBotao == HIGH) {
    delay(50);

    if (digitalRead(botaoA) == LOW) {
      nivelAtual = (nivelAtual + 1) % totalNiveis;
      analogWrite(led1, niveis[nivelAtual]);

      Serial.print("Brilho: ");
      Serial.print(nivelAtual * 25);
      Serial.println("%");
    }
  }

  estadoAnteriorBotao = estadoAtual;
}
