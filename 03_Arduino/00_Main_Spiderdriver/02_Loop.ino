
void loop(){
  // SERVO winkel in PWM rechner
  //short ist ein int16_t (-32,768 .. 32,767)
  //unsigned short ist ein uint16_t (0 .. 65,535)
  int16_t pulselen_div_lx = map(trigger_lx, 0, 255, -(pwm_lenk_max - pwm_lenk_min)/2, (pwm_lenk_max - pwm_lenk_min)/2);
  int16_t pulselen_div_ly = map(trigger_ly, 0, 255, -(pwm_lenk_max - pwm_lenk_min)/2, (pwm_lenk_max - pwm_lenk_min)/2);
  int16_t pulselen_div_rx = map(trigger_rx, 0, 255, -(pwm_lenk_max - pwm_lenk_min)/2, (pwm_lenk_max - pwm_lenk_min)/2);
  int16_t pulselen_div_ry = map(trigger_ry, 0, 255, -(pwm_lenk_max - pwm_lenk_min)/2, (pwm_lenk_max - pwm_lenk_min)/2);
  int16_t pulselen_div_lt = map(trigger_lt, 0, 255, 0, (pwm_speed_forw_max - SERVO90));
  int16_t pulselen_div_rt = map(trigger_rt, 0, 255, 0, (SERVO90 - pwm_speed_back_max));
   Usb.Task();
  //Serial.print(pulselen_div_lx + " | " + pulselen_div_ly);
  
  //Das PWM der Servos wird um x an das PWM-Ziel angenähert und ausgeführt
  Robi.PWM_refresh(5);
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    //Serial.print(F("\r\nLeftHatX: "));
    //Linker und Rechter Steuertrigger
    ///////////////////////////////////////////
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      //SERVO---
      trigger_lx = PS3.getAnalogHat(LeftHatX);
      Serial.print(" trigger_lx: "); Serial.print(trigger_lx);
      //---------
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      //SERVO---
      trigger_ly = PS3.getAnalogHat(LeftHatY);
      //---------
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        Serial.print(F("\tRightHatX: "));
        Serial.print(PS3.getAnalogHat(RightHatX));
        //SERVO---
        trigger_rx = PS3.getAnalogHat(RightHatX);
        //---------
        Serial.print(F("\tRightHatY: "));
        Serial.print(PS3.getAnalogHat(RightHatY));
        //SERVO---
        trigger_ry = PS3.getAnalogHat(RightHatY);
        //---------
      }
      Robi.setLenkung(trigger_lx);
      Robi.walk(trigger_ly);
    }
    // Triggersticks werden nach betätigung auf den std Winkel resettet---------------------
    //////////////////////////////////////////////////////////////////////////////
    if (PS3.getAnalogHat(LeftHatY) < 137 && PS3.getAnalogHat(LeftHatY) > 117) {
      trigger_ly=std_agl;
      
    }
    if (PS3.getAnalogHat(LeftHatX) < 137 && PS3.getAnalogHat(LeftHatX) > 117) {
      trigger_lx=std_agl;
      Robi.setLenkung(std_agl);
    }
    if (PS3.getAnalogHat(RightHatY) < 137 && PS3.getAnalogHat(RightHatY) > 117) {
      trigger_ry=std_agl;
    }
    if (PS3.getAnalogHat(RightHatX) < 137 && PS3.getAnalogHat(RightHatX) > 117) {
      trigger_rx=std_agl;
    }
    
    //--------------------------------------------------------------------------------------
    // Analog button values can be read from almost all buttons
    // Trigger R2(rt) und L2(lt)
    //////////////////////////////////////////////////////////////////////////////
      //lenkung
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
    
    //Bremsen////////////////////////////////
      if ((PS3.getAnalogButton(L2)) && PS3.getAnalogButton(R2)) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
        trigger_rt=PS3.getAnalogButton(R2);
        servo_l.setPWM(Robi.escl.getPin(), 0, SERVO90 - pulselen_div_rt);
        servo_r.setPWM(Robi.escr.getPin(), 0, SERVO90 - pulselen_div_rt);
      }
      ///////////////////////////////////////////
      
      //Fahren///////////////////////////////////
      if (PS3.getAnalogButton(L2)>50 && PS3.getAnalogButton(R2)<50) {
        Serial.print(F("\r\nL2: "));
        Serial.print(PS3.getAnalogButton(L2));
        trigger_lt=PS3.getAnalogButton(L2);
        
        servo_l.setPWM(Robi.escl.getPin(), 0, SERVO90-pulselen_div_lt);
        servo_r.setPWM(Robi.escr.getPin(), 0, SERVO90-pulselen_div_lt);
      }
      if (PS3.getAnalogButton(L2)<50 && PS3.getAnalogButton(R2)>50) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
        trigger_rt=PS3.getAnalogButton(R2);
        servo_l.setPWM(Robi.escl.getPin(), 0, SERVO90+pulselen_div_rt);
        servo_r.setPWM(Robi.escr.getPin(), 0, SERVO90+pulselen_div_rt);
      }
      if (PS3.getAnalogButton(L2)<50 && PS3.getAnalogButton(R2)<50) {
        //Serial.print(F("\tstop");
        Serial.print(PS3.getAnalogButton(R2));
        trigger_rt=PS3.getAnalogButton(R2);
        servo_l.setPWM(Robi.escl.getPin(), 0, SERVO90);
        servo_r.setPWM(Robi.escr.getPin(), 0, SERVO90);
      }
      else{noTone(2);}
      
    ////////////////////////////////////////////
    }
    //L2 und R2 auf 0 setzen nach Betätigung
    if (!PS3.getAnalogButton(L2)){trigger_lt=0;}
    if (!PS3.getAnalogButton(R2)){trigger_rt=0;}
    
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE)) {
        Robi.hl.set_cord(0,23, -7);
//        Robi.hr.set_cord(0, 23, -7);
        Robi.mr.set_cord(0, 23, -7);
//        Robi.ml.set_cord(0, 23, -7);
        Robi.vl.set_cord(0, 23, -7);
//        Robi.vr.set_cord(0,23, -7);
        
        Serial.print(F("\r\nTriangle")); 
        // PS3.setRumbleOn(RumbleLow);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Robi.hl.set_cord(0,10, -12);
        Robi.hr.set_cord(5, 10, -5);
        Robi.mr.set_cord(0, 10, -12);
        Robi.ml.set_cord(0, 10, -5);
        Robi.vl.set_cord(0, 10, -12);
        Robi.vr.set_cord(0,10, -5);
        Serial.print(F("\r\nCircle"));
        // PS3.setRumbleOn(RumbleHigh);
      }
      if (PS3.getButtonClick(CROSS)){
//        Robi.hl.set_cord(0,23, -7);
        Robi.hr.set_cord(0, 23, -7);
//        Robi.mr.set_cord(0, 23, -7);
        Robi.ml.set_cord(0, 23, -7);
//        Robi.vl.set_cord(0, 23, -7);
        Robi.vr.set_cord(0,23, -7);
        
        Serial.print(F("\r\nCross"));
      }
      if (PS3.getButtonClick(SQUARE)){
        Robi.hl.set_cord(0,10, -12);
        Robi.hr.set_cord(0, 10, -12);
        Robi.mr.set_cord(0, 10, -12);
        Robi.ml.set_cord(0, 10, -12);
        Robi.vl.set_cord(0, 10, -12);
        Robi.vr.set_cord(0,7, -12);
        Serial.print(F("\r\nSquare"));
      }
      if (PS3.getButtonClick(UP)) {
        Robi.hl.set_cord(-1,10, -27);
        Robi.hr.set_cord(1, 10, -27);
        Robi.mr.set_cord(0, 10, -27);
        Robi.ml.set_cord(0, 10, -27);
        Robi.vl.set_cord(1, 10, -27);
        Robi.vr.set_cord(-1,10, -27);
        Serial.print(F("\r\nUp"));
        // test_up(0, 25, 0);
        if (PS3.PS3Connected) {
          if(Robi.LaufSchritt<6){
            
            }
          Robi.walk(trigger_ly);
          // PS3.setLedOff();
          // PS3.setLedOn(LED4);
        }
      }
      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if (PS3.PS3Connected) {
          Robi.hl.set_cord(-8, 10, -12);
          Robi.hr.set_cord(8, 10, -12);
          Robi.mr.set_cord(4, 8, -10);
          Robi.ml.set_cord(-4, 8, -10);
          Robi.vl.set_cord(0, 6, -10);
          Robi.vr.set_cord(0, 6, -10);
          // PS3.setLedOff();
          // PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        
        Robi.hl.set_cord(-1,10, 0);
        Robi.hr.set_cord(1, 10, 0);
        Robi.mr.set_cord(0, 10, 0);
        Robi.ml.set_cord(0, 10, 0);
        Robi.vl.set_cord(1, 10, 0);
        Robi.vr.set_cord(-1,10, 0);
        /*
        Serial.print(F("\r\nDown"));
        if (PS3.PS3Connected) {
          if(Robi.LaufSchritt>0){
            

            }
          Robi.walk(trigger_ly);
          // PS3.setLedOff();
          // PS3.setLedOn(LED2);
        }
        */
      }
      if (PS3.getButtonClick(LEFT)) {

        Robi.hl.set_cord(-1,10, -15);
        Robi.hr.set_cord(1, 10, -15);
        Robi.mr.set_cord(0, 10, -15);
        Robi.ml.set_cord(0, 10, -15);
        Robi.vl.set_cord(1, 10, -15);
        Robi.vr.set_cord(-1,10, -15);
        /*
        Serial.print(F("\r\nLeft"));
        if (PS3.PS3Connected) {
          Robi.vl.set_cord(16, 10, -12);
            Robi.vr.set_cord(-16, 10, -12);
            Robi.mr.set_cord(-8, 8, -10);
            Robi.ml.set_cord(8, 8, -10);
            Robi.hl.set_cord(0, 6, -10);
            Robi.hr.set_cord(0, 6, -10);
          // PS3.setLedOff();
          // PS3.setLedOn(LED3);
        }
        */
      }

      if (PS3.getButtonClick(L1)){
        Robi.setPosition(SERVO90, SERVO90);
        if(0){
          Robi.ml.hubservo.move(SERVO90);
          Robi.mr.hubservo.move(SERVO90);
        }
        
        Serial.print(F("\r\nL1"));
      }
      if (PS3.getButtonClick(L3)){
        Serial.print(F("\r\nL3"));
        Robi.ml.SerialCord();
      }
      if (PS3.getButtonClick(R1)){
        Robi.addLaufSchritt();
        Serial.print(F("\r\nR1"));
      }      
      if (PS3.getButtonClick(R3)) {
        Robi.hl.SerialCord();
        Serial.print(F("\r\nR3"));
      }      
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        if(Robi.laufen){
          tone(2, 1000);
          delay(100);
          noTone(2);
        };
        Robi.setLaufen(false);
        Robi.ml.lenkservo.setPWM(SERVO90);
        Robi.mr.lenkservo.setPWM(SERVO90);
        Serial.print("\r\nLaufen: ausgeschaltet");
        PS3.printStatusString();
        //restservos
        ///robo_stand(0, 0);
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        if(!Robi.laufen){
          tone(2, 4100);
          delay(100);
          noTone(2);
          delay(80);
          tone(2, 4100);
          delay(100);
          noTone(2);
        }
        
        printAngle = !printAngle;
        Robi.setLaufen(true);
        Serial.print("\r\nLaufen: eingeschaltet");
        //restservos
       // int sev2 = -200;
       // int sev3 = 200;
        ///robo_stand(-100, 150);
      }
      
    }
#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
#if 0 // Set this to 1 in order to enable support for the Playstation Move controller
  else if (PS3.PS3MoveConnected) {
    if (PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: "));
      Serial.print(PS3.getAnalogButton(T));
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      }
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      }
      if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      }
      if (PS3.getButtonClick(MOVE)) {
        PS3.moveSetBulb(Off);
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - "));
        PS3.printStatusString();
      }
    }
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    else if (printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
  }
#endif
  
}