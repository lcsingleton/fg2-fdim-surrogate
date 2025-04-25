#ifndef BUTTONS_H
#define BUTTONS_H

#include "Pins.h"

namespace Keypad
{

enum FdmButtonType
{
	FBT_HVAC_OFF,
	FBT_RECIRC,
	FBT_AC,
	FBT_AUTO,
	FBT_HAZARD,
	FBT_FRONT_DEMIST,
	FBT_VENTS,
	FBT_REAR_DEMIST,
	FBT_PASS_TEMP_MINUS,
	FBT_PASS_TEMP_PLUS,
	FBT_FAN_MINUS,
	FBT_FAN_PLUS,
	FBT_DRIVER_TEMP_MINUS,
	FBT_DRIVER_TEMP_PLUS,
	FBT_EJECT,
	FBT_SOURCE_CD,
	FBT_SCN_AS,
	FBT_SOURCE_MEDIA,
	FBT_SOURCE_FM_AM,
	FBT_BACK,
	FBT_OK,
	FBT_MENU,
	FBT_AUDIO_POWER,
	FBT_SEEK_LEFT,
	FBT_SEEK_RIGHT,
	FBT_LOCK,
	FBT_UNLOCK,
	FBT_DSC,
	FBT_INTERIOR_LIGHT,

	FBT_COUNT
};

struct FdmButton
{
	FdmButtonType buttonType;
	InterconnectPin signalPin;
	InterconnectPin groundPin;
	const char *displayName;
};


struct FdmRotaryEncoder
{
	InterconnectPin signalPinA;
	InterconnectPin signalPinC;
	InterconnectPin groundPinB;
	const char *displayName;
};

struct FdmTempSensor
{
	InterconnectPin sensePin;
	InterconnectPin groundPin;
	const char *displayName;
};


const FdmButton buttons[ FdmButtonType::FBT_COUNT ] = {
	{ FdmButtonType::FBT_HVAC_OFF, InterconnectPin::IP_ELEVEN, InterconnectPin::IP_SIXTEEN, "Toggle HVAC" },
	{ FdmButtonType::FBT_RECIRC, InterconnectPin::IP_TWELVE, InterconnectPin::IP_SIXTEEN, "Recirc/Fresh" },
	{ FdmButtonType::FBT_AC, InterconnectPin::IP_THIRTEEN, InterconnectPin::IP_SIXTEEN, "Toggle Air Conditioning" },
	{ FdmButtonType::FBT_AUTO, InterconnectPin::IP_FOURTEEN, InterconnectPin::IP_SIXTEEN, "Enable Climate Control" },

	{ FdmButtonType::FBT_FAN_MINUS, InterconnectPin::IP_ELEVEN, InterconnectPin::IP_SEVENTEEN, "Reduce Fan Speed" },
	{ FdmButtonType::FBT_FAN_PLUS, InterconnectPin::IP_TWELVE, InterconnectPin::IP_SEVENTEEN, "Increase Fan Speed" },

	// This is conjecture - I don't have a DZ Climate Control ICC
	{ FdmButtonType::FBT_PASS_TEMP_PLUS, InterconnectPin::IP_THIRTEEN, InterconnectPin::IP_SEVENTEEN,
	  "Increase Passenger Temp" },
	{ FdmButtonType::FBT_PASS_TEMP_MINUS, InterconnectPin::IP_FOURTEEN, InterconnectPin::IP_SEVENTEEN,
	  "Reduce Passenger Temp" },

	{ FdmButtonType::FBT_VENTS, InterconnectPin::IP_ELEVEN, InterconnectPin::IP_EIGHTEEN, "Cycle Vents" },
	{ FdmButtonType::FBT_FRONT_DEMIST, InterconnectPin::IP_TWELVE, InterconnectPin::IP_EIGHTEEN,
	  "Toggle Windscreen Demister" },
	{ FdmButtonType::FBT_DRIVER_TEMP_MINUS, InterconnectPin::IP_THIRTEEN, InterconnectPin::IP_EIGHTEEN,
	  "Reduce Temperature" },
	{ FdmButtonType::FBT_DRIVER_TEMP_PLUS, InterconnectPin::IP_FOURTEEN, InterconnectPin::IP_EIGHTEEN,
	  "Increase Temperature" },
	{ FdmButtonType::FBT_REAR_DEMIST, InterconnectPin::IP_FIFTEEN, InterconnectPin::IP_EIGHTEEN,
	  "Toggle Rear Demister" },

	{ FdmButtonType::FBT_DSC, InterconnectPin::IP_ELEVEN, InterconnectPin::IP_NINETEEN, "Toggle Stability Control" },
	{ FdmButtonType::FBT_SCN_AS, InterconnectPin::IP_TWELVE, InterconnectPin::IP_NINETEEN, "Scan Radio" },
	{ FdmButtonType::FBT_SOURCE_MEDIA, InterconnectPin::IP_THIRTEEN, InterconnectPin::IP_NINETEEN,
	  "Cycle Media Audio Sources" },
	{ FdmButtonType::FBT_SOURCE_FM_AM, InterconnectPin::IP_FOURTEEN, InterconnectPin::IP_NINETEEN,
	  "Cycle FM, AM Audio Sources" },
	{ FdmButtonType::FBT_BACK, InterconnectPin::IP_SIXTEEN, InterconnectPin::IP_NINETEEN, "Back" },

	{ FdmButtonType::FBT_SOURCE_CD, InterconnectPin::IP_ELEVEN, InterconnectPin::IP_TWENTY, "Select CD Audio Source" },
	{ FdmButtonType::FBT_OK, InterconnectPin::IP_TWELVE, InterconnectPin::IP_TWENTY, "OK" },
	{ FdmButtonType::FBT_MENU, InterconnectPin::IP_THIRTEEN, InterconnectPin::IP_TWENTY, "Menu" },
	{ FdmButtonType::FBT_SEEK_LEFT, InterconnectPin::IP_FOURTEEN, InterconnectPin::IP_TWENTY, "Seek Lower" },
	{ FdmButtonType::FBT_SEEK_RIGHT, InterconnectPin::IP_FIFTEEN, InterconnectPin::IP_TWENTY, "Seek Higher" },

	{ FdmButtonType::FBT_HAZARD, InterconnectPin::IP_FIVE, InterconnectPin::IP_TWENTY_TWO, "Toggle Hazard Lights" },
	{ FdmButtonType::FBT_AUDIO_POWER, InterconnectPin::IP_SIX, InterconnectPin::IP_TWENTY_TWO, "Toggle Audio Power" },
	{ FdmButtonType::FBT_EJECT, InterconnectPin::IP_SEVEN, InterconnectPin::IP_TWENTY_TWO, "Eject CD" },
	{ FdmButtonType::FBT_LOCK, InterconnectPin::IP_EIGHT, InterconnectPin::IP_TWENTY_TWO, "Lock Car Doors" },
	{ FdmButtonType::FBT_UNLOCK, InterconnectPin::IP_NINE, InterconnectPin::IP_TWENTY_TWO, "Unlock Car Doors" },
	{ FdmButtonType::FBT_INTERIOR_LIGHT, InterconnectPin::IP_TEN, InterconnectPin::IP_TWENTY_TWO,
	  "Toggle Cabin Light" },
};


const FdmRotaryEncoder encoder = { InterconnectPin::IP_TWENTY_TWO, InterconnectPin::IP_TWENTY_THREE,
								   InterconnectPin::IP_TWENTY_SIX, "Volume Control" };

const FdmTempSensor tempSensor = { InterconnectPin::IP_TWENTY_FIVE, InterconnectPin::IP_TWENTY_FOUR,
								   "Cabin Temp Sensor" };


enum FdmButtonStatus
{
	UNKNOWN = 0,
	ON = 1,
	OFF = 2,
};

// ---------------------------------------
// Current System Status Variables
// ---------------------------------------
FdmButtonStatus lastButtonStatus[ FdmButtonType::FBT_COUNT ] = {};
FdmButtonStatus currentButtonStatus[ FdmButtonType::FBT_COUNT ] = {};

typedef unsigned McuPin;

struct InterconnectPinMap
{
	InterconnectPin connectorPin;
	McuPin mcuPin;
};


const McuPin PIN_NOT_SET = 0XFF;

const InterconnectPinMap pinMap[ InterconnectPin::IP_COUNT ] = {
	// TODO: Fill this out when the header is completed
	{ .connectorPin = InterconnectPin::IP_ONE, .mcuPin = PIN_NOT_SET }, // LED +
	{ .connectorPin = InterconnectPin::IP_TWO, .mcuPin = PIN_NOT_SET }, // LED -
	{ .connectorPin = InterconnectPin::IP_THREE, .mcuPin = PIN_NOT_SET }, // NC
	{ .connectorPin = InterconnectPin::IP_FOUR, .mcuPin = PIN_NOT_SET }, // NC
	{ .connectorPin = InterconnectPin::IP_FIVE, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_SIX, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_SEVEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_EIGHT, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_NINE, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_ELEVEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWELVE, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_THIRTEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_FOURTEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_FIFTEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_SIXTEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_SEVENTEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_EIGHTEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_NINETEEN, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY_ONE, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY_TWO, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY_THREE, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY_FOUR, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY_FIVE, .mcuPin = PIN_NOT_SET },
	{ .connectorPin = InterconnectPin::IP_TWENTY_SIX, .mcuPin = PIN_NOT_SET },
};


template<typename Callback>
bool withPin( const InterconnectPin iPin, Callback callback )
{
	if( !iPin || iPin >= InterconnectPin::IP_COUNT )
	{
		return false;
	}
	auto mcuPin = pinMap[ iPin ].mcuPin;
	if( mcuPin == PIN_NOT_SET )
	{
		return false;
	}
	callback( mcuPin );
}

void setupSensorPins()
{
	withPin( tempSensor.sensePin, []( McuPin mcuPin ) { pinMode( mcuPin, OUTPUT ); } );

	auto setPinAsInput = []( McuPin mcuPin ) { pinMode( mcuPin, INPUT ); };

	withPin( encoder.signalPinA, setPinAsInput );
	withPin( encoder.signalPinC, setPinAsInput );

	auto writeHigh = []( McuPin mcuPin ) { digitalWrite( mcuPin, HIGH ); };

	withPin( encoder.signalPinA, writeHigh );
	withPin( encoder.signalPinC, writeHigh );
}

void setupKeypadPins()
{
	auto setPinAsInputPullup = []( McuPin mcuPin ) { pinMode( mcuPin, INPUT_PULLUP ); };

	for( unsigned i = 0; i < FdmButtonType::FBT_COUNT; i++ )
	{
		auto fdmButton = buttons[ i ];

		withPin( fdmButton.signalPin, setPinAsInputPullup );
	}
}


template<typename ReprType, ReprType DefaultValue = 0x00, unsigned short ExtBitOffset = 0x00,
		 unsigned short ExtBitMask = 0xFF>
struct DataPoint
{
	using bitMask = ExtBitMask;
	using bitOffset = ExtBitOffset;
	using defaultValue = DefaultValue;

	ReprType value;

	constexpr DataPoint() : value( defaultValue ) {}

	operator ReprType() const { return value; }

	operator=( ReprType newValue ){ value = newValue };

	inline operator unsigned long() const { return ( bitMask & value ) << bitOffset; }

	inline unsigned long operator|( const unsigned long &other ) const
	{
		return static_cast<unsigned long>( this ) | other;
	};

	// template<typename OtherDataPoint>
	// unsigned long operator|( const OtherDataPoint &rhs ) const
	//{
	//	return static_cast<unsigned long>( this ) | static_cast<unsigned long>( rhs );
	// }
};

enum ButtonState
{
	BS_RELEASED = 0,
	BS_PRESSED = 1,
};

template<unsigned short BitOffset>
using Button = DataPoint<ButtonState, ButtonState::BS_RELEASED, BitOffset, 1>;

}

#endif // BUTTONS_H
