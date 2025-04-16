#ifndef ICCKEEPALIVE_H
#define ICCKEEPALIVE_H


union IccKeepAlive
{
	uint8_t bytes[8] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
};

void outputKeepAlive()
{
	IccKeepAlive iccKeepAlive;

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

#endif