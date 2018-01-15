#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <OLEDDisplay.h>
#include <OLEDDisplayFonts.h>
#include <OLEDDisplayUi.h>
#include <SSD1306.h>
#include <SoftwareSerial.h>

/**
 * The mobile part that tracks the movement
 * Board: WeMos D1 mini
 * 
 * Egor Tamarin, 2017
 */

SSD1306 display(0x3C, D3, D5);
TinyGPSPlus gps;
SoftwareSerial ss(D1,D2);

void setup() {
  // put your setup code here, to run once:
  ss.begin(9600);
  Serial.begin(115200); // serial is used for debugging
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,0,"Initializing...");
  display.drawString(0,15,"Display alignment test");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (ss.available() > 0)
    gps.encode(ss.read());
  if (gps.location.isUpdated()){
    Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
    Serial.print("LNG="); Serial.println(gps.location.lng(), 6);
  }
}
