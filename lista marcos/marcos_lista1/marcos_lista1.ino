const int botaoA = 2;
const int botaoB = 3;
const int led1 = 13;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
}

void loop() {

  bool estadoA = digitalRead(botaoA) == LOW;
  bool estadoB = digitalRead(botaoB) == LOW;


  if (estadoB) { 
    if (estadoA) {
      digitalWrite(led1, HIGH); 
    } else {
      digitalWrite(led1, LOW);  
  } else {
    digitalWrite(led1, LOW); 
  }
}
