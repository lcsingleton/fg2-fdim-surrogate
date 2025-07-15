// Reset and Clock Controls
#include <libopencm3/stm32/rcc.h>

// F4 Timer Constants
#include <libopencm3/stm32/f4/timer.h>

// Interrupt Controllers
#include <libopencm3/cm3/nvic.h>

// Timer Features
#include <libopencm3/cm3/systick.h>

#include "Core/Timer.h"

using namespace Core::Timer;


IntervalTimer::IntervalTimer( milliseconds intervalMs, Handler handler, milliseconds nextExecuteMs ) :
	intervalMs( intervalMs ), handler( handler ), nextExecuteMs( nextExecuteMs )
{}


IntervalTimer::IntervalTimer( milliseconds intervalMs, Handler handler ) : IntervalTimer( intervalMs, handler, intervalMs ) {}

bool IntervalTimer::ShouldExecute( milliseconds currentMs ) const { return currentMs >= nextExecuteMs; }

void IntervalTimer::ExecuteHandler() { handler(); }

void IntervalTimer::Tick( const milliseconds currentMs )
{
	if( ShouldExecute( currentMs ) )
	{
		ExecuteHandler();
		ResetTimer( currentMs );
	}
}

void IntervalTimer::ResetTimer( const milliseconds currentMs )
{
	// May cause overflow (once every 49.7 days), but currentMs will overflow at the same time
	nextExecuteMs += intervalMs;
}

/* milliseconds since boot */
static volatile milliseconds sysUptimeMs;

/* Called when systick fires */
void sys_tick_handler( void ) { sysUptimeMs++; }

/* simple sleep for delay milliseconds */
void milli_sleep( milliseconds delay )
{
	Core::Timer::milliseconds wake = sysUptimeMs + delay;
	while( wake > sysUptimeMs )
	{
		continue;
	}
}

/* Getter function for the current time */
milliseconds GetSysUptimeMs() { return sysUptimeMs; }

/*
 * clock_setup(void)
 *
 * This function sets up both the base board clock rate
 * and a 1khz "system tick" count. The SYSTICK counter is
 * a standard feature of the Cortex-M series.
 */
void InitTimerSystem()
{
	/* Base board frequency, set to 168Mhz */
	rcc_clock_setup_pll( &rcc_hse_8mhz_3v3[ RCC_CLOCK_3V3_168MHZ ] );

	/* clock rate / 168000 to get 1mS interrupt rate */
	systick_set_reload( 168000 );
	systick_set_clocksource( STK_CSR_CLKSOURCE_AHB );
	systick_counter_enable();

	/* this done last */
	systick_interrupt_enable();
}
