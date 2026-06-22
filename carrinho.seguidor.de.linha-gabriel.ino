/*

  CARRINHO SEGUIDOR DE LINHA

  Colegio SATC 
  Data:22/06/2026
  Autores: Gabriel Lucas, Matheus Moneretto
  Curso: Mecatronica 3ºfase
  Professor: Marcos Coelho

*/

//  Definição dos Pinos de Controle de Velocidade (PWM) 
const int ENA = 5;  
const int ENB = 6;  

//  Definição dos Pinos de Direção dos Motores  
const int IN1 = 8;  // Motor Esquerdo Frente
const int IN2 = 9;  // Motor Esquerdo Trás
const int IN3 = 10; // Motor Direito Frente
const int IN4 = 11; // Motor Direito Trás

//  Definição dos 5 Sensores 
const int S1 = A0;  // Sensor 1
const int S2 = A1;  // Sensor 2
const int S3 = A2;  // Sensor Central
const int S4 = A3;  // Sensor 4
const int S5 = A4;  // Sensor 5

//  Configuração de Velocidade 
const int VELOCIDADE = 255; 

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  analogWrite(ENA, VELOCIDADE);
  analogWrite(ENB, VELOCIDADE);
}

void loop() {
  int leituraS1 = digitalRead(S1);
  int leituraS2 = digitalRead(S2);
  int leituraS3 = digitalRead(S3);
  int leituraS4 = digitalRead(S4);
  int leituraS5 = digitalRead(S5);

  //  LÓGICA COM INVERSÃO DE SENSORES LATERAIS 

  if (leituraS3 == HIGH) {
    moverFrente();
  }
  // Se ativar o sensor S2, faz a curva suave para a DIREITA
  else if (leituraS2 == HIGH) {
    curvaSuaveDireita();
  }
  // Se ativar o sensor S4, faz a curva suave para a ESQUERDA
  else if (leituraS4 == HIGH) {
    curvaSuaveEsquerda();
  }
  // Se ativar o sensor S1, faz a curva fechada para a DIREITA
  else if (leituraS1 == HIGH) {
    curvaFechadaDireita();
  }
  // Se ativar o sensor S5, faz a curva fechada para a ESQUERDA
  else if (leituraS5 == HIGH) {
    curvaFechadaEsquerda();
  }
  else {
    parar();
  }
}

// Funções de Movimentação 

void moverFrente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void curvaSuaveEsquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void curvaSuaveDireita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void curvaFechadaEsquerda() {
  // Roda Esquerda para TRÁS , Roda Direita para FRENTE
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void curvaFechadaDireita() {
  // Roda Esquerda para FRENTE , Roda Direita para TRÁS
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}