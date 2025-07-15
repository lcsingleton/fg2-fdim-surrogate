#include "Keypad/MediaControlState.h"
#include "Core/Can.h"

using namespace Keypad::MediaControlState;

struct CanMediaControlState
{
	const unsigned int arbitrationId = 0x2FC;
	const unsigned char data[ 8 ] = { 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};


void OutputMediaControlState()
{
	auto result = Core::Can::Send( CanMediaControlState{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
