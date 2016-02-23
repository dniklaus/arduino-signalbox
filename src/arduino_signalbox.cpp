// Do not remove the include below
#include "arduino_signalbox.h"

#include "Timer.h"          // https://github.com/dniklaus/arduino-utils-timer
#include "ToggleButton.h"   // https://github.com/dniklaus/arduino-toggle-button
#include "Blanking.h"       // https://github.com/dniklaus/arduino-utils-blanking
#include "Point.h"

const int cPt05BtnDev = 32;
const int cPt05BtnStr = 33;
const int cPt05IndDev = 34;
const int cPt05IndStr = 35;

const int cPt20BtnDev = 44;
const int cPt20BtnStr = 45;
const int cPt20IndDev = 46;
const int cPt20IndStr = 47;

const int cPt21BtnDev = 40;
const int cPt21BtnStr = 41;
const int cPt21IndDev = 42;
const int cPt21IndStr = 43;

const int cPt22BtnDev = 36;
const int cPt22BtnStr = 37;
const int cPt22IndDev = 38;
const int cPt22IndStr = 39;

const int cPt23BtnDev = 22;
const int cPt23BtnStr = 23;
const int cPt23Ind1 = 27;
const int cPt23Ind2 = 26;
const int cPt23Ind3 = 24;
const int cPt23Ind4 = 25;

const int cPt24BtnDev = 28;
const int cPt24BtnStr = 29;
const int cPt24IndDev = 30;
const int cPt24IndStr = 31;

class Point* pt05;
class Point* pt20;
class Point* pt21;
class Point* pt22;
class Point* pt23;
class Point* pt24;

//-----------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Hello from Signal Box Arduino Application!\n"));

  pt05 = new Point(cPt05BtnDev, cPt05BtnStr, cPt05IndDev, cPt05IndStr);
  pt20 = new Point(cPt20BtnDev, cPt20BtnStr, cPt20IndDev, cPt20IndStr);
  pt21 = new Point(cPt21BtnDev, cPt21BtnStr, cPt21IndDev, cPt21IndStr);
  pt22 = new Point(cPt22BtnDev, cPt22BtnStr, cPt22IndDev, cPt22IndStr);
  pt23 = new Crossing(cPt23BtnDev, cPt23BtnStr, cPt23Ind1, cPt23Ind2, cPt23Ind3, cPt23Ind4);
  pt24 = new Point(cPt24BtnDev, cPt24BtnStr, cPt24IndDev, cPt24IndStr);
}

void loop()
{
  yield();
}
