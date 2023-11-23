
// Draw current speed in Km/h.
void drawSpeed(int speed) {
  const int x = 80;
  const int y = 30;

  // Format speed.
  char speedChar[4];
  snprintf(speedChar, 4, "%d", speed);

  u8g2.firstPage();
  u8g2.setColorIndex(1);
  do {
    // Draw speed numbers.
    u8g2.setFont(u8g2_font_freedoomr25_mn);
    u8g2.drawStr(x - u8g2.getStrWidth(speedChar), y, speedChar);

    // Draw Km/h.
    u8g2.setFont(u8g2_font_6x12_me);
    u8g2.drawStr(x + 2, y - 2, "Km/h");
  } while (u8g2.nextPage());
}

// Draw RPM values divided by 1000.
void drawRpm(int rpm) {
  const int x = 80;
  const int y = 30;

  // Format RPM.
  const double divided = rpm / 1000.0;
  char rotation[5];
  dtostrf(divided, 3, 1, rotation);

  u8g2.firstPage();
  do {

    if (divided >= RPM_SHIFT_LIGHT) {
      u8g2.setColorIndex(1);
      u8g2.drawBox(0, 0, 128, 32);
      u8g2.setColorIndex(0);
    } else {
      u8g2.setColorIndex(1);
    }

    // Draw rpm numbers divided by 1000.
    u8g2.setFont(u8g2_font_freedoomr25_mn);
    u8g2.drawStr(x - u8g2.getStrWidth(rotation), y, rotation);

    // Draw rpm x1000.
    u8g2.setFont(u8g2_font_6x12_me);
    u8g2.drawStr(x + 3, y - 12, "rpm");
    u8g2.drawStr(x + 3, y - 2, "x1000");
  } while (u8g2.nextPage());
}

// Draw temperature in Celsius.
void drawTemp(int temp) {
  const int x = 80;
  const int y = 30;

  // format temp
  char tempChar[4];
  snprintf(tempChar, 4, "%d", temp);

  u8g2.firstPage();
  u8g2.setColorIndex(1);
  do {
    // Draw temperature.
    u8g2.setFont(u8g2_font_freedoomr25_mn);
    u8g2.drawStr(x - u8g2.getStrWidth(tempChar), y, tempChar);

    u8g2.setFont(u8g2_font_6x12_me);
    // Draw little "°".
    u8g2.drawStr(x + 3, y - 20, "0");
    // Draw temp string.
    u8g2.drawStr(x + 3, y - 2, "temp");

  } while (u8g2.nextPage());
}

// logo
void drawLogo() {
  Serial.println("logo will be shown");

  u8g2.setBitmapMode(1);
  u8g2.setFontMode(1);
  u8g2.setColorIndex(1);
  for (int i = 0; i <= epd_bitmap_allArray_LEN; i++) {

    u8g2.firstPage();
    do {
      u8g2.drawXBMP(24, 0, 80, 32, epd_bitmap_allArray[i]);
    } while (u8g2.nextPage());

    if (i == epd_bitmap_allArray_LEN) {
      delay(3000);
    } else {
      delay(75);
    }
  }

  u8g2.setBitmapMode(0);

  logoWasShown = true;

  Serial.println("logo was shown");
}

void drawLogoReverse() {
  Serial.println("reverse logo will be shown");

  u8g2.setBitmapMode(1);
  u8g2.setFontMode(1);
  u8g2.setColorIndex(1);
  for (int i = epd_bitmap_allArray_LEN; i >= 0; i--) {

    u8g2.firstPage();
    do {
      u8g2.drawXBMP(24, 0, 80, 32, epd_bitmap_allArray[i]);
    } while (u8g2.nextPage());

    if (i == epd_bitmap_allArray_LEN) {
      delay(3000);
    } else {
      delay(75);
    }
  }

  u8g2.setBitmapMode(0);

  Serial.println("reverse logo was shown");
}
