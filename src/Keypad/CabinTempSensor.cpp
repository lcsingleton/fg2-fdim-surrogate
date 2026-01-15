#include "Keypad/CabinTempSensor.h"

#include <cmath>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

using namespace Keypad::CabinTempSensor;


const auto Adc = ADC1; // Use ADC1 for the temperature sensor

const auto KelvinZeroPoint = 273.15; // Kelvin to Celsius conversion
const auto InitialTempCelcius = 22.0f; // Initial temperature in Celsius
const auto InitialAdcValue = 1024u; // Initial ADC value

const auto ntcValue = 10000u;
const auto scalar = 639.5;
const auto exponent = -0.1332;
const auto offset = -162.5;

const auto referenceResistor = 10000u; // 10K ohm fixed resistor
const auto supplyVoltage = 3.3; // STM32 supply voltage
const auto adcResolution = 4095.0; // 12-bit ADC (2^12 - 1)


// When the cabin temperature sensor is initialized, use a sensible default
// which shouldn't cause the HVAC to go crazy on startup.
volatile auto g_latestAdcValue = InitialAdcValue; // Latest ADC value read from the sensor


void Keypad::CabinTempSensor::InitTempSensor()
{
	// Configure GPIO Pin A1 as analog input for the temperature sensor
	// This pin will be connected to the voltage divider circuit with the NTC thermistor
	gpio_mode_setup( GPIOA, // Port A
					 GPIO_MODE_ANALOG, // Set as analog input mode
					 GPIO_PUPD_NONE, // Disable pull-up/pull-down resistors
					 GPIO1 // Pin 1
	);

	// Enable the clock for ADC1 peripheral
	// Without this, the ADC registers cannot be accessed
	rcc_periph_clock_enable( RCC_ADC1 );

	// Set the ADC clock prescaler to divide by 2
	// This sets the ADC clock frequency based on the APB2 clock
	// Slower clock = more accurate conversions, faster clock = quicker conversions
	adc_set_clk_prescale( ADC_CCR_ADCPRE_BY2 );

	// Disable scan mode - we're only reading one channel at a time
	// Scan mode would be used to automatically sequence through multiple channels
	adc_disable_scan_mode( Adc );

	// Set single conversion mode instead of continuous conversion
	// This means the ADC will perform one conversion when triggered
	// and then stop, waiting for the next trigger
	adc_set_single_conversion_mode( Adc );

	// Set the sample time for ADC Channel 0 to 144 cycles
	// Longer sample times allow the ADC's internal capacitor to fully charge
	// This results in more accurate readings, especially for high impedance sources
	// The NTC thermistor circuit benefits from this longer sample time
	adc_set_sample_time( Adc, ADC_CHANNEL0, ADC_SMPR_SMP_144CYC );

	// Configure the regular conversion sequence with a single channel
	// The sequence defines which channels to convert and in what order
	uint8_t channels[] = { ADC_CHANNEL0 };
	adc_set_regular_sequence( Adc, // ADC1 peripheral
							  1, // Number of channels in the sequence
							  channels // Array of channel numbers to convert
	);

	// Set the ADC to independent mode (not using dual/triple ADC features)
	// In independent mode, ADC1 operates standalone without synchronization to other ADCs
	adc_set_multi_mode( ADC_CCR_MULTI_INDEPENDENT );

	// Set 12-bit resolution for ADC conversions
	// This provides values from 0-4095, giving good precision for temperature measurements
	// Higher resolution (12-bit) is slower but more accurate than lower resolutions
	adc_set_resolution( Adc, ADC_CR1_RES_12BIT );

	// Power on the ADC peripheral
	// The ADC requires a stabilization time after power-on before conversions can begin
	adc_power_on( Adc );

	// Enable the ADC end-of-conversion interrupt
	// This allows the ADC to notify the CPU when a conversion is complete
	// The CPU can then read the result without polling
	adc_enable_eoc_interrupt( Adc );

	// Enable the ADC interrupt in the NVIC (Nested Vectored Interrupt Controller)
	// This allows the adc_isr() function to be called when conversions complete
	nvic_enable_irq( NVIC_ADC_IRQ );
}

/**
 * ADC Interrupt Handler - Called when ADC conversion completes
 * 
 * This interrupt service routine is automatically invoked by the NVIC
 * when the ADC completes a conversion and the end-of-conversion flag is set.
 * It reads the converted value and stores it for later temperature calculation.
 */
void adc_isr( void )
{
	// Check if the end-of-conversion flag is set
	// If not set, this interrupt was triggered by a different ADC event
	if( adc_eoc( Adc ) == 0 )
	{
		// This interrupt was not triggered for the "End of Conversion" event for ADC1
		return;
	}

	// Read the ADC value from the data register
	// This operation automatically clears the end-of-conversion flag in hardware
	// The volatile variable ensures this value is visible across all code
	// that might read the temperature sensor
	g_latestAdcValue = adc_read_regular( Adc );
}


/**
 * Trigger a new temperature sensor reading
 * 
 * This function initiates an ADC conversion for the temperature sensor.
 * The actual reading is performed asynchronously by the ADC hardware,
 * and when complete, the adc_isr() interrupt handler will store the result.
 * This non-blocking approach allows the CPU to perform other tasks while
 * the ADC performs the conversion.
 */
void Keypad::CabinTempSensor::UpdateCabinTempSensor()
{
	// Start a single ADC conversion
	// The ADC will convert the analog voltage on Channel 0 to a digital value
	// When complete, it will trigger the adc_isr() interrupt handler
	adc_start_conversion_regular( Adc );
}

/**
 * Calculate and return the current cabin temperature in Celsius
 * 
 * This function converts the latest ADC reading into a temperature value.
 * It uses cached calculations to avoid redundant computation when the
 * ADC value hasn't changed. The conversion process:
 * 1. Convert ADC value (0-4095) to voltage (0-3.3V)
 * 2. Calculate NTC thermistor resistance using voltage divider formula
 * 3. Convert resistance to temperature using calibration curve
 * 4. Convert from Kelvin to Celsius
 * 
 * @return Current cabin temperature in degrees Celsius
 */
float GetLatestTempCelsius()
{
	// Static variables maintain their values between function calls
	// This allows us to cache the last calculation and skip redundant work
	static auto lastCalculatedAdcValue = InitialAdcValue;
	static auto lastCalculatedTemp = InitialTempCelcius;

	// If the ADC value hasn't changed since the last call, return the cached result
	// This optimization avoids expensive floating-point calculations when unnecessary
	if( g_latestAdcValue == lastCalculatedAdcValue )
	{
		return lastCalculatedTemp;
	}

	// Read the latest ADC value from the volatile global variable
	// The ADC interrupt handler updates this asynchronously
	auto adcValue = g_latestAdcValue;

	// Convert the ADC reading to voltage
	// ADC range: 0-4095 maps to voltage range: 0-3.3V
	// Formula: V = (ADC_value * V_ref) / ADC_max_value
	auto voltage = ( adcValue * supplyVoltage ) / adcResolution;

	// Calculate the NTC thermistor resistance using the voltage divider formula
	// Circuit: V_supply ---[R_fixed]--- V_measure ---[R_ntc]--- GND
	// Rearranged: R_ntc = R_fixed * ((V_supply / V_measure) - 1)
	auto ntcResistance = referenceResistor * ( ( supplyVoltage / voltage ) - 1 );

	// Convert resistance to temperature using the calibration formula
	// This is a power-law approximation fitted to the NTC thermistor's characteristic curve
	// T(K) = scalar * R^exponent + offset
	// The coefficients (scalar, exponent, offset) are specific to this NTC thermistor
	auto tempKelvin = scalar * std::pow( ntcResistance, exponent ) + offset;

	// Convert from Kelvin to Celsius
	// Formula: T(°C) = T(K) - 273.15
	auto tempCelsius = tempKelvin - KelvinZeroPoint;

	// Update the cached values for the next function call
	// This allows us to detect when the ADC value has changed
	lastCalculatedAdcValue = g_latestAdcValue;
	lastCalculatedTemp = tempCelsius;

	// Return the calculated temperature in degrees Celsius
	return tempCelsius;
}
