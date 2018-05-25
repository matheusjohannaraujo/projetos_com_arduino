/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2018-01-13
*/

#define pinoVelocidade 10
#define pinoSentidoHorario 11
#define pinoSentidoAntiHorario 12

void setup() {
  pinMode(pinoVelocidade, OUTPUT);
  pinMode(pinoSentidoHorario, OUTPUT);
  pinMode(pinoSentidoAntiHorario, OUTPUT);
  analogWrite(pinoVelocidade, 0);
  digitalWrite(pinoSentidoHorario, LOW);
  digitalWrite(pinoSentidoAntiHorario, LOW);
  Serial.begin(9600);
}

void loop() {
  switch (Serial.read()) {
    case '0':
      analogWrite(pinoVelocidade, 0);
      digitalWrite(pinoSentidoHorario, LOW);
      digitalWrite(pinoSentidoAntiHorario, LOW);
      Serial.println("Motor parado.");
      break;
    case '1':
      analogWrite(pinoVelocidade, 255);
      digitalWrite(pinoSentidoHorario, HIGH);
      digitalWrite(pinoSentidoAntiHorario, LOW);
      Serial.println("Motor rodando no sentido horário.");
      break;
    case '2':
      analogWrite(pinoVelocidade, 255);
      digitalWrite(pinoSentidoHorario, LOW);
      digitalWrite(pinoSentidoAntiHorario, HIGH);
      Serial.println("Motor rodando no sentido anti-horário.");
      break;
  }
  delay(1000);
}
