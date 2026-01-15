// CAN System
#include <libopencm3/stm32/can.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

// Register definitions for the MCU

#include "Core/Can.h"

using namespace Core::Can;

constexpr auto CanPort = CAN1;

Core::Can::SendResult Core::Can::SendPayload( unsigned long arbitrationId, const unsigned char* data )
{

	auto result = can_transmit( CanPort,
								arbitrationId, // Arbitration id
								false, // Not extended
								false, // Not a request to transmit
								8, // size of payload
								const_cast<unsigned char*>(data) // data to transmit
	);

	if( result == SEND_SUCCESS_QUEUE_1 || result == SEND_SUCCESS_QUEUE_2 || result == SEND_SUCCESS_QUEUE_3 )
	{
		return static_cast<SendResult>( result );
	}

	return SendResult::SEND_FAILED;
}

// Interupt handler for the CAN FIFO 0 and FIFO 1 message pending interrupts
void can1_rx0_isr( void )
{
	uint32_t id;
	bool isExtended;
	bool isRequestToTransmit;
	uint8_t filterMatchId;
	uint8_t payloadSize;
	uint8_t payload[8];

	can_receive(
		CanPort, // Working with CAN1 Can Controller
		0, // FIFO 0
		true, // Release the FIFO after reading
		&id, // Pointer to store the message ID
		&isExtended, // Pointer to store if the message ID is extended
		&isRequestToTransmit, // Pointer to store if this is a request of transmission
		&filterMatchId, // Pointer to store the filter match ID
		&payloadSize, // Pointer to store the payload size
		payload, // Pointer to store the payload data
		nullptr
	);

}

void can1_rx1_isr( void )
{
	uint32_t id;
	bool isExtended;
	bool isRequestToTransmit;
	uint8_t filterMatchId;
	uint8_t payloadSize;
	uint8_t payload[8];

	can_receive(
		CanPort, // Working with CAN1 Can Controller
		1, // FIFO 1
		true, // Release the FIFO after reading
		&id, // Pointer to store the message ID
		&isExtended, // Pointer to store if the message ID is extended
		&isRequestToTransmit, // Pointer to store if this is a request of transmission
		&filterMatchId, // Pointer to store the filter match ID
		&payloadSize, // Pointer to store the payload size
		payload, // Pointer to store the payload data
		nullptr
	);


}

void Core::Can::InitCanSystem()
{
	// Enable the clock for the Port A, the CAN1 is on Port A
	rcc_periph_clock_enable( RCC_GPIOA );

	// Enable the clock for CAN1
	rcc_periph_clock_enable( RCC_CAN1 );

	// Set up the GPIO pins for CAN1
	gpio_mode_setup( GPIOA, // Port A
					 GPIO_MODE_AF, // Set as alternate function mode
					 GPIO_PUPD_NONE, // Disable the pull up or down
					 GPIO11 | GPIO12 // Pins 11 and 12 - the CAN1 RX and TX pins
	);

	gpio_set_af( GPIOA, // Port A
				 GPIO_AF9, // Alternate Function 9 (0 indexed) for PortA11 and PortA12 for CAN1
				 GPIO11 | GPIO12 // Pins 11 and 12
	); // Set the selected alternate function of the GPIO pins

	// Set the GPIO pins to 50MHz speed
	gpio_set_output_options( GPIOA, // Port A
							 GPIO_OTYPE_PP, // Push Pull Output Type
							 GPIO_OSPEED_50MHZ, // 50MHz Speed
							 GPIO11 | GPIO12 // Pins 11 and 12
	);


	// Reset the inbuilt CAN1 Can Controller
	can_reset( CanPort );


	// Baud rate = 1/ Bit time
	// 1 / 0.000008s = 125000 = 125 kbps
	// Bit time = tPCLK + ( tPCLK * Time Segment 1 ) + ( tPCLK * Time Segment 2 )
	// tPCLK = 1 / 25MHz (APB1Clk) * 20 (Baud Rate Prescaler) = 0.0000008s
	// 0.0000008s + ( 0.0000008s * 7 ) + ( 0.0000008s * 2) =  0.000008s

	// Initialize the CAN1 Can Controller
	auto result =
			can_init( CanPort, // Working with CAN1 Can Controller
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
					  false, // Disable transmission loopback, we know what we're sending, we don't want it echoed back
					  false // Disable silent mode, we want to send and receive messages, and ack messages on the bus
			);

	if( result != 0 )
	{
		// If the result is not 0, then the initialization failed
		return;
	}

	// Filter init mode
	can_filter_init( CanPort, // Working with CAN1 Can Controller
					 false, // 32 bit filter scale
					 0, // Filter number 0
					 0, // Filter ID low bits
					 0, // Filter ID high bits
					 0, // FIFO 0 for filter
					 true // Enable the filter
	);


	// Set the Can Port's FIFO registers as empty and ready to receive
	can_fifo_release( CanPort, 0 );
	can_fifo_release( CanPort, 1 );

	can_enable_irq( CanPort,
					CAN_IER_FMPIE0 | CAN_IER_FMPIE1 // Enable FIFO 0 and FIFO 1 message pending register flags
	);

	// Enable the CAN1 receive flags to trigger the interrupt handler code
	nvic_enable_irq( NVIC_CAN1_RX0_IRQ );
	nvic_enable_irq( NVIC_CAN1_RX1_IRQ );
}
