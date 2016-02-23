#ifndef _POINT_H
#define _POINT_H

#include "ToggleButton.h"

class SetLatch : public ToggleButton
{
public:
  SetLatch(int buttonPin, int indicatorPin, bool isButtonNegativeLogic = ToggleButton::IS_NEG_LOGIC, ToggleButtonAdapter* adapter = 0);
  virtual void toggle();
private:  // forbidden functions
  SetLatch();                                 // default constructor
  SetLatch(const SetLatch& src);              // copy constructor
  SetLatch& operator = (const SetLatch& src); // assignment operator
};

//-----------------------------------------------------------------------------

class Point
{
private:
  SetLatch* m_devToggleButton;
  SetLatch* m_strToggleButton;
public:
  Point(int devButtonPin, int strButtonPin, int devIndicatorPin = ToggleButton::IND_NC, int strIndicatorPin = ToggleButton::IND_NC);
  SetLatch* getDev() { return m_devToggleButton; }
  SetLatch* getStr() { return m_strToggleButton; } 
private:  // forbidden functions
  Point();                              // default constructor
  Point(const Point& src);              // copy constructor
  Point& operator = (const Point& src); // assignment operator
};

//-----------------------------------------------------------------------------

class Blanking;
class Timer;

class Crossing : public Point
{
private:
  int m_indicator1Pin;
  int m_indicator2Pin;
  int m_indicator3Pin;
  int m_indicator4Pin;
  Blanking* m_blanking;
  Timer* m_updateDisplayTimer;
public:
  Crossing(int devButtonPin, int strButtonPin, int indicator1Pin, int indicator2Pin, int indicator3Pin, int indicator4Pin);
  friend class UpdateDisplayTimerAdapter;
private:
  void updateDisplay();
private:  // forbidden functions
  Crossing();                                 // default constructor
  Crossing(const Crossing& src);              // copy constructor
  Crossing& operator = (const Crossing& src); // assignment operator  
};

//-----------------------------------------------------------------------------

class PointToggleButtonAdapter : public ToggleButtonAdapter
{
private:
  ToggleButton* m_mateToggleButton;
public:
  PointToggleButtonAdapter(ToggleButton* mateToggleButton);
  virtual void notifyStatusChanged(bool isActive);
private:  // forbidden functions
  PointToggleButtonAdapter();                                                 // default constructor
  PointToggleButtonAdapter(const PointToggleButtonAdapter& src);              // copy constructor
  PointToggleButtonAdapter& operator = (const PointToggleButtonAdapter& src); // assignment operator
};

//-----------------------------------------------------------------------------

#endif