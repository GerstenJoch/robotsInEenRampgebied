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
int pixy_x, pixy_y,pixy_age,pixy_width,pixy_height, pixy_old_x;
int pixy_x_j, pixy_y_j,pixy_age_j,pixy_width_j,pixy_height_j;
int i;
int j;
int ageCheck;
//Button & Buzzer
const int startButton = 2;
int startButtonState;
const int ledPin = 6;
const int stopButtonPin = 7;
int stopButtonState;

void setup() {                        //Let's all the components initiate
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
  pinMode(ledPin, OUTPUT);
  pinMode(stopButtonPin, INPUT);
  pixy.init();
  digitalWrite(ledPin, LOW);  
}

void loop() {
  justWork();
}

void justWork(){
    startButtonState = digitalRead(startButton);                         //Checks the state of the start and stop buttons
  stopButtonState = digitalRead(stopButtonPin);
  
  if (startButtonState == HIGH) {                                      //Robot starts when startbutton is pressed
    Serial.print("Protocol initiated /n");
  
    digitalWrite(ledPin, HIGH);
    fwd(255);
    /* while (true){  
    objectDetection();
    distanceCheck();
   
    stopButtonState = digitalRead(stopButtonPin);
    if (stopButtonState == HIGH){
      return false;
    }
    } */
  }
  if (stopButtonState == HIGH) {                                       //Robot stops when stopbutton is pressed
    Serial.print("Protocol stopped /n");
    digitalWrite(ledPin, LOW);
    stopAll();
    /*while (true){        
    startButtonState = digitalRead(startButton);
     if (startButtonState == HIGH){
      return false;
    }
    }
    }*/
  }
}
//Driving functions these can be call in the logic and alorithms to be more efficient when coding
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

//Functions for the ultrasonic distance sensor to call them later. This makes coding easier
void distanceSensorFront(){
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
  pinMode(echoPinF, INPUT);
  duration = pulseIn(echoPinF, HIGH);
  cmF = (duration/2) / 29.1;
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

//These 2 functions are used for the logic to let the robot stop when it's nearing a wall and let it find it's way through

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
    Serial.print("Check complete on RIGHT sensor, turning right /n");
    return;
  } else if (cmR <= 20) {
    distanceSensorLeft();
    if (cmL > 20){
      rotateLeft(255, 500);
      Serial.print("Check complete on LEFT sensor, turning right /n");
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
//Function for the pixy cam. The camera detection. It look if the detected object is left or right. Depending on that, 
//it rotates and drives the robot until it's right in front of it
//It goes to a filtering system to make sure when more that 1 object is detected,
//It detects the right one.
void objectDetection(){ 
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
      pixy_width = pixy.ccc.blocks[i].m_width;
      pixy_height = pixy.ccc.blocks[i].m_height;
      if (pixy_age > 30){
        if (!(pixy_y <=50 || pixy_y >= 250)){
          if ((!(pixy_width <= 10 || pixy_width >= 50)) || (!(pixy_height <= 10 || pixy_height >= 50))){
            pixy_old_x = pixy_x;
            if (pixy_old_x <= 140){
              while (pixy_x <= 140){
                rotateLeft(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              } while (pixy_x > 140 && pixy_x <= 170){
                fwd(255);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
                distanceSensorFront();
                if(cmF <= 1 || cmF > 20){
                fwd(180);
                }if (cmF > 1 && cmF <= 20) {
                stop();
                break;
                }
              } while (pixy_x > 170){
                rotateRight(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }
              }

              if (pixy_old_x > 140 && pixy_old_x <= 170){
              while (pixy_x <= 140){
                rotateLeft(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              } while (pixy_x > 140 && pixy_x <= 170){
                fwd(255);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
                distanceSensorFront();
                if(cmF <= 1 || cmF > 20){
                fwd(180);
                }if (cmF > 1 && cmF <= 20) {
                stop();
                break;
                }
              } while (pixy_x > 170){
                rotateRight(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }
              }

              if (pixy_old_x > 170){
              while (pixy_x <= 140){
                rotateLeft(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              } while (pixy_x > 140 && pixy_x <= 170){
                fwd(255);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
                distanceSensorFront();
                if(cmF <= 1 || cmF > 20){
                fwd(180);
                }if (cmF > 1 && cmF <= 20) {
                stop();
                break;
                }
              } while (pixy_x > 170){
                rotateRight(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }
              }
          }
        }
    }
    }
  }   
}
void pixyBlockCheck(){
  for (int j = 0; j < pixy.ccc.numBlocks;j++){
    pixy_x_j = pixy.ccc.blocks[j].m_x;
    pixy_y_j = pixy.ccc.blocks[j].m_y;
    pixy_age_j = pixy.ccc.blocks[j].m_age;
    pixy_width_j = pixy.ccc.blocks[j].m_width;
    pixy_height_j = pixy.ccc.blocks[j].m_height;
    if ((((pixy_x_j - 15) >= pixy_x) || ((pixy_x_j + 15) <= pixy_x)) && (((pixy_y_j - 15) >= pixy_y) || ((pixy_y_j + 15) <= pixy_y))){
    pixy_x = pixy.ccc.blocks[j].m_x;
    pixy_y = pixy.ccc.blocks[j].m_y;
    pixy_age = pixy.ccc.blocks[j].m_age;
    pixy_width = pixy.ccc.blocks[j].m_width;
    pixy_height = pixy.ccc.blocks[j].m_height;
    }
  }
}
