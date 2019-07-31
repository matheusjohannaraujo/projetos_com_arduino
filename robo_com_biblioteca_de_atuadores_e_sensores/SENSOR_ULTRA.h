/*
 
  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2019-07-31
  
*/

// Definindo o nome da biblioteca
#ifndef __SENSOR_ULTRA_H__
#define __SENSOR_ULTRA_H__

typedef struct {

  bool debug = true;
  int trig = 7;
  int echo = 8;

  void println(String val) {
    if (debug) {
      Serial.println("SENSOR_ULTRA: " + val);
    }
  }

  void pinos(bool deb) {
    debug = deb;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    println("pinos() => " + String(trig) + ", " + String(echo));
  }

  void definir(int t, int e, bool deb) {
    trig = t;
    echo = e;
    pinos(deb);
  }

  unsigned int ler(String modo) {
    // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
    digitalWrite(trig, LOW);
    // Espera dois micro segundos
    delayMicroseconds(2);
    // Escreve valor ligado no pino do Trig (controlando a porta do Arduino)
    digitalWrite(trig, HIGH);
    // Espera dez micro segundos
    delayMicroseconds(10);
    // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
    digitalWrite(trig, LOW);
    // Faz a leitura pulso no pino Echo em nível alto
    float pulso = pulseIn(echo, HIGH);
    // Pulso dividido por 58, tem-se a distancia em "cm".
    unsigned int cm = pulso / 58;
    // Pulso dividido por 148, tem-se a distancia em "pol".
    unsigned int pol = pulso / 148;
    println("ler() => " + String(cm) + "cm, " + String(pol) + "pol");
    if (modo == "cm") {
      return cm;
    } else if (modo == "pol") {
      return pol;
    } else {
      return 0;
    }
  }

} SENSOR_ULTRA;

#endif
