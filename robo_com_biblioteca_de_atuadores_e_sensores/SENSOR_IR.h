/*

  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2019-07-31

*/

// Definindo o nome da biblioteca
#ifndef __SENSOR_IR_H__
#define __SENSOR_IR_H__

// Define que irá existir uma estrutura
typedef struct {

  // Variável para debug.
  bool debug = true;

  //Tipo do sensor, ANALOGICO = false e DIGITAL = true.
  bool sensor_tipo = true;

  // Variável que contém o número do pino do sensor IR.
  int sensor_pin = 13;

  // Função que exibe informações sobre o sensor IR se o valor da variável for verdadeiro.
  void println(String val) {
    if (debug) {
      Serial.println("SENSOR_IR: " + val);
    }
  }

  // Função que define os pinos do sensor IR.
  void pinos(bool deb) {
    debug = deb;
    pinMode(sensor_pin, INPUT);
    println("pinos() => " + String(sensor_pin));
  }

  // Função que define o valor da variável do pino do sensor IR.
  void definir(int pino, bool tipo, bool deb) {
    sensor_pin = pino;
    sensor_tipo = tipo;
    pinos(deb);
  }

  // Função que retorna a leitura do sensor IR de acordo com seu sensor_tipo (digital ou analógico).
  unsigned int ler() {
    unsigned int leitura = 0;
    if (sensor_tipo) {
      leitura = digitalRead(sensor_pin);
    } else {
      leitura = analogRead(sensor_pin);
    }
    println("ler() => " + String(leitura));
    return leitura;
  }

} SENSOR_IR;

#endif
