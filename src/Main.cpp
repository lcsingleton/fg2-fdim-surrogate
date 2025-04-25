#include "Main.h"

using Core::Timer;



void setup()
{

	// initialize serial to 38.4kbps - this is the speed that head units listen at
	Serial.begin( 115200 );

	// setupSensorPins();
	// setupKeypadPins();
	Core::setupCanComms();
}

const auto t1 = Core::Timer<25>
{
	[]() { ReadKeypadState(); 
};

const auto allTimers[4] = {
	// Update the internal state of the Keypad every 25 milliseconds
	
			   // Update the internal state of the Keypad every 25 milliseconds
						Timer<100>{
					   []() { OutputMediaControlState(); },
					   Timer<125>{ []() { OutputKeepAlive(); } },
					   Timer<500>{ []() { OutputHvacStatus(); } },
					   Timer<100000>{ []() { ReadTempState(); } },
			   };


void loop()
{
	readRotaryState();

	for( auto timer: allTimers )
	{
		timer.Tick( mtime() );
	}
}


void main()
{
	setup();

	loop();
}
