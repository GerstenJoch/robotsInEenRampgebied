#include "Robot.h"
//Robot V1.1 by Jorrit van den Eerenbeemt for L298N motor driver boards
//
//In de eerste regel word de standaart snelheid bepaald op dit moment 130 dit kan een getal tussen de 130-255 zijn. 
//Robot.fwd(speed); zorgt ervoor dat je vooruit gaat met de standaart snelheid.
//Robot.bwd(255); zorgt ervoor dat je achteruit gaat met de maximale snelheid doordat het word speed is vervangen door 255. 
//                Dus bij 1 malige gebruik van een andere snelheid speed vervangen door gewenste snelhied
//Robot.stp(); zorgt ervoor dat de robot stopt.
//Robot.thr(); zorgt ervoor dat de robot een "harde" rechtse bocht maakt.
//Robot.thl(); zorgt ervoor dat de robot een "harde" linkse bocht maakt.
//Robot.tsr(speed); zorgt ervoor dat de robot een flauwe bocht maakt.
//Robot.tsl(speed); zorgt ervoor dat de robot en flauwe bocht maakt.
//Mocht de robot verkeerd gaan verwissel dan hier onder "Robot Robot(8, 9, 5, 3, 4, 2);" met "Robot Robot(ENA, IN1, IN2, IN3, IN4, ENB);".
//Zie motor boord voor pin nummers.
//
//verdere verzoeken voor functies even doorgeven. jorrit@vdeerenbeemt.nl
//


int speed = 200; //130-235

//Robot(ENA, IN1, IN2, IN3, IN4, ENB)   Op 
Robot Robot(8, 9, 5, 3, 4, 2);

void setup()
{
  Serial.begin(9600);

  
}
void loop()
{
  Robot.fwd(speed);
  delay(2000);
  Robot.stp();
  delay(100);
  Robot.thr();
  delay(500);
  Robot.bwd(255);
  delay(1000);
  Robot.stp();
  delay(100);
  Robot.thl();
  delay(500);
}


