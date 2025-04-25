#ifndef ACM_KEEPALIVE_H
#define ACM_KEEPALIVE_H

#include "Core/Can.h"

namespace ACM {

union IccKeepAlive
{
	unsigned short bytes[8] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void outputKeepAlive()
{
	IccKeepAlive iccKeepAlive;

	Can::send_messae(
        KeepAlive()
	)
	auto result = can_transmit(
		canPort,
		0x425, // Arbitration id
		false, // Not extended 
		false, // Not a request to transmit
		sizeof (iccKeepAlive), // size of payload
		iccKeepAlive.bytes // data to transmit
	);

	if (result >= 0) {
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}
}


#endif // ACM_KEEPALIVE_H
