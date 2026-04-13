const int pinoNTC      = A0;  
const int ledExaustor  = 9;   
const int ledAlerta    = 8;   
// Parâmetros do NTC (divisor de tensão)
const float VCC         = 5.0;
const float R_FIXO      = 10000.0;  
const float R_NOM       = 10000.0;  
const float T_NOM       = 298.15;   
const float BETA        = 3950.0;   

// Limiares de temperatura
const float TEMP_BAIXA  = 30.0;  
const float TEMP_ALTA   = 60.0;  

// Potências em PWM (0–255)
const int PWM_MIN       = 51;   
const int PWM_MAX       = 255;  

void setup() {
  pinMode(ledExaustor, OUTPUT);
  pinMode(ledAlerta,   OUTPUT);
  digitalWrite(ledAlerta, LOW);
  analogWrite(ledExaustor, PWM_MIN);

  Serial.begin(9600);
  Serial.println("Sistema iniciado.");
  Serial.println("Temp(C) | Potencia(%) | PWM | Estado");
  Serial.println("--------|-------------|-----|------------------");
}

void loop() {
  // ── Leitura e conversão NTC ──────────────────
  int   adc     = analogRead(pinoNTC);
  float vOut    = adc * (VCC / 1023.0);
  float rNTC    = R_FIXO * (VCC / vOut - 1.0);  // NTC no lado do GND
  float tempK   = 1.0 / (1.0/T_NOM + log(rNTC/R_NOM)/BETA);
  float tempC   = tempK - 273.15;

  // ── Lógica de controle ───────────────────────
  int   pwm        = PWM_MIN;
  float potencia   = 20.0;
  String estado    = "";

  if (tempC < TEMP_BAIXA) {
   
    pwm      = PWM_MIN;
    potencia = 20.0;
    estado   = "Velocidade minima";
    digitalWrite(ledAlerta, LOW);

  } else if (tempC <= TEMP_ALTA) {
   
    potencia = 20.0 + (tempC - TEMP_BAIXA)
               * (100.0 - 20.0) / (TEMP_ALTA - TEMP_BAIXA);
    pwm      = (int)((potencia / 100.0) * 255.0);
    estado   = "Velocidade proporcional";
    digitalWrite(ledAlerta, LOW);

  } else {
  
    pwm      = PWM_MAX;
    potencia = 100.0;
    estado   = ">>> CAPACIDADE MAXIMA <<<";
    digitalWrite(ledAlerta, HIGH);
  }

  analogWrite(ledExaustor, pwm);

  // ── Serial Monitor ───────────────────────────
  Serial.print(tempC,    1); Serial.print(" C  \t| ");
  Serial.print(potencia, 1); Serial.print("% \t| ");
  Serial.print(pwm);         Serial.print("  \t| ");
  Serial.println(estado);

  delay(500);
}
