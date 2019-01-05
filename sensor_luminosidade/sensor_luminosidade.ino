/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2018-07-02
*/

// Definindo porta do sensor LDR (Fotoresistor)
#define ldr A2

// Função principal e de execução única
void setup(){
  // Definindo o modo de funcionamento do pinos - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(ldr, INPUT);
  // Iniciando comunicação serial com taxa de bits 9600  
  Serial.begin(9600);
}

// Declarando variável que terá o valor lido do LDR
int vLdr = 0;

// Função secundária e de repetição infinita
void loop(){
  // Ler o potênciometro e guarda o valor de 0 até 1023 (0v ~ 5v) na variável
  vLdr = analogRead(ldr);  
  // Escreve na comunicação serial
  Serial.print("LDR: ");
  // Escreve e quebra a linha "[ENTER]" ou "\n"
  Serial.println(vLdr);
  // Espera um segundo (1s = 1000ms)
  delay(1000);
}

// Recomendações
// https://www.youtube.com/watch?v=6ApIdQKU5uo&index=13&list=PLx4x_zx8csUgWBTvA-fluHV970SzDJRBw
// https://portal.vidadesilicio.com.br/sensor-de-luz-com-ldr/