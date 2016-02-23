#include "Arduino.h"

#include "Point.h"
#include "Timer.h"
#include "Blanking.h"

//-----------------------------------------------------------------------------
SetLatch::SetLatch(int buttonPin, int indicatorPin, bool isButtonNegativeLogic, ToggleButtonAdapter* adapter)
: ToggleButton(buttonPin, indicatorPin, isButtonNegativeLogic, adapter)
{ }

void SetLatch::toggle()
{
  if (!isActive())
  {
    setIsActive(true);
  }
}

//-----------------------------------------------------------------------------

Point::Point(int devButtonPin, int strButtonPin, int devIndicatorPin, int strIndicatorPin)
: m_devToggleButton(new SetLatch(devButtonPin, devIndicatorPin))
, m_strToggleButton(new SetLatch(strButtonPin, strIndicatorPin))
{
  m_devToggleButton->setIsActive(false);
  m_strToggleButton->setIsActive(true);

  m_devToggleButton->attachAdapter(new PointToggleButtonAdapter(m_strToggleButton));
  m_strToggleButton->attachAdapter(new PointToggleButtonAdapter(m_devToggleButton));
}

//-----------------------------------------------------------------------------

class UpdateDisplayTimerAdapter : public TimerAdapter
{
private:
  Crossing* m_crossing;
public:
  UpdateDisplayTimerAdapter(Crossing* crossing)
  : m_crossing(crossing)
  { }
  void timeExpired()
  {
    if (0 != m_crossing)
    {
      m_crossing->updateDisplay();
    }
  }
};

Crossing::Crossing(int devButtonPin, int strButtonPin, int indicator1Pin, int indicator2Pin, int indicator3Pin, int indicator4Pin)
: Point(devButtonPin, strButtonPin)
, m_indicator1Pin(indicator1Pin)
, m_indicator2Pin(indicator2Pin)
, m_indicator3Pin(indicator3Pin)
, m_indicator4Pin(indicator4Pin)
, m_blanking(new Blanking(2000))
, m_updateDisplayTimer(new Timer(new UpdateDisplayTimerAdapter(this), Timer::IS_RECURRING, 100))
{ 
  if (0 <= m_indicator1Pin)
  {
    pinMode(m_indicator1Pin, OUTPUT);
    digitalWrite(m_indicator1Pin, true);
  }
  if (0 <= m_indicator2Pin)
  {
    pinMode(m_indicator2Pin, OUTPUT);
    digitalWrite(m_indicator2Pin, false);
  }
  if (0 <= m_indicator3Pin)
  {
    pinMode(m_indicator3Pin, OUTPUT);
    digitalWrite(m_indicator3Pin, true);
  }
  if (0 <= m_indicator4Pin)
  {
    pinMode(m_indicator4Pin, OUTPUT);
    digitalWrite(m_indicator4Pin, false);
  }
}

void Crossing::updateDisplay()
{
  bool isBlanked = false;
  if (0 != m_blanking)
  {
    isBlanked = m_blanking->isSignalBlanked();
  }
  bool ind1 = !isBlanked;
  bool ind2 = !ind1;
  bool ind3 = getStr()->isActive() ? !isBlanked : isBlanked;
  bool ind4 = !ind3;
  if (0 <= m_indicator1Pin)
  {
    digitalWrite(m_indicator1Pin, ind1);
  }
  if (0 <= m_indicator2Pin)
  {
    digitalWrite(m_indicator2Pin, ind2);
  }
  if (0 <= m_indicator3Pin)
  {
    digitalWrite(m_indicator3Pin, ind3);
  }
  if (0 <= m_indicator4Pin)
  {
    digitalWrite(m_indicator4Pin, ind4);
  }
}

//-----------------------------------------------------------------------------

PointToggleButtonAdapter::PointToggleButtonAdapter(ToggleButton* mateToggleButton)
: m_mateToggleButton(mateToggleButton)
{ }

void PointToggleButtonAdapter::notifyStatusChanged(bool isActive)
{
  if (0 != m_mateToggleButton)
  {
    m_mateToggleButton->setIsActive(!isActive);
  }
}
