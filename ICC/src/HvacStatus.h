#ifndef HVAC_STATUS_H
#define HVAC_STATUS_H



union HvacStatus
{
	uint8_t bytes[8] = { 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00 };
	struct {

		uint8_t something1;
		uint8_t something2;
		uint8_t something3;
		uint8_t internalTemp;
		uint8_t something5;
		uint8_t something6;
		uint8_t something7;
	};

};

void outputHvacStatus()
{
	HvacStatus hvacStatus;


	auto result = can_transmit(
		canPort,
		0x307, // Arbitration id
		false, // Not extended 
		false, // Not a request to transmit
		sizeof (hvacStatus.bytes), // size of payload
		hvacStatus.bytes // data to transmit
	);

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}

#endif // !HVAC_STATUS_H

