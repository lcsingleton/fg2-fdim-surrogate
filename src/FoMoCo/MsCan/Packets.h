#ifndef FOMOCO_MSCAN_PACKETS_H
#define FOMOCO_MSCAN_PACKETS_H

#include "Core/BitPack.h"


namespace FoMoCo
{
namespace MsCan
{

// ------------------------------------------
//
// Lateral and Longitudinal G forces
// 0x397, (D5 * x + D6 ) Long or lat
// 0x397, (D7 * x + D8 ) Long or lat
// ------------------------------------------
struct Accelerometer
{

	uint16_t lateralGs = 0x0F;
	uint16_t longitudinalGs = 0x0F;
};

uint64_t PackAccelerometer(const Accelerometer& acc)
{
	return Core::BitPack::CanData<
	Core::BitPack::FixedField<0, 32>,
	Core::BitPack::Field<uint16_t, 8>,
	Core::BitPack::Field<uint16_t, 8>
	>::Pack(
		Core::BitPack::FixedField<0, 32>(),
			Core::BitPack::Field<uint16_t, 8>(acc.lateralGs),
			Core::BitPack::Field<uint16_t, 8>(acc.longitudinalGs)
	);
}

uint64_t PackAccelerometer(Accelerometer acc)
{
	return Pack(FixedField<0,32>(), // Not sure what the first 32 bits are
			Field<uint16_t, 8>(lateralGs),
			Field<uint16_t, 8>(longitudinalGs)
	);
}

} // namespace MsCan
} // namespace FoMoCo

#endif // FOMOCO_MSCAN_PACKETS_H
