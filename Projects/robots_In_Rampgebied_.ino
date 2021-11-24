/*
-----------------------------------------------------
               ROBOTS IN RAMPGEBIED
-----------------------------------------------------
  Authors: ...
  Year: ...
  Build Version: ...

 
 * IMPORTANT *   

  Serial Monitor:
    Will only be used for desplaying important status updates, for example:
     - Device is ON/OFF.
     - Request recieved.
    
    Please do not use the Serial Monitor for displaing live readings from sensor(s). 
*/

int fsrAnalogPin = 0;         //Analog pin for the pressure sensor. Use: power button
int pressureIsTrueLed = 11;   //Probably rename this LED, it shows if the device is turned on
int fsrReading;
int ledBrightness;
int isButtonPressed;

void setup() {
  Serial.begin(9600);
  pinMode(pressureIsTrueLed, OUTPUT);   //Set LED to output
  isButtonPressed = 0;    //Set button status to "0", aka false; the button has not been pressed before, or has been set to status "0"
}

void loop() {
  fsrReading = analogRead(fsrAnalogPin);
  
  if (isButtonPressed == 0 && fsrReading > 100) {
    isButtonPressed = 1;      //Set button status to "1", aka true, the button has been pressed before, and has been set to status "1"
    Serial.print(">>> ON ");  //Print ">>> ON " in serial, for status updates
    digitalWrite(pressureIsTrueLed, HIGH);  //Turn on LED
  }

  else if (isButtonPressed == 1 && fsrReading > 100) {
    isButtonPressed = 0;      //Set button status to "0", aka false, the button has been pressen before, but is not set to false so the button can be pressed again
    Serial.print(">>> OFF");  //Print ">>> OFF " in serial, for status updates
    digitalWrite(pressureIsTrueLed, LOW);   //Turn off LED
    //l;jvdShfiusadyhgfbngvjsaknegfvaseuyfgesivub fgw

  }
}