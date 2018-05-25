/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2017-10-13
*/

#include <Servo.h>

Servo servoMotor;

void setup(){
  Serial.begin(9600);
  servoMotor.attach(10);
}

void loop(){
  Serial.print("Servo motor indo para 0º");
  servoMotor.write(0);
  delay(1000);
  Serial.print("Servo motor indo para 180º");
  servoMotor.write(180);
  delay(1000);
}
