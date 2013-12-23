#ifndef _I2C_COMMON_h
#define _I2C_COMMON_h

struct I2C_DeviceAddress
{
    enum Value 
    {
        RearLogicDisplay = 10,
        MagicPanel = 20,
        PS2 = 110,
        MP3 = 111
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

struct I2C_MagicPanel_Command
{
    enum Value 
    {
        On = 0,
        Off = 1,
        Brightness = 2,
        Mode = 3,
        Random = 4
    };
};

struct I2C_MagicPanel_Mode
{
    enum Value
    {
        Alert = 0,
        ToggleTopBottom = 1,
        ToggleLeftRight = 2,
        ToggleQuad = 3,
        QuadCycleCounterClockwise = 4,
        QuadCycleClockwise = 5,
        TraceUp = 6,
        TraceDown = 7,
        TraceUpDown = 8,
        TraceLeft = 9,
        TraceRight = 10,
        TraceLeftRight = 11,
        SingleLEDTest = 12,
        DoubleLEDTest = 13,
        RandomPixel = 14,
        String = 15
    };
};

struct I2C_MP3_Device
{
    enum Value
    {
        Body = 0,
        Dome = 1,
        Feet = 2,
        None = 4
    };
};

struct I2C_MP3_Command
{
    enum Value
    {
        PlaySound = 0,
        SetVolume = 1
    };
};

#endif

