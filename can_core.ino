// this section needs to be customizaed for each model.
void processFrame() {
  if (!logoWasShown) {
    wakeOled();
    drawLogo();
    return;
  }

  if ((mode == RPM || mode == KPH) && canMsg.can_id == CAN_ID_RPM) {
    if (mode == KPH) {
      int carSpeed = ((canMsg.data[4] << 8) | canMsg.data[5]) / 100;  // bytes 4 & 5 can be added and divided by 100. This works for KPH. Not sure about MPH.
      if (val != carSpeed) {                                          // this verification is important for performance. Read values from can is fast. Draw on screen in not.
        val = carSpeed;
        return drawSpeed(val);
      }
    } else {
      int engineSpeed = (canMsg.data[0] << 8) | canMsg.data[1];  // byte 0 is RPM values.
      if (val != engineSpeed) {
        val = engineSpeed;
        return drawRpm(val);
      }
    }
  }

  if (mode == TEMP && canMsg.can_id == CAN_ID_CTEMP) {
    int engineTemp = canMsg.data[0] - 40;  // byte 0 is Coolant temp + 40 in Celcius.
    if (val != engineTemp) {
      val = engineTemp;
      return drawTemp(val);
    }
  }
}