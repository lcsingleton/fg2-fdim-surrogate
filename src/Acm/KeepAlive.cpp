#include "Acm/KeepAlive.h"
#include "Core/Can.h"

using namespace Acm::KeepAlive;

struct AcmKeepAlive
{
	const unsigned int arbitrationId = 0x425;
	const unsigned char data[ 8 ] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void OutputKeepAlive()
{
	auto result = Core::Can::Send<AcmKeepAlive>( AcmKeepAlive{} );

	if( result >= 0 )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
