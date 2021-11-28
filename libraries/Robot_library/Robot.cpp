/*  Robot.h V1.1 for L298N motor driver boards
 *  By Jorrit van den Eerenbeemt, 19-2-2018  
 *  Private use 
 */

#include "Robot.h"
#include "Arduino.h"
//ENA=right
//ENB=left
Robot::Robot(int ENA, int IN1, int IN2, int IN3, int IN4, int ENB) {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  _ENA = ENA;
  _ENB = ENB;
  _IN1 = IN1;
  _IN2 = IN2;
  _IN3 = IN3;
  _IN4 = IN4;
}

void Robot::fwd(int speed){
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  analogWrite(_ENA, speed);
  Serial.println("Motor1 fired up");
  delay(1);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
  analogWrite(_ENB, speed);
  Serial.println("Motor2 fired up");
  Serial.println("Forward!!");
}

void Robot::bwd(int speed){
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
  analogWrite(_ENA, speed);
  Serial.println("Motor1 fired up");
  delay(1);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);
  analogWrite(_ENB, speed);
  Serial.println("Motor2 fired up");
  Serial.println("Backward!!");
}

void Robot::stp(){
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
  Serial.println("Motor1 killed");
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW);
  Serial.println("Motor2 killed");  
  Serial.println("Halt!!");
}

void Robot::thl(){
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  analogWrite(_ENA, 225);
  Serial.println("Motor1 fired up");
  delay(1);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW); 
  delay(500);
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
  Serial.println("Turn hard right!!");
}

void Robot::thr(){
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
  analogWrite(_ENA, 225);
  delay(1);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW); 
  Serial.println("Motor2 fired up");
  delay(500);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW);
  Serial.println("Turn hard left!!");
}

void Robot::tsl(int speed){
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  analogWrite(_ENA, speed);
  Serial.println("Motor1 fired up");
  delay(1);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
  analogWrite(_ENB, speed-100);
  Serial.println("Motor2 fired up");
  Serial.println("Slow left!!");
}


void Robot::tsr(int speed){
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  analogWrite(_ENA, speed-100);
  Serial.println("Motor1 fired up");
  delay(1);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
  analogWrite(_ENB, speed);
  Serial.println("Motor2 fired up");
  Serial.println("Slow right!!");
}
