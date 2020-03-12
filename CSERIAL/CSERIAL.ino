#include "CSERIAL.h"

CSERIAL cserial;

void setup() {
  cserial.definir(10, 11, 9600);
}

void loop() {
  String *leitura = cserial.ler();// [0 = "USB", 1 = "PIN"]
  if (leitura[0] != "") {
    cserial.escrever_pin("USB>" + leitura[0]);
  }
  if (leitura[1] != "") {
    cserial.escrever_usb("PIN>" + leitura[1]);
  }
}
