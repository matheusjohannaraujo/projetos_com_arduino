/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2017-10-13
*/

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

// Função secundária e de repetição infinita
void loop(){
  // Imprimindo na comunicação serial, que o servo irá para 0 grau
  Serial.println("Servo motor indo para 0º");
  // Escrevendo o ângulo no servo - Zero Grau
  servoMotor.write(0);
  // Espera um segundo (1s = 1000ms)
  delay(1000);
  // Imprimindo na comunicação serial, que o servo irá para 180 graus
  Serial.println("Servo motor indo para 180º");
  // Escrevendo o ângulo no servo - Cento e Oitenta Graus
  servoMotor.write(180);
  // Espera um segundo (1s = 1000ms)
  delay(1000);
}
