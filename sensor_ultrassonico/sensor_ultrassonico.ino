/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2017-09-28
*/

// Declaração das variáveis que possuem os pinos utilizados pelo Sensor de Distância Ultrassônico HC-SR04
int pinTrig = 1;
int pinEcho = 2;

// Função principal e de execução única
void setup(){
  // Definindo o modo de funcionamento do pino - INPUT (Entrada) / INPUT_PULLUP (Entrada + Resistores internos do Arduino) / OUTPUT (Saída)
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  // Iniciando comunicação serial com taxa de bits 9600
  Serial.begin(9600);
}

// Função que mede a distância com o utrassônico, recebe como parâmetro os pinos Trigger e Echo em formato de ponteiro
// E tem como retorno um valor inteiro sem sinal (número natural), esse valor é a distância medida em cm.
unsigned int distanciaUltrasonico(int *pinTrig, int *pinEcho){
  // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(*pinTrig, LOW);
  // Espera dois micro segundos
  delayMicroseconds(2);
  // Escreve valor ligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(*pinTrig, HIGH);
  // Espera dez micro segundos
  delayMicroseconds(10);
  // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(*pinTrig, LOW);
  // Faz a leitura pulso no pino Echo, e divide o valor da leitura por 58. Com isso obtem-se a distância em centímetros
  return (pulseIn(*pinEcho, HIGH) / 58);
}

// Variável que guardará o valor retornado pelo sensor utrassônico
int distancia = 0;

// Função secundária e de repetição infinita
void loop(){
  // Ler o sensor e retorna a distância em cm e guarda o valor na variável
  distancia = distanciaUltrasonico(&pinTrig, &pinEcho);
  // Escreve na comunicação serial
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println("cm");
  // Espera um segundo (1s = 1000ms)
  delay(1000);
}