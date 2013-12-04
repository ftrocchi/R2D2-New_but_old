#ifndef _I2C_COMMON_h
#define _I2C_COMMON_h

struct I2C_DeviceAddress
{
	enum Value 
	{
		RearLogicDisplay = 10
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

#endif

