#include "Acm/KeepAlive.h"
#include "Core/Can.h"
#include <cstdint>

using namespace Acm::KeepAlive;

struct AcmKeepAlive
{
	const uint32_t arbitrationId = 0x425;
	const uint8_t data[ 8 ] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void Acm::KeepAlive::OutputKeepAlive()
{
	auto result = Core::Can::Send<AcmKeepAlive>( AcmKeepAlive{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
