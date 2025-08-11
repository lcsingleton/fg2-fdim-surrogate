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

/* Interrupt handler which is called when systick fires */
void sys_tick_handler( void ) { sysUptimeMs++; }

/* simple sleep for delay milliseconds */
void Sleep( milliseconds delay )
{
	Core::Timer::milliseconds wakeAt = sysUptimeMs + delay;

	// Spin until wakeAt is reached
	while( wakeAt > sysUptimeMs );
}

/* Getter function for the current time */
milliseconds GetSysUptimeMs() { return sysUptimeMs; }

// Clock configuration for 50MHz operation
// This is a 50MHz clock from an 8MHz external crystal
const rcc_clock_scale ClockConf50Mhz = {
	/* 100MHz from 8MHz external crystal */
	.pllm = 8,
	.plln = 100,
	.pllp = 2,
	.pllq = 2,
	.pllr = 2,
	.pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
	.flash_config = 0,
	.hpre = RCC_CFGR_HPRE_NODIV,
	.ppre1 = RCC_CFGR_PPRE_DIV2,
	.ppre2 = RCC_CFGR_PPRE_DIV2,
	.voltage_scale = PWR_SCALE1,
	.ahb_frequency  = 50000000,
	.apb1_frequency = 25000000,
	.apb2_frequency = 25000000,
};


/*
 * clock_setup(void)
 *
 * This function sets up both the base board clock rate
 * and a 1khz "system tick" count. The SYSTICK counter is
 * a standard feature of the Cortex-M series.
 */
void InitTimerSystem()
{
	/* Base board frequency, set to 50MHz - half the max for the STM32F412R */
	rcc_clock_setup_pll( &ClockConf50Mhz );
	// Use the external 8MHz Oscillator
	
	/* clock rate / 50000 to get 1mS interrupt rate */
	systick_set_reload( 49999 );
	systick_set_clocksource( STK_CSR_CLKSOURCE_AHB );
	systick_clear();
	systick_counter_enable();

	/* this done last */
	systick_interrupt_enable();
}
