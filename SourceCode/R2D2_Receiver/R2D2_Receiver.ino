#include <SPI.h>
#include <Wire.h>
#include <Ethernet.h>
#include "I2C_Common.h"

#define MAX_FRAME_LENGTH 64
#include <WebSocket.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xE1, 0xB5 };
byte ip[] = { 82, 50, 68, 51 };

WebSocket wsServer;

void onConnect(WebSocket &socket)
{
    Serial.println("onConnect called");
}

void onData(WebSocket &socket, char* dataString, byte frameLength) 
{ 
  Serial.print("Got data: ");
  Serial.write((unsigned char*)dataString, frameLength);
  Serial.println();

    // split the data 
  byte i2cCommand[12];
  int i2cIndex = 0;
  char *savePointer;
  char *token;

  for (token = strtok_r(dataString, "/", &savePointer); token; token = strtok_r(NULL, "/", &savePointer))
  {
    i2cCommand[i2cIndex] = atoi(token);
    i2cIndex++;
  }

  if (i2cCommand[0] < 127) {
    Wire.beginTransmission(i2cCommand[0]);
    for (int i = 1; i < i2cIndex; i++)
      Wire.write(i2cCommand[i]);
    Wire.endTransmission();
  } 
}

void onDisconnect(WebSocket &socket) 
{
  Serial.println("onDisconnect called");
}
    
#define MAX_ARRAY_LENGTH 20
byte gamePadState[MAX_ARRAY_LENGTH];

void setup()
{
    Serial.begin(57600);
    Serial.println("setup");

  Wire.begin();

  Ethernet.begin(mac, ip);
  
  wsServer.registerConnectCallback(&onConnect);
  wsServer.registerDataCallback(&onData);
  wsServer.registerDisconnectCallback(&onDisconnect);  
  wsServer.begin();
  
  delay(100); // Give Ethernet time to get ready

  // play sound so we know we're ready
  Wire.beginTransmission(I2C_DeviceAddress::MP3);
  Wire.write(I2C_MP3_Device::Body);
  Wire.write(I2C_MP3_Command::PlaySound);
  Wire.write(52);
  Wire.endTransmission();
}

void loop()
{
  wsServer.listen();
  
  // Do other stuff here, but don't hang or cause long delays.
  delay(100);
}

//------------------------------------------------------------------
// WEB SOCKET
//------------------------------------------------------------------
void WebSocketSetup()
{
}

void processPS2()
{
    Wire.requestFrom(I2C_DeviceAddress::PS2, 20);

    int index = 0;
    while (Wire.available())
    {
        gamePadState[index] = Wire.read();
        index++;
    }
}
