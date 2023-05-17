#include "Bein.h"
#include "GlobaleVariablen.h"

String Bein::seite()
{
  String seitereturn;
  if(this->position==1||position==3||position==5){seitereturn="links";}
  if(this->position==2||position==4||position==6){seitereturn="rechts";}
  else{Serial.print("\r\nError: Die Seite von dem Bein: "); Serial.print(position); Serial.print(" konnte nicht bestimmt werden. Überprüfe die Eingabe");}
  return seitereturn;
}

byte Bein::pin(int addnumber)
{  
  byte pinreturn=0;
  if(this->position==1||this->position==2){pinreturn= 0;}
  else if(position==3||position==4){pinreturn= 4;}
  else if(position==5||position==6){pinreturn= 8;}
  else{Serial.print("\r\n[Error] Die Pins zum Bein: "); Serial.print(position); Serial.print(" konnte nicht zugewiesen werden");}
  return (pinreturn + addnumber);
}
void Bein::PWM_refresh(uint8_t PWMschrittweite)
{
  lenkservo.PWM_refresh(PWMschrittweite);
  hubservo.PWM_refresh(PWMschrittweite);
  stellservo.PWM_refresh(PWMschrittweite);
}

void Bein::setLaufen(bool laufen)
{
  this->laufen = laufen;
  lenkservo.setLaufen(laufen);
  hubservo.setLaufen(laufen);
  stellservo.setLaufen(laufen);
}

void Bein::set_cord(int cx, int cy, int cz)
{
  if(laufen){
    if((xmin<=cx<=xmax) && (ymin<=cy<=ymax) && (zmin<=cz<=zmax)){
      this->x = cx;
      this->y = cy;
      this->z = cz;
      const int offset_lenkservo = 0;
      const int offset_hubservo = 0;
      const int offset_stellservo = 0;
      
      //Berechnung Abstand Ursprung-Endpunkt waagerecht
      float Abstand_UEw = sqrt(sq(cx)+sq(cy));
      //Winkel Lenkservo
      float Winkel_lenk = atan((float)cx/cy)*(180/PI);
      
      //Berechnung Abstand Ursprung-Endpunkt senkrecht
      float Abstand_UEs = sqrt(sq(Abstand_UEw)+sq(cz));

      //Winkel Ursprung-Endpunkt senkrecht
      float Winkel_UEs = atan(cz/Abstand_UEw)*(180/PI);

      //Winkelberechnung

      float Winkel_Stellservo  = acos((sq(oberarm) +sq(unterarm) -sq(Abstand_UEs)) / (2 * unterarm * oberarm))*(180/PI);
      float Teilwinkel_Hubservo = acos((sq(Abstand_UEs) +sq(oberarm) -sq(unterarm)) / (2 * Abstand_UEs * oberarm))*(180/PI);      

      //Gesamtwinkel Hubservo
      float Winkel_Hubservo = Teilwinkel_Hubservo + Winkel_UEs;
      

      //Winkel in PWM
      int16_t PWM1 = map(Winkel_lenk, -90, 90, SERVO180, SERVO0);
      int16_t PWM2 = map(Winkel_Hubservo, -90, 90, SERVO180, SERVO0);
      int16_t PWM3 = map(Winkel_Stellservo, 0, 180, SERVO180, SERVO0);

      Serial.print(Winkel_Hubservo);
      

      Serial.print("\r\nLenkservo PWM: ");Serial.print(PWM1); Serial.print(" Cord: ");Serial.print(cx);
      Serial.print("\r\nHubservo PWM: ");Serial.print(PWM2); Serial.print(" Cord: ");Serial.print(cy);
      Serial.print("\r\nStellservo PWM: ");Serial.print(PWM3); Serial.print(" Cord: ");Serial.print(cz);
      Serial.print("\r\n");
      lenkservo.setPWM(PWM1);
      hubservo.setPWM(PWM2);
      stellservo.setPWM(PWM3);
    }
    else {Serial.print("\r\n[Error] Die Koordinaten fuer das Bein:  "); Serial.print(position); Serial.print(" konnte nicht bestimmt werden. Überprüfe die Eingabe. (Bein.cpp)");}
  }  
}
void Bein::setLaufschritt(uint8_t laufSchritt, int cord[6][3], int sub)
{
  laufSchritt-=1;
  if(laufen){
    Serial.print("\r\nCoordinaten: "); Serial.print(cord[laufSchritt][1]);
    set_cord(cord[laufSchritt][0], cord[laufSchritt][1], cord[laufSchritt][2]);
  }
}

void Bein::setStehen(uint16_t hub, uint16_t stell){
  lenkservo.setPWM(SERVO90);
  hubservo.setPWM(hub);
  stellservo.setPWM(stell);
}
void Bein::SerialCord()
{
  Serial.print("\r\n-- Koordinateneingabe --");
  Serial.print("\r\nx: ");
  while (Serial.available()==0) {  }
  int inx = Serial. parseInt();
  Serial.print(inx);
  Serial.print("\r\ny: ");
  while(!Serial.available()){}
  int iny = Serial. parseInt();
  Serial.print(iny);
  Serial.print("\r\nz: ");
  while(!Serial.available()){}
  int inz = Serial. parseInt();
  Serial.print(inz);
  set_cord(inx, iny, inz);
}