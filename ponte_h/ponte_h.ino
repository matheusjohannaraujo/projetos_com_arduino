/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2018-01-13
*/

// Declaração das portas a serem utilizadas
#define pinoVelocidade 10 // ENA
#define pinoSentidoHorario 11 // IN1
#define pinoSentidoAntiHorario 12 // IN2

// Função principal e de execução única
void setup() {
  // Definindo o modo de funcionamento do pinos - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(pinoVelocidade, OUTPUT);
  pinMode(pinoSentidoHorario, OUTPUT);
  pinMode(pinoSentidoAntiHorario, OUTPUT);
  // Escrevendo o valor zero em um pino PWM - Valores possíveis (0 até 255) onde o pino pode fornecer de 0 Volt até +5 Volts
  analogWrite(pinoVelocidade, 0);
  // Escrevendo o valor zero em um pino digital - Valores possíveis (LOW = FALSE = 0 / HIGH = TRUE= 1) o pino pode fornecer 0 Volt ou +5 Volts
  digitalWrite(pinoSentidoHorario, LOW);
  digitalWrite(pinoSentidoAntiHorario, LOW);
  // Iniciando comunicação serial com taxa de bits 9600
  Serial.begin(9600);
}

// Função secundária e de repetição infinita
void loop() {
  // Lendo a comunicação serial
  char caractere = Serial.read();
  // Estrutura condicional de caso
  switch (caractere) {
    // Caso o caractere seja '0' faça
    case '0':
      // Escrevendo valores nos pinos (controlando as portas do Arduino)
      analogWrite(pinoVelocidade, 0);
      digitalWrite(pinoSentidoHorario, LOW);
      digitalWrite(pinoSentidoAntiHorario, LOW);
      // Escrevendo na comunicação serial
      Serial.println("Motor parado.");
      // Sai da estrutura Switch Case
      break;
    case '1':
      analogWrite(pinoVelocidade, 255);
      digitalWrite(pinoSentidoHorario, HIGH);
      digitalWrite(pinoSentidoAntiHorario, LOW);
      Serial.println("Motor rodando no sentido horário.");
      break;
    case '2':
      analogWrite(pinoVelocidade, 255);
      digitalWrite(pinoSentidoHorario, LOW);
      digitalWrite(pinoSentidoAntiHorario, HIGH);
      Serial.println("Motor rodando no sentido anti-horário.");
      break;
  }
  // Espera um segundo (1s = 1000ms)
  delay(1000);
}
