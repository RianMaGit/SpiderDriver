#include "Arduino.h"
#include "variablen.h"


//Funktion für Servo sv1
void servo_sv1(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sv1, 0, std_agl+of_sv1+PWM_input);}
  else{servo_r.setPWM(sv1, 0, std_agl+of_sv1+PWM_input);}
}
//Funktion für Servo sv2
void servo_sv2(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sv2, 0, std_agl+of_sv2+PWM_input);}
  else{servo_r.setPWM(sv2, 0, std_agl+of_sv2+PWM_input);}
}
//Funktion für Servo sv3
void servo_sv3(String Seite, uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sv3, 0, std_agl+of_sv3+PWM_input);}
  else{servo_r.setPWM(sv3, 0, std_agl+of_sv3+PWM_input);}
}


//Funktion für Servo sm1
void servo_sm1(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sm1, 0, std_agl+of_sm1+PWM_input);}
  else{servo_r.setPWM(sm1, 0, std_agl+of_sm1+PWM_input);}
}
//Funktion für Servo sm2
void servo_sm2(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sm2, 0, std_agl+of_sm2+PWM_input);}
  else{servo_r.setPWM(sm2, 0, std_agl+of_sm2+PWM_input);}
}
//Funktion für Servo sm3
void servo_sm3(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sm3, 0, std_agl+of_sm3+PWM_input);}
  else{servo_r.setPWM(sm3, 0, std_agl+of_sm3+PWM_input);}
}



//Funktion für Servo sh1
void servo_sh1(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sh1, 0, std_agl+of_sh1+PWM_input);}
  else{servo_r.setPWM(sh1, 0, std_agl+of_sh1+PWM_input);}
}
//Funktion für Servo sh2
void servo_sh2(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sh2, 0, std_agl+of_sh2+PWM_input);}
  else{servo_r.setPWM(sh2, 0, std_agl+of_sh2+PWM_input);}
}
//Funktion für Servo sh3
void servo_sh3(String Seite ,uint16_t PWM_input){
  if(Seite=="links"){servo_l.setPWM(sh3, 0, std_agl+of_sh3+PWM_input);}
  else{servo_r.setPWM(sh3, 0, std_agl+of_sh3+PWM_input);}
}



//Funktion für Servo esc
void esc_control(String Seite ,uint16_t PWM_input){
  servo_l.setPWM(esc, 0, pwm_speed_mid+PWM_input);
  if(Seite=="links"){servo_l.setPWM(sh3, 0, pwm_speed_mid+PWM_input);}
  else{servo_r.setPWM(sh3, 0, pwm_speed_mid+PWM_input);}
}
