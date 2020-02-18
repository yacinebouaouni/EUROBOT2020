
#include<AccelStepper.h>
#include<MultiStepper.h>

const float test=21.22;

const byte TRIGGER_PIN = 3; // Broche TRIGGER
const byte ECHO_PIN = 2;    // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

const int ppr=400;
const float r=2.7;
const float l=9.3;//rayon de la base
const float coeff=23.5785;
const float rayobot=11.0;

const int pinStepG =6;
const int pinDirG = 5;

const int pinStepD =9;
const int pinDirD=8;

const int sleep1=2;
const int sleep2=3;

const int echo=2;
const int trig=3;
const int VitesseMaxGauche=600;
const int AccelMaxGauche=1000;
const int VitesseMaxDroite=600;
const int AccelMaxDroite=1000;

AccelStepper MGauche(AccelStepper::DRIVER,pinStepG, pinDirG,true);
AccelStepper MDroit(AccelStepper::DRIVER,pinStepD, pinDirD,true);
MultiStepper steppers;


void tourner(long angle){
  long dir[2];
  float pulse=(ppr/360)*(l*angle/r);
  dir[0]=pulse;
  dir[1]=-pulse;
  steppers.moveTo(dir);//Set the target positions of all managed steppers according to a coordinate array.
  steppers.runSpeedToPosition();
 
  
 MDroit.setCurrentPosition(dir[0]);
 MGauche.setCurrentPosition(dir[1]);
  
}












void avancer (long dist){

long distogo;
distogo=test*dist;





MDroit.moveTo(distogo);
MGauche.moveTo(distogo);
runner :
//while(MDroit.distanceToGo()&& MGauche.distanceToGo()){
  while(MDroit.run()&& MGauche.run()){

Serial.println(MDroit.currentPosition()/test);
if (ultrason()=='1'){break;}
}

red:
if(ultrason()=='1'){goto red;}
//delay(5000);
if(MDroit.run()&& MGauche.run()){
goto runner;
}
//Serial.println(MDroit.currentPosition()/test);


}


void setup(){

  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  
  
  Serial.begin(9600);
  steppers.addStepper(MDroit);
  steppers.addStepper(MGauche);
  MGauche.setMaxSpeed(VitesseMaxGauche);
  MGauche.setAcceleration(AccelMaxGauche);
  MDroit.setSpeed(400.0);
  MGauche.setSpeed(400.0);
  MDroit.setMaxSpeed(VitesseMaxDroite);
  MDroit.setAcceleration(AccelMaxDroite);
    
   avancer(100.0);
   delay(5000);
   avancer(200.0);
   Serial.println(MDroit.currentPosition());
   Serial.println(MGauche.currentPosition());
   
   
   


}

void loop(){
  /*while(Serial.available()){
    char data=Serial.read();
   // Serial.println(data);
    avancer(100.0);
  }
*/


//Serial.println(MGauche.currentPosition());


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
  
  
  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
  //delay(100);
