#include "KeepAlive.h"
#include "Core/Can.h"
#include <cstdint>

using namespace Icc::KeepAlive;

struct IccKeepAlive
{
	const uint32_t arbitrationId = 0x425;
	const uint8_t data[ 8 ] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void Icc::KeepAlive::OutputKeepAlive()
{
	auto result = Core::Can::Send( IccKeepAlive{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
