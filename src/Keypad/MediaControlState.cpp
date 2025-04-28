#include "Keypad/MediaControlState.h"
#include "Core/Can.h"

using namespace Keypad::MediaControlState;
using Core;

struct CanMediaControlState
{
	const uint32_t arbitrationId = 0x2FC;
	const unsigned short words[ 8 ] = { 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};


void MediaControlState::OutputMediaControlState()
{
	auto result = Can::Send( CanMediaControlState{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
