/*

  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2019-07-31

*/

// Definindo o nome da biblioteca
#ifndef __ATUADOR_PH_H__
#define __ATUADOR_PH_H__

// Define que irá existir uma estrutura
typedef struct {

  // Variável para debug
  bool debug = true;

  //Motor A e suas portas
  int ena = 3;
  int in1 = 2;
  int in2 = 4;

  //Motor B e suas portas
  int enb = 6;
  int in3 = 5;
  int in4 = 7;

  // Função que exibe informações sobre a ponte H se o valor da variável for verdadeiro
  void println(String val) {
    if (debug) {
      Serial.println("ATUADOR_PH: " + val);
    }
  }

  // Função que define os pinos da ponte H
  void pinos(bool deb) {
    debug = deb;
    pinMode(ena, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enb, OUTPUT);
    println("pinos() => " + String(ena) + ", " + String(in1) + ", " + String(in2) + ", " + String(in3) + ", " + String(in4) + ", " + String(enb));
  }

  // Função que define os valores das variáveis dos pinos da ponte H
  void definir(int a, int b, int c, int d, int e, int f, bool deb) {
    ena = a;
    in1 = b;
    in2 = c;
    in3 = d;
    in4 = e;
    enb = f;
    pinos(deb);
  }

  // Função que movimenta o motor esquerdo
  void esq(int vel, bool dir1, bool dir2) {
    println("esq(" + String(vel) + ", " + String(dir1) + ", " + String(dir2) + ")");
    analogWrite(ena, vel);
    digitalWrite(in1, dir1);
    digitalWrite(in2, dir2);
  }

  // Função que movimenta o motor direito
  void dir(int vel, bool dir1, bool dir2) {
    println("dir(" + String(vel) + ", " + String(dir1) + ", " + String(dir2) + ")");
    analogWrite(enb, vel);
    digitalWrite(in3, dir1);
    digitalWrite(in4, dir2);
  }

  // Função que para os dois motores por um determinado tempo
  void parar(int timer) {
    println("parar(" + String(timer) + ")");
    esq(0, 0, 0);
    dir(0, 0, 0);
    if (timer > 0) {
      delay(timer);
    }
  }

  // Função que espera um determinado tempo para chamar a função que para ambos os motores
  void tempo(int timer) {
    println("tempo(" + String(timer) + ")");
    if (timer > 0) {
      delay(timer);
      parar(0);
    }
  }

  // Função que movimenta os dois motores para frente (sentido horário)
  void frente(int vel, int timer) {
    println("frente(" + String(timer) + ")");
    esq(vel, 0, 1);
    dir(vel, 0, 1);
    tempo(timer);
  }

  // Função que movimenta os dois motores para trás (sentido anti-horário)
  void tras(int vel, int timer) {
    println("tras(" + String(timer) + ")");
    esq(vel, 1, 0);
    dir(vel, 1, 0);
    tempo(timer);
  }

  // Função que movimenta os dois motores para virar a direita por um determinado tempo e velocidade
  void direita(int vel, int timer) {
    println("direita(" + String(timer) + ")");
    esq(vel, 0, 1);
    dir(vel, 1, 0);
    tempo(timer);
  }

  // Função que movimenta os dois motores para virar a esquerda por um determinado tempo e velocidade
  void esquerda(int vel, int timer) {
    println("esquerda(" + String(timer) + ")");
    esq(vel, 1, 0);
    dir(vel, 0, 1);
    tempo(timer);
  }

} ATUADOR_PH;

#endif
