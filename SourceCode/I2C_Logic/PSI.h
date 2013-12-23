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
		unsigned long lastTimeCheck;
		I2C_PSI_Mode::Value currentMode;

		// normal
		void ResetModes(int first, int second, int transition);
		void AnimateNormal();	
		int delayAtStage[9];
		int stage;
		int slideDirection;
		int maxStage;

		// march
		void AnimateMarch();
		bool firstColor;

		// ring
		void AnimateSpin();
		int spinState;

		// march
		void AnimateRing();
		int ringState;
		int ringDirection;

		// up down
		void AnimateUpDown();
		int upDownState;
		int upDownDirection;

		// left right
		void AnimateLeftRight();
		int leftRightState;
		int leftRightDirection;

		bool IsTimeForStateChange(int delay);
        bool isModeActive;

	public:
		PSI(I2C_DeviceAddress::Value i2cAddress, LedControl *led, int deviceIndex, int first, int second, int transition);
		~PSI();
	
		void ProcessCommand();
		void Update();

		// COMMANDS
		void On();
		void Off();
		void SetBrightness(int brightness);
		void SetMode(I2C_PSI_Mode::Value mode);
};

#endif

