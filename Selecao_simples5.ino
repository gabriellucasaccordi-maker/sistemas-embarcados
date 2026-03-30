/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Seleção simples

Autor: Marcos Antonio Jeremias Coelho
Data: 06/03/2023
Versão: 1.0

************************************************************************ */
const int Pin_botao = 3;
const int Pin_led = 9;
int estado_led = LOW;
int estado_botao;
int ultimo_estado_botao = HIGH;
unsigned long tempo_debounce = 0;
unsigned long atraso = 50;

void setup() {
  pinMode(Pin_botao, INPUT_PULLUP);
  pinMode(Pin_led, OUTPUT);
  digitalWrite(Pin_led, estado_led);
}

void loop() {
  int leitura = digitalRead(Pin_botao);
  if (leitura != ultimo_estado_botao) {
    tempo_debounce = millis();
  }
  if ((millis() - tempo_debounce) > atraso) {
    if (leitura != estado_botao) {
      estado_botao = leitura;
      if (estado_botao == LOW) {
        estado_led = !estado_led;
      }
    }
  }
  digitalWrite(Pin_led, estado_led);
  ultimo_estado_botao = leitura;
}
