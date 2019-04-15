/*

Função: Piano Musical
Desenvolvido por: Matheus Johann Araújo
E-mail: matheusjohannaraujo@gmail.com
GitHub: https://github.com/matheusjohannaraujo/projetos_com_arduino/piano_musical/
Data: 15/04/2019

*/

void setPinInp(int *vet, int len);
void setPinOut(int *vet, int len);
unsigned int distanciaUltrassonico(int *pinTrig, int *pinEcho);
void playUltraSoundLed();

// Notas
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

// Pinos
#define pinBuzz 9
const int nota[] = { NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5 };
const String cifra[] = { "C5", "D5", "E5", "F5", "G5", "A5", "B5" };
const int pinUltraTrig[] = { 22, 24, 26, 28, 30, 32, 34 };
const int pinUltraEcho[] = { 23, 25, 27, 29, 31, 33, 35 };
const int pinLed[] = { 2, 3, 4, 5, 6, 7, 8 };

// Constantes
#define delayBuzz 200
#define maxDistan 40

void setup() {
  setPinOut(pinUltraTrig, sizeof(pinUltraTrig) / sizeof(int));
  setPinInp(pinUltraEcho, sizeof(pinUltraEcho) / sizeof(int));
  setPinOut(pinLed, sizeof(pinLed) / sizeof(int));
  pinMode(pinBuzz, OUTPUT);
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
unsigned int distanciaUltrassonico(int *pinTrig, int *pinEcho) {
  // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(*pinTrig, LOW);
  // Espera dois micro segundos
  delayMicroseconds(2);
  // Escreve valor ligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(*pinTrig, HIGH);
  // Espera dez micro segundos
  delayMicroseconds(10);
  // Escreve valor desligado no pino do Trig (controlando a porta do Arduino)
  digitalWrite(*pinTrig, LOW);
  // Faz a leitura pulso no pino Echo, e divide o valor da leitura por 58. Com isso obtem-se a distância em centímetros
  return (pulseIn(*pinEcho, HIGH) / 58);
}

void playUltraSoundLed() {
  for (int i = 0, distancia = 0; i < 7; i++) {
    distancia = distanciaUltrassonico(&pinUltraTrig[i], &pinUltraEcho[i]);
    if (distancia <= maxDistan) {
      Serial.println("Utrassônico: " + String(distancia) + "cm");
      Serial.println("Cifra: " + String(cifra[i]));
      tone(pinBuzz, nota[i], delayBuzz);
      digitalWrite(pinLed[i], HIGH);
      delay(delayBuzz);
      noTone(pinBuzz);
      digitalWrite(pinLed[i], LOW);
      delay(delayBuzz);
      break;
    }
  }
}
