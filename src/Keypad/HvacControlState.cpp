/**
 * HVAC Control State CAN Message Handler
 * 
 * This module packages the current state of all HVAC and keypad controls
 * into a CAN message and transmits it on the vehicle bus.
 * 
 * The message uses arbitration ID 0x307 and follows the vehicle's protocol
 * for communicating climate control and auxiliary button states.
 */

#include <cstdint>
#include "Core/BitPack.h"
#include "Core/Can.h"

#include "Keypad/HvacControlState.h"
#include "Keypad/KeypadState.h"

using namespace Keypad::HvacControlState;
using namespace Core::Can;
using namespace Core::BitPack;

/**
 * CAN Message Structure for HVAC Control State
 * 
 * Arbitration ID: 0x307
 * Data Length: 8 bytes (64 bits)
 * 
 * This structure packs all HVAC and auxiliary control button states
 * into a single 64-bit CAN message following the vehicle's protocol.
 * Bit positions match the expected format of the climate control module.
 */
struct CanHvacControlState
{
	const uint32_t arbitrationId = 0x307;
	uint8_t data[8];

	CanHvacControlState( const Keypad::KeypadState::State &keypadState )
	{
		// Pack all control states into 64 bits following the vehicle protocol
		// Unused bits are set to 0 and reserved for dual-zone climate features
		auto packed = PackCanData(
			BoolField(keypadState.ac),                // AC on/off
			BoolField(keypadState.airSource),         // Recirculation/fresh air
			BoolField(keypadState.rearDemist),        // Rear window demister
	        FixedField<0, 5>(),                       // Reserved for dual-zone climate (5 bits)
			BoolField(keypadState.vent),              // Vent mode selection
	        FixedField<0, 1>(),                       // Reserved bit
			BoolField(keypadState.hvacAuto),          // Auto climate mode
			BoolField(keypadState.hvacOff),           // HVAC system off
			BoolField(keypadState.fanIncrease),       // Fan speed up
			BoolField(keypadState.fanReduce),         // Fan speed down
			BoolField(keypadState.frontDemist),       // Windscreen demister
			FixedField<0, 1>(),                       // Reserved bit
			BoolField(keypadState.tempIncrease),      // Temperature up
			BoolField(keypadState.tempReduce),        // Temperature down
			BoolField(keypadState.hazard),            // Hazard lights
			FixedField<0, 1>(),                       // Reserved bit
			BoolField(keypadState.lock),              // Door lock
			BoolField(keypadState.interiorLight),     // Cabin light
			BoolField(keypadState.dynamicStabilityControl), // DSC toggle
			FixedField<0, 1>(),                       // Reserved bit
			BoolField(keypadState.unlock),            // Door unlock
			Field<uint8_t, 8>(keypadState.cabinTemp), // Cabin temperature (full byte)
			FixedField<0, 1>()                        // Padding to 64 bits
		);
		
		// Copy packed bytes to array (will be copied again to CAN registers anyway)
		for( size_t i = 0; i < 8; i++ )
		{
			data[i] = packed.bytes[i];
		}
	}
};

/**
 * Transmit the current HVAC control state on the CAN bus
 * 
 * Reads the current keypad state and packages it into a CAN message,
 * then transmits it on the vehicle bus for the climate control module
 * to process.
 */
void Keypad::HvacControlState::OutputHvacControlState()
{
	// Package current state and send via CAN bus
	auto result = Send( CanHvacControlState{ Keypad::KeypadState::GetState() } );

	// Message is fire-and-forget - the CAN controller handles retries
	// Result indicates which transmit mailbox was used, or failure
	if( result != SendResult::SEND_FAILED )
	{
		// Successfully queued for transmission
	}
}
