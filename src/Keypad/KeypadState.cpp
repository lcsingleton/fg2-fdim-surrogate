#include "KeypadState.h"

#include "Buttons.h"
#include "RotaryDial.h"

#include <libopencm3/stm32/gpio.h>

using namespace Keypad::KeypadState;
using namespace Keypad::RotaryDial;
using namespace Keypad::Buttons;



enum ButtonStatus
{
	BS_UNKNOWN = 0,
	BS_RELEASED = 1,
	BS_PRESSED = 2,
};

ButtonStatus buttonStates[FdmButtonType::FBT_COUNT] = { 
	ButtonStatus::BS_UNKNOWN, // FBT_HVAC_OFF
	ButtonStatus::BS_UNKNOWN, // FBT_RECIRC
	ButtonStatus::BS_UNKNOWN, // FBT_AC
	ButtonStatus::BS_UNKNOWN, // FBT_AUTO
	ButtonStatus::BS_UNKNOWN, // FBT_HAZARD
	ButtonStatus::BS_UNKNOWN, // FBT_FRONT_DEMIST
	ButtonStatus::BS_UNKNOWN, // FBT_VENTS
	ButtonStatus::BS_UNKNOWN, // FBT_REAR_DEMIST
	ButtonStatus::BS_UNKNOWN, // FBT_PASS_TEMP_MINUS
	ButtonStatus::BS_UNKNOWN, // FBT_PASS_TEMP_PLUS
	ButtonStatus::BS_UNKNOWN, // FBT_FAN_MINUS
	ButtonStatus::BS_UNKNOWN, // FBT_FAN_PLUS
	ButtonStatus::BS_UNKNOWN, // FBT_DRIVER_TEMP_MINUS
	ButtonStatus::BS_UNKNOWN, // FBT_DRIVER_TEMP_PLUS
	ButtonStatus::BS_UNKNOWN, // FBT_EJECT
	ButtonStatus::BS_UNKNOWN, // FBT_SOURCE_CD
	ButtonStatus::BS_UNKNOWN, // FBT_SCN_AS
	ButtonStatus::BS_UNKNOWN, // FBT_SOURCE_MEDIA
	ButtonStatus::BS_UNKNOWN, // FBT_SOURCE_FM_AM
	ButtonStatus::BS_UNKNOWN, // FBT_BACK
	ButtonStatus::BS_UNKNOWN, // FBT_OK
	ButtonStatus::BS_UNKNOWN, // FBT_MENU
	ButtonStatus::BS_UNKNOWN, // FBT_AUDIO_POWER
	ButtonStatus::BS_UNKNOWN, // FBT_SEEK_LEFT
	ButtonStatus::BS_UNKNOWN, // FBT_SEEK_RIGHT
	ButtonStatus::BS_UNKNOWN, // FBT_LOCK
	ButtonStatus::BS_UNKNOWN, // FBT_UNLOCK
	ButtonStatus::BS_UNKNOWN, // FBT_DSC
	ButtonStatus::BS_UNKNOWN  // FBT_INTERIOR_LIGHT
};


void InitKeypadGpios()
{
	// Set up the GPIO pins for the keypad buttons
	for( unsigned i = 0; i < FdmButtonType::FBT_COUNT; i++ )
	{
		auto fdmButton = buttons[ i ];

		gpio_mode_setup(
			GPIOB
			GPIO_MODE_OUTPUT, // Set as output mode
			GPIO_PUPD_NONE, // Disable the pull up or down
			fdmButton.groundPin // Pin
		);

		// Set the ground pin to LOW
		gpio_set(
			GPIOB, // Port
			fdmButton.groundPin // Ground Pin
		);

		gpio_mode_setup(
			GPIOB,
			GPIO_MODE_INPUT, // Set as input mode so we can read the signal pin
			GPIO_PUPD_PULLUP, // Enable the pull up resistor
			fdmButton.signalPin // Pin
		);

		// Set the ground pin to LOW
		gpio_set(
			GPIOB, // Port
			fdmButton.signalPin // Signal Pin
		);
	}

	// Set up the GPIO pins for the rotary encoder
	gpio_mode_setup(
		GPIOB,
		GPIO_MODE_INPUT, // Set as input mode so we can read the signal pin
		GPIO_PUPD_PULLUP, // Enable the pull up resistor
		encoder.signalPinA // Signal Pin A
	);
	gpio_mode_setup(
		GPIOB,
		GPIO_MODE_INPUT, // Set as input mode so we can read the signal pin
		GPIO_PUPD_PULLUP, // Enable the pull up resistor
		encoder.signalPinC // Signal Pin C
	);

	// Set up the GPIO pins for the temperature sensor
	gpio_mode_setup(
		GPIOB,
		GPIO_MODE_OUTPUT, // Set as output mode
		GPIO_PUPD_NONE, // Disable the pull up or down
		tempSensor.sensePin // Sense Pin
	);

	gpio_set(
		GPIOB, // Port B
		tempSensor.sensePin // Sense Pin
	);

	// Set the ground pin to LOW
	gpio_mode_setup(
		GPIOB,
		GPIO_MODE_OUTPUT, // Set as output mode
		GPIO_PUPD_NONE, // Disable the pull up or down
		encoder.groundPinB // Ground Pin B
	);
	gpio_set(
		GPIOB, // Port B
		encoder.groundPinB // Ground Pin B
	);

}

void InitKeypadState()
{
	InitKeypadGpios();

	InitRotaryDialSystem();

}

void UpdateKeypadState()
{
	// Clear all of the ground pins and signal pins
	for ( unsigned i = 0; i < FdmButtonType::FBT_COUNT;
		i++ )
	{
		auto fdmButton = buttons[ i ];

		gpio_clear(
			GPIOB, // Port B
			fdmButton.groundPin // Ground Pin
		);
		gpio_set(
			GPIOB, // Port B
			fdmButton.signalPin // Signal Pin
		);
	}


	// Perform a matrix scan of the buttons
	for ( unsigned i = 0; i < FdmButtonType::FBT_COUNT; i++ )
	{
		auto fdmButton = buttons[ i ];

		gpio_mode_setup(
			fdmButton.groundPin, // Port
			GPIO_MODE_INPUT,
			GPIO_PUPD_PULLUP, // Enable the pull up resistor
			fdmButton.groundPin // Pin
		);
		gpio_set(
			GPIOB, // Port B
			fdmButton.signalPin // Signal Pin
		);

		// Read the status of the signal pin
		auto pinStatus = gpio_get(
			GPIOB, // Port B
			fdmButton.signalPin // Signal Pin
		);

		// Set the signal pin back to HIGH
		gpio_clear(
			GPIOB, // Port B
			fdmButton.signalPin // Signal Pin
		);

		//
		if ( pinStatus )
		{
			buttonStates[ i ] = BS_PRESSED;
		}
		else
		{
			buttonStates[ i ] = BS_RELEASED;
		}
	}

}

