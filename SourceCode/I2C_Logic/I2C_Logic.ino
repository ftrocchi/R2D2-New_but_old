#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Wire.h>
#include <LedControl.h>
#include "I2C_Common.h"
#include "PSI.h"

#define FLD // RLD, FLD, or CBI

#ifdef RLD
    LedControl ledControl = LedControl(2, 4, 8, 3);
    PSI psi(I2C_DeviceAddress::RearLogicDisplay, &ledControl, 3, 1000, 2000, 200);
#endif

#ifdef FLD
    LedControl ledControl = LedControl(2, 4, 8, 4);
    PSI psi(I2C_DeviceAddress::FrontLogicDisplay, &ledControl, 2, 2000, 1000, 200);
#endif

void receiveEvent(int eventCode)
{
    I2C_Logic_Device::Value logicDevice = (I2C_Logic_Device::Value)Wire.read();

#ifdef RLD
    if (logicDevice == I2C_Logic_Device::PSI)
        psi.ProcessCommand();
#endif

#ifdef FLD
    if (logicDevice == I2C_Logic_Device::PSI)
        psi.ProcessCommand();
#endif
}


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

#ifdef FLD
    Wire.begin(I2C_DeviceAddress::FrontLogicDisplay);
    ledControl.setIntensity(0, 7);
    ledControl.setIntensity(1, 7);
    ledControl.setIntensity(2, 15);
#endif

    Wire.onReceive(receiveEvent);
}

void loop()
{
#ifdef RLD
    psi.Update();
#endif

#ifdef FLD
    psi.Update();
#endif
}



