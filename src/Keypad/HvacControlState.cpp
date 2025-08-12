#include <cstdint>
#include "Core/Can.h"

#include "Keypad/Buttons.h"
#include "Keypad/HvacControlState.h"
#include "Keypad/KeypadState.h"

using namespace Keypad::HvacControlState;
using namespace Core::Can;

struct CanHvacControlState
{
	const uint32_t arbitrationId = 0x307;
	union
	{
		uint8_t bytes[ 8 ];
		uint32_t words[ 2 ];
	} data = { 0l, 0l };

	CanHvacControlState( const Keypad::KeypadState::State &keypadState )
	{
		// Zero out all bytes
		for( int i = 0; i < 8; ++i )
		{
			data.bytes[ i ] = 0;
		}


		data.bytes[ 0 ] = ( keypadState.airSource << 6 ) | // RECIRC (bit 6)
						  ( keypadState.rearDemist << 5 ) | // R DEMIST (bit 5)
						  ( keypadState.ac << 7 ); // AC (bit 7)

		data.bytes[ 1 ] = ( keypadState.frontDemist << 1 ) | // F DEMIST (bit 1)
						  ( keypadState.fanReduce << 2 ) | // FAN- (bit 2)
						  ( keypadState.fanIncrease << 3 ) | // FAN+ (bit 3)
						  ( keypadState.hvacOff << 4 ) | // HVAC OFF (bit 4)
						  ( keypadState.hvacAuto << 5 ) | // AUTO (bit 5)
						  ( keypadState.vent << 7 ); // VENT (bit 7)

		data.bytes[ 2 ] = ( keypadState.hazard << 0 ); // HAZARD (bit 0)

		data.bytes[ 3 ] = ( keypadState.tempReduce << 6 ) | // TEMP- (bit 6)
						  ( keypadState.tempIncrease << 7 ); // TEMP+ (bit 7)

		data.bytes[ 4 ] = ( keypadState.unlock << 2 ) | // UNLOCK (bit 2)
						  ( keypadState.dynamicStabilityControl << 4 ) | // DSC (bit 4)
						  ( keypadState.interiorLight << 5 ) | // LAMP (bit 5)
						  ( keypadState.lock << 6 ); // LOCK (bit 6)

		data.bytes[ 5 ] = keypadState.cabinTemp;
		data.bytes[ 6 ] = 0;
		data.bytes[ 7 ] = 0;
	}
};

void OutputHvacControlState()
{
	auto result = Send( CanHvacControlState{ Keypad::KeypadState::GetState() } );


	if( result != SendResult::SEND_FAILED )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
