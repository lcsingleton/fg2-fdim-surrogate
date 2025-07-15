#ifndef KEYPAD_PINS_H
#define KEYPAD_PINS_H

namespace Keypad
{
namespace Pins
{

enum InterconnectPin
{
	IP_ONE, // LED +
	IP_TWO, // LED -
	IP_THREE, // NC
	IP_FOUR, // NC
	IP_FIVE,
	IP_SIX,
	IP_SEVEN,
	IP_EIGHT,
	IP_NINE,
	IP_TEN,
	IP_ELEVEN,
	IP_TWELVE,
	IP_THIRTEEN,
	IP_FOURTEEN,
	IP_FIFTEEN,
	IP_SIXTEEN,
	IP_SEVENTEEN,
	IP_EIGHTEEN,
	IP_NINETEEN,
	IP_TWENTY,
	IP_TWENTY_ONE,
	IP_TWENTY_TWO,
	IP_TWENTY_THREE,
	IP_TWENTY_FOUR,
	IP_TWENTY_FIVE,
	IP_TWENTY_SIX,

	IP_COUNT,
};

const char *InterconnectPinDisplayNameMap[ InterconnectPin::IP_COUNT ] = {

	"LED+", // LED +
	"LED-", // LED -
	"NC", // NC
	"NC", // NC
	"FIVE",
	"SIX",
	"SEVEN",
	"EIGHT",
	"NINE",
	"TEN",
	"ELEVEN",
	"TWELVE",
	"THIRTEEN",
	"FOURTEEN",
	"FIFTEEN",
	"SIXTEEN",
	"SEVENTEEN",
	"EIGHTEEN",
	"NINETEEN",
	"TWENTY",
	"TWENTY_ONE",
	"ROTARY_ENCODER_A",
	"ROTARY_ENCODER_C",
	"TEMP_SENSE",
	"GROUND",
	"ROTARY_ENCODER_B",
};

} // namespace Pins
} // namespace Keypad

#endif // KEYPAD_PINS_H
