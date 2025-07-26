// CAN System
 #include <libopencm3/stm32/can.h>

// Register definitions for the MCU
// #include <Chip/Unknown/STMicro/STM32F41x/CAN1.hpp>

#include "Core/Can.h"

using namespace Core::Can;

constexpr auto CanPort = CAN1;

SendResult SendPayload( uint32_t arbitrationId, uint8_t (&data)[ 8 ] ) {

	auto result = can_transmit( CanPort,
								arbitrationId, // Arbitration id
								false, // Not extended
								false, // Not a request to transmit
								8, // size of payload
								data // data to transmit
	);

	if( result == SEND_SUCCESS_QUEUE_1 || result == SEND_SUCCESS_QUEUE_2 || result == SEND_SUCCESS_QUEUE_3 )
	{
		return static_cast<SendResult>(result);
	}

	return SendResult::SEND_FAILED;
}

void InitCanSystem()
{
	// Reset the inbuilt CAN1 Can Controller
	can_reset( CanPort );
	auto result = can_init( CanPort, // Working with CAN1 Can Controller
							false, // Time triggered comms off
							true, // Auto bus off management enabled
							true, // Auto wake up enabled
							true, // Automatic re-transmission enable
							false, // Keep the most recent CAN frames when FIFO is full
							false, // Send the most recent CAN frames when FIFO is full
							CAN_BTR_SJW_1TQ, // Resync time quanta jump width
							CAN_BTR_TS1_7TQ, // Time Segment 1 Quanta width
							CAN_BTR_TS2_2TQ, // Time Segment 2 Quanta width
							19, // Baud Rate prescalar - register values are off by one
							false, // Disable transmission loopback
							false // not silent ??
	);

	// Baud rate = 1/ Bit time
	// 1 / 0.000008s = 125000 = 125 kbps
	// Bit time = tPCLK + ( tPCLK * Time Segment 1 ) + ( tPCLK * Time Segment 2 )
	// tPCLK = 1 / 25MHz (APB1Clk) * 20 (Baud Rate Prescaler) = 0.0000008s
	// 0.0000008s + ( 0.0000008s * 7 ) + ( 0.0000008s * 2) =  0.000008s


	// Set the Can Port's FIFO registers as empty and ready to receive
	can_fifo_release( CanPort, 0 );
	can_fifo_release( CanPort, 1 );
}
