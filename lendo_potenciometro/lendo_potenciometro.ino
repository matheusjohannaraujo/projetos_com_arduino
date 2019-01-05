// Country: Brasil
// State: Pernambuco
// Developer: Matheus Johann Araújo
// Date: 2017-11-03

// Definindo porta do potênciometro
#define pot A1

// Função principal e de execução única
void setup() {
  // Iniciando comunicação serial com taxa de bits 9600
  Serial.begin(9600);
  // Definindo o modo de funcionamento do pino - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(pot, INPUT);
}

// Declarando variável que terá o valor lido do potênciometro
int vPot = 0;

// Função secundária e de repetição infinita
void loop() {
  // Ler o potênciometro e guarda o valor de 0 até 1023 (0v ~ 5v) na variável
  vPot = analogRead(pot);
  // Transfere a escala de 0 até 1023 para uma semelhante de 0 à 255
  vPot = map(vPot, 0, 1023, 0, 255); 
  // Escreve na comunicação serial
  Serial.print("Potênciometro: ");
  // Escreve e quebra a linha "[ENTER]" ou "\n"
  Serial.println(vPot);
  // Espera meio segundo (1s = 1000ms)
  delay(500);
}