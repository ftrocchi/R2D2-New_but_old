#include "MagicPanel.h"

MagicPanel::MagicPanel(I2C_DeviceAddress::Value address, LedControl *led)
{
	i2cAddress = address;
	ledControl = led;

	toggleTopBottomState = true;
}

void MagicPanel::Update()
{
	switch (currentmode)
	{
		case I2C_MagicPanel_Mode::ToggleTopBottom:
			AnimateToggleTopBottom();
			break;
	};
}

// ----------------------------------------------------------------------------
// COMMANDS
// ----------------------------------------------------------------------------
void MagicPanel::SetBrightness(int brightness)
{
	ledControl->setIntensity(0, brightness);
	ledControl->setIntensity(1, brightness);
}

void MagicPanel::Off()
{
	ledControl->clearDisplay(0);
	ledControl->clearDisplay(1);
}

void MagicPanel::On()
{
	for(int row=0;row<8;row++) 
	{
		for(int col=0;col<8;col++) 
		{
			vMagicPanel[row][col]=true;
		}
	}

  MapAndPrint();
}

void MagicPanel::SetMode(I2C_MagicPanel_Mode::Value mode)
{
	currentmode = mode;
}

// ----------------------------------------------------------------------------
// MODES
// ----------------------------------------------------------------------------
void MagicPanel::AnimateToggleTopBottom()
{
	if (!IsTimeForStateChange(250))
		return;

	if (toggleTopBottomState)
	{
		for (int row = 0; row < 8; row++)
		{
			ledControl->setRow(0, row, B11111111);
			ledControl->setRow(1, row, B00000000);
		}
	}
	else
	{
		for (int row = 0; row < 8; row++)
		{
			ledControl->setRow(0, row, B00000000);
			ledControl->setRow(1, row, B11111111);
		}
	}

	toggleTopBottomState = !toggleTopBottomState;
}

void MagicPanel::MapAndPrint() 
{
	MapBoolGrid();
	PrintGrid();
}

void MagicPanel::MapBoolGrid()
{
	for(int Row=0; Row<8; Row++)
	{
		panel[2 * Row]     = 128 * vMagicPanel[Row][7] + 
			                  64 * vMagicPanel[Row][6] + 
							  32 * vMagicPanel[Row][5] + 
							  16 * vMagicPanel[Row][4];       // 0, 2, 4, 6, 8, 10, 12, 14

		panel[2 * Row + 1] =   8 * vMagicPanel[Row][3] + 
			                   4 * vMagicPanel[Row][2] +
							   2 * vMagicPanel[Row][1] + 
								   vMagicPanel[Row][0];            // 1, 3, 5, 7, 9, 11, 13, 15
	}
}

void MagicPanel::PrintGrid(){
	for(int i=0; i<16; i++)
	{
		if(i<8)
		{
			ledControl->setRow(0, i, panel[i]);
		}
		else
		{
			ledControl->setRow(1, i-8, panel[i]);
		}
	}
}

bool MagicPanel::IsTimeForStateChange(int delay)
{
	unsigned long timeNow = millis();
  
	// early exit if we don't need to do anything
	if (timeNow - lastTimeCheck < delay)
		return false;

	// set the time  
	lastTimeCheck = timeNow;

	// clear the device
	ledControl->clearDisplay(0);
	ledControl->clearDisplay(1);

	return true;
}