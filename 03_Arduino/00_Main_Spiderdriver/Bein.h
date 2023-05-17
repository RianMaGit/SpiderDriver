#include "Servo.h"

class Bein{
private:
  uint8_t position=0;            //vl:vorne-links, hr:hinten-rechts, ml:mitte-links ...
  int cord_pos[3];     //x,y,z
  bool isMooving = false;     //gerade in Bewegung?
  String seite();
  byte pin(int addnumber);
  void set_cord();


  const float unterarm = 16.0;
  const float oberarm = 14.54;

  int8_t x = 0;
  int8_t y = 15;
  int8_t z = -15;

  bool laufen = false;
  
public:
  MyServo lenkservo; 
  MyServo hubservo; 
  MyServo stellservo;



  Bein(){
    // this->position;
    // lenkservo.initialize("links", pin(0));
    // hubservo.initialize("links", pin(1));
    // stellservo.initialize("links", pin(2));
  }

  void initialize(int position, Adafruit_PWMServoDriver driver, uint8_t offset_lenkservo=0, uint8_t offset_hubservo=0, uint8_t offset_stellservo=0){
    this-> position = position;
    MyServo ProvLenkservo(seite(), pin(0), driver, offset_lenkservo);
    Serial.print("\r\nLenkservo: "); Serial.print(ProvLenkservo.getPin()); Serial.print(" "); Serial.print(position);  
    MyServo ProvHubservo(seite(), pin(1), driver,offset_hubservo);
    MyServo ProvStellservo(seite(), pin(2), driver, offset_stellservo);
    this->lenkservo=ProvLenkservo;
    this->hubservo=ProvHubservo;
    this->stellservo=ProvStellservo;
    // lenkservo.initialize(seite(), pin(0), driver);
    // hubservo.initialize(seite(), pin(1), driver);
    // stellservo.initialize(seite(), pin(2), driver);
  }
  void PWM_refresh(uint8_t PWMschrittweite=1);
   void send_cord(int8_t x, int8_t y, int8_t z){
    if((xmin<=x<=xmax) && (ymin<=y<=ymax) && (zmin<=z<=zmax)){
      this->x = x;
      this->y = y;
      this->z = z;
      }
    else {Serial.print("\r\nDie Koordinaten: "); Serial.print(position); Serial.print(" konnte nicht bestimmt werden. Überprüfe die Eingabe");}
  }
  
  ~Bein(){};
  void setLaufen(bool laufen);
  void set90(){
    lenkservo.setPWM(SERVO90);
    hubservo.setPWM(SERVO90);
    stellservo.setPWM(SERVO90);
  };
  void set_cord(int cx, int cy, int cz);
  void setLaufschritt(uint8_t laufSchritt, int cord[6][3], int sub);
  void setStehen(uint16_t hub, uint16_t stell);
  void SerialCord();
};