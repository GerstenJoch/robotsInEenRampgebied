//*************************************************************************//
//                                                                         //
//                        ROBOTS IN EEN RAMPGEBIED                         //
//                                                                         //
//                              Code Written By:                           //
//                                                                         //
//                            - Alexander Mosselaar                        //
//                            - Guido Ruijs                                //
//                            - Sander Reinders                            //
//                                                                         //
//*************************************************************************//
#include <Pixy2.h>
#include <SPI.h>

//wheels robot
const int RB_Motor = 3;
const int RF_Motor = 4;
const int LB_Motor = 9; 
const int LF_Motor = 5; 
int speed1;
//ultrasonic sensor
#define trigPinF 11    // Trigger
#define echoPinF 10    // Echo
#define trigPinL 0
#define echoPinL 1   
#define echoPinR 12 
#define trigPinR 13 
long duration; 
int distance, distanceL, distanceR;
//pixycam
Pixy2 pixy;
int pixy_x, pixy_y,pixy_age,pixy_width,pixy_height, pixy_old_x;
int pixy_x_j, pixy_y_j,pixy_age_j,pixy_width_j,pixy_height_j;
int j;
int x = 0;
//Button & Buzzer
const int startButton = 2;
int startButtonState;
const int ledPin = 6;
const int stopButtonPin = 7;
int stopButtonState;

void setup() {                        //Let's all the components initiate
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(RF_Motor, OUTPUT);
  pinMode(LF_Motor, OUTPUT);
  pinMode(RB_Motor, OUTPUT);
  //pinMode(trigPinF, OUTPUT);
  //pinMode(echoPinF, INPUT);
  pinMode(startButton, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(stopButtonPin, INPUT);                  //Initiates camera
  digitalWrite(ledPin, LOW);  
  Serial.begin(115200);  
  pixy.init();
  pinMode(trigPinR, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinR, INPUT); // Sets the echoPin as an INPUT
}

void loop() {                     //Loops through all the code
  justWork();
}

void justWork(){    //Runs all the necessary code to work. Can be in the loop function, but is created as a joke
  startButtonState = digitalRead(startButton);                         //Checks the state of the start and stop buttons
  stopButtonState = digitalRead(stopButtonPin);
  if (startButtonState == HIGH) {                                      //Robot starts when startbutton is pressed
    Serial.print("Protocol initiated \n");
    delay(200);
    while (true){                                                     //Loops through all the code for the robot to drive and function
    digitalWrite(ledPin, HIGH);
    fwd(255);
    //distanceCheck();
    objectDetection();
    x = 0;
    startButtonState = digitalRead(startButton); 
    if (startButtonState == HIGH){                                  //Robot stops when button is pressed again
      Serial.println("Return false");
      delay(200);
      break;
    }
  }
  startButtonState = digitalRead(startButton);
  stopAll();
    digitalWrite(ledPin, LOW);
  Serial.println("Robot stopped");
  delay(500);
}
}
//Driving functions these can be call in the logic and alorithms to be more efficient when coding
void rotateRight(int speed){       //Rotates robot to the RIGHT given a time and speed                        
  analogWrite(LF_Motor, speed);
  analogWrite(RB_Motor, speed);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, 0);
  Serial.println("Rotating RIGHT \n");
}
                                                                        
void rotateLeft(int speed){       //Rotates robot to the LEFT given a time and speed
  analogWrite(LF_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(RF_Motor, speed);
  analogWrite(LB_Motor, speed);
  Serial.println("Rotating LEFT \n");
}

void stop() {                //Sets all the driving motors to 0 power
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(LF_Motor, 0);
  analogWrite(RF_Motor, 0);
  Serial.println("Stopped \n");
}

void stopAll(){             //Sets everything to 0 power
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
  Serial.println("Stopped all \n");
}

void fwd(int speed){      //Goes forward infinitely given a speed
  analogWrite(LF_Motor, speed); //Has less power to correct the robot to go in a straight line
  analogWrite(RF_Motor, speed);
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  Serial.println("Driving FORWARD ");
}

void bwd(int speed1){    //Goes backwards infinitely given a speed
  analogWrite(LF_Motor, 0);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, speed1);
  analogWrite(RB_Motor, speed1);
  Serial.println("Driving BACKWARDS \n");
}

//Functions for the ultrasonic distance sensor to call them later. This makes coding easier
void distanceSensorFront(){       //Gets distance value from front sensor
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
  duration = pulseIn(echoPinF, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Front: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void distanceSensorRight(){     //Gets distance value from right sensor 
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  duration = pulseIn(echoPinR, HIGH);
  distanceR = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Right: ");
  Serial.print(distanceR);
  Serial.println(" cm");
}

void distanceSensorLeft(){    //Gets distance value from left sensor
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  duration = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  distanceL = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Right: ");
  Serial.print(distanceL);
  Serial.println(" cm");
}

//These 2 functions are used for the logic to let the robot stop when it's nearing a wall and let it find it's way through

void distanceCheck() {
  distanceSensorFront();
  if (distance > 1 && distance <= 35) {  //If it's greater than 1 and smaller/equal than 20 it stops and checks left & right, else goes forward
  //greater than 1 is called because value can randomly change to 1
  Serial.println("Object encounterd: checking LEFT and RIGHT \n");
  stop();
  rotateRight(255);               //Rotates 90 degrees
  delay(600);
  stop();
  //distanceLeftRightCheck();     Should be called, but the prototype can't handle 3 distance sensors
  }
}
void distanceLeftRightCheck(){
  distanceSensorRight();
  if (cmR > 20){   
    Serial.print("Check complete on RIGHT sensor, turning right \n");         //Checks right sensor if open, rotates right, else, checks left sensor
    rotateRight(255);
    return;
  } else if (cmR <= 20) { 
    Serial.println("Check complete on RIGHT sensor, right side is not open to rotate \n");                           
    distanceSensorLeft();
    if (cmL > 20){    
      Serial.print("Check complete on LEFT sensor, turning right \n");        //Checks left sensor if open, rotates left, else, goes backwards
      rotateLeft(255);
      return;
    } else if (cmL <= 20) {
        Serial.print("Not enough space on left and right, moving in reverse \n");
        while (cmL <= 20 && cmR <= 20){        //Drives backwards until left or right is open
          bwd(255);
          distanceSensorLeft();
          distanceSensorRight();
          if (cmL > 20){
            stop();
            rotateLeft(255);
            Serial.print("Found enough space on left side, stopping on return and rotating left. \n");
            break;
          } if (cmR >20){
            stop();
            rotateLeft(255);
            Serial.print("Found enough space on right side, stopping on return and rotating right. \n");
            break;
        }
     }
  }
  }
}
//Function for the pixy cam. The camera detection. It look if the detected object is left or right. Depending on that, 
//it rotates and drives the robot until it's right in front of it
void objectDetection(){ 
  int i;
  pixy.ccc.getBlocks();
  Serial.println("Help");
  if (pixy.ccc.numBlocks && (x == 0 || x == 2))     //Checks if there are objects
  Serial.println("NogMeerHelp");
  {
    x = 0;
    for (i=0; i<pixy.ccc.numBlocks; i++)         //Iterates through all detected objects
    {
      pixy_x = pixy.ccc.blocks[i].m_x;
      pixy_y = pixy.ccc.blocks[i].m_y;
      pixy_age = pixy.ccc.blocks[i].m_age;
      pixy_width = pixy.ccc.blocks[i].m_width;
      pixy_height = pixy.ccc.blocks[i].m_height;
      // ^ Gets x,y,age,width,height values from current object
      if (pixy_age > 30){           
        Serial.println("Age 30+");        //Checks if it's long enough in frame to not be a random object and checks if the y, width and heigt
        pixy.ccc.blocks[i].print();
        if (!(pixy_y <=50 || pixy_y >= 200)){
          Serial.println("Good enough y");        //Checks if the y levels are not unreasonable high
          if ((!(pixy_width <= 10 || pixy_width >= 200)) || (!(pixy_height <= 10 || pixy_height >= 200))){ //Checks if the width and height are not unreasonable high
            Serial.println("Good enough width, height");
            pixy_old_x = pixy_x;  //Backs original value up to not change the if statements to false if true visa versa
            if (pixy_old_x <= 140 || x == 0){
              while (pixy_x <= 120 && x == 0){
                rotateLeft(180);
                Serial.println("Rotating Left L");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixy_x = pixy.ccc.blocks[i].m_x;
                if (!pixy.ccc.numBlocks){
                  pixy.ccc.blocks[i].print();
                  stop();
                  x =2;
                  break;
                }
              } // Rotates left and updates valuest
              while (pixy_x > 120 && pixy_x <= 180 && x == 0){
                stop();                                        //Stops when object is in the middle, then it flickers the
                delay(200);                                    //LED 3 times to let you know and rotates 90 degrees so 
                digitalWrite(ledPin, LOW);                     //the object can't be seen by the camera and then goes
                delay(400);                                    //back to it's original routine
                digitalWrite(ledPin, HIGH);
                delay(400);
                digitalWrite(ledPin, LOW);
                delay(400);
                digitalWrite(ledPin, HIGH);
                delay(400);
                digitalWrite(ledPin, LOW);
                delay(400);
                digitalWrite(ledPin, HIGH);
                delay(500);
                rotateRight(255);
                delay(600);
                x = 2;
                break;
              } while (pixy_x > 180 && x == 0){
                rotateRight(180);
                Serial.println("Rotating Right L");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixy_x = pixy.ccc.blocks[i].m_x;
                if (!pixy.ccc.numBlocks){
                  pixy.ccc.blocks[i].print();
                  stop();
                  x =2;
                  break;
                }
              }// Rotates right and updates values
              }
              if (pixy_old_x > 120 && pixy_old_x <= 180 || x == 0){
              while (pixy_x <= 120 && x == 0){
                Serial.println("Rotating Left M");
                Serial.print("X = ");
                Serial.println(pixy_x);
                rotateLeft(180);
                pixy.ccc.getBlocks();
                pixy_x = pixy.ccc.blocks[i].m_x;
                if (!pixy.ccc.numBlocks){
                  pixy.ccc.blocks[i].print();
                  stop();
                  x =2;
                  break;
                }
              }// Rotates left and updates values and stop when it's right in front of it
              while (pixy_x > 120 && pixy_x <= 180 && x == 0){
                stop();                                       //Stops when object is in the middle, then it flickers the                            
                delay(200);                                   //LED 3 times to let you know and rotates 90 degrees so 
                digitalWrite(ledPin, LOW);                    //the object can't be seen by the camera and then goes                
                delay(400);                                   //back to it's original routine
                digitalWrite(ledPin, HIGH);         
                delay(400);
                digitalWrite(ledPin, LOW);
                delay(400);
                digitalWrite(ledPin, HIGH);
                delay(400);
                digitalWrite(ledPin, LOW);
                delay(400);
                digitalWrite(ledPin, HIGH);
                delay(500);
                rotateRight(255);
                delay(600);
                x = 2;
                break;
                }// Drives forward and updates values 
              } while (pixy_x > 180 && x == 0){
                Serial.println("Rotating Right M");
                Serial.print("X = ");
                Serial.println(pixy_x);
                
                rotateRight(180);
                pixy.ccc.getBlocks();
                pixy_x = pixy.ccc.blocks[i].m_x;
                if (!pixy.ccc.numBlocks){
                  pixy.ccc.blocks[i].print();
                  stop();
                  x =2;
                  break;
                }
              }// Rotates right and updates values
              }

              if (pixy_old_x > 180 || x == 0){
              while (pixy_x <= 120 && x == 0){
                Serial.println("Rotating Left R");
                Serial.print("X = ");
                Serial.println(pixy_x);
                rotateLeft(180);
                pixy.ccc.getBlocks();
                pixy_x = pixy.ccc.blocks[i].m_x;
                if (!pixy.ccc.numBlocks){
                  pixy.ccc.blocks[i].print();
                  stop();
                  x =2;
                  break;
                }
              }// Rotates left and updates values
              while (pixy_x > 120 && pixy_x <= 180 && x == 0){
                stop();                                            
                delay(200);                               //Stops when object is in the middle, then it flickers the
                digitalWrite(ledPin, LOW);                //LED 3 times to let you know and rotates 90 degrees so 
                delay(400);                               //the object can't be seen by the camera and then goes
                digitalWrite(ledPin, HIGH);               //back to it's original routine   
                delay(400);
                digitalWrite(ledPin, LOW);
                delay(400);
                digitalWrite(ledPin, HIGH);
                delay(400);
                digitalWrite(ledPin, LOW);
                delay(400);
                digitalWrite(ledPin, HIGH);
                delay(500);
                rotateRight(255);
                delay(600);
                x = 2;
                break;
                }// Drives forward and updates values and stops if it's right in front of it
              } while (pixy_x > 180 && x == 0){
                rotateRight(180);
                Serial.println("Rotating Right R");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixy_x = pixy.ccc.blocks[i].m_x;
                if (!pixy.ccc.numBlocks){
                  pixy.ccc.blocks[i].print();
                  stop();
                  x =2;
                  break;
                }
              }// Rotates right and updates values
              }
              //All while loops in an if statements eventually loop through "while (pixy_x > 120 && pixy_x <= 180)"
              //To let is go forward and stops when it's right in front of it
          }
        }
  }
}