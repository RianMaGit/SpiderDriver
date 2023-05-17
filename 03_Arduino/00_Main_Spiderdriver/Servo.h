#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "GlobaleVariablen.h"

#ifndef SERVO_H
#define SERVO_H

class MyServo{
private:
  byte pin;
  String seite;
  int16_t offset;
  int16_t PWM = SERVO90;
  int16_t PWMziel = SERVO90;
  bool isMooving = false;
  uint8_t numberOfServos = 16;
  bool laufen = false;
  Adafruit_PWMServoDriver driver;

public:
  MyServo(String seite="unbenannt", byte pin=0, Adafruit_PWMServoDriver driver=Adafruit_PWMServoDriver(0x40), int16_t offset=0){
    this->seite = seite;
    this->pin = pin;
    this->offset = offset;
    this->driver = driver;
  };
  ~MyServo(){};
  void setPWM(uint16_t PWM);
  void setLaufen(bool laufen);
  byte getPin();
  void PWM_refresh(uint8_t PWMschrittweite=1);
  void initialize(String seite, byte pin, Adafruit_PWMServoDriver driver, int16_t offset=0);
  void move(uint16_t PWMinput = 0);
};
#endif