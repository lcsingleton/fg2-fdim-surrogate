#include "Keypad/MediaControlState.h"
#include "Core/Can.h"
#include <cstdint>

using namespace Keypad::MediaControlState;

struct CanMediaControlState
{
	const uint32_t arbitrationId = 0x2FC;
	const uint8_t data[ 8 ] = { 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};


void Keypad::MediaControlState::OutputMediaControlState()
{
	auto result = Core::Can::Send( CanMediaControlState{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
