****************************************************************************************************************

14. Controle de Nível e Transbordo de Silo
Descrição: Um silo industrial utiliza um de distância potenciométrico (0 silo vazio, 1023 silo
cheio) para medir o volume de grãos. O sistema possui uma válvula de carga (LED 1) e um
alarme de transbordo (LED 2).
A válvula de carga deve permanecer aberta enquanto o nível estiver abaixo de 80%. Se o
nível atingir 95%, a válvula deve fechar imediatamente e o alarme (LED 4) deve ser
acionado de forma intermitente. A válvula só poderá ser reaberta quando o nível cair abaixo
de 30%.

****************************************************************************************************************

const int sensor = A0;

const int valvula = 8; // LED 1
const int alarme = 11; // LED 4

// limites
const int LIMITE_ABRE = 307;   // 30%
const int LIMITE_FECHA = 819;  // 80%
const int LIMITE_ALARME = 972; // 95%

bool valvulaAberta = false;
bool alarmeAtivo = false;
bool estadoAlarme = false;

unsigned long tempoAnterior = 0;
const unsigned long intervalo = 300;

void setup() {
  pinMode(valvula, OUTPUT);
  pinMode(alarme, OUTPUT);
}

void loop() {
  int nivel = analogRead(sensor);
  unsigned long agora = millis();

  // ======================
  // CONTROLE DA VÁLVULA
  // ======================

  // reabertura permitida
  if (nivel < LIMITE_ABRE) {
    valvulaAberta = true;
  }

  // fechamento por segurança
  if (nivel >= LIMITE_FECHA) {
    valvulaAberta = false;
  }

  digitalWrite(valvula, valvulaAberta ? HIGH : LOW);

  // ======================
  // CONTROLE DO ALARME
  // ======================

  if (nivel >= LIMITE_ALARME) {
    alarmeAtivo = true;
  } else {
    alarmeAtivo = false;
    digitalWrite(alarme, LOW);
  }

  if (alarmeAtivo) {
    if (agora - tempoAnterior >= intervalo) {
      tempoAnterior = agora;
      estadoAlarme = !estadoAlarme;
      digitalWrite(alarme, estadoAlarme);
    }
  }
}