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

	Wire.begin(I2C_DeviceAddress::MagicPanel);

	Wire.onReceive(receiveEvent);

	magicPanel.Random();
}

void loop()
{
	magicPanel.Update();
}

void receiveEvent(int eventCode)
{
	magicPanel.ProcessCommand();
}
