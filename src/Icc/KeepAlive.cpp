#include "KeepAlive.h"
#include "Core/Can.h"

using namespace Icc::KeepAlive;

struct IccKeepAlive
{
	const unsigned int arbitrationId = 0x425;
	const unsigned char data[ 8 ] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void OutputKeepAlive()
{
	auto result = Core::Can::Send( IccKeepAlive{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
