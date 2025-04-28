#include "Core/Can.h"

#include "Keypad/HvacControlState.h"
#include "Keypad/Buttons.h"

using namespace Keypad::HvacControlState;
using Core::Can;

struct CanHvacControlState
{
	const uint32_t arbitrationId = 0x407;
	union
	{
		unsigned short bytes[ 8 ];
		unsigned long dwords[ 2 ];
	} data = { 0l, 0l };

	CanHvacStatus( const HvacStatus &hvacStatus )
	{

		//auto x = hvacStatus.fanIncrease | static_cast<unsigned long>( hvacStatus.hvacOff );
		data.dwords[ 0 ] = static_cast<unsigned long>(
				hvacStatus.airSource) | hvacStatus.rearDemist | hvacStatus.ac | hvacStatus.frontDemist |
				hvacStatus.fanReduce | hvacStatus.fanIncrease | hvacStatus.hvacOff | hvacStatus.hvacAuto |
				hvacStatus.vent | hvacStatus.hazard | hvacStatus.tempReduce | hvacStatus.tempIncrease |
				hvacStatus.unlock | hvacStatus.dynamicStabilityControl | hacStatus.interiorLight | hvacStatus.lock );

		data.dwords[ 1 ] = hvacStatus.cabinTemp;
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
