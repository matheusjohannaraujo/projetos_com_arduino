/*

  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2019-07-31

*/

// Definindo o nome da biblioteca
#ifndef __ATUADOR_SM_H__
#define __ATUADOR_SM_H__

// Inclui a biblioteca do fabricante do Shield Motor
#include "AFMotor.h"

// Define que irá existir uma estrutura.
typedef struct {

  // Variável para debug.
  bool debug = true;

  // Função que exibe informações sobre o Shield Motor se o valor da variável for verdadeiro.
  void println(String val) {
    if (debug) {
      Serial.println("ATUADOR_SM: " + val);
    }
  }

  // Variáveis de cada motor
  AF_DCMotor *ma;
  AF_DCMotor *mb;

  // Função que define os pinos do Shield Motor
  void definir(int a, int b, bool deb) {
    debug = deb;
    println("pinos() => " + String(a) + ", " + String(b));
    ma = new AF_DCMotor(a);
    mb = new AF_DCMotor(b);
  }

  void esq(int vel, int dir) {
    println("esq(" + String(vel) + ", " + String(dir) + ")");
    (*ma).setSpeed(vel);
    (*ma).run(dir);
  }

  void dir(int vel, int dir) {
    println("dir(" + String(vel) + ", " + String(dir) + ")");
    (*mb).setSpeed(vel);
    (*mb).run(dir);
  }

  // Função para parar dois motores por um determinado tempo
  void parar(int timer) {
    println("parar(" + String(timer) + ")");
    esq(0, 3);// Parar
    dir(0, 3);// Parar
    delay(50);
    esq(0, 4);// Liberar
    dir(0, 4);// Liberar
    if (timer > 0) {
      delay(timer);
    }
  }

  // Função que espera um determinado tempo para chamar a função que para os dois motores
  void tempo(int timer) {
    println("tempo(" + String(timer) + ")");
    if (timer > 0) {
      delay(timer);
      parar(0);
    }
  }

  // Função que movimenta os dois motores para frente durante um determinado tempo e velocidade
  void frente(int vel, int timer) {
    println("frente(" + String(vel) + ", " + String(timer) + ")");
    esq(vel, 1);
    dir(vel, 1);
    tempo(timer);
  }

  // Função que movimenta os dois motores para trás durante um determinado tempo e velocidade
  void tras(int vel, int timer) {
    println("tras(" + String(vel) + ", " + String(timer) + ")");
    esq(vel, 2);
    dir(vel, 2);
    tempo(timer);
  }

  // Função que movimenta os dois motores para direita durante um determinado tempo e velocidade
  void direita(int vel, int timer) {
    println("direita(" + String(vel) + ", " + String(timer) + ")");
    esq(vel, 1);
    dir(vel, 2);
    tempo(timer);
  }

  // Função que movimenta os dois motores para esquerda durante um determinado tempo e velocidade
  void esquerda(int vel, int timer) {
    println("esquerda(" + String(vel) + ", " + String(timer) + ")");
    esq(vel, 2);
    dir(vel, 1);
    tempo(timer);
  }

} ATUADOR_SM;

#endif
