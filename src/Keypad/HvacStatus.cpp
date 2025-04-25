#include "Core/Can.h"

#include "Keypad/HvacStatus.h"
#include "Keypad/Buttons.h"

using namespace Keypad;
using Core::Can;

struct HvacStatus
{
	// Byte 0
	Button<31> ac;
	Button<30> airSource;
	Button<29> rearDemist;

	// Byte 1
	Button<27> vent;
	Button<25> hvacAuto;
	Button<24> hvacOff;
	Button<23> fanIncrease;
	Button<22> fanReduce;
	Button<21> frontDemist;

	// Byte 2
	Button<15> tempIncrease;
	Button<14> tempReduce;
	Button<8> hazard;

	// Byte 3
	Button<6> lock;
	Button<5> interiorLight;
	Button<4> dynamicStabilityControl;
	Button<2> unlock;

	// Byte 4
	DataPoint<unsigned char, 0, 3> cabinTemp;
};

struct CanHvacStatus
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

void OutputHvacStatus()
{
	auto result = Can::Send( CanHvacStatus{ HvacStatus{} } );


	if( result != Can::SendResult::SEND_FAILED )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
