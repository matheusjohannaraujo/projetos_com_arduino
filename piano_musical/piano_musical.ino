/*
  Função: Piano Musical
  Desenvolvido por: Matheus Johann Araújo
  E-mail: matheusjohannaraujo@gmail.com
  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino/tree/master/piano_musical
  Data: 24/04/2019
*/
// Carrega a biblioteca do Sensor Ultrassonico HC-SR04 ao Arduino
// https://github.com/filipeflop/Ultrasonic
#include <Ultrasonic.h>

// Notas
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

// Constantes
#define minDistan 3
#define maxDistan 40
#define delayBuzz 250

// Pinos
#define pinBuzz 10
#define pinButt 11
const int nota[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };
const String cifra[] = { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" };
const int pinLed[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

// Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic_1(22, 23);
Ultrasonic ultrasonic_2(24, 25);
Ultrasonic ultrasonic_3(26, 27);
Ultrasonic ultrasonic_4(28, 29);
Ultrasonic ultrasonic_5(30, 31);
Ultrasonic ultrasonic_6(32, 33);
Ultrasonic ultrasonic_7(34, 35);
Ultrasonic ultrasonic_8(36, 37);

// Funções
void setPinInp(int *vet, int len) {
  for (int i = 0; i < len; i++)
    pinMode(vet[i], INPUT);
}

void setPinOut(int *vet, int len) {
  for (int i = 0; i < len; i++)
    pinMode(vet[i], OUTPUT);
}

// Gravador de notas
const int vet_size = 128;
int vet_int[vet_size];
int vet_count = 0;

void insereVet(int i) {
  if (vet_count == vet_size) {
    vet_count = 0;
  }
  vet_int[vet_count++] = i;
}

void limpaVet() {
  for (int i = 0, x = 0; i < vet_size; i++) {
    vet_int[i] = -1;
  }
}

void tocarVet() {
  for (int i = 0; i < vet_size; i++) {
    int x = vet_int[i];
    if (x == -1) {
      break;
    }
    Serial.println("Numero da nota: " + String(x) + ", Cifra: " + String(cifra[x]));
    tone(pinBuzz, nota[x], delayBuzz);
    digitalWrite(pinLed, HIGH);
    delay(delayBuzz);
    noTone(pinBuzz);
    digitalWrite(pinLed, LOW);
  }
  vet_count = 0;
  limpaVet();
}

void playUltraSoundLed(int distancia, int numeroSensor) {
  Serial.println("Utrassônico " + String(numeroSensor--) + ": " + String(distancia) + "cm");
  if (distancia >= minDistan && distancia <= maxDistan) {
    Serial.println("Cifra: " + String(cifra[numeroSensor]));
    tone(pinBuzz, nota[numeroSensor], delayBuzz);
    digitalWrite(pinLed[numeroSensor], HIGH);
    delay(delayBuzz);
    noTone(pinBuzz);
    digitalWrite(pinLed[numeroSensor], LOW);
    insereVet(numeroSensor);
  }
  if (digitalRead(pinButt)) {
    tocarVet();
  }
}

void setup() {
  setPinOut(pinLed, sizeof(pinLed) / sizeof(int));
  pinMode(pinBuzz, OUTPUT);
  pinMode(pinButt, INPUT);
  Serial.begin(9600);
  limpaVet();
}

void loop() {
  playUltraSoundLed(ultrasonic_1.convert(ultrasonic_1.timing(), Ultrasonic::CM), 1);
  playUltraSoundLed(ultrasonic_2.convert(ultrasonic_2.timing(), Ultrasonic::CM), 2);
  playUltraSoundLed(ultrasonic_3.convert(ultrasonic_3.timing(), Ultrasonic::CM), 3);
  playUltraSoundLed(ultrasonic_4.convert(ultrasonic_4.timing(), Ultrasonic::CM), 4);
  playUltraSoundLed(ultrasonic_5.convert(ultrasonic_5.timing(), Ultrasonic::CM), 5);
  playUltraSoundLed(ultrasonic_6.convert(ultrasonic_6.timing(), Ultrasonic::CM), 6);
  playUltraSoundLed(ultrasonic_7.convert(ultrasonic_7.timing(), Ultrasonic::CM), 7);
  playUltraSoundLed(ultrasonic_8.convert(ultrasonic_8.timing(), Ultrasonic::CM), 8);
}
