#include "Bein.h"

class Robo{
private:
  int servospeed=1;
  
  int x_unten = 3;
  int x_oben_offset = 1;
  int x_mitte_offset = 3;

  int y = 7;

  int z_unten = -17;
  int z_oben_offset = 7;

  /*int walkcordA[6][3] ={
    {  0, 7,-17},
    { -3, 7,-17},
    { -3, 7,-17},
    { -2, 7, -10},
    {  2, 7, -10}, 
    {  3, 7,-17}};
  */
  //immer 6 Beine auf dem oden//////////////////////////
  //////////////////////////////////////////////////////
  /*
  int x = 0;
  int y = 7;
  int z = -17;
  int frontb = 3;
  int high = 7;
  int walkcordAinv[6][3] ={
    {  x,        y, z},
    {  x+frontb, y, z},
    {  x,        y, z+high},
    {  x-frontb, y, z},
    {  x,        y, z}};
    //, 
    //{  x,        y, z}};

  int walkcordA[6][3] ={
    {  x,        y, z},
    {  x-frontb, y, z},
    {  x,        y, z+high},
    {  x-frontb, y, z},
    {  x,        y, z}};
    //,
    //{  x,        y, z}};
    */
  ///////Tripod Laufstiel/////////////////////////////////
  ////////////////////////////////////////////////////////
  
  int walkcordA[6][3] ={
    {x_unten-x_mitte_offset,   y, z_unten},
    {-x_unten,                 y, z_unten},
    {-x_unten,                 y, z_unten},
    {-x_unten+x_oben_offset,   y, z_unten+z_oben_offset},
    {x_unten-x_oben_offset,    y, z_unten+z_oben_offset},
    {x_unten,                  y, z_unten}};
  
  int walkcordAinv[6][3] ={
    {x_unten-x_mitte_offset,   y, z_unten},
    {x_unten,                  y, z_unten},
    {x_unten,                  y, z_unten},
    {x_unten-x_oben_offset,    y, z_unten+z_oben_offset},
    {-x_unten+x_oben_offset,   y, z_unten+z_oben_offset},
    {-x_unten,                 y, z_unten}};
  ////////////////////////////////////////////////////////

//---------------------------
public: 
  unsigned long int step;
  bool laufen=false;
  int LaufSchritt = 1;
  int LaufSchrittB = 4;
  int LaufSchrittInv = 1;
  int LaufSchrittBInv = 4;
  Bein vl; Bein vr; Bein ml; Bein mr; Bein hl; Bein hr;
  MyServo escl; MyServo escr;
  Robo(Adafruit_PWMServoDriver driver_l, Adafruit_PWMServoDriver driver_r){
    vl.initialize(1, driver_l, 0,5,0);
    vr.initialize(2, driver_r, 0,12,0);
    ml.initialize(3, driver_l, 25,2,0);
    mr.initialize(4, driver_r, 0,10,0);
    hl.initialize(5, driver_l, 0,27,0);
    hr.initialize(6, driver_r, 0,18,0);
    escl.initialize("links",   12, driver_l);
    escr.initialize("rechts",  12, driver_r);
  }
  ~Robo(){};
  void PWM_refresh(uint8_t PWMschrittweite=1);
  void setLaufen(bool laufen);
  void setLenkung(uint8_t ControllerTrigger);
  void setPosition(uint16_t hub, uint16_t stell);

  void walk(uint8_t ControllerTrigger);
  void addLaufSchritt(){
    LaufSchritt -=1;
    LaufSchrittB -=1;
  }
};