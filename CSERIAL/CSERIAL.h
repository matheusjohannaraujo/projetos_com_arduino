/*

  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2020-03-12

*/

// Definindo o nome da biblioteca
#ifndef __CSERIAL_H__
#define __CSERIAL_H__

#include <SoftwareSerial.h>

typedef struct {

  unsigned int rx = 10;
  unsigned int tx = 11;
  unsigned int vel = 9600;
  bool br = true;
  SoftwareSerial *sSerial;
  String leitura[2] = {"", ""};

  void pinos() {
    Serial.begin(vel);
    Serial.println("USB>Conectado");
    sSerial = new SoftwareSerial(rx, tx);// RX, TX
    (*sSerial).begin(vel);
    (*sSerial).println("PIN>Conectado");
  }

  void definir(unsigned int _rx, unsigned int _tx, unsigned int _vel) {
    rx = _rx;
    tx = _tx;
    vel = _vel;
    pinos();
  }

  String ler_usb() {
    String response = "";
    if (Serial.available()) {
      response = Serial.readString();
      response.replace("\r", "");
      response.replace("\n", "");
    }
    return response;
  }

  String ler_pin() {
    String response = "";
    if ((*sSerial).available()) {
      response = (*sSerial).readString();
      response.replace("\r", "");
      response.replace("\n", "");
    }
    return response;
  }

  int ler() {
    leitura[0] = ler_usb();
    leitura[1] = ler_pin();
    return &leitura;
  }

  void escrever_usb(String request) {
    if (request != "") {
      Serial.print(request + (br ? "\r\n" : ""));
    }
  }

  void escrever_pin(String request) {
    if (request != "") {
      (*sSerial).print(request + (br ? "\r\n" : ""));
    }
  }

  void escrever(String request) {
    escrever_usb(request);
    escrever_pin(request);
  }

} CSERIAL;

#endif
