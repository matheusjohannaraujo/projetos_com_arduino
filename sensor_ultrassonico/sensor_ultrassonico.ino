/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2017-09-28
*/

int pinTrig1 = 1;
int pinEcho1 = 2;

void setup(){
  Serial.begin(9600);
  pinMode(pinTrig1, OUTPUT);
  pinMode(pinEcho1, INPUT);
}

int distanciaUltrasonico(int *pinTrig, int *pinEcho){
  digitalWrite(*pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(*pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(*pinTrig, LOW);
  return (pulseIn(*pinEcho, HIGH) / 58);
}

void loop(){
  Serial.print("Distância sensor ultrassonico: ");
  Serial.print(distanciaUltrasonico(&pinTrig1, &pinEcho1));
  Serial.println("cm");  
  delay(1000);
}
