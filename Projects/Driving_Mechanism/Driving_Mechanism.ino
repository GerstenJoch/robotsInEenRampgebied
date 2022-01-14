#include <Pixy2.h>
#include <SPI.h>

//wheels robot
const int RB_Motor = 3;
const int RF_Motor = 4;
const int LB_Motor = 9; 
const int LF_Motor = 5; 
int speed1;
//ultrasonic sensor
const int trigPinF = 12;    // Trigger
const int echoPinF = 13;    // Echo
const int trigPinL = 10;
const int echoPinL = 11;
int trigPinR;         //Moet nog sensor aangesloten
int echoPinR;         //""
double duration, cmF,cmR,cmL;
//pixycam
Pixy2 pixy;
int pixy_x;
int pixy_y;
int pixy_age;
int i;
int x = 1;
int j;
int ageCheck;
//Button & Buzzer
const int startButton = 2;
int startButtonState;
const int buzzer = 8;
const int ledPin = 6;
const int stopButtonPin = 7;
int stopButtonState;

void setup() {
  Serial.begin(9600);
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(RF_Motor, OUTPUT);
  pinMode(LF_Motor, OUTPUT);
  pinMode(RB_Motor, OUTPUT);
  pinMode(LB_Motor, OUTPUT);
  pinMode(startButton, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(stopButtonPin, INPUT);
  pixy.init();
  digitalWrite(ledPin, LOW);  
}

void loop() {
  startButtonState = digitalRead(startButton);
  stopButtonState = digitalRead(stopButtonPin);
  
  if (startButtonState == HIGH) {
    Serial.print("Protocol initiated /n");
   // while (true){    
    digitalWrite(ledPin, HIGH);
    fwd(255);
    //objectDetection();
    //distanceCheck();
   
   // stopButtonState = digitalRead(stopButtonPin);
   // if (stopButtonState == HIGH){
   //   return false;
   // }
   // }
  }
  if (stopButtonState == HIGH) {
    Serial.print("Protocol stopped /n");
    //while (true){        
    digitalWrite(ledPin, LOW);
    stopAll();
    //startButtonState = digitalRead(startButton);
 //   if (startButtonState == HIGH){
 //     return false;
  //  }
  }
}
//}
//}
void rotateRight(int speed, int time){
  analogWrite(LF_Motor, speed);
  analogWrite(RB_Motor, speed);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, 0);
  delay(time);
  stop();
}

void rotateLeft(int speed, int time){
  analogWrite(LF_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(RF_Motor, speed);
  analogWrite(LB_Motor, speed);
  delay(time);
  stop();
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
  analogWrite(trigPinF, LOW);
  analogWrite(echoPinF, LOW);
  analogWrite(trigPinL, LOW);
  analogWrite(echoPinL, LOW);
  analogWrite(trigPinR, LOW);
  analogWrite(echoPinR, LOW);
}

void fwd(int speed){
  analogWrite(LF_Motor, speed - 30);
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
/*void onOrOffCheck(){
   int buttonOutput = digitalRead(button);
 if (isButtonPressed == 0 && buttonOutput == HIGH){
  onOrOff = 1; 
  isButtonPressed = 1;
  delay(200);
}if (isButtonPressed == 1 && buttonOutput == HIGH){
  onOrOff = 0;
  isButtonPressed = 0;
  delay(200);
}
}
*/

void distanceSensorFront(){
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
      // Read the signal from the sensor: a HIGH pulse whose
      // duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
  pinMode(echoPinF, INPUT);
  duration = pulseIn(echoPinF, HIGH);
      // Convert the time into a distance
  cmF = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  delay(10);
}

void distanceSensorRight(){
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
      // Read the signal from the sensor: a HIGH pulse whose
      // duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
  pinMode(echoPinR, INPUT);
  duration = pulseIn(echoPinR, HIGH);
      // Convert the time into a distance
  cmR = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  delay(10);
}
void distanceSensorLeft(){
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
      // Read the signal from the sensor: a HIGH pulse whose
      // duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
  pinMode(echoPinL, INPUT);
  duration = pulseIn(echoPinL, HIGH);
      // Convert the time into a distance
  cmL = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  delay(10);
}
void distanceCheck() {
  distanceSensorFront();
  // if cm is bigger then 20, if cm is smaller or equal to 20
  if(cmF <= 1 || cmF > 20){
  fwd(180);
  }if (cmF > 1 && cmF <= 20) {
  stop();
  distanceLeftRightCheck();
  }
}
void distanceLeftRightCheck(){
  distanceSensorRight();
  if (cmR > 20){
    rotateRight(255, 500);
    Serial.print("Check complete on right sensor, turning right /n");
    return;
  } else if (cmR <= 20) {
    distanceSensorLeft();
    if (cmL > 20){
      rotateLeft(255, 500);
      Serial.print("Not enough space on right side, turning left /n");
      return;
    } else if (cmL <= 20) {
        while (cmL <= 20 && cmR <= 20){
          bwd(255);
          Serial.print("Not enough space on left and right, moving in reverse /n");
          distanceSensorLeft();
          distanceSensorRight();
        }
        if (cmL > 20){
          stop();
          rotateLeft(255, 500);
          Serial.print("Found enough space on left side, stopping on return and rotating left. /n");
        } if (cmR >20){
          stop();
          rotateLeft(255, 500);
          Serial.print("Found enough space on right side, stopping on return and rotating right. /n");
        }
  }
  }
}
/*void collisionCheck() {
  if (cmF > 20);
  stopAll();
}
*/

void objectDetection(){ 
  /*// grab blocks!
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    //pixy.ccc.numBlocks)
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      pixy_x = pixy.ccc.blocks[i].m_x;
      pixy_y = pixy.ccc.blocks[i].m_y;
      pixy_age = pixy.ccc.blocks[i].m_age;
    }
    if (pixy_age > 30){

    }
       /*if (pixy_age < 30){
         return;
         } else {
           if (pixy.ccc.numBlocks > 1){
             for (j = 1; j < pixy.ccc.numBlocks; j++){
              int k = pixy.ccc.blocks[j].m_age;
             int l = pixy.ccc.blocks[j-1].m_age;
             if (k > l){
               ageCheck = k;
             }
             else {
               ageCheck = l;
             }

             //Runs if more than one object
             if (j+1 == pixy.ccc.numBlocks){
               if (pixy.ccc.blocks[j].m_age == ageCheck){
                 if (pixy_x <= 140){
                   while (pixy_x <= 140){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 170){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 }
                 x = 1;
                }else if (pixy_x > 140 && pixy_x <= 170){
                  while (pixy_x <= 140){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 170){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 }
                 x = 1;
                } else {
                  while (pixy_x <= 140){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 170){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 }
                 x = 1;
              }
               }
             } 
           } 
           } 
           
           //Runs if only one object
           
           //else if (pixy.ccc.numBlocks <= 1){
           if (pixy.ccc.numBlocks > 0){
           if (pixy_x <= 140){
                while (pixy_x <= 140){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 } while (pixy_x > 170){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 }
                 x = 1;
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                   Serial.println(pixy_x);
                 }
                 x = 1;
                } else if (pixy_x > 140 && pixy_x <= 170){
                  while (pixy_x <= 140){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                 } while (pixy_x > 170){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                 }
                 x = 1;
                } else {
                while (pixy_x <= 140){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                 } while (pixy_x > 140 && pixy_x <= 170){
                   fwd(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                 } while (pixy_x > 170){
                   rotateLeft(200);
                   pixy.ccc.getBlocks();
                   checkJValue();
                   pixy_x = pixy.ccc.blocks[j].m_x;
                 }
                 x = 1;
              }
         }
    }
}
void checkJValue(){
  for (int g=0; g<pixy.ccc.numBlocks; g++)
    {
      int min = pixy.ccc.blocks[g].m_x - 10;
      int max = pixy.ccc.blocks[g].m_x + 10;
      if (min >= pixy.ccc.blocks[j].m_x && max <= pixy.ccc.blocks[j].m_x){
        j = g;
      }
    }*/
}

