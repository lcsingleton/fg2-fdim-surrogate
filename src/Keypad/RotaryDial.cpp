
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <stdint.h>


#include "Keypad/RotaryDial.h"

using namespace Keypad::RotaryDial;

constexpr auto Timer = TIM3;

// Flag to indicate the last movement of the rotary dial
uint16_t lastPosition = 0;


void ReadRotaryState()
{
	uint16_t position = timer_get_counter(Timer);
	
	if (position == lastPosition) {
		return; // No change in position
	}

	if (position > lastPosition) {
		// Rotary dial moved clockwise
		RotaryDialMovement movement = ROTARY_DIAL_MOVEMENT_CLOCKWISE;
	} else {
		// Rotary dial moved counterclockwise
		RotaryDialMovement movement = ROTARY_DIAL_MOVEMENT_COUNTERCLOCKWISE;
	}
	

	lastPosition = position;
}

void InitRotaryDialSystem()
{
	// Enable GPIOA and TIM2 clocks
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM2);

    // Set PA0 and PA1 to alternate function mode (AF1 for TIM2)
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO0 | GPIO1);
    gpio_set_af(GPIOA, GPIO_AF1, GPIO0 | GPIO1);

    // Configure TIM2 in encoder mode
    timer_disable_counter(Timer);
    timer_set_prescaler(Timer, 0); // No prescaler
    timer_set_period(Timer, 0xFFFF); // Max count

    // Encoder mode 3: count up/down on both TI1 and TI2 edges
    timer_slave_set_mode(Timer, TIM_SMCR_SMS_EM3); // Encoder mode 3

    // Configure input filters and polarity if needed
    timer_ic_set_input(Timer, TIM_IC1, TIM_IC_IN_TI1);
    timer_ic_set_input(Timer, TIM_IC2, TIM_IC_IN_TI2);

    // Optionally set input filter for noise
    timer_ic_set_filter(Timer, TIM_IC1, TIM_IC_DTF_DIV_32_N_8);
    timer_ic_set_filter(Timer, TIM_IC2, TIM_IC_DTF_DIV_32_N_8);

    timer_enable_counter(Timer);
}
