#include "Keypad/CabinTempSensor.h"

using namespace Keypad::CabinTempSensor;

const auto ntcValue = 10000u;
const auto scalar = 639.5, exponent = -0.1332, offset = -162.5;

void UpdateCabinTempSensor()
{

	/*
	withPin( tempSensor.sensePin,
		 []( unsigned mcuPin )
		 {
			 auto ntcVoltage = ( analogRead( mcuPin ) * 5.0 ) / 1023.0;
			 auto ntcResistance = ntcValue * ( ( 5.0 / ntcVoltage ) - 1 );
			 // auto tempKelvin = a * pow(ntcResistance, exponent) + offset;

			 // TODO do something with the temp now that we've calculated it.
		 } );
		  */
}
