#include "Robot.h"

//wheels robot
int RF_Motor = 3;
int RB_Motor = 4;
int LF_Motor = 9; 
int LB_Motor = 5; 

int speedAcc = 40;

//ultrasonic sensor
int trigPin = 6;    // Trigger
int echoPin = 7;    // Echo
double duration, cm;
int speed1;
int ledPin = 11;

void setup() {
  Serial.begin(9600);
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

  // if cm is bigger then 20, if cm is smaller or equal to 20
  if(cm <= 1 || cm > 20){
  fwd(255);
  }if (cm > 1 && cm <= 20) {
  stop();
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
  Serial.print(cm);
  Serial.println(" cm");
}
