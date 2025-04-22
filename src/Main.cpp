
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

// Register definitions for the MCU
#include <Chip/Unknown/STMicro/STM32F41x/CAN1.hpp>

#include "Main.h"


void setup()
{

	// initialize serial to 38.4kbps - this is the speed that head units listen at
	Serial.begin(115200);

	// setupSensorPins();
	// setupKeypadPins();
	Core::setupCanComms();

}

const Core::Timer allTimers[5] {
	{ .intervalMs = 25, []() { ReadKeypadState(); } },
	{ .intervalMs = 100, []() { OutputMediaControlState(); } },
	{ .intervalMs = 125, [] { OutputKeepAlive(); } },
	{ .intervalMs = 500, [] { OutputHvacStatus(); } },
	{ .intervalMs = 10000, []{ ReadTempState(); } },
};


void loop()
{
  readRotaryState();

  auto deltaMs = 0;
	for ( auto timer : allTimers ) 
	{
		timer.Tick(deltaMs);
	}


	for ( auto timer : allTimers )
	{
		if( timer.ShouldExecute() )
        {
        	timer.Execute();
    	}
	}

        for ( auto& timer : allTimers )
          {
          timer.ResetTimerFlags();
          }
}


void main()
{
	setup();

	loop();
}