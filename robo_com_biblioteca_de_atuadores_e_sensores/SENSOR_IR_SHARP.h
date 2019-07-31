/*

  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2019-07-31

*/

// Definindo o nome da biblioteca
#ifndef __SENSOR_IR_SHARP_H__
#define __SENSOR_IR_SHARP_H__

// Inclui a biblioteca do fabricante do sensor IR de distância
#include "SharpIR.h"

// Define que irá existir uma estrutura
typedef struct {

  // Variável para debug
  bool debug = true;

  // Variável que contém o número do pino do sensor IR de distância
  int sensor_pin = A2;

  // Variável que contém o modelo do sensor IR de distância
  int sensor_model = 1080;

  SharpIR *sharp_ir;

  void println(String val) {
    if (debug) {
      Serial.println("SENSOR_IR_D: " + val);
    }
  }

  void pinos(bool deb) {
    debug = deb;
    sharp_ir = new SharpIR(sensor_pin, sensor_model);
    println("pinos() => " + String(sensor_pin) + ", " + String(sensor_model));
  }

  void definir(int numSensor, int modelSensor, bool deb) {
    sensor_pin = numSensor;
    sensor_model = modelSensor;
    pinos(deb);
  }

  unsigned int ler() {
    unsigned int cm = (*sharp_ir).distance();
    println("ler() => " + String(cm) + "cm");
    return cm;
  }

} SENSOR_IR_SHARP;

#endif
