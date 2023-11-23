#include "U8g2lib.h"
#include <mcp2515.h>
#include <SPI.h>

#define SWITCH_PIN A0
#define MCP_CS_PIN 10
#define CAN_ID_RPM 0x201    // ID 201 is the default params for KPM and RPM on the Fiesta MK7.
#define CAN_ID_SPEED 0x201 
#define CAN_ID_CTEMP 0x420  // ID 420 is the default coolant temp params for the Fiesta MK7.
#define RPM_SHIFT_LIGHT 6.0 // If RPM go higher, should turn on shift light in RPM mode.
#define DEFAULT_MODE RPM
#define S_TO_SLEEP 3

enum modes { KPH,
             RPM,
             TEMP };

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
MCP2515 mcp2515(MCP_CS_PIN);

modes mode = DEFAULT_MODE;
struct can_frame canMsg;
unsigned long lastMessage = 0;
unsigned long val = 0;

bool canIsSleep = false;
bool logoWasShown = false;

// Ino logic:
void setup(void) {
  Serial.begin(115200);

  u8g2.begin();

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  mcp2515.reset();
  int set = mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  // Works for Fiesta MK7.
  mcp2515.setNormalMode();

  lastMessage = millis();

  Serial.println("ino is booting");
  Serial.println(set);
}

void loop(void) {

  if (digitalRead(SWITCH_PIN) == LOW) {
    delay(500);
    switchOperationModes();
  }

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {  // Read messages and save in canMsg var.
    lastMessage = millis();                                 // valid messages will be counted.

    if (canIsSleep) {
      wakeCan();
    }
  }


  // signal to sleep will be received if no messages are received in S_TO_SLEEP seconds.
  if (millis() - lastMessage >= (S_TO_SLEEP * 1000) && !canIsSleep) {
    Serial.println("no activity for S_TO_SLEEP seconds");
    sleepOled();
    sleepCan();
  }

  if (!canIsSleep) processFrame();
}
