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

		case I2C_PSI_Mode::March:
			AnimateMarch();
			break;

		case I2C_PSI_Mode::Spin:
			AnimateSpin();
			break;

		case I2C_PSI_Mode::Ring:
			AnimateRing();
			break;

		case I2C_PSI_Mode::UpDown:
			AnimateUpDown();
			break;

		case I2C_PSI_Mode::LeftRight:
			AnimateLeftRight();
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

	// march
	firstColor = true;

	// spin
	spinState = 0;

	// ring
	ringState = 0;
	ringDirection = 1;

	// up down
	upDownState = 0;
	upDownDirection = 1;

	// left right
	leftRightState = 0;
	leftRightDirection = 1;
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
void PSI::AnimateMarch()
{
	int delay = 250;

	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delay)
		return;

	// set the time  
	lastTimeCheck = timeNow;

	ledControl->clearDisplay(device);

	if (firstColor)
	{
		ledControl->setRow(device, 0, patternAtStage[0]);
		ledControl->setRow(device, 1, ~patternAtStage[0]);
		ledControl->setRow(device, 2, patternAtStage[0]);
		ledControl->setRow(device, 3, ~patternAtStage[0]);
		ledControl->setRow(device, 4, patternAtStage[0]);
	}
	else
	{
		ledControl->setRow(device, 0, patternAtStage[4]);
		ledControl->setRow(device, 1, ~patternAtStage[4]);
		ledControl->setRow(device, 2, patternAtStage[4]);
		ledControl->setRow(device, 3, ~patternAtStage[4]);
		ledControl->setRow(device, 4, patternAtStage[4]);
	}

	firstColor = !firstColor;
}


// ----------------------------------------------------------------------------
// SPIN
// ----------------------------------------------------------------------------
void PSI::AnimateSpin() 
{
	int delay = 50;

	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delay)
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
void PSI::AnimateRing()
{
	int delay = 250;

	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delay)
		return;

	// set the time  
	lastTimeCheck = timeNow;

	ledControl->clearDisplay(device);

	switch (ringState)
	{
		case 0: 
			ledControl->setRow(device, 0, B01111000);
			ledControl->setRow(device, 1, B10000100);
			ledControl->setRow(device, 2, B10000100);
			ledControl->setRow(device, 3, B10000100);
			ledControl->setRow(device, 4, B01111000);
			break;

		case 1: 
			ledControl->setRow(device, 0, B00000000);
			ledControl->setRow(device, 1, B01111000);
			ledControl->setRow(device, 2, B01001000);
			ledControl->setRow(device, 3, B01111000);
			ledControl->setRow(device, 4, B00000000);
			break;

		case 2: 
			ledControl->setRow(device, 0, B00000000);
			ledControl->setRow(device, 1, B00000000);
			ledControl->setRow(device, 2, B00110000);
			ledControl->setRow(device, 3, B00000000);
			ledControl->setRow(device, 4, B00000000);
			break;
	}

	ringState += ringDirection;
	if (ringState < 0)
	{
		ringState = 1;
		ringDirection = 1;
	} 
	else if (ringState > 2)
	{
		ringState = 1;
		ringDirection = -1;
	}
}

// ----------------------------------------------------------------------------
// UP / DOWN
// ----------------------------------------------------------------------------
void PSI::AnimateUpDown()
{
	int delay = 250;

	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delay)
		return;

	// set the time  
	lastTimeCheck = timeNow;

	ledControl->clearDisplay(device);

	ledControl->setRow(device, upDownState, B11111111);

	upDownState += upDownDirection;
	if (upDownState < 0)
	{
		upDownState = 1;
		upDownDirection = 1;
	} 
	else if (upDownState > 4)
	{
		upDownState = 3;
		upDownDirection = -1;
	}
}

// ----------------------------------------------------------------------------
// LEFT / RIGHT
// ----------------------------------------------------------------------------
void PSI::AnimateLeftRight()
{
	int delay = 250;

	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delay)
		return;

	// set the time  
	lastTimeCheck = timeNow;

	ledControl->clearDisplay(device);

	switch (leftRightState)
	{
		case 0: 
			ledControl->setRow(device, 0, B10000000);
			ledControl->setRow(device, 1, B10000000);
			ledControl->setRow(device, 2, B10000000);
			ledControl->setRow(device, 3, B10000000);
			ledControl->setRow(device, 4, B10000000);
			break;

		case 1: 
			ledControl->setRow(device, 0, B01000000);
			ledControl->setRow(device, 1, B01000000);
			ledControl->setRow(device, 2, B01000000);
			ledControl->setRow(device, 3, B01000000);
			ledControl->setRow(device, 4, B01000000);
			break;

		case 2: 
			ledControl->setRow(device, 0, B00100000);
			ledControl->setRow(device, 1, B00100000);
			ledControl->setRow(device, 2, B00100000);
			ledControl->setRow(device, 3, B00100000);
			ledControl->setRow(device, 4, B00100000);
			break;

		case 3: 
			ledControl->setRow(device, 0, B00010000);
			ledControl->setRow(device, 1, B00010000);
			ledControl->setRow(device, 2, B00010000);
			ledControl->setRow(device, 3, B00010000);
			ledControl->setRow(device, 4, B00010000);
			break;

		case 4: 
			ledControl->setRow(device, 0, B00001000);
			ledControl->setRow(device, 1, B00001000);
			ledControl->setRow(device, 2, B00001000);
			ledControl->setRow(device, 3, B00001000);
			ledControl->setRow(device, 4, B00001000);
			break;

		case 5: 
			ledControl->setRow(device, 0, B00000100);
			ledControl->setRow(device, 1, B00000100);
			ledControl->setRow(device, 2, B00000100);
			ledControl->setRow(device, 3, B00000100);
			ledControl->setRow(device, 4, B00000100);
			break;
	};

	leftRightState += leftRightDirection;
	if (leftRightState < 0)
	{
		leftRightState = 1;
		leftRightDirection = 1;
	}
	else if (leftRightState > 5)
	{
		leftRightState = 4;
		leftRightDirection = -1;
	}
}




