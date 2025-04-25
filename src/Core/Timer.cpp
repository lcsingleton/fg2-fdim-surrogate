#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/f4/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#include "Core/Timer.h"

/* milliseconds since boot */
static volatile Core::milliseconds sysUptimeMs;

/* Called when systick fires */
void sys_tick_handler( void ) { system_millis++; }

/* simple sleep for delay milliseconds */
void milli_sleep( uint32_t delay )
{
	Core::milliseconds wake = system_millis + delay;
	while( wake > system_millis )
	{
		continue;
	}
}

/* Getter function for the current time */
Core::milliseconds GetSysUptimeMs( ) const { return sysUptimeMs; }

/*
 * clock_setup(void)
 *
 * This function sets up both the base board clock rate
 * and a 1khz "system tick" count. The SYSTICK counter is
 * a standard feature of the Cortex-M series.
 */
void Core::InitTimerSystem( void )
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
