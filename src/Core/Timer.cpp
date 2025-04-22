#include "Timer.h"

#include <utility>

using namespace Core;

Timer::Timer( unsigned long intervalMs, std::function<void()> handler): intervalMs(intervalMs), handler(std::move(handler)) {}

bool Timer::ShouldExecute() const { return true; }

void Timer::Tick( unsigned long elaspedMs )
{
	this->timer -= elaspedMs;

	auto ms = millis();
	auto deltaMs = getTfDeltaMs( ms );


	tf._25ms -= deltaMs;
}

unsigned long Timer::GetTfDeltaMs( unsigned long currentMs )
{
	auto distanceToUnderflow = 1l - tf.lastMs;


	// Check if currentMs has overflowed since lastMs was set
	if( currentMs < tf.lastMs )
	{
		Serial.println( "Overflow since last exection" );
		// overflow has happened
		auto lastToOverflowMs = -1l - tf.lastMs;
		return lastToOverflowMs + currentMs;
	}

	auto diff = currentMs - tf.lastMs;
	return diff;
}

bool Timer::ShouldExecute( short tfAttribute ) { return tfAttribute <= 0; }

void Timer::ResetTimerFlags()
{
	auto ms = millis();
	auto deltaMs = getTfDeltaMs( ms );

	if( shouldExecute( tf._25ms ) )
	{
		tf._25ms = 25 - deltaMs;
	}
	if( shouldExecute( tf._100ms ) )
	{
		tf._100ms = 100 - deltaMs;
	}
	if( shouldExecute( tf._125ms ) )
	{
		tf._125ms = 125 - deltaMs;
	}
	if( shouldExecute( tf._500ms ) )
	{
		tf._500ms = 500 - deltaMs;
	}
	if( shouldExecute( tf._10000ms ) )
	{
		tf._10000ms = 10000 - deltaMs;
	}
}
