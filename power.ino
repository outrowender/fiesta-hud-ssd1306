void sleepCan() {
  Serial.println("can to sleep");
  canIsSleep = true;
  mcp2515.setSleepMode();
}

void sleepOled() {
  Serial.println("oled to sleep");
  drawLogoReverse();

  u8g2.sleepOn();
}

void wakeCan() {
  canIsSleep = false;
  logoWasShown = false;
  mcp2515.setNormalMode();  // wake again
  Serial.println("can was wake");
}

void wakeOled() {
  Serial.println("oled was wake");
  u8g2.sleepOff();
}

void switchOperationModes() {
  val = 0;

  switch (mode) {
    case KPH:
      mode = RPM;
      drawRpm(val);
      break;
    case RPM:
      mode = TEMP;
      drawTemp(val);
      break;
    case TEMP:
      mode = KPH;
      drawSpeed(val);
      break;
  }
}
