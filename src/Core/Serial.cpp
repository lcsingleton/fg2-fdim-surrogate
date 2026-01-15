// Reset and Clock Controls
#include <libopencm3/stm32/rcc.h>

// IO Pin Controls
#include <libopencm3/stm32/gpio.h>

// USART (Serial) Configuration
#include <libopencm3/stm32/usart.h>

#include "Core/Serial.h"

using namespace Core::Serial;

void ClockSetup()
{
	/* Enable GPIOD clock for the status LED & USART. */
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Enable clocks for USART. */
	rcc_periph_clock_enable(RCC_USART1);
}

void PinSetup()
{
	/* Setup pin 2 (GPIO2) on Port B (GPIOB) for GPIO usage for LED. */
	gpio_mode_setup(
		GPIOB, // Port B
		GPIO_MODE_OUTPUT, // Set as output mode
		GPIO_PUPD_NONE, // Disable the pull up or down
		GPIO2 // Pin 2
	);

	/* PLace A9 in alternate function mode. */
	gpio_mode_setup(
		GPIOA, // Port A
		GPIO_MODE_AF, // Alternate function mode
		GPIO_PUPD_NONE, // Disable the pull up or down
		GPIO9 // Pin 9
	);

	/* Select USART TX as the enabled Alternate Function on A9. */
	gpio_set_af(
		GPIOA, // Port A
		GPIO_AF3, // Alternate Function 3 (0 indexed) for PortA9 for is USART1_TX 
		GPIO9 // Pin 9
	);
}

void SerialSetup()
{

	// initialize serial to 38.4kbps - this is the speed that head units listen at
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

void Core::Serial::InitUsartSystem()
{
	ClockSetup();
	PinSetup();
	SerialSetup();

	gpio_toggle(GPIOB, GPIO2);	/* LED on/off */
	usart_send_blocking(USART1, ':');
	usart_send_blocking(USART1, ')');
	usart_send_blocking(USART1, '\r');
	usart_send_blocking(USART1, '\n');
	gpio_toggle(GPIOB, GPIO2);	/* LED on/off */
}

