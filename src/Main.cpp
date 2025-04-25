#include "Main.h"

using Core::Timer;


const auto allTimers[ 5 ] = {
	// Update the internal state of the Keypad every 25 milliseconds
	Timer<25>{ []() { Keypad::ReadKeypadState(); } },

	// Output the CAN with the new state of the Media Key States every 100ms
	Timer<100>{ []() { OutputMediaControlState(); } },

	// Output the CAN with the new state of the Media Key States every 100ms
	Timer<125>{ []() { OutputKeepAlive(); } },

	// Output the CAN with the new state of the Media Key States every 100ms
	Timer<500>{ []() { OutputHvacStatus(); } },

	// Update the state of the interior cabim temp every 10 seconds
	Timer<100000>{ []() { ReadTempState(); } },
};

void InitGpio {  }
void InitGpio {  }
void InitUsart{  }

void Setup()
{
	Core::Timer::InitTimerSystem();
	// Core::InitGpio();
	// Core::InitUsart();
	Core::Can::InitCanSystem();

	/*	
	usart_setup();
	clock_setup();
	gpio_setup();
	can_setup();
	*/


	// initialize serial to 38.4kbps - this is the speed that head units listen at
	Serial.begin( 115200 );

}


void Loop()
{
	readRotaryState();

	for( auto timer: allTimers )
	{
		timer.Tick( Timer::GetSysUptimeMs() );
	}
}


void main()
{
	Setup();

	Loop();
}
