

void setup() {
  Serial.begin(115200);//115200
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
  //SERVO Stuff setup----------------------------------------------------
  servo_l.begin();
  servo_r.begin();
  servo_l.setPWMFreq(60.5);
  servo_r.setPWMFreq(60.5);
  delay(10);
  
  Serial.print("\r\nLenkservo vl: "); Serial.print(Robi.vl.hubservo.getPin()); Serial.print(" ");
  //Lenkung MIN/MAX Umrechnung (Grad -> PWM)
  pwm_lenk_min = map(LENKUNG_MIN, 0, 180, SERVO0, SERVO180);
  pwm_lenk_max = map(LENKUNG_MAX, 0, 180, SERVO0, SERVO180);

  pwm_speed_forw_max = map(SPEED_FORW_MAX, 0, 100, SERVO90, SERVO180);
  pwm_speed_back_max = map(SPEED_BACK_MAX, 0, 100, SERVO90, SERVO0);
  // Robo Robi;
  //---------------------------------------------------------------------
}