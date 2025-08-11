#include "Main.h"


const Core::Timer::IntervalTimer allTimers[ 6 ] = {
	// Update the internal state of the Keypad every 25 milliseconds
	Core::Timer::IntervalTimer{ 25, []() { Keypad::KeypadState::UpdateKeypadState(); } },

	// Output the CAN with the new state of the Media Key States every 100ms
	Core::Timer::IntervalTimer{ 100, []() { Keypad::MediaControlState::OutputMediaControlState(); } },

	// Output the CAN with the ICC Keepalive every 125ms
	Core::Timer::IntervalTimer{ 125, []() { Icc::KeepAlive::OutputKeepAlive(); } },

	// Output the CAN with the ACM Keepalive every 125ms
	Core::Timer::IntervalTimer{ 125, []() { Acm::KeepAlive::OutputKeepAlive(); } },

	// Output the CAN with the new state of the Media Key States every 500ms
	Core::Timer::IntervalTimer{ 500, []() { Keypad::HvacControlState::OutputHvacControlState(); } },

	// Update the internal state of the Cabin Temp Sensor every 5 seconds
	Core::Timer::IntervalTimer{ 5000, []() { Keypad::CabinTempSensor::UpdateCabinTempSensor(); } },

};

void Setup()
{
	Core::Timer::InitTimerSystem();
	Core::Serial::InitUsartSystem();
	Core::Can::InitCanSystem();
	Keypad::KeypadState::InitKeypadState();
}


void Loop()
{
	for( auto timer: allTimers )
	{
		timer.Tick( Core::Timer::GetSysUptimeMs() );
	}
}


int main()
{
	Setup();

	Loop();

	return 1;
}
