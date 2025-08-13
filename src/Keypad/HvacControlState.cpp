#include <cstdint>
#include <array>
#include "Core/BitPack.h"
#include "Core/Can.h"

#include "Keypad/HvacControlState.h"
#include "Keypad/KeypadState.h"

using namespace Keypad::HvacControlState;
using namespace Core::Can;
using namespace Core::BitPack;

struct CanHvacControlState
{
	const uint32_t arbitrationId = 0x307;
	std::array<uint8_t, 8> data;

	CanHvacControlState( const Keypad::KeypadState::State &keypadState )
	{
		data = PackCanData(
			BoolField(keypadState.ac),
			BoolField(keypadState.airSource),
			BoolField(keypadState.rearDemist),
	        FixedField<0, 5>(), // Next 5 bits unused for Single Zone Climate Control
			BoolField(keypadState.vent),
	        FixedField<0, 1>(), // Pack 1 bit with 0
			BoolField(keypadState.hvacAuto),
			BoolField(keypadState.hvacOff),
			BoolField(keypadState.fanIncrease),
			BoolField(keypadState.fanReduce),
			BoolField(keypadState.frontDemist),
			FixedField<0, 1>(), // Pack 1 bit with 0
			BoolField(keypadState.tempIncrease),
			BoolField(keypadState.tempReduce),
			BoolField(keypadState.hazard),
			FixedField<0, 1>(), // Pack 1 bit with 0
			BoolField(keypadState.lock),
			BoolField(keypadState.interiorLight),
			BoolField(keypadState.dynamicStabilityControl),
			FixedField<0, 1>(), // Pack 1 bit with 0
			BoolField(keypadState.unlock),
			Field<uint8_t, 8>(keypadState.cabinTemp), // Cabin Temp occupied a whole byte
			FixedField<0, 1>() // Pack the remainder of the 64 bits with 0 
		).bytes;
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
