#include "MagicPanel.h"

MagicPanel::MagicPanel(I2C_DeviceAddress::Value address, LedControl *led)
{
	i2cAddress = address;
	ledControl = led;

}

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