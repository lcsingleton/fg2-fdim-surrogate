
// Reset and Clock Controls
#include <libopencm3/stm32/rcc.h>

//
#include <libopencm3/stm32/gpio.h>

// Timer Features
#include <libopencm3/cm3/systick.h>

// Interrupt RegisterControls
#include <libopencm3/cm3/nvic.h>

// CAN System
#include <libopencm3/stm32/can.h>

#include "Timer.h"

constexpr auto canPort = CAN1;

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



	 can_fifo_release(canPort, 0);
	 can_fifo_release(canPort, 1);

}

void setup()
{

	// initialize serial to 38.4kbps - this is the speed that head units listen at
	Serial.begin(115200);

	// setupSensorPins();
	// setupKeypadPins();
	setupCanComms();

}


struct TimerFlags
{
	short _25ms = 25;
	short _100ms = 100;
	short _125ms = 125;
	short _500ms = 500;
	short _10000ms = 10000;
	unsigned long lastMs = -1l;
};

TimerFlags tf;

unsigned long getTfDeltaMs(unsigned long currentMs)
{
	auto distanceToUnderflow = 1l - tf.lastMs;


	// Check if currentMs has overflowed since lastMs was set
	if (currentMs < tf.lastMs)
	{
		Serial.println("Overflow since last exection");
		// overflow has happened
		auto lastToOverflowMs = -1l - tf.lastMs;
		return lastToOverflowMs + currentMs;
	}

	auto diff = currentMs - tf.lastMs;
	return diff;
}

void tickTimerFlags()
{
	auto ms = millis();
	auto deltaMs = getTfDeltaMs(ms);

	tf._25ms -= deltaMs;
	tf._100ms -= deltaMs;
	tf._125ms -= deltaMs;
	tf._500ms -= deltaMs;
	tf._10000ms -= deltaMs;
	tf.lastMs = ms;
}


bool shouldExecute(short tfAttribute)
{
	return tfAttribute <= 0;
}

Timer allTimers[5] = {
	{ 25 },
	{ 100 },
	{ 125 },
	{ 500 },
	{ 1000 },
};

void resetTimerFlags()
{
	auto ms = millis();
	auto deltaMs = getTfDeltaMs(ms);

	if (shouldExecute(tf._25ms))
	{
		tf._25ms = 25 - deltaMs;
	}
	if (shouldExecute(tf._100ms))
	{
		tf._100ms = 100 - deltaMs;
	}
	if (shouldExecute(tf._125ms))
	{
		tf._125ms = 125 - deltaMs;
	}
	if (shouldExecute(tf._500ms))
	{
		tf._500ms = 500 - deltaMs;
	}
	if (shouldExecute(tf._10000ms))
	{
		tf._10000ms = 10000 - deltaMs;
	}
}

void loop()
{
	for ( auto timer : allTimers ) 
	{
		timer.ShouldExecute()
	}
	tickTimerFlags();
	// readRotaryState();

	if (shouldExecute(tf._25ms))
	{
		// readKeypadState();
	}

	if (shouldExecute(tf._100ms))
	{
		// 2FC
		outputMediaControlState();
	}

	if (shouldExecute(tf._125ms))
	{
		// 425
		outputKeepAlive();
	}

	if (shouldExecute(tf._500ms))
	{
		// 307
		outputHvacStatus();
	}

	if (shouldExecute(tf._10000ms))
	{
		// readTempState();
	}

	resetTimerFlags();
}
