#ifndef Robot_h
#define Robot_h
/*
Description of the robot :
--Contains two drivers for 2 stepper motors with 2 pins for each one the first for 
--right motor pins are p1:pinstepD,p2:pindirD
--Left motor pins are p3:pinstepG,p4:pindirG
--sleep (enable) pins are p5,p6 for right and left
*/

float ppr,l,r;
class Robot {

public:
Robot(int pinstepD,int pindirD,int pinstepG,int pindirG);
void avancer(double distance,double distTopulse,bool absolue);
void tourner(double angle,double distTopulse,bool absolue);
//void Robot::evitement(bool stop);
//int Robot::active_action(bool activate);
//void Robot::position(double x,double y,double angle,bool absolute);
char Robot::ultrason();


private:

float x,y,teta;
AccelStepper MGauche;//(AccelStepper::DRIVER,pinStepG, pinDirG,true);
AccelStepper MDroit;//(AccelStepper::DRIVER,pinStepD, pinDirD,true);
MultiStepper steppers;


};

#endif