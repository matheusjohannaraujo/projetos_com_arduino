
/*
  Desenvolvidor por: Matheus Johann Araujo
  Data: 23/05/2019
  --------------------------------------------------------------------------
  Projeto com uso de Sensor de Gas MQ-3 (usando-o como sensor de alcool), e que possui
  indicadores luminosos (leds) para os niveis de alcool detectado pelo sensor.
*/

#define sensorMQ3 A1
#define ledVerde 11
#define ledAmarelo 12
#define ledVermelho 13

unsigned int tempoAquecimento = 300;
unsigned int valorSensor = 0;
unsigned int statusTemporizador = 1;
unsigned long temporizador;
String estadoSensor;

void controleDeLeds(int *v) {
  digitalWrite(ledVerde, !!v[0]);
  digitalWrite(ledVerde, !!v[1]);
  digitalWrite(ledVerde, !!v[2]);
}

void setup(void) {
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(sensorMQ3, INPUT);
}

void loop() {
  temporizador = millis() / 1000;
  if (temporizador <= tempoAquecimento) {
    temporizador = map(temporizador, 0, tempoAquecimento, 0, 30);
    statusTemporizador = 1;
  } else {
    statusTemporizador = 0;
  }
  if (statusTemporizador == 0) {
    valorSensor = analogRead(sensorMQ3);
    if (valorSensor >= 0 && valorSensor <= 50) {
      int v[] = { 1, 0, 0 };
      controleDeLeds(v);
      estadoSensor = "Alcool nao encontrado.";
    } else if (valorSensor >= 51 && valorSensor <= 200) {
      int v[] = { 1, 1, 0 };
      controleDeLeds(v);
      estadoSensor = "Um pouco de alcool foi encontrado.";
    } else if (valorSensor >= 201 && valorSensor <= 400) {
      int v[] = { 0, 1, 0 };
      controleDeLeds(v);
      estadoSensor = "Alcool detectado! Valor acima do minimo.";
    }  else if (valorSensor >= 401 && valorSensor <= 600) {
      int v[] = { 0, 1, 1 };
      controleDeLeds(v);
      estadoSensor = "Alcool encontrado! Valor acima do valor medio.";
    } else if (valorSensor >= 601) {
      int v[] = { 0, 0, 1 };
      controleDeLeds(v);
      estadoSensor = "Atencao, muito alcool detectado!";
    }
    Serial.println(estadoSensor);
    Serial.println("O valor lido pelo sensor foi: " + String(estadoSensor));
    delay(3000);
    {
      int v[] = { 1, 1, 1 };
      controleDeLeds(v);
    }
    delay(2000);
    {
      int v[] = { 0, 0, 0 };
      controleDeLeds(v);
    }
  } else if (statusTemporizador == 1) {
    if (temporizador == 0) {
      temporizador = 1;
    }
  }
  delay(50);
}
