#ifndef HVAC_STATUS_H
#define HVAC_STATUS_H
#include "../Core/Can.h"

struct CanHvacStatus
{
	const uint32_t arbitrationId = 0x407;
	unsigned short bytes[ 8 ] = { 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00 };
};

struct HvacStatus
{
	uint8_t cabinTemp = 0x00u;
	auto recirc = false;
	auto rearDemist = false;
	auto acCompressor = false;
	auto frontDemist = false;
	auto fanReduce = false;
	auto fanIncrease = false;
	auto hvacOff = false;
	auto hvacAuto = false;
	auto vent = false;
	auto hazard = false;
	auto tempReduce = false;
	auto tempIncrease = false;
	auto unlock = false;
	auto lock = false;
	auto dynamicStabilityControl = false;
	auto interiorLight = false;
};

void outputHvacStatus()
{
	auto result = Core::Can::send(
		CanHvacStatus{
			HvacStatus {}
		}
	);

	if( result != Core::Can::SEND_FAILED )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}

#endif // !HVAC_STATUS_H

