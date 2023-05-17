#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver servo_l = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver servo_r = Adafruit_PWMServoDriver(0x41);
#define SERVOMIN  150
#define SERVOMAX  600
uint8_t servonum = 0;
uint8_t numberOfServos = 16;


// Standard Winkel (0-255)
const uint8_t std_agl = 127; //127 = 90 grad

//Winkel definieren (0-180 Grad)
const uint8_t LENKUNG_MIN = 45;  //MIN Winkel der Beine beim Lenken
const uint8_t LENKUNG_MAX = 135; //MAX Winkel der Beine beim Lenken
//Fahrgeschwindigkeit definieren (0-100%)
const uint8_t SPEED_FORW_MAX = 100; //Vorwärts
const uint8_t SPEED_BACK_MAX = 20;  //Rückwärts

//Trigger definition (0 - 255)
uint8_t trigger_lx = std_agl; //Linker Trigger X-Achse
uint8_t trigger_ly = std_agl; //Linker Trigger Y-Achse
uint8_t trigger_rx = std_agl; //Rechter Trigger X-Achse
uint8_t trigger_ry = std_agl; //Rechter Trigger Y-Achse
uint8_t trigger_lt, trigger_rt; // Linker/Rechter Trigger LT/RT (=0)

//uint16_t pulselen_lx, pulselen_ly, pulselen_rx, pulselen_ry, pulselen_lt, pulselen_rt;
uint16_t pwm_lenk_min, pwm_lenk_max;

const uint16_t pwm_speed_mid = 375; //PWM für stehende BL-Motoren

uint16_t pwm_speed_forw_max = pwm_speed_mid;
uint16_t pwm_speed_back_max = pwm_speed_mid;


//Servos vorne 
const uint8_t sv1 = 0; //Lenkservo
const uint8_t of_sv1 = 0;

const uint8_t sv2 = 1; //Hubservo
const uint8_t of_sv2 = 0;

const uint8_t sv3 = 2; //Stellservo
const uint8_t of_sv3 = 0;

//Servos mitte
const uint8_t sm1 = 4;
const uint8_t of_sm1 = 0;

const uint8_t sm2 = 5;
const uint8_t of_sm2 = 0;

const uint8_t sm3 = 6;
const uint8_t of_sm3 = 0;


//Servos hinten
const uint8_t sh1 = 8;
const uint8_t of_sh1 = 0;

const uint8_t sh2 = 9;
const uint8_t of_sh2 = 0;

const uint8_t sh3 = 10;
const uint8_t of_sh3 = 0;

//BLMotor Regler
const uint8_t esc = 12;


//Funktion für Servo sv1
void servo_sv1(String Seite ,uint16_t PWM_input);
//Funktion für Servo sv2
void servo_sv2(String Seite ,uint16_t PWM_input);
//Funktion für Servo sv3
void servo_sv2(String Seite ,uint16_t PWM_input);


//Funktion für Servo sm1
void servo_sm1(String Seite ,uint16_t PWM_input);
//Funktion für Servo sm2
void servo_sm2(String Seite ,uint16_t PWM_input);
//Funktion für Servo sm3
void servo_sm3(String Seite ,uint16_t PWM_input);


//Funktion für Servo sh1
void servo_sh1(String Seite ,uint16_t PWM_input);
//Funktion für Servo sh2
void servo_sh2(String Seite ,uint16_t PWM_input);
//Funktion für Servo sh3
void servo_sh3(String Seite ,uint16_t PWM_input);


//Funktion für Servo sm1
void esc_control(String Seite ,uint16_t PWM_input);
