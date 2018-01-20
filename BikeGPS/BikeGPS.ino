#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <OLEDDisplay.h>
#include <OLEDDisplayFonts.h>
#include <OLEDDisplayUi.h>
#include <SSD1306.h>
#include <SoftwareSerial.h>

/**
   The mobile part that tracks the movement
   Board: WeMos D1 mini

   Egor Tamarin, 2017
*/

SSD1306 display(0x3C, D3, D5);
TinyGPSPlus gps;
SoftwareSerial ss(D1, D2);

// compass rose
String compass[17] = {"N","NNE","NE","ENE","E","ESE","SE","SSE","S","SSW","SW","WSW","W","WNW","NW","NNW","N"};
// display strings
String upperBar[4] = {"SAT in range:", "X", "XX", "XX"};
String heading = "FIX";
String pos[2] = {"NO","FIX"};

// coordinates for the UI
int timeCoords[2] = {100, 0};
int hdngCoords[2] = {0, 15};
int posCoords[2] = {0,50};

void setup() {
  // start the serial communication
  ss.begin(9600);
  Serial.begin(115200); // serial is used for debugging
  display.init(); // start the display
  display.setFont(ArialMT_Plain_10); // display settings
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void loop() {
  // clear the display buffer so we don't write over anything
  display.clear();
  // GPS is polled at 1 HZ, so double the poll rate is enough fo a smooth data update rate
  smartDelay(500);
  // update all the data on screen
  // it will not change if nothing new was received
  updateTime();
  updateSatNum();
  updateHdng();
  updatePos();
  // update the display
  display.display();
}

// update the time
void updateTime() {
  if (gps.time.isUpdated()) {
    upperBar[2] = String(gps.time.hour());
    upperBar[3] = String(gps.time.minute());
    if (gps.time.minute() < 10) upperBar[3] = "0" + upperBar[3];
  }
  display.drawString(timeCoords[0], timeCoords[1], upperBar[2] + ":" + upperBar[3]);
}

// update the number of satellites in LOS
void updateSatNum() {
  if (gps.satellites.isUpdated()) {
    upperBar[1] = String(gps.satellites.value());
  }
  display.drawString(0, 0, upperBar[0] + " " + upperBar[1]);
}

// update the heading
void updateHdng() {
  if (gps.course.isUpdated()) {
    heading = String(compassRose(gps.course.deg()));
  }
  display.setFont(ArialMT_Plain_24);
  display.drawString(hdngCoords[0], hdngCoords[1], heading);
  display.setFont(ArialMT_Plain_10);
}

// update the current position
void updatePos() {
  if (gps.location.isUpdated()) {
    pos[0] = String(gps.location.lat(), 3);
    pos[1] = String(gps.location.lng(), 3);
  }
  display.drawString(posCoords[0],posCoords[1],pos[0]+";"+pos[1]);
}

// translate degree heading into a compass rose
String compassRose(double degree){
  int index = (int)degree%350;
  index = round(index/22.5);
  return compass[index];
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

