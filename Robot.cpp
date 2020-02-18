#include<iostream>
#include<arduino.h>
#include"Robot.h"
#include"define.h"
#include"AccelStepper/AccelStepper.h"
#include"AccelStepper/MultiStepper.h"



//Constructor of the class Robot it initializes the two objects of type Accelstepper with their correspondant pins
Robot::Robot(int pinstepD,int pindirD,int pinstepG,int pindirG):MDroit(AccelStepper::DRIVER,pinstepD,pindirD),MGauche(AccelStepper::DRIVER,pinstepG,pindirG)
{
  steppers.addStepper(MDroit);
  steppers.addStepper(MGauche);
  this->x=0.0;
  this->y=0.0;
  this->teta=0.0;
}

void Robot::avancer(double distance,double distTopulse,bool absolue){
  long dir[2]; 
  
  dir[0]=distTopulse*distance;
  dir[1]=distTopulse*distance;
  steppers.moveTo(dir);//Set the target positions of all managed steppers according to a coordinate array.
  steppers.runSpeedToPosition();

  //Upgrade the postion x,y,teta
  this->x=this->x+distance*cos(this->teta);
  this->y=this->y+distance*sin(this->teta);
  
  
    if(absolue==false){ // In case of relative 
      
      MDroit.setCurrentPosition(distance);
      MGauche.setCurrentPosition(distance);
    }
}

void Robot::tourner(double angle,double distTopulse,bool absolue){


  long dir[2];
  float pulse=(ppr/360)*(l*angle/r);
  dir[0]=pulse;
  dir[1]=-pulse;
  steppers.moveTo(dir);//Set the target positions of all managed steppers according to a coordinate array.
  steppers.runSpeedToPosition();

      //Update the angle 
      this->teta=this->teta+angle;

      //In case of relative distance
      if(absolue==false){
     MDroit.setCurrentPosition(dir[0]);
     MGauche.setCurrentPosition(dir[1]);
      }
      
}
  
char ultrason() {

  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  float dist=distance_mm / 10.0;
  /* Affiche les résultats en mm, cm et m */
  if (dist<=20){
  return'1';
  }else{
    return'0';
    }
}
