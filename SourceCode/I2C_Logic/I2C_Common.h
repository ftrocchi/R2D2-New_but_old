#ifndef _I2C_COMMON_h
#define _I2C_COMMON_h

struct I2C_DeviceAddress {
	enum Value 
	{
		RearLogicDisplay = 10
	};
};

struct I2C_Logic_Device {
	enum Value 
	{
		Logic = 0,
		PSI = 1
	};
};

struct I2C_PSI_Commands {
	enum Value 
	{
		On = 0,
		Off = 1,
		Brightness = 2
	};
};

#endif

