// Country: Brasil
// State: Pernambuco
// Developer: Matheus Johann Araújo
// Date: 2017-11-15

// Declaração da porta a ser utilizada
#define led 13

// Função principal e de execução única
void setup() {
  // Definindo o modo de funcionamento do pinos - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(led, OUTPUT);
}

// Função secundária e de repetição infinita
void loop() {
  // Escrevendo o valor zero em um pino digital - Valores possíveis (LOW = FALSE = 0 / HIGH = TRUE= 1) o pino pode fornecer 0 Volt ou +5 Volts
  digitalWrite(led, HIGH);
  // Espera um segundo (1s = 1000ms)
  delay(1000);
  // Escrevendo o valor zero em um pino digital - Valores possíveis (LOW = FALSE = 0 / HIGH = TRUE= 1) o pino pode fornecer 0 Volt ou +5 Volts
  digitalWrite(led, LOW);
  // Espera um segundo (1s = 1000ms)
  delay(1000);
}