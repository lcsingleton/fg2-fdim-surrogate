#include "Core/Can.h"

#include "Keypad/Buttons.h"
#include "Keypad/HvacControlState.h"
#include "Keypad/KeypadState.h"

using namespace Keypad::HvacControlState;
using Core::Can;

struct CanHvacControlState
{
	const uint32_t arbitrationId = 0x407;
	union
	{
		uint8_t bytes[ 8 ];
		uint32_t dwords[ 2 ];
	} data = { 0l, 0l };

	CanHvacControlState( const KeypadStatus &keypadStatus)
	{

		// auto x = keypadStatus.fanIncrease | static_cast<unsigned long>( keypadStatus.hvacOff );
		data.dwords[ 0 ] = static_cast<unsigned long>(
				keypadStatus.airSource) | keypadStatus.rearDemist | keypadStatus.ac | keypadStatus.frontDemist |
				keypadStatus.fanReduce | keypadStatus.fanIncrease | keypadStatus.hvacOff | keypadStatus.hvacAuto |
				keypadStatus.vent | keypadStatus.hazard | keypadStatus.tempReduce | keypadStatus.tempIncrease |
				keypadStatus.unlock | keypadStatus.dynamicStabilityControl | keypadStatus.interiorLight | keypadStatus.lock );

		data.dwords[ 1 ] = keypadStatus.cabinTemp;
	}
};

void OutputHvacControlState()
{
	auto result = Can::Send( CanHvacControlState{ HvacStatus{} } );


	if( result != Can::SendResult::SEND_FAILED )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
