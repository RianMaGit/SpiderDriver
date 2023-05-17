//V23.11.21,16:00
#include "Robo.h"
#include <PS3BT.h>
#include <usbhub.h>
#include <math.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
// Verbindung USB Shield und Controller ?
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
//SERVO Stuff define --------------------------------------------------
#include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver servo_l = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver servo_r = Adafruit_PWMServoDriver(0x41);
Robo Robi(servo_l, servo_r);
// Standard Winkel für Trigger(0-255)
#define std_agl 127         //127 = 90 grad
// max. Lenkwinkel?
//Winkel definieren (0-180 Grad)
#define LENKUNG_MIN 60      //MIN Winkel der Beine beim Lenken
#define LENKUNG_MAX 120     //MAX Winkel der Beine beim Lenken
//Fahrgeschwindigkeit definieren (0-100%)

int Xdata;
int Ydata;
int Zdata;
//Trigger definition (0 - 255)
uint8_t trigger_lx = std_agl; //Linker Trigger X-Achse
uint8_t trigger_ly = std_agl; //Linker Trigger Y-Achse
uint8_t trigger_rx = std_agl; //Rechter Trigger X-Achse
uint8_t trigger_ry = std_agl; //Rechter Trigger Y-Achse
uint8_t trigger_lt, trigger_rt; // Linker/Rechter Trigger LT/RT (=0)

//uint16_t pulselen_lx, pulselen_ly, pulselen_rx, pulselen_ry, pulselen_lt, pulselen_rt;

int16_t pwm_lenk_min, pwm_lenk_max;

#define pwm_speed_mid 375     //PWM für stehende BL-Motoren

uint16_t pwm_speed_forw_max = pwm_speed_mid;
uint16_t pwm_speed_back_max = pwm_speed_mid;

// Robo Robi;
