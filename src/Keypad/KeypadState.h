#ifndef KEYPAD_KEYPADSTATE_H
#define KEYPAD_KEYPADSTATE_H

namespace Keypad
{
namespace KeypadState
{

// enum RotaryDialMovement
// {
// 	ROTARY_NONE,
// 	ROTARY_CLOCKWISE,
// 	ROTARY_COUNTER_CLOCKWISE
// };

// struct State
// {

// 	bool back = false;
// 	bool cd = false;
// 	bool eject = false;
// 	bool leftSeek = false;
// 	bool rightSeek = false;
// 	bool media = false;
// 	bool menu = false;
// 	bool ok = false;
// 	bool power = false;
// 	bool scan = false;
// 	bool fmAm = false;
// 	RotaryDialMovement rotaryDialMovement = ROTARY_NONE;
// 	bool ac = false;
// 	bool airSource = false;
// 	bool rearDemist = false;
// 	bool vent = false;
// 	bool hvacAuto = false;
// 	bool hvacOff = false;
// 	bool fanIncrease = false;
// 	bool fanReduce = false;
// 	bool frontDemist = false;
// 	bool tempIncrease = false;
// 	bool tempReduce = false;
// 	bool hazard = false;
// 	bool lock = false;
// 	bool interiorLight = false;
// 	bool dynamicStabilityControl = false;
// 	bool unlock = false;
// 	unsigned char cabinTemp = 0;
// };

// State &GetState();


void UpdateKeypadState();

void InitKeypadState();

} // namespace KeypadState

} // namespace Keypad

#endif // KEYPAD_KEYPADSTATE_H
