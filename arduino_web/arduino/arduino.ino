// Country: Brasil
// State: Pernambuco
// Developer: Matheus Johann Araújo
// Date: 2018-03-07

// Definindo porta do LED em um pino PWM - Valores possíveis (0 até 255) onde o pino pode fornecer de 0 Volt até +5 Volts
#define led 11

// Função principal e de execução única
void setup() {
  // Iniciando comunicação serial com taxa de bits 9600
  Serial.begin(9600);
  // Definindo o modo de funcionamento do pino - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(led, OUTPUT);
}

// Função que lê uma string da Serial e retorna-a.
String leStringSerial(){
  String conteudo = "";
  char caractere;  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if(caractere != '\n'){
      //Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }    
  // Serial.print("Recebi: ");
  // Serial.println(conteudo);
  return conteudo;
}

// Variável que armazena a leitura da comunicação serial
String leitura = "";

// Função secundária e de repetição infinita
void loop() {
  // Faz a leitura do que é escrito na comunicação serial e guarda o resultado na variável 
  leitura = leStringSerial();
  // Estrutura condicional (SE, SENÃO)
  if(leitura == "L"){
    // Escreve na comunicação serial e quebra a linha "[ENTER]" ou "\n"
    Serial.println("LED LIGADO!");
    // Escrevendo o valor no pino PWM (controlando a porta do Arduino)
    analogWrite(led, 130);    
  }else if(leitura == "D"){
    // Escreve na comunicação serial e quebra a linha "[ENTER]" ou "\n"
    Serial.println("LED DESLIGADO!");
    // Escrevendo o valor no pino PWM (controlando a porta do Arduino)
    analogWrite(led, 0);    
  }
}