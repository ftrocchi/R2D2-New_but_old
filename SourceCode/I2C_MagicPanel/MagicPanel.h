#ifndef _MAGICPANEL_h
#define _MAGICPANEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>
#include <LedControl.h>
#include "I2C_Common.h"


class MagicPanel
{
	private:
		LedControl *ledControl;
		I2C_DeviceAddress::Value i2cAddress;
		bool vMagicPanel[8][8];
		unsigned char panel[16];
		I2C_MagicPanel_Mode::Value currentmode;
		unsigned long lastTimeCheck;

		int state;
		int state2;
		int direction;

		// Alert
		void AnimateAlert();
//		bool alertState;

		// ToggleTopBottom
		void AnimateToggleTopBottom();
//		bool toggleTopBottomState;

		// ToggleLeftRight
		void AnimateToggleLeftRight();
//		bool toggleLeftRightState;

		// ToggleQuad
		void AnimateToggleQuad();
//		bool toggleQuadState;

		// Quad Cycle Counter Clockwise
		void AnimateQuadCycleCounterClockwise();
//		int quadCycleCounterClockwiseState;

		void AnimateQuadCycleClockwise();
//		int quadCycleClockwiseState;

		// Trace Up
		void AnimateTraceUp();
//		int traceUpState;

		// Trace Down
		void AnimateTraceDown();
//		int traceDownState;

		// Trace Up Down
		void AnimateTraceUpDown();
//		int traceUpDownState;
//		int traceUpDownDirection;

		// Trace Left
		void AnimateTraceLeft();
//		int traceLeftState;

		// Trace Right
		void AnimateTraceRight();
//		int traceRightState;

		// Trace Left Right
		void AnimateTraceLeftRight();
//		int traceLeftRightState;
//		int traceLeftRightDirection;

		// Single Led Test
		void AnimateSingleLEDTest();
//		int singleLEDTestRow;
//		int singleLEDTestCol;

		// Double LED Test
		void AnimateDoubleLEDTest();
//		int doubleLEDTestRow;
//		int doubleLEDTestCol;

		// Animate String
		void AnimateString();
		bool feedGridLeftComplete;
		int letterIndex;
		String englishString;

		void MapAndPrint();
		void MapBoolGrid();
		void PrintGrid();
		bool IsTimeForStateChange(int delay, bool clear = false);
		void SetRow(int ledRow, unsigned char rowState);
		void SetCol(int ledCol, unsigned char colState);
		unsigned char GetCol(int ledCol);
		void ClearButDoNotShow(bool isOn);
		void DrawLetter(char letter);
		void FeedGridLeft(unsigned char newColumn);
		void ResetModeVariables();

	public:
		MagicPanel(I2C_DeviceAddress::Value i2cAddress, LedControl *led);

		void ProcessCommand();
		void Update();

		void SetBrightness(int brightness);
		void Off();
		void On();
		void SetMode(I2C_MagicPanel_Mode::Value mode);
};

#endif

