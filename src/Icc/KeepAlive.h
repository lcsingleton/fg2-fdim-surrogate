#ifndef ICC_KEEPALIVE_H
#define ICC_KEEPALIVE_H

#include <cstdint>

#include "Core/Can.h"

namespace Icc {

struct KeepAlive
{
	const uint32_t arbitrationId = 0x425;
	const unsigned short words[8] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void outputKeepAlive()
{
	auto result = Core::Can::send<KeepAlive>( KeepAlive{} );

	// auto result = can_transmit(
	// 	canPort,
	// 	0x425, // Arbitration id
	// 	false, // Not extended
	// 	false, // Not a request to transmit
	// 	sizeof (iccKeepAlive), // size of payload
	// 	iccKeepAlive.bytes // data to transmit
	// );

	if (result >= 0) {
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}

}

#endif // ICC_KEEPALIVE_H
