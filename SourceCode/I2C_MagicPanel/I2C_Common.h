#ifndef _I2C_COMMON_h
#define _I2C_COMMON_h

struct I2C_DeviceAddress
{
	enum Value 
	{
		RearLogicDisplay = 10,
		MagicPanel = 20
	};
};

struct I2C_Logic_Device 
{
	enum Value 
	{
		Logic = 0,
		PSI = 1
	};
};

struct I2C_PSI_Command 
{
	enum Value 
	{
		On = 0,
		Off = 1,
		Brightness = 2,
		Mode = 3
	};
};

struct I2C_PSI_Mode
{
	enum Value
	{
		Normal = 0,
		March = 1,
		Spin = 2,
		Ring = 3,
		UpDown = 4,
		LeftRight = 5
	};
};

struct I2C_MagicPanel_Mode
{
	enum Value
	{
		ToggleTopBottom = 0,
		Alert = 1,
		TraceUp = 2,
		TraceDown = 3,
		TraceUpDown = 4,
		TraceLeft = 5,
		TraceRight = 6,
		TraceLeftRight = 7,
		SingleLEDTest = 8,
		DoubleLEDTest = 9,
		String = 10
	};
};

#endif

