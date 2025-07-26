// Interrupt RegisterControls
#include <libopencm3/cm3/nvic.h>

#include "Keypad/RotaryDial.h"

using namespace Keypad::RotaryDial;

const int encoderStates[ 4 ][ 4 ] = {
	{ 0, -1, 1, 0 },
	{ 1, 0, 0, -1 },
	{ -1, 0, 0, 1 },
	{ 0, 1, -1, 0 },
};

void ReadRotaryState()
{

	// const auto lowBitPin = pinMap[ encoder.signalPinA ].mcuPin;
	// const auto highBitPin = pinMap[ encoder.signalPinC ].mcuPin;

	// auto state = ( digitalRead( highBitPin ) << 1 ) | digitalRead( lowBitPin );

	// count += encoderStates[prevState][state];
	// if (state != prevState)
	//{
	//	Serial.print(state, DEC);
	//	Serial.print(' ');
	//	Serial.print(prevState, DEC);
	//	Serial.print(' ');
	//	Serial.println(count, DEC);
	// }
}


void InitRotaryDialSystem()
{
	// Set up GPIO Pins

	// Set and attach Interrupt
}
