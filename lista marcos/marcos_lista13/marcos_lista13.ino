const int pinoPoт = A0;   
const int led1    = 9;    


const int NIVEL_1 = 409;  
const int NIVEL_2 = 818;  

const unsigned long INTERVALO_PISCA = 500;
unsigned long ultimoToggle = 0;
bool estadoLed             = false;

void setup() {
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);

  Serial.begin(9600);
  Serial.println("Sistema iniciado.");
}

void loop() {
  int leitura          = analogRead(pinoPoт);
  float tensao         = leitura * (5.0 / 1023.0);
  unsigned long agora  = millis();


  if (leitura <= NIVEL_1) {
    digitalWrite(led1, LOW);
    estadoLed = false;

    Serial.print("DESLIGADO | ");
  }

 
  else if (leitura > NIVEL_1 && leitura < NIVEL_2) {
    if (agora - ultimoToggle >= INTERVALO_PISCA) {
      ultimoToggle = agora;
      estadoLed    = !estadoLed;
      digitalWrite(led1, estadoLed ? HIGH : LOW);
    }

    Serial.print("PISCANDO  | ");
  }


  else {
    digitalWrite(led1, HIGH);
    estadoLed = true;

    Serial.print("LIGADO    | ");
  }

  
  Serial.print("ADC: ");
  Serial.print(leitura);
  Serial.print(" | ");
  Serial.print(tensao, 2);
  Serial.println(" V");

  delay(100); 
}
