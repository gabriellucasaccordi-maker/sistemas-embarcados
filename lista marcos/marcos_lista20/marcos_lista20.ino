const int pinoPOT     = A0;   
const int pinoNTC     = A1;   
const int pinoBotao   = 2;   
const int ledValvula  = 8;    
const int ledAquecedor= 9;    
const int ledAlarme   = 10;   

const float VCC       = 5.0;
const float R_FIXO    = 10000.0;
const float R_NOM     = 10000.0;
const float T_NOM     = 298.15;   
const float BETA      = 3950.0;


const int NIVEL_BAIXO = 306;
const int NIVEL_ALTO  = 716;


const float TEMP_FRIA     = 40.0;  
const float TEMP_CRITICA  = 80.0;   


const int PWM_AQUECEDOR = 180;     


bool  sistemaHabilitado   = false;
bool  estadoAnteriorBotao = HIGH;
unsigned long ultimoDebounce = 0;
const unsigned long DEBOUNCE_MS = 50;


void setup() {
  pinMode(pinoBotao,    INPUT_PULLUP);
  pinMode(ledValvula,   OUTPUT);
  pinMode(ledAquecedor, OUTPUT);
  pinMode(ledAlarme,    OUTPUT);

 
  desligarTudo();

  Serial.begin(115200);
  imprimirCabecalho();
}


void loop() {
  lerBotao();

  if (!sistemaHabilitado) {
    desligarTudo();
    Serial.println("SISTEMA DESABILITADO — pressione o botao para iniciar.");
    delay(1000);
    return;
  }

 
  int   adcNivel  = analogRead(pinoPOT);
  float tempC     = lerTemperatura();

 
  bool valvulaAberta;
  String estadoNivel;

  if (adcNivel <= NIVEL_BAIXO) {
    valvulaAberta = true;
    estadoNivel   = "BAIXO ";
  } else if (adcNivel >= NIVEL_ALTO) {
    valvulaAberta = false;
    estadoNivel   = "ALTO  ";
  } else {
   
    valvulaAberta = digitalRead(ledValvula);
    estadoNivel   = "NORMAL";
  }
  digitalWrite(ledValvula, valvulaAberta ? HIGH : LOW);

 
  int   pwmAquecedor    = 0;
  String estadoAquecedor = "";

  if (tempC >= TEMP_CRITICA) {
    
    pwmAquecedor    = 0;
    estadoAquecedor = "DESLIG(ALARME)";
  } else if (tempC < TEMP_FRIA) {
  
    pwmAquecedor    = PWM_AQUECEDOR;
    estadoAquecedor = "LIGADO        ";
  } else {
   
    pwmAquecedor    = 0;
    estadoAquecedor = "DESLIG(NORMAL)";
  }
  analogWrite(ledAquecedor, pwmAquecedor);

 
  bool alarmeAtivo = (tempC >= TEMP_CRITICA);
  digitalWrite(ledAlarme, alarmeAtivo ? HIGH : LOW);

  
  Serial.print("Nivel: ");
  Serial.print(estadoNivel);
  Serial.print(" (ADC ");
  Serial.print(adcNivel);
  Serial.print(") | Temp: ");
  Serial.print(tempC, 1);
  Serial.print(" C | Valvula: ");
  Serial.print(valvulaAberta ? "ABERTA " : "FECHADA");
  Serial.print(" | Aquecedor: ");
  Serial.print(estadoAquecedor);
  Serial.print(" | Alarme: ");
  Serial.println(alarmeAtivo ? "ON" : "OFF");

  delay(500);
}




void lerBotao() {
  bool estadoAtual = digitalRead(pinoBotao);
  unsigned long agora = millis();

  if (estadoAtual == LOW && estadoAnteriorBotao == HIGH) {
    if (agora - ultimoDebounce >= DEBOUNCE_MS) {
      ultimoDebounce      = agora;
      sistemaHabilitado   = !sistemaHabilitado;

      Serial.print("\n>>> Sistema ");
      Serial.println(sistemaHabilitado ? "HABILITADO <<<" : "DESABILITADO <<<");
    }
  }
  estadoAnteriorBotao = estadoAtual;
}


float lerTemperatura() {
  int   adc   = analogRead(pinoNTC);
  float vOut  = adc * (VCC / 1023.0);
  float rNTC  = R_FIXO * (VCC / vOut - 1.0);
  float tempK = 1.0 / (1.0 / T_NOM + log(rNTC / R_NOM) / BETA);
  return tempK - 273.15;
}


void desligarTudo() {
  digitalWrite(ledValvula,   LOW);
  analogWrite(ledAquecedor,  0);
  digitalWrite(ledAlarme,    LOW);
}

void imprimirCabecalho() {
  Serial.println("========================================");
  Serial.println(" CONTROLE DE TANQUE INDUSTRIAL");
  Serial.println("========================================");
  Serial.println(" Nivel baixo  : ADC <= 306 (~0-30%)");
  Serial.println(" Nivel alto   : ADC >= 717 (~70-100%)");
  Serial.println(" Temp. fria   : < 40 C  → aquecedor ON");
  Serial.println(" Temp. critica: > 80 C  → alarme ON");
  Serial.println("========================================\n");
}
