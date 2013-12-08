#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>
#include <LedControl.h>
#include "I2C_Common.h"
#include "MagicPanel.h"

LedControl ledControl = LedControl(8,7,6,2);
MagicPanel magicPanel(I2C_DeviceAddress::MagicPanel, &ledControl);
int mode = 0;
unsigned long lastTimeCheck = 0;

void setup()
{
	ledControl.shutdown(0,false);
	ledControl.shutdown(1,false);

	magicPanel.SetBrightness(15);
	magicPanel.Off();

	magicPanel.SetMode(I2C_MagicPanel_Mode::QuadCycleCounterClockwise);
}

void loop()
{
	magicPanel.Update();

	//unsigned long timeNow = millis();
 // 
	//// early exit if we don't need to do anything
	//if (timeNow - lastTimeCheck < 10000)
	//	return;

	//// set the time  
	//lastTimeCheck = timeNow;

	//mode++;
	//if (mode == 9)
	//	mode = 0;

	//magicPanel.SetMode((I2C_MagicPanel_Mode::Value)mode);
}
