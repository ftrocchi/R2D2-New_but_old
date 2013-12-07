#ifndef _MAGICPANEL_h
#define _MAGICPANEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>
#include <LedControl.h>
#include "I2C_Common.h"


class MagicPanel
{
	private:
		LedControl *ledControl;
		I2C_DeviceAddress::Value i2cAddress;
		bool vMagicPanel[8][8];
		unsigned char panel[16];


		void MapAndPrint();
		void MapBoolGrid();
		void PrintGrid();

	public:
		MagicPanel(I2C_DeviceAddress::Value i2cAddress, LedControl *led);

		void SetBrightness(int brightness);
		void Off();
		void On();
};

#endif

