#include <SendOnlySoftwareSerial.h>
#include <MP3Trigger.h>
#include <Wire.h>
#include "I2C_Common.h"

int RXLED = 17;
int BODYSERIAL = 15;
int DOMESERIAL = 14;
int FEETSERIAL = 16;

SendOnlySoftwareSerial bodySerial(BODYSERIAL);
SendOnlySoftwareSerial domeSerial(DOMESERIAL);
SendOnlySoftwareSerial feetSerial(FEETSERIAL);
MP3Trigger bodyTrigger;
MP3Trigger domeTrigger;
MP3Trigger feetTrigger;

void SetVolume(I2C_MP3_Device::Value board, int value)
{
    switch (board)
    {
        case I2C_MP3_Device::Body:
            bodyTrigger.setVolume(value);
            break;

        case I2C_MP3_Device::Dome:
            domeTrigger.setVolume(value);
            break;

        case I2C_MP3_Device::Feet:
            feetTrigger.setVolume(value);
            break;
    };
}

void PlaySound(I2C_MP3_Device::Value board, int value)
{
    switch (board)
    {
        case I2C_MP3_Device::Body:
            bodyTrigger.play(value);
            break;

        case I2C_MP3_Device::Dome:
            domeTrigger.play(value);
            break;

        case I2C_MP3_Device::Feet:
            feetTrigger.play(value);
            break;
    };
}

void SetLEDs(I2C_MP3_Device::Value board)
{
    digitalWrite(RXLED, board == I2C_MP3_Device::Body || board == I2C_MP3_Device::Feet ? LOW : HIGH);
    board == I2C_MP3_Device::Dome || board == I2C_MP3_Device::Feet ? TXLED1 : TXLED0;
}

void setup()
{
    pinMode(RXLED, OUTPUT);

    bodyTrigger.setup(&bodySerial);
    bodySerial.begin(MP3Trigger::serialRate());
    SetVolume(I2C_MP3_Device::Body, 0);

    domeTrigger.setup(&domeSerial);
    domeSerial.begin(MP3Trigger::serialRate());
    SetVolume(I2C_MP3_Device::Dome, 0);

    feetTrigger.setup(&feetSerial);
    feetSerial.begin(MP3Trigger::serialRate());
    SetVolume(I2C_MP3_Device::Feet, 0);

    Wire.begin(I2C_DeviceAddress::MP3);
    Wire.onReceive(receiveEvent);

    delay(3000);

    PlaySound(I2C_MP3_Device::Body, 52);
}

void loop()
{
    delay(2000);
    SetLEDs(I2C_MP3_Device::None);
}

void receiveEvent(int eventCode)
{
    I2C_MP3_Device::Value board = (I2C_MP3_Device::Value)Wire.read();
    I2C_MP3_Command::Value command = (I2C_MP3_Command::Value)Wire.read();
    int value = Wire.read();

    SetLEDs(board);

    switch (command)
    {
        case I2C_MP3_Command::PlaySound:
            PlaySound(board, value);
            break;

        case I2C_MP3_Command::SetVolume:
            SetVolume(board, value);
            break;
    };
}



