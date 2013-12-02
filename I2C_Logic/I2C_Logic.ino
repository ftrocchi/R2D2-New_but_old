#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Wire.h>
#include <LedControl.h>
#include "I2C_Common.h"
#include "PSI.h"

#define RLD // RLD, FLD, or CBI

#ifdef RLD
    LedControl ledControl = LedControl(2, 4, 8, 4);
	PSI psi(I2C_DeviceAddress::RearLogicDisplay, &ledControl, 3, 1000, 2000, 200);
#endif

void setup()
{

	// clear the device
	for (int device = 0; device < ledControl.getDeviceCount(); device++) 
	{
		ledControl.shutdown(device, false);
		ledControl.clearDisplay(device);
	}

#ifdef RLD
	Wire.begin(I2C_DeviceAddress::RearLogicDisplay);
	ledControl.setIntensity(0, 7);
	ledControl.setIntensity(1, 7);
	ledControl.setIntensity(2, 7);
	ledControl.setIntensity(3, 15);
#endif


	//Wire.onReceive(receiveEvent);
}

void loop()
{
	int i=0;
	for (i=0; i <4; i++) 
	{
		psi.Off();
		delay(250);
		psi.On();
		delay(250);
	}
	for (i=0; i < 16; i++) 
	{
		psi.SetBrightness(i);
		delay(250);
	}
	for (i=15; i >= 0; i--) 
	{
		psi.SetBrightness(i);
		delay(250);
	}
}


