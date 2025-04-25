#ifndef HVAC_STATUS_H
#define HVAC_STATUS_H

#include "Core/BitFieldMember.h"
#include "Core/Can.h"

namespace Keypad
{

template<typename ReprType, ReprType DefaultValue = 0x00, unsigned short ExtBitOffset = 0x00, unsigned short ExtBitMask = 0xFF>
struct DataPoint
{
	using bitMask = ExtBitMask;
	using bitOffset = ExtBitOffset;
	using defaultValue = DefaultValue;

	ReprType value;
	
	constexpr DataPoint() : value( defaultValue ) {}

	operator ReprType() const { return value; }

	operator=( ReprType newValue ){ value = newValue };

	inline operator unsigned long() const { return (bitMask & value ) << bitOffset; }

	inline unsigned long operator|( const unsigned long &other ) const {
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


struct HvacStatus
{
	// Byte 0
	Button<31> ac;
	Button<30> airSource;
	Button<29> rearDemist;

	// Byte 1
	Button<27> vent;
	Button<25> hvacAuto;
	Button<24> hvacOff;
	Button<23> fanIncrease;
	Button<22> fanReduce;
	Button<21> frontDemist;

	// Byte 2
	Button<15> tempIncrease;
	Button<14> tempReduce;
	Button<8> hazard;

	// Byte 3
	Button<6> lock;
	Button<5> interiorLight;
	Button<4> dynamicStabilityControl;
	Button<2> unlock;

	// Byte 4
	DataPoint<unsigned char, 0, 3> cabinTemp;
};

struct CanHvacStatus
{
	const uint32_t arbitrationId = 0x407;
	union
	{
		unsigned short bytes[ 8 ];
		unsigned long dwords[ 2 ];
	} data = { 0l, 0l };

	CanHvacStatus( const HvacStatus &hvacStatus )
	{

		//auto x = hvacStatus.fanIncrease | static_cast<unsigned long>( hvacStatus.hvacOff );
		data.dwords[ 0 ] = static_cast<unsigned long>(
				hvacStatus.airSource) | hvacStatus.rearDemist | hvacStatus.ac | hvacStatus.frontDemist |
				hvacStatus.fanReduce | hvacStatus.fanIncrease | hvacStatus.hvacOff | hvacStatus.hvacAuto |
				hvacStatus.vent | hvacStatus.hazard | hvacStatus.tempReduce | hvacStatus.tempIncrease |
				hvacStatus.unlock | hvacStatus.dynamicStabilityControl | hacStatus.interiorLight | hvacStatus.lock );

		data.dwords[ 1 ] = hvacStatus.cabinTemp;
	}
};

void outputHvacStatus()
{
	auto hvacStatus = HvacStatus{};

	CanHvacStatus canHvacStatus( hvacStatus );
	canHvacStatus.data.dwords auto result = Core::Can::send( CanHvacStatus{ HvacStatus{} } );

	if( result != Core::Can::SEND_FAILED )
	{
		// success, result contains the mailbox (0, 1, or 2) the message was placed in
	}
}

} // namespace Keypad

#endif // HVAC_STATUS_H
