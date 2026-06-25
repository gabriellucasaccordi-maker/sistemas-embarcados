
#include <Ultrasonic.h>
const int eletrovalvulae = 10;
const int eletrovalvulas = 11;
const int aquecedor = 12;
const int alarme1 = 13;
const int alarme2 = 7;
const int sensor_temp = A0;
int valor_sensor = 0;
Ultrasonic ultrasonic(8, 9);
int distance;
const int botaoa = 2;
void setup() {
  Serial.begin(9600);
  pinMode(sensor_temp, INPUT);
  pinMode(eletrovalvulae, OUTPUT);
  pinMode(eletrovalvulas, OUTPUT);
  pinMode(aquecedor, OUTPUT);
  pinMode(alarme1, OUTPUT);
  pinMode(alarme2, OUTPUT);
  pinMode(botaoa, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botaoa), desliga, CHANGE);
}

void loop() {
  distance = ultrasonic.read();
  int capacidade = map(distance, 0, 200, 100, 0);

  valor_sensor = analogRead(sensor_temp);
  int temperatura = map(valor_sensor, 0, 1023, 0, 50);

  if (capacidade < 100) {
    digitalWrite(eletrovalvulae, 1);
  } else {
    digitalWrite(eletrovalvulae, 0);
  }
  if (capacidade <= 40 || temperatura < 25 || temperatura > 27) {
    digitalWrite(eletrovalvulas, 0);
  } else {
    digitalWrite(eletrovalvulas, 1);
  }
  if (capacidade < 10) {

    digitalWrite(alarme2, 1);
  }
  if (capacidade < 20) {
    digitalWrite(alarme1, 1);
  } else {
    digitalWrite(alarme1, 0);
  }
  if (capacidade >= 10 && temperatura < 25) {
    digitalWrite(aquecedor, 1);
  } else {
    digitalWrite(aquecedor, 0);
  }
  Serial.println(temperatura);
}
void desliga() {
  digitalWrite(alarme2, 0);
}
