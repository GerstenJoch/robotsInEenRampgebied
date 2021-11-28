/*  Robot.h V1.1 for L298N motor driver boards
 *  By Jorrit van den Eerenbeemt, 19-2-2018  
 *  Private use 
 */

#ifndef Robot_h
#define Robot_h

#include "Arduino.h"

class Robot
{

  public: 
    Robot(int ENA, int ENB, int IN1, int IN2, int IN3, int IN4);
    void fwd(int speed);
    void bwd(int speed);
    void stp();
    void thr();
    void thl();
    void tsl(int speed);
    void tsr(int speed);
    
  private:
  int _ENA;
  int _ENB;
  int _IN1;
  int _IN2;
  int _IN3;
  int _IN4;
   
};

#endif

