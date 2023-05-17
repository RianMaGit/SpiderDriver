#include "Robo.h"
#include "GlobaleVariablen.h"

uint16_t PWMlenkungMIN = map(lenkungMIN, 0, 180, SERVO0, SERVO180);
uint16_t PWMlenkungMAX = map(lenkungMAX, 0, 180, SERVO0, SERVO180);

void Robo::PWM_refresh(uint8_t PWMschrittweite)
{
  step++;
  vl.PWM_refresh(PWMschrittweite);
  vr.PWM_refresh(PWMschrittweite);
  ml.PWM_refresh(PWMschrittweite);
  mr.PWM_refresh(PWMschrittweite);
  hl.PWM_refresh(PWMschrittweite);
  hr.PWM_refresh(PWMschrittweite);
}
void Robo::setLaufen(bool laufen){
  this->laufen = laufen;
  vl.setLaufen(laufen);
  vr.setLaufen(laufen);
  ml.setLaufen(laufen);
  mr.setLaufen(laufen);
  hl.setLaufen(laufen);
  hr.setLaufen(laufen);
}

void Robo::setLenkung(uint8_t ControllerTrigger){
  if(!laufen){
    int16_t PWMlenkung = map(ControllerTrigger, 0, 255, PWMlenkungMIN, PWMlenkungMAX);
    int16_t PWMlenkungInvert = map(ControllerTrigger, 0, 255, PWMlenkungMAX, PWMlenkungMIN);
    vl.lenkservo.setPWM(PWMlenkungInvert);
    vr.lenkservo.setPWM(PWMlenkungInvert);
    hl.lenkservo.setPWM(PWMlenkung);
    hr.lenkservo.setPWM(PWMlenkung);
  }
}

void Robo::walk(uint8_t ControllerTrigger){
  if(laufen){
    Serial.print("\r\nSteps: "); Serial.print(step);
    if(step%20==0){
      
      if(LaufSchritt==0){LaufSchritt=6;}
      if(LaufSchrittB==0){LaufSchrittB=6;}
      Serial.print("\r\nLaufschritt: "); Serial.print(LaufSchritt);
      // if(LaufSchritt==1||2||3){LaufSchrittB=LaufSchritt+3;}
      // if(LaufSchritt==4||5||6){LaufSchrittB=LaufSchritt-3;}

      vl.setLaufschritt(LaufSchritt, walkcordA, 1);
      vr.setLaufschritt(LaufSchrittB, walkcordAinv, 1);
      ml.setLaufschritt(LaufSchrittB, walkcordA, 1);
      mr.setLaufschritt(LaufSchritt, walkcordAinv, 1);
      hl.setLaufschritt(LaufSchritt, walkcordA, 1);
      hr.setLaufschritt(LaufSchrittB, walkcordAinv, 1);
      LaufSchritt-=1;
      LaufSchrittB-=1;
      
    }
  }
}

void Robo::setPosition(uint16_t hub, uint16_t stell){
  if(!laufen){
    vl.setStehen(hub, stell);
    vr.setStehen(hub, stell);
    ml.setStehen(hub, stell);
    mr.setStehen(hub, stell);
    hl.setStehen(hub, stell);
    hr.setStehen(hub, stell);
  }
}