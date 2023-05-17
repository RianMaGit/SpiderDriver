#include "Servo.h"
#include "GlobaleVariablen.h"

void MyServo::move(uint16_t PWMinput)
{
  if(PWMinput==0){PWMinput = PWM;}
  driver.setPWM(pin, 0, PWMinput + offset); 
  Serial.print("\r\nBewege: "); Serial.print(seite); Serial.print( " mit Pin: "); Serial.print(pin); Serial.print( " mit PWM: "); Serial.print(PWM);
}

byte MyServo::getPin(){return this->pin;}

void MyServo::setPWM(uint16_t PWM)
{
  if(SERVO0<=PWM<=SERVO180)
  {PWMziel = PWM;}
  else{Serial.print("\r\n[Error] Der übergebene PWM-Wert liegt nicht im erlaubten bereich. (Servo.cpp 22)");}
}

void MyServo::setLaufen(bool laufen)
{
  this->laufen = laufen;
}

void MyServo::PWM_refresh(uint8_t PWMschrittweite)
{
  if(PWM==PWMziel){this->isMooving=false;}
  else if(abs(PWM-PWMziel) < PWMschrittweite) {PWM = PWMziel;}
  else if(PWM < PWMziel){isMooving=true; PWM=PWM+PWMschrittweite; move();}
  else if(PWM > PWMziel){isMooving=true; PWM=PWM-PWMschrittweite; move();}
}

void MyServo::initialize(String seite, byte pin, Adafruit_PWMServoDriver driver, int16_t offset)
{
  this->seite = seite;
  this->pin = pin;
  this->offset = offset;
  this->driver = driver;
}
