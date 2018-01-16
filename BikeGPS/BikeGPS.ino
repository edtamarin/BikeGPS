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

String timeDisplay[2];

int timeCoords[2] = {85,15};

void setup() {
  // put your setup code here, to run once:
  ss.begin(9600);
  Serial.begin(115200); // serial is used for debugging
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,0,"Initializing...");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clear();
  smartDelay(500);
  if (gps.location.isUpdated()){
    Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
    Serial.print("LNG="); Serial.println(gps.location.lng(), 6);
  }
  updateTime();
  display.display();
}

void updateTime(){
  if (gps.time.isUpdated()){
  timeDisplay[0] = String(gps.time.hour());
  timeDisplay[1] = String(gps.time.minute());
  }
  display.drawString(timeCoords[0],timeCoords[1],timeDisplay[0]+":"+timeDisplay[1]);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

