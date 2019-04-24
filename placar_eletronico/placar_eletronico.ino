/*
  Função: Placar Eletronico
  Desenvolvido por: Matheus Johann Araújo
  E-mail: matheusjohannaraujo@gmail.com
  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino/tree/master/placar_eletronico
  Data: 15/04/2019
*/
#include <EEPROM.h>

const int btn_mais_a = 2;
const int btn_menos_a = 5;
const int btn_mais_b = 4;
const int btn_menos_b = 5;

const int led_1 = 22;
const int led_2[] = {23, 24, 25, 26, 27, 28, 29};
const int led_3[] = {30, 31, 32, 33, 34, 35, 36};

const int led_4 = 37;
const int led_5[] = {38, 39, 40, 41, 42, 43, 44};
const int led_6[] = {45, 46, 47, 48, 49, 50, 51};

/*

  1 = Cima E
  2 = Cima
  3 = Cima D
  4 = Centro
  5 = Baixo E
  6 = Baixo
  7 = Baixo D
*/

const int segmentos[10][7] = { // 11 linhas, 8 colunas
  { 1, 1, 1, 0, 1, 1, 1 }, //0
  { 0, 0, 1, 0, 0, 0, 1 }, //1
  { 0, 1, 1, 1, 1, 1, 0 }, //2
  { 0, 1, 1, 1, 0, 1, 1 }, //3
  { 1, 0, 1, 1, 0, 0, 1 }, //4
  { 1, 1, 0, 1, 0, 1, 1 }, //5
  { 1, 1, 0, 1, 1, 1, 1 }, //6
  { 0, 1, 1, 0, 0, 0, 1 }, //7
  { 1, 1, 1, 1, 1, 1, 1 }, //8
  { 1, 1, 1, 1, 0, 1, 1 }, //9
};

int contador_a = 0, contador_b = 0, eeAddress = 0;

struct contadores
{
  int a;
  int b;
};

struct contadores var_contadores;

void cduLedsA(int valor) {
  const int c = valor / 100;
  const int d = (valor % 100) / 10;
  const int u = ((valor % 100) % 10);
  if (c == 1)
    digitalWrite(22, !HIGH);
  else
    digitalWrite(22, !LOW);
  mostrarNumero(23, d);
  mostrarNumero(30, u);
}

void cduLedsB(int valor) {
  const int c = valor / 100;
  const int d = (valor % 100) / 10;
  const int u = ((valor % 100) % 10);
  if (c == 1)
    digitalWrite(37, !HIGH);
  else
    digitalWrite(37, !LOW);
  mostrarNumero(38, d);
  mostrarNumero(45, u);
}

void incrementoA() {
  Serial.println("Incrementando A: " + String(contador_a));
  if (++contador_a > 199) {
    contador_a = 199;
  }
  cduLedsA(contador_a);
}

void decrementoA() {
  Serial.println("Decrementando A: " + String(contador_a));
  if (--contador_a < 0) {
    contador_a = 0;
  }
  cduLedsA(contador_a);
}

void incrementoB() {
  Serial.println("Incrementando B: " + String(contador_b));
  if (++contador_b > 199) {
    contador_b = 199;
  }
  cduLedsB(contador_b);
}

void decrementoB() {
  Serial.println("Decrementando B: " + String(contador_b));
  if (--contador_b < 0) {
    contador_b = 0;
  }
  cduLedsB(contador_b);
}

void mostrarNumero(int pinoInicial, int valor) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinoInicial, !segmentos[valor][i]);
    pinoInicial++;
  }
}

void setLedPin(int *v, int n) {
  for (int i = 0; i < n; i++) {
    pinMode(v[i], OUTPUT);
    digitalWrite(v[i], HIGH);
  }
}

void checkLedPin() {
  digitalWrite(led_1, !LOW);
  digitalWrite(led_4, !LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(led_2[i], !HIGH);
    digitalWrite(led_3[i], !HIGH);
    digitalWrite(led_5[i], !HIGH);
    digitalWrite(led_6[i], !HIGH);
    delay(500);
    digitalWrite(led_2[i], !LOW);
    digitalWrite(led_3[i], !LOW);
    digitalWrite(led_5[i], !LOW);
    digitalWrite(led_6[i], !LOW);
  }
  digitalWrite(led_1, !HIGH);
  digitalWrite(led_4, !HIGH);
  for (int i = 9; i >= 0; i--) {
    mostrarNumero(23, i);
    mostrarNumero(30, i);
    mostrarNumero(38, i);
    mostrarNumero(45, i);
    delay(500);
  }
  digitalWrite(led_1, !LOW);
  digitalWrite(led_4, !LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(led_1, OUTPUT);
  digitalWrite(led_1, HIGH);
  setLedPin(led_2, sizeof(led_2) / sizeof(int));
  setLedPin(led_3, sizeof(led_3) / sizeof(int));
  pinMode(led_4, OUTPUT);
  digitalWrite(led_4, HIGH);
  setLedPin(led_5, sizeof(led_5) / sizeof(int));
  setLedPin(led_6, sizeof(led_6) / sizeof(int));
  pinMode(btn_mais_a, INPUT);
  pinMode(btn_menos_a, INPUT);
  pinMode(btn_mais_b, INPUT);
  pinMode(btn_menos_b, INPUT);
  checkLedPin();
  EEPROM.get(eeAddress, var_contadores);
  contador_a = var_contadores.a;
  contador_b = var_contadores.b;
  cduLedsA(contador_a);
  cduLedsB(contador_b);
}

void loop() {
  if (!digitalRead(btn_mais_a)) {
    Serial.println("BTN_A +");
    incrementoA();
  }
  if (!digitalRead(btn_menos_a)) {
    Serial.println("BTN_A -");
    decrementoA();
  }
  if (!digitalRead(btn_mais_a) && !digitalRead(btn_menos_a)) {
    Serial.println("BTN_A (+) e (-)");
    contador_a = 0;
  }
  if (!digitalRead(btn_mais_b)) {
    Serial.println("BTN_B +");
    incrementoB();
  }
  if (!digitalRead(btn_menos_b)) {
    Serial.println("BTN_B -");
    decrementoB();
  }
  if (!digitalRead(btn_mais_b) && !digitalRead(btn_menos_b)) {
    Serial.println("BTN_B (+) e (-)");
    contador_b = 0;
  }
  delay(200);
  var_contadores.a = contador_a;
  var_contadores.b = contador_b;
  EEPROM.put(eeAddress, var_contadores);
}
