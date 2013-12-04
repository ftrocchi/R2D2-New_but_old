#include "PSI.h"

const int PSI::patternAtStage[9] = { B01010101, B11010101, B10010101, B10110101, B10101010, B00101010, B01101010, B01010101, B01010101 };

PSI::PSI(I2C_DeviceAddress::Value address, LedControl *led, int deviceIndex, int first, int second, int transition) 
{
	  i2cAddress = address;
	  ledControl = led;
	  device = deviceIndex;

	  currentMode = I2C_PSI_Mode::Normal;
  
	  ResetModes(first, second, transition);
}

PSI::~PSI() 
{
}

void PSI::ProcessCommand() 
{
	I2C_PSI_Command::Value command = (I2C_PSI_Command::Value)Wire.read();
  
	switch (command) 
	{
		case I2C_PSI_Command::On:
			On();
			break;
	  
		case I2C_PSI_Command::Off:
			Off();
			break;
	  
		case I2C_PSI_Command::Brightness:
			SetBrightness(Wire.read());
			break;

		case I2C_PSI_Command::Mode:
			SetMode((I2C_PSI_Mode::Value)Wire.read());
			break;
	}
}

void PSI::Update()
{
	switch (currentMode)
	{
		case I2C_PSI_Mode::Normal:
			AnimateNormal();
			break;

		case I2C_PSI_Mode::Spin:
			AnimateSpin();
			break;
	}
}

// ----------------------------------------------------------------------------
// COMMANDS
// ----------------------------------------------------------------------------
void PSI::On() 
{
	for (int row = 0; row < 6; row ++)
		ledControl->setRow(device, row, 255);
}

void PSI::Off() 
{
	ledControl->clearDisplay(device);
}

void PSI::SetBrightness(int brightness) 
{
	ledControl->setIntensity(device, brightness);  
}

void PSI::SetMode(I2C_PSI_Mode::Value mode)
{
	currentMode = mode;
}

// ----------------------------------------------------------------------------
// MODES
// ----------------------------------------------------------------------------
// NORMAL
// ----------------------------------------------------------------------------
void PSI::ResetModes(int first, int second, int transition) 
{
	delayAtStage[0] = first;
	delayAtStage[1] = transition / 3; 
	delayAtStage[2] = delayAtStage[1];
	delayAtStage[3] = delayAtStage[1]; 
	delayAtStage[4] = second; 
	delayAtStage[5] = delayAtStage[1]; 
	delayAtStage[6] = delayAtStage[1]; 
	delayAtStage[7] = delayAtStage[1]; 
	delayAtStage[8] = first; 
  
	stage = 0;
	slideDirection = 1;
	maxStage = 8;
	lastTimeCheck = 0;

	// spin
	spinState = 0;
}

void PSI::AnimateNormal() 
{
	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delayAtStage[stage])
		return;
  
	// set the time  
	lastTimeCheck = timeNow;
  
	// move to next stage
	stage += slideDirection;
  
	// bounds check for stage
	if (stage >= maxStage) {
		stage = maxStage;
		slideDirection = -1;
	} 
	else if (stage <= 0) 
	{
		stage = 0;
		slideDirection = 1;
	}
  
	// set the stage pattern
	ledControl->setRow(device, 0, patternAtStage[stage]);
	ledControl->setRow(device, 1, ~patternAtStage[stage]);
	ledControl->setRow(device, 2, patternAtStage[stage]);
	ledControl->setRow(device, 3, ~patternAtStage[stage]);
	ledControl->setRow(device, 4, patternAtStage[stage]);
}

// ----------------------------------------------------------------------------
// MARCH
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// SPIN
// ----------------------------------------------------------------------------
void PSI::AnimateSpin() 
{
	int spinDelay = 50;

	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < spinDelay)
		return;

	// set the time  
	lastTimeCheck = timeNow;

	ledControl->clearDisplay(device);

	switch (spinState) 
	{
		case 0 : ledControl->setRow(device, 0, B01000000); break;
		case 1 : ledControl->setRow(device, 1, B10000000); break;
		case 2 : ledControl->setRow(device, 2, B10000000); break;
		case 3 : ledControl->setRow(device, 3, B10000000); break;
		case 4 : ledControl->setRow(device, 4, B01000000); break;
		case 5 : ledControl->setRow(device, 4, B00100000); break;
		case 6 : ledControl->setRow(device, 4, B00010000); break;
		case 7 : ledControl->setRow(device, 4, B00001000); break;
		case 8 : ledControl->setRow(device, 3, B00000100); break;
		case 9 : ledControl->setRow(device, 2, B00000100); break;
		case 10: ledControl->setRow(device, 1, B00000100); break;
		case 11: ledControl->setRow(device, 0, B00001000); break;
		case 12: ledControl->setRow(device, 0, B00010000); break;
		case 13: ledControl->setRow(device, 0, B00100000); break;
	};

	spinState++;
	if (spinState == 14)
		spinState = 0;
}

// ----------------------------------------------------------------------------
// RING
// ----------------------------------------------------------------------------



