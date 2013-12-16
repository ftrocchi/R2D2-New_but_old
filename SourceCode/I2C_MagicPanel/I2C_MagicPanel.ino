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

    //magicPanel.Random();
}

void loop()
{
    magicPanel.Update();

    if (millis() - lastTimeCheck < 10000)
        return;

    lastTimeCheck = millis();

    magicPanel.SetMode((I2C_MagicPanel_Mode::Value)mode);

    mode++;
    if (mode > 15)
        mode = 0;
}

void receiveEvent(int eventCode)
{
    magicPanel.ProcessCommand();
}
