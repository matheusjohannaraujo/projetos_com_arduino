/*

  Função: Piano Musical
  Desenvolvido por: Matheus Johann Araújo
  E-mail: matheusjohannaraujo@gmail.com
  GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino/tree/master/piano_musical
  Data: 15/04/2019

*/

// Notas
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

// Pinos
#define pinBuzz 10
#define pinButt 11
const int nota_4[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C4 };
const int nota_5[] = { NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C5 };
const String cifra_4[] = { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C4" };
const String cifra_5[] = { "C5", "D5", "E5", "F5", "G5", "A5", "B5", "C5" };
const int pinUltraTrig[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
const int pinUltraEcho[] = { 23, 25, 27, 29, 31, 33, 35, 37 };
const int pinLed[] = { 2, 3, 4, 5, 6, 7, 8, 9 };


// Constantes
#define delayBuzz 250
#define maxDistan 25

void setup() {
  setPinOut(pinUltraTrig, sizeof(pinUltraTrig) / sizeof(int));
  setPinInp(pinUltraEcho, sizeof(pinUltraEcho) / sizeof(int));
  setPinOut(pinLed, sizeof(pinLed) / sizeof(int));
  pinMode(pinBuzz, OUTPUT);
  pinMode(pinButt, INPUT);
  Serial.begin(9600);
}

void loop() {
  playUltraSoundLed();
}

void setPinInp(int *vet, int len) {
  for (int i = 0; i < len; i++)
    pinMode(vet[i], INPUT);
}

void setPinOut(int *vet, int len) {
  for (int i = 0; i < len; i++)
    pinMode(vet[i], OUTPUT);
}

// Função que mede a distância com o utrassônico, recebe como parâmetro os pinos Trigger e Echo em formato de ponteiro
// E tem como retorno um valor inteiro sem sinal (número natural), esse valor é a distância medida em cm.
unsigned int distanciaUltrassonico(int pinTrig, int pinEcho) {
  // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(pinTrig, LOW);
  // Espera dois micro segundos
  delayMicroseconds(2);
  // Escreve valor ligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(pinTrig, HIGH);
  // Espera dez micro segundos
  delayMicroseconds(10);
  // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(pinTrig, LOW);
  // Faz a leitura pulso no pino Echo, e divide o valor da leitura por 58. Com isso obtem-se a distância em centímetros
  return (pulseIn(pinEcho, HIGH) / 58);
}

void playUltraSoundLed() {
  for (int i = 0; i < 8; i++) {
    int distancia = distanciaUltrassonico(pinUltraTrig[i], pinUltraEcho[i]);
    Serial.println("Utrassônico " + String(i + 1) + ": " + String(distancia) + "cm");
    if (distancia > 2 && distancia <= maxDistan) {
      Serial.println("Cifra: " + String(cifra_5[i]));
      tone(pinBuzz, nota_5[i], delayBuzz);
      digitalWrite(pinLed[i], HIGH);
      delay(delayBuzz);
      noTone(pinBuzz);
      digitalWrite(pinLed[i], LOW);
    }
  }
}
