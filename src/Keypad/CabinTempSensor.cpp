#include "Keypad/CabinTempSensor.h"

#include <cmath>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
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


void InitTempSensor()
{
	// TODO: Confirm the correct ADC Channel
    // TODO: Configure GPIO pins for the temperature sensor

	// Power on the ADC
	adc_power_on( Adc );

	// Unsure what this does more so that it is required
	adc_calibrate( Adc );

	// Use 12 bit resolution for ADC conversions
	adc_set_resolution( Adc, ADC_RESOLUTION_12BIT );

	// Set the ADC clock prescaler to 4
	adc_set_prescaler( Adc, ADC_PRESCALER_4 );

	// Enable the "Single Shot" conversion mode
	// This means the ADC will perform a single conversion when requested
	adc_set_operation_mode( Adc, ADC_MODE_SINGLE );

	adc_set_regular_sequence( Adc, &tempSensor.adcChannel, 1 );


	// Set the sample time for the temperature sensor channel
	// Use relatively long sample time to ensure stable readings
	// This isn't an issue for CPU time as the ADC will be triggered by an interrupt
	// and the CPU can do other things while waiting on the conversion
	adc_set_sample_time( Adc, ADC_CHANNEL0, ADC_SMPR_SMP_144CYC );
}

/**
 * ADC Interrupt Handler - For Adc conversion complete
 */
void adc_isr( void )
{
	if( adc_eoc( Adc ) == 0 )
	{
		// This interrupt was not triggered for the "End of Conversion" event for ADC1
		return;
	}

	// Clear the end of conversion flag
	adc_clear_eoc( Adc );

	// Read the ADC value and process it
	g_latestAdcValue = adc_read_regular( Adc );
}


void UpdateCabinTempSensor()
{
	// Start ADC conversion, rely on the interrupt handler to read the value when the conversion is complete
	adc_start_conversion_regular( Adc );
}

float GetLatestTempCelsius()
{

	static auto lastCalculatedAdcValue = InitialAdcValue;
	static auto lastCalculatedTemp = InitialTempCelcius;

	// If the ADC value hasn't changed, skip the calculation
	if( g_latestAdcValue == lastCalculatedAdcValue )
	{
		return lastCalculatedTemp;
	}

	// Read the latest ADC value
	auto adcValue = g_latestAdcValue;

	// Convert to voltage
	auto voltage = ( adcValue * supplyVoltage ) / adcResolution;

	// Calculate NTC resistance using voltage divider formula
	auto ntcResistance = referenceResistor * ( ( supplyVoltage / voltage ) - 1 );

	// Convert resistance to temperature using your calibration formula
	auto tempKelvin = scalar * std::pow( ntcResistance, exponent ) + offset;

	// Convert Kelvin to Celsius
	auto tempCelsius = tempKelvin - KelvinZeroPoint;

	// Update the last calculated values
	lastCalculatedAdcValue = g_latestAdcValue;
	lastCalculatedTemp = tempCelsius;

	// Return the calculated temperature in Celsius
	return tempCelsius;
}
