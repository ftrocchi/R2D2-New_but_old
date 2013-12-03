#ifndef _PSI_h
#define _PSI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>
#include <LedControl.h>
#include "I2C_Common.h"

class PSI
{
	private:
		static const int patternAtStage[9];
		LedControl *ledControl;
		I2C_DeviceAddress::Value i2cAddress;
		int device;
		int delayAtStage[9];
		int stage;
		int slideDirection;
		int maxStage;
		unsigned long lastTimeCheck;
	
		void ResetDelays(int first, int second, int transition);

	public:
		PSI(I2C_DeviceAddress::Value i2cAddress, LedControl *led, int deviceIndex, int first, int second, int transition);
		~PSI();
	
		void ProcessCommand();
  
		void On();
		void Off();
		void SetBrightness(int brightness);
		void Animate();	
};

#endif

