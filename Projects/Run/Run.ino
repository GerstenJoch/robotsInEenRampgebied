#include <Pixy2.h>
#include <SPI.h>

//wheels robot
const int RB_Motor = 3;
const int RF_Motor = 4;
const int LB_Motor = 9; 
const int LF_Motor = 5; 
int speed1;
//ultrasonic sensor
#define trigPinF 12    // Trigger
#define echoPinF 13    // Echo
#define trigPinL 0
#define echoPinL 1        
int cmF,cmR,cmL;
#define echoPinR 11 
#define trigPinR 10 
long duration; 
int distance;
//pixycam
Pixy2 pixy;
int pixy_x, pixy_y,pixy_age,pixy_width,pixy_height, pixy_old_x;
int pixy_x_j, pixy_y_j,pixy_age_j,pixy_width_j,pixy_height_j;
int j;
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
  Serial.begin(9600);  
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
    while (true){
    digitalWrite(ledPin, HIGH);
    fwd(255);
    distanceCheck();
    objectDetection();
    startButtonState = digitalRead(startButton); 
    if (startButtonState == HIGH){
      Serial.println("Return false");
      delay(500);
      break;
    }
  }
  startButtonState = digitalRead(startButton);
  stopAll();
    digitalWrite(ledPin, LOW);
  Serial.println("Robot stopped");
}
}
//Driving functions these can be call in the logic and alorithms to be more efficient when coding
void rotateRight(int speed, int time){       //Rotates robot to the RIGHT given a time and speed                        
  analogWrite(LF_Motor, speed);
  analogWrite(RB_Motor, speed);
  analogWrite(RF_Motor, 0);
  analogWrite(LB_Motor, 0);
  Serial.println("Rotating RIGHT \n");
  delay(time); //Rotates for a give time in millisecond and the stops
  stop();
}
                                                                        
void rotateLeft(int speed, int time){       //Rotates robot to the LEFT given a time and speed
  analogWrite(LF_Motor, 0);
  analogWrite(RB_Motor, 0);
  analogWrite(RF_Motor, speed);
  analogWrite(LB_Motor, speed);
  Serial.println("Rotating LEFT \n");
  delay(time); //Rotates for a give time in millisecond and the stops
  stop();
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
  //analogWrite(trigPinF, LOW);
  //analogWrite(echoPinF, LOW);
  //analogWrite(trigPinL, LOW);
  //analogWrite(echoPinL, LOW);
  //analogWrite(trigPinR, LOW);
  //analogWrite(echoPinR, LOW);
  Serial.println("Stopped all \n");
}

void fwd(int speed){      //Goes forward infinitely given a speed
  //Serial.println(speed);
  analogWrite(LF_Motor, 255); //Has less power to correct the robot to go in a straight line
  analogWrite(RF_Motor, 180);
  analogWrite(LB_Motor, 0);
  analogWrite(RB_Motor, 0);
  //distanceCheck();
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
    // Clears the trigPin condition
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinF, HIGH);
  // Calculating the distance
  cmF = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Front: ");
  Serial.print(cmF);
  Serial.println(" cm");
}

void distanceSensorRight(){     //Gets distance value from right sensor
    // Clears the trigPin condition
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinR, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Right: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void distanceSensorLeft(){    //Gets distance value from left sensor
  // Clears the trigPin condition
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  cmF = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(cmF);
  Serial.println(" cm");
}

//These 2 functions are used for the logic to let the robot stop when it's nearing a wall and let it find it's way through

void distanceCheck() {
  distanceSensorRight();
  if (distance > 1 && distance <= 35) {  //If it's greater than 1 and smaller/equal than 20 it stops and checks left & right, else goes forward
  //greater than 1 is called because value can randomly change to 1
  Serial.println("Object encounterd: checking LEFT and RIGHT \n");
  stop();
  rotateRight(255,700);
  //distanceLeftRightCheck();
  }
}
void distanceLeftRightCheck(){
  distanceSensorRight();
  if (cmR > 20){   
    Serial.print("Check complete on RIGHT sensor, turning right \n");         //Checks right sensor if open, rotates right, else, checks left sensor
    rotateRight(255, 500);
    return;
  } else if (cmR <= 20) { 
    Serial.println("Check complete on RIGHT sensor, right side is not open to rotate \n");                           
    distanceSensorLeft();
    if (cmL > 20){    
      Serial.print("Check complete on LEFT sensor, turning right \n");        //Checks left sensor if open, rotates left, else, goes backwards
      rotateLeft(255, 500);
      return;
    } else if (cmL <= 20) {
        Serial.print("Not enough space on left and right, moving in reverse \n");
        while (cmL <= 20 && cmR <= 20){        //Drives backwards until left or right is open
          bwd(255);
          distanceSensorLeft();
          distanceSensorRight();
          if (cmL > 20){
            stop();
            rotateLeft(255, 500);
            Serial.print("Found enough space on left side, stopping on return and rotating left. \n");
            break;
          } if (cmR >20){
            stop();
            rotateLeft(255, 500);
            Serial.print("Found enough space on right side, stopping on return and rotating right. \n");
            break;
        }
     }
  }
  }
}
//Function for the pixy cam. The camera detection. It look if the detected object is left or right. Depending on that, 
//it rotates and drives the robot until it's right in front of it
//It goes to a filtering system to make sure when more that 1 object is detected,
//It detects the right one.
void objectDetection(){ 
  int i;
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks)     //Checks if there are objects
  {
    for (i=0; i<pixy.ccc.numBlocks; i++)         //Iterates through all detected objects
    {
      pixy_x = pixy.ccc.blocks[i].m_x;
      pixy_y = pixy.ccc.blocks[i].m_y;
      pixy_age = pixy.ccc.blocks[i].m_age;
      pixy_width = pixy.ccc.blocks[i].m_width;
      pixy_height = pixy.ccc.blocks[i].m_height;
      // ^ Gets x,y,age,width,height values from current object
      if (pixy_age > 30){
        if (!(pixy_y <=50 || pixy_y >= 250)){
          if ((!(pixy_width <= 10 || pixy_width >= 50)) || (!(pixy_height <= 10 || pixy_height >= 50))){
            //Checks if it's long enough in frame to not be a random object and checks if the y, width and heigt
            //are reasonable to get the important block only
            pixy_old_x = pixy_x;  //Backs original value up to not change the if statements to false if true visa versa
            if (pixy_old_x <= 140){
              while (pixy_x <= 140){
                //rotateLeft(255,500);
                Serial.println("Rotating Left");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              } // Rotates left and updates values and makes sure to get the correct object
              while (pixy_x > 140 && pixy_x <= 170){
                //fwd(255);
                Serial.println("Moving Forward");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
                distanceSensorFront();
                if (distance > 1 && distance <= 20) {
                stop();
                break;
                }// Drives forward and updates values and makes sure to get the correct object and stops if it's right in front of it
              } while (pixy_x > 170){
                //rotateRight(255,500);
                Serial.println("Rotating Right");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }// Rotates right and updates values and makes sure to get the correct object
              }
              if (pixy_old_x > 140 && pixy_old_x <= 170){
              while (pixy_x <= 140){
                Serial.println("Rotating Left");
                Serial.print("X = ");
                Serial.println(pixy_x);
                //rotateLeft(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }// Rotates left and updates values and makes sure to get the correct object 
              while (pixy_x > 140 && pixy_x <= 170){
                Serial.println("Moving Forward");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
                distanceSensorFront();
                if (cmF > 1 && cmF <= 20) {
                stop();
                break;
                }// Drives forward and updates values and makes sure to get the correct object and stops if it's right in front of it
              } while (pixy_x > 170){
                Serial.println("Rotating Right");
                Serial.print("X = ");
                Serial.println(pixy_x);
                //rotateRight(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }// Rotates right and updates values and makes sure to get the correct object
              }

              if (pixy_old_x > 170){
              while (pixy_x <= 140){
                Serial.println("Rotating Left");
                Serial.print("X = ");
                Serial.println(pixy_x);
                //rotateLeft(255,500);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }// Rotates left and updates values and makes sure to get the correct object 
              while (pixy_x > 140 && pixy_x <= 170){
                Serial.println("Moving Forward");
                Serial.print("X = ");
                Serial.println(pixy_x);
                //fwd(255);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
                distanceSensorFront();
                if (cmF > 1 && cmF <= 20) {
                stop();
                break;
                }// Drives forward and updates values and makes sure to get the correct object and stops if it's right in front of it
              } while (pixy_x > 170){
                //rotateRight(255,500);
                Serial.println("Rotating Right");
                Serial.print("X = ");
                Serial.println(pixy_x);
                pixy.ccc.getBlocks();
                pixyBlockCheck();
              }// Rotates right and updates values and makes sure to get the correct object
              }
              //All while loops in an if statements eventually loops through "while (pixy_x > 140 && pixy_x <= 170)"
              //To let is go forward and stops when it's right in front of it
          }
        }
    }
    }
  }   
}
void pixyBlockCheck(){    //Makes sure to update the right x-value, because the block number changes when updated so 
  //you can't use the same block index i, because that will change to another object's value
  for (int j = 0; j < pixy.ccc.numBlocks;j++){
    pixy_x_j = pixy.ccc.blocks[j].m_x;                   //Iterates through all values again
    pixy_y_j = pixy.ccc.blocks[j].m_y;
    pixy_age_j = pixy.ccc.blocks[j].m_age;
    pixy_width_j = pixy.ccc.blocks[j].m_width;
    pixy_height_j = pixy.ccc.blocks[j].m_height;
      if ((((pixy_x_j - 15) >= pixy_x) || ((pixy_x_j + 15) <= pixy_x)) && (((pixy_y_j - 15) >= pixy_y) || ((pixy_y_j + 15) <= pixy_y))){
        pixy_x = pixy.ccc.blocks[j].m_x;                   //If the block's values are roughly the same, the values will update
        pixy_y = pixy.ccc.blocks[j].m_y;                   //to the corresponding data
        pixy_age = pixy.ccc.blocks[j].m_age;
        pixy_width = pixy.ccc.blocks[j].m_width;
        pixy_height = pixy.ccc.blocks[j].m_height;
      }
  }
}
void objectDetectionTest(){ 
  int i; 
  // grab blocks!
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }
}
}
