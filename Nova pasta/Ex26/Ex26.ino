const int botao1 = 12;
const int botao2 = 13;
const int ledMaquina = 2; 
unsigned long tempoBotao1 = 0;
unsigned long tempoBotao2 = 0;
bool aguardandoReset = false; 
bool acionouSaida = false;

void setup() {
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(ledMaquina, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  bool b1 = !digitalRead(botao1);
  bool b2 = !digitalRead(botao2);


  if (b1 && tempoBotao1 == 0) tempoBotao1 = millis();
  if (!b1) tempoBotao1 = 0; 

  if (b2 && tempoBotao2 == 0) tempoBotao2 = millis();
  if (!b2) tempoBotao2 = 0; 
  if (b1 && b2 && !aguardandoReset) {
    long diferenca = abs((long)tempoBotao1 - (long)tempoBotao2);

    if (diferenca <= 200) {
      acionouSaida = true;
      digitalWrite(ledMaquina, HIGH);
      Serial.println("MAQUINA ACIONADA: Segurança confirmada.");
    } else {
      Serial.println("ERRO: Falha de simultaneidade!");
    }
    aguardandoReset = true; 
  }


  if (!b1 && !b2) {
    digitalWrite(ledMaquina, LOW);
    aguardandoReset = false;
    acionouSaida = false;
  }
}