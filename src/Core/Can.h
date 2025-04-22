#ifndef CAN_H
#define CAN_H

#include <libopencm3/stm32/can.h>

namespace Core
{
	namespace Can
	{

		constexpr auto CanPort = CAN1;

		enum SendResult
		{
			SEND_FAILED,
			SEND_SUCCESS_QUEUE_1,
			SEND_SUCCESS_QUEUE_2,
			SEND_SUCCESS_QUEUE_3,
		};

		template<typename Type>
		SendResult send( Type message )
		{
			auto result = can_transmit( CanPort,
										message.arbitationId, // Arbitration id
										false, // Not extended
										false, // Not a request to transmit
										8, // size of payload
										message.data // data to transmit
			);
			if( result == SEND_SUCCESS_QUEUE_1 || result == SEND_SUCCESS_QUEUE_2 || result == SEND_SUCCESS_QUEUE_3 )
			{
				return result;
			}
			return SendResult::SEND_FAILED;
		}
	}

	void setupCanComms()
	{
		// Reset the inbuilt CAN1 Can Controller
		can_reset( canPort );
		auto result = can_init(
			canPort, // Working with CAN1 Can Controller
			false, // Time triggered comms off
			true, // Auto bus off management enabled
			true, // Auto wake up enabled
			true, // Automatic re-transmission enable
			false, // Keep the most recent CAN frames when FIFO is full
			false, // Send the most recent CAN frames when FIFO is full
			CAN_BTR_SJW_1TQ, // Resync time quanta jump width
			CAN_BTR_TS1_6TQ, // Time Segment 1 Quanta width
			CAN_BTR_TS2_1TQ, // Time Segment 2 Quanta width
			99, // Baud Rate prescalar - register values are off by one
			false, // Disable transmission loopback
			false // not silent ??
		 );

		// Baud rate = 1/ Bit time
		// 1 / 0.000008s = 125000 = 125 kbps
		// Bit time = tPCLK + ( tPCLK * Time Segment 1 ) + ( tPCLK * Time Segment 2 )
		// tPCLK = 1 / 100MHz = 0.000001s
		// 0.000001s + ( 0.000001s * 6 ) + ( 0.000001s *) =  0.000008s

		if ( result )

			can_fifo_release(canPort, 0);
		can_fifo_release(canPort, 1);

	}
} // namespace Can
} // namespace Core
#endif // CAN_H
