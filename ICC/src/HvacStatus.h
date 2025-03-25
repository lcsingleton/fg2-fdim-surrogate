#ifndef HVAC_STATUS_H
#define

union HvacStatus
{
	uint8_t bytes[8];
	struct {

		uint8_t something1{ 0x00 };
		uint8_t something2{ 0x00 };
		uint8_t something3{ 0x00 };
		uint8_t internalTemp{ 0xFF };
		uint8_t something5{ 0x00 };
		uint8_t something6{ 0x00 };
		uint8_t something7{ 0x00 };
	};

};

#endif // !HVAC_STATUS_H
