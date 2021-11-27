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
long duration, cm;
int speed1;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RF_Motor, OUTPUT);
  pinMode(LF_Motor, OUTPUT);
  pinMode(RB_Motor, OUTPUT);
  pinMode(LB_Motor, OUTPUT);


}

void loop() {
  while(cm > 40){
  distanceSensor();
  fwd(130);
  }
  distanceSensor();
  stop();
}
void rotateRight(int max, double amplifier){
    while(speedAcc < max){
      speedAcc = speedAcc * amplifier;
      analogWrite(LF_Motor, speedAcc);
      analogWrite(RB_Motor, speedAcc);
      analogWrite(RF_Motor, 0);
      analogWrite(LB_Motor, 0);
      delay(1000);
  }
}

void rotateLeft(int max, double amplifier){
  while(speedAcc < max){
  speedAcc = speedAcc * amplifier;
  analogWrite(LB_Motor, speedAcc);
  analogWrite(RF_Motor, speedAcc);
  analogWrite(LF_Motor, 0);
  analogWrite(RB_Motor, 0);
  delay(100);
  }
}
void stop() {
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(LF_Motor, 0);
  analogWrite(RF_Motor, 0);
}

void fwd(int speed1){
  analogWrite(LF_Motor, speed1);
  analogWrite(RF_Motor, speed1);
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

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
