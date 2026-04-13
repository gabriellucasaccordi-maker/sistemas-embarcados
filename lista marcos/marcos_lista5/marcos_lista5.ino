const int botaoA = 2;      // Botão A — controla o brilho
const int botao3 = 4;      // Botão 3 — chave de permissão
const int led1   = 9;      // LED 1 (pino PWM)

const int niveis[]    = {0, 64, 128, 191, 255};
const int totalNiveis = 5;

int  nivelAtual          = 0;
bool estadoAnteriorBotaoA = HIGH;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  analogWrite(led1, 0);

  Serial.begin(9600);
  Serial.println("Sistema iniciado.");
}

void loop() {
  bool estadoA = digitalRead(botaoA);
  bool b3Livre  = digitalRead(botao3) == HIGH; // HIGH = solto (INPUT_PULLUP)

  // Se Botão 3 for solto, apaga imediatamente o LED
  if (b3Livre) {
    analogWrite(led1, 0);
    // Mantém o nível salvo — ao pressionar B3 novamente, retoma do mesmo nível
  } else {
    // Botão 3 está pressionado — LED ativo no nível atual
    analogWrite(led1, niveis[nivelAtual]);
  }

  // Detecta clique no Botão A (borda de descida)
  if (estadoA == LOW && estadoAnteriorBotaoA == HIGH) {
    delay(50); // Debounce

    if (digitalRead(botaoA) == LOW) {
      // Só avança o nível se Botão 3 estiver pressionado
      if (digitalRead(botao3) == LOW) {
        nivelAtual = (nivelAtual + 1) % totalNiveis;
        analogWrite(led1, niveis[nivelAtual]);

        Serial.print("Brilho: ");
        Serial.print(nivelAtual * 25);
        Serial.println("%");
      } else {
        Serial.println("Permissão negada — pressione o Botão 3.");
      }
    }
  }

  estadoAnteriorBotaoA = estadoA;
