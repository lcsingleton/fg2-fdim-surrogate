#include "Icc/KeepAlive.h"
#include "Core/Can.h"

using namespace Icc::KeepAlive;
using Core;

struct IccKeepAlive
{
	const uint32_t arbitrationId = 0x425;
	const unsigned short words[ 8 ] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void OutputKeepAlive()
{
	auto result = Can::Send( IccKeepAlive{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
