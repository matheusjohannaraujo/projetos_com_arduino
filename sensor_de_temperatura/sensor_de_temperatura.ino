/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2018-05-17
*/

// Definindo a porta analógica utilizada pelo sensor de temperatura - Sensor LM35
#define temp A0
// Variável do tipo float (real) que guardara o valor lido pelo sensor
float vTemp = 0f;

// Função principal e de execução única              
void setup(){
  // Iniciando comunicação serial com taxa de bits 9600
  Serial.begin(9600);
  // Definindo o modo de funcionamento do pino - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(temp, INPUT);
}

// Função secundária e de repetição infinita
void loop(){
  // Ler o sensor de temperatura e guarda o valor de 0 até 1023 (0v ~ 5v) na variável
  vTemp = analogRead(temp);
  // Calculo matemático para converter o valor lido na temperatura
  vTemp = (vTemp * 0.0048828125 * 100);
  // Imprime na comunicação serial
  Serial.print("Temperatura: ");
  Serial.print(vTemp);
  // Imprime e quebra a linha "[ENTER]" ou "\n"
  Serial.println(" C");
  // Espera meio segundo (1s = 1000ms)
  delay(500);
} 

// Exemplo de uso - https://portal.vidadesilicio.com.br/lm35-medindo-temperatura-com-arduino/