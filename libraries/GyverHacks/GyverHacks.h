#ifndef GyverHacks_h
#define GyverHacks_h
#include <Arduino.h>

int getVCC();
void setConstant(uint16_t voltage);
int getVoltage(uint8_t pin);
float getTemp();

class GTimer
{
  public:
	GTimer();
	GTimer(uint16_t interval);
	void setInterval(uint16_t interval);
	boolean isReady();
	void reset();
  private:
	uint32_t _timer;
	uint16_t _interval;
};

int medianFilter(int a, int b, int c);

class GFilterRA
{
  public:
	GFilterRA();	
	void setCoef(float coef);
	void setStep(uint16_t interval);
	float filteredTime(int16_t value);
	float filtered(int16_t value);
  private:
	float _coef, _lastValue;
	uint32_t _filterTimer;
	uint16_t _filterInterval;
};

void setPWMPrescaler(uint8_t pin, uint16_t prescale);

#endif