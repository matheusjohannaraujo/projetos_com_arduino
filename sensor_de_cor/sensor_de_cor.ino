/*
  Desenvolvidor por: Matheus Johann Araujo
  Data: 27/05/2019
  --------------------------------------------------------------------------
  Projeto com uso de Sensor de Cor TCS3200, para detectar as cores do RGB (vermelho, verde e azul).
  Fonte de referência: https://www.arduinoecia.com.br/2014/02/sensor-de-reconhecimento-de-cor-tcs230.html  
*/

void pinSensorCor(int s0, int s1, int s2, int s3, int out, int frequencia) {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  if (frequencia == 0) {
    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
  } else if (frequencia == 2) {
    digitalWrite(s0, LOW);
    digitalWrite(s1, HIGH);
  } else if (frequencia == 20) {
    digitalWrite(s0, HIGH);
    digitalWrite(s1, LOW);
  } else if (frequencia == 100) {
    digitalWrite(s0, HIGH);
    digitalWrite(s1, HIGH);
  }
}

int *lerSensorCor(int s2, int s3, int out, bool debug) {
  int *rgb = calloc(3, sizeof(int));
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  rgb[0] = pulseIn(out, (digitalRead(out) == HIGH) ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  rgb[2] = pulseIn(out, (digitalRead(out) == HIGH) ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  rgb[1] = pulseIn(out, (digitalRead(out) == HIGH) ? LOW : HIGH);
  if (debug) {
    Serial.println("RGB(" + String(rgb[0]) + "," + String(rgb[1]) + "," + String(rgb[2]) + ")");
    if (rgb[0] < rgb[2] && rgb[0] < rgb[1] && rgb[0] < 100) {
      Serial.println("Cor: Vermelho");
    } else if (rgb[2] < rgb[0] && rgb[2] < rgb[1]) {
      Serial.println("Cor: Azul");
    } else if (rgb[1] < rgb[0] && rgb[1] < rgb[2]) {
      Serial.println("Cor: Verde");
    }    
  }
  return rgb;
}

int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;
int out = 12;
bool debug = true;

void setup() {
  Serial.begin(9600);
  pinSensorCor(s0, s1, s2, s3, out, 20);
}

void loop() {
  int *rgb = lerSensorCor(s2, s3, out, debug);
  //Serial.println("RGB(" + String(rgb[0]) + "," + String(rgb[1]) + "," + String(rgb[2]) + ")");
  delay(250);
}
