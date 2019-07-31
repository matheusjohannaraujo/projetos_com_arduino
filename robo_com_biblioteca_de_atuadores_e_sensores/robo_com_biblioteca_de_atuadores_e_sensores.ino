/*

  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2019-07-31

  OBS.: Portas usadas do Arduino Mega 2560.
        Caso seja outro, altere as portas.

*/

// ----------- Incluindo bibliotecas -----------

// Ponte H
//#include "ATUADOR_PH.h" 

// Shield Motor
#include "ATUADOR_SM.h"

// Sensor Infravermelho de Luz.
#include "SENSOR_IR.h"

// Sensor Infravermelho de Distância.
#include "SENSOR_IR_SHARP.h"

// Sensor Ultrassônico de Distância.
#include "SENSOR_ULTRA.h"

// ------------ Bibliotecas Incluídas -----------

// Definindo as variáveis responsáveis pelo controle de motor e sensor.
//ATUADOR_PH motores;
ATUADOR_SM motores;
SENSOR_IR s1, s2, s3, s4;
SENSOR_IR_SHARP sharp;
SENSOR_ULTRA ultra;

// Definindo valores que serão utilizados para o controle de motores.
#define velocidade 100
#define limiar 100

// Definindo funções abstratas.
void seguidor();
void obstaculo();

void setup() {
  // Inicia comunicação Serial com bitrate (taxa de transferência) de 9600 bits por segundo.
  Serial.begin(9600);

  // Variável que controla todas as saídas de informação de debug.
  bool debug = true;

  // Ponte H -> Define todos as portas da controladora de motores, e ativa (true) ou desativa (false) o debug das informações relativas a ponte h.
  // motores.definir(3, 2, 4, 5, 7, 6, debug);// (ENA, IN1, IN2, IN3, IN4, ENB, Debug)

  // Shield Motor -> Define as portas da controladora de motores (Motor A e Motor B), e ativa (true) ou desativa (false) o debug das informações relativas ao shield motores.
  motores.definir(3, 4, debug);// (MA, MB, Debug)

  // Sensor Infravermelho de Luz -> Definindo as portas dos Sensores IR, o tipo Digital (true) ou Analógico (false) e se o debug será ativado (true) ou desativado (false).
  s1.definir(22, true, debug);// (Porta, Tipo, Debug) -> Sensor 1.
  s2.definir(23, true, debug);// (Porta, Tipo, Debug) -> Sensor 2.
  s3.definir(24, true, debug);// (Porta, Tipo, Debug) -> Sensor 3.
  s4.definir(25, true, debug);// (Porta, Tipo, Debug) -> Sensor 4.

  // Sensor Ultrassônico de Distância -> Definindo as portas do sensor (Trigger e Echo) e o Debug (ativado = true, desativado = false).
  ultra.definir(52, 53, debug);// (Trig, Echo, Debug)

  // Sensor Infravermelho de Distância -> Definindo a porta analógica do sensor, modelo do sensor e se o debug será ativado (true) ou desativado (false).
  sharp.definir(A8, 1080, debug);// (AnalogPort, Model, Debug)
}

void loop() {
  // Chamando funções.
  obstaculo();
  seguidor();
  // Verifica se existe informação na comunicação serial.
  if (Serial.available() > 0) {
    // Armazena o caractere da comunicação serial para controle do robô.
    char c = (char) Serial.read();
    if (c == 'e')
      motores.esquerda(velocidade + limiar, 100);
    else if (c == 'd')
      motores.direita(velocidade + limiar, 100);
    else if (c == 'f')
      motores.frente(velocidade + limiar, 100);
    else if (c == 't')
      motores.tras(velocidade + limiar, 100);
    else if (c == 'p')
      motores.parar(100);
  }
}

// Função que detecta um obstáculo com sensores ultrassonico e infravermelho.
void obstaculo() {
  // Detecta o obstáculo usando o sensor ultrassônico
  int distancia_ultra = ultra.ler("cm");// Faz a leitura da distância do sensor ultrassônico.
  if (distancia_ultra < 25) {
    Serial.println("Obstaculo Ultra" );
  }
  // Detecta o obstáculo usando o sensor infravermelho de distância.
  int distancia_sharp = sharp.ler();// Faz a leitura da distância com o sensor infravermelho.
  if (distancia_sharp < 25) {
    Serial.println("Obstaculo IR");
  }
}

// Função para o robô seguir linha.
void seguidor() {
  // Faz as leituras dos sensores infravermelhos de luz. Se o tipo for Digital (true) as leituras serão (0 = Branco ou Preto = 1), caso Analógico (false) as leituras serão de (Preto = 0 até 1023 = Branco).
  int a = s1.ler();
  int b = s2.ler();
  int c = s3.ler();
  int d = s4.ler();
  if (a == 1 && b == 1 && c == 0 && d == 0) { //90 Dir
    Serial.println("DIREITA 90");
    motores.direita(velocidade + limiar, 300);
  } else if (a == 0 && b == 0 && c == 1 && d == 1) { //90 Esq
    Serial.println("ESQUERDA 90");
    motores.esquerda(velocidade + limiar, 250);
  } else if ((a == 1 || b == 1) && c == 0 && d == 0) { //45 Dir
    Serial.println("DIREITA 45");
    motores.direita(velocidade + limiar, 50);
    while ((a == 1 || b == 1)) {
      Serial.println("DIREITA 45");
      motores.direita(velocidade + limiar, 50);
      a = s1.ler();
      b = s2.ler();
    }
  } else if (a == 0 && b == 0 && (c == 1 || d == 1)) { //45 Esq
    Serial.println("ESQUERDA 45");
    motores.esquerda(velocidade + limiar, 50);
    while ((c == 1 || d == 1)) {
      Serial.println("ESQUERDA 45");
      motores.esquerda(velocidade + limiar, 50);
      c = s3.ler();
      d = s4.ler();
    }
  } else {
    Serial.println("FRENTE");
    motores.frente(velocidade + limiar, 0);
  }
}
