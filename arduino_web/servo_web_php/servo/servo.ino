// Country: Brasil
// State: Pernambuco
// Developer: Matheus Johann Araújo
// Date: 2019-01-04

// Incluíndo biblioteca Servo
#include <Servo.h>

// Declarando variável do tipo Servo
Servo servoMotor;

// Função principal e de execução única
void setup(){
  // Iniciando comunicação serial com taxa de bits 9600
  Serial.begin(9600);
  // Função que informa o pino (porta) que o servo está conectado
  servoMotor.attach(10);
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
  // Estrutura condicional - (Switch Case)
  switch(leitura){
    // Caso (leitura igual "a") faça
    case "a":
      // Escrevendo o ângulo no servo
      servoMotor.write(0);
      // Imprimindo na comunicação serial o ângulo atual do servo motor
      Serial.println("0°");
      break;
    case "b":
      servoMotor.write(45);
      Serial.println("45°");
      break;
    case "c":
      servoMotor.write(90);
      Serial.println("90°");
      break;
    case "d":
      servoMotor.write(135);
      Serial.println("135°");
      break;
    case "e":
      servoMotor.write(180);
      Serial.println("180°");
      break;
  }
  // Espere meio segundo (1s = 1000ms)
  delay(500);
}