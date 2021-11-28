#include "Robot.h"

//wheels robot
int RF_Motor = 3; //Right Front Motors front
int LF_Motor = 9; //Left Front Motors front
int LB_Motor = 5; //Left
int RB_Motor = 4;
int speedAcc = 40;

//ultrasonic sensor
int trigPin = 6;    // Trigger
int echoPin = 7;    // Echo
double duration, cm;
int speed1;
int ledPin = 11;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RF_Motor, OUTPUT);
  pinMode(LF_Motor, OUTPUT);
  pinMode(RB_Motor, OUTPUT);
  pinMode(LB_Motor, OUTPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  distanceSensor();
  digitalWrite(ledPin,LOW);
  if(cm > 20){
  distanceSensor();
  fwd(150);
  delay(500);
  digitalWrite(ledPin, HIGH);
  }
  if (cm <= 20){
  stop();
  digitalWrite(ledPin, HIGH);
  distanceSensor();
  }
  /*delay(300);
  rotateRight(140);
  delay(400);
  distanceSensor();
  }/*
  distanceSensor();
  delay(300);
  rotateRight(140);
  delay(400);
  distanceSensor();*/
}

void rotateRight(int speed){
  analogWrite(LF_Motor, speed);
  analogWrite(RB_Motor, speed);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, 0);
  
}

void rotateLeft(int speed){
  analogWrite(LF_Motor, speed);
  analogWrite(RB_Motor, speed);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, 0);
}

void stop() {
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(LF_Motor, 0);
  analogWrite(RF_Motor, 0);
}

void stopAll(){
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(LF_Motor, 0);
  analogWrite(RF_Motor, 0);
  analogWrite(trigPin, LOW);
  analogWrite(echoPin, LOW);
}

void fwd(int speed){
  analogWrite(LF_Motor, speed);
  analogWrite(RF_Motor, speed);
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  
}

void bwd(int speed1){
  analogWrite(LF_Motor, 0);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, speed1);
  analogWrite(RB_Motor, speed1);
  
}

void distanceSensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  delay(250);
}
