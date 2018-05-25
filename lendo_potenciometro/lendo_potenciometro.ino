/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2017-11-03
*/

#define potenciometro A1

void setup() {
  Serial.begin(9600);
  pinMode(potenciometro, INPUT);
}

void loop() {
  Serial.print("Potênciometro em: ");
  Serial.print(analogRead(potenciometro));  
  delay(1000);
}
