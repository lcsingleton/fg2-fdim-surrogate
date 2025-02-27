
enum InterconnectPin
{
	ONE, // LED +
	TWO, // LED -
	THREE, // NC
	FOUR, // NC
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	ELEVEN,
	TWELVE,
	THIRTEEN,
	FOURTEEN,
	FIFTEEN,
	SIXTEEN,
	SEVENTEEN,
	EIGHTEEN,
	NINETEEN,
	TWENTY,
	TWENTY_ONE,
	TWENTY_TWO,
	TWENTY_THREE,
	TWENTY_FOUR,
	TWENTY_FIVE,
	TWENTY_SIX,

	COUNT,
};

enum FdimButtonType
{
	HVAC_OFF,
	RECIRC,
	AC,
	AUTO,
	HAZARD,
	FRONT_DEMIST,
	VENTS,
	REAR_DEMIST,
	PASS_TEMP_MINUS,
	PASS_TEMP_PLUS,
	FAN_MINUS,
	FAN_PLUS,
	DRIVER_TEMP_MINUS,
	DRIVER_TEMP_PLUS,
	EJECT,
	SOURCE_CD,
	SCN_AS,
	SOURCE_MEDIA,
	SOURCE_FM_AM,
	BACK,
	OK,
	MENU,
	AUDIO_POWER,
	SEEK_LEFT,
	SEEK_RIGHT,
	LOCK,
	UNLOCK,
	DSC,
	INTERIOR_LIGHT,

	COUNT
};

struct FdimButton
{
	FdimButtonType buttonType;
	InterconnectPin signalPin;
	InterconnectPin groundPin;
	const char *displayName;
};


struct FdimRotaryEncoder
{
	InterconnectPin signalPinA;
	InterconnectPin signalPinC;
	InterconnectPin groundPinB;
	const char *displayName;
};

struct FdimTempSensor
{
	InterconnectPin sensePin;
	InterconnectPin groundPin;
	const char *displayName;
};

const char * InterconnectPinDisplayNameMap[InterconnectPin::COUNT] = {

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
	"TWENTY_TWO",
	"TWENTY_THREE",
	"TWENTY_FOUR",
	"TWENTY_FIVE",
	"TWENTY_SIX",
}


const FdimButton buttons[FdimButtonType::COUNT] = {
	{ FdimButtonType::HVAC_OFF, 		InterconnectPin::ELEVEN, 	InterconnectPin::SIXTEEN, "Toggle HVAC"},
	{ FdimButtonType::RECIRC, 			InterconnectPin::TWELVE, 	InterconnectPin::SIXTEEN, "Recirc/Fresh"},
	{ FdimButtonType::AC, 				InterconnectPin::THIRTEEN, 	InterconnectPin::SIXTEEN, "Toggle Air Conditioning"},
	{ FdimButtonType::AUTO, 			InterconnectPin::FOURTEEN, 	InterconnectPin::SIXTEEN, "Enable Climate Control"},

	{ FdimButtonType::FAN_MINUS, 		InterconnectPin::ELEVEN, 	InterconnectPin::SEVENTEEN, "Reduce Fan Speed"},
	{ FdimButtonType::FAN_PLUS, 		InterconnectPin::TWELVE, 	InterconnectPin::SEVENTEEN, "Increase Fan Speed"},
	{ FdimButtonType::PASS_TEMP_PLUS, 	InterconnectPin::THIRTEEN, 	InterconnectPin::SEVENTEEN, "Increase Passenger Temp"},
	{ FdimButtonType::PASS_TEMP_MINUS, 	InterconnectPin::FOURTEEN, 	InterconnectPin::SEVENTEEN, "Reduce Passenger Temp"},

	{ FdimButtonType::VENTS,			InterconnectPin::ELEVEN, 	InterconnectPin::EIGHTEEN , "Cycle Vents"},
	{ FdimButtonType::FRONT_DEMIST,		InterconnectPin::TWELVE, 	InterconnectPin::EIGHTEEN, "Toggle Windscreen Demister"},
	{ FdimButtonType::DRIVER_TEMP_MINUS,InterconnectPin::THIRTEEN, 	InterconnectPin::EIGHTEEN, "Reduce Temperature"},
	{ FdimButtonType::DRIVER_TEMP_PLUS,	InterconnectPin::FOURTEEN, 	InterconnectPin::EIGHTEEN, "Increase Temperature"},
	{ FdimButtonType::REAR_DEMIST,		InterconnectPin::FIFTEEN, 	InterconnectPin::EIGHTEEN, "Toggle Rear Demister"},

	{ FdimButtonType::DSC,				InterconnectPin::ELEVEN, 	InterconnectPin::NINETEEN, "Toggle Stability Control"},
	{ FdimButtonType::SCN_AS,			InterconnectPin::TWELVE, 	InterconnectPin::NINETEEN, "Scan Radio"},
	{ FdimButtonType::SOURCE_MEDIA,		InterconnectPin::THIRTEEN, 	InterconnectPin::NINETEEN, "Cycle Media Audio Sources"},
	{ FdimButtonType::SOURCE_FM_AM,		InterconnectPin::FOURTEEN, 	InterconnectPin::NINETEEN, "Cycle FM, AM Audio Sources"},
	{ FdimButtonType::BACK,				InterconnectPin::SIXTEEN, 	InterconnectPin::NINETEEN, "Back"},

	{ FdimButtonType::SOURCE_CD,		InterconnectPin::ELEVEN, 	InterconnectPin::TWENTY, "Select CD Audio Source"},
	{ FdimButtonType::OK,			 	InterconnectPin::TWELVE, 	InterconnectPin::TWENTY, "OK"},
	{ FdimButtonType::MENU,			 	InterconnectPin::THIRTEEN, 	InterconnectPin::TWENTY, "Menu"},
	{ FdimButtonType::SEEK_LEFT,		InterconnectPin::FOURTEEN, 	InterconnectPin::TWENTY, "Seek Lower"},
	{ FdimButtonType::SEEK_RIGHT,		InterconnectPin::FIFTEEN, 	InterconnectPin::TWENTY, "Seek Higher"},

	{ FdimButtonType::HAZARD,       	InterconnectPin::FIVE, 		InterconnectPin::TWENTY_TWO, "Toggle Hazard Lights"},
	{ FdimButtonType::AUDIO_POWER,  	InterconnectPin::SIX, 		InterconnectPin::TWENTY_TWO, "Toggle Audio Power"},
	{ FdimButtonType::EJECT,        	InterconnectPin::SEVEN, 	InterconnectPin::TWENTY_TWO, "Eject CD"},
	{ FdimButtonType::LOCK,       		InterconnectPin::EIGHT, 	InterconnectPin::TWENTY_TWO, "Lock Car Doors"},
	{ FdimButtonType::UNLOCK,       	InterconnectPin::NINE, 		InterconnectPin::TWENTY_TWO, "Unlock Car Doors"},
	{ FdimButtonType::INTERIOR_LIGHT,   InterconnectPin::TWELVE, 	InterconnectPin::TWENTY_TWO, "Toggle Cabin Light"},
};


const FdimRotaryEncoder encoder = {
	InterconnectPin::TWENTY_TWO,
	InterconnectPin::TWENTY_THREE,
	InterconnectPin::TWENTY_SIX,
	"Volume Control"
};

const FdimTempSensor tempSensor = {
	InterconnectPin::TWENTY_FIVE,
	InterconnectPin::TWENTY_FOUR,
	"Cabin Temp Sensor"
};


enum DigitalPinStatus
{
	UNKNOWN = 0,
	ON = 1,
	OFF = 2,
};


DigitalPinStatus lastButtonState[FdimButtonType::COUNT] = {};
DigitalPinStatus currentButtonState[FdimButtonType::COUNT] = {};

struct InterconnectPinMap
{
	InterconnectPin connectorPin;
	unsigned mcuPin;
};


const InterconnectPinMap pinMap[InterconnectPin::COUNT] = {
	{ .connectorPin = InterconnectPin::EIGHT, .mcuPin = 2 },
	{ InterconnectPin::EIGHT, 3 },
};


void setup()
{

	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);

	for (unsigned i = 0; i < FdimButtonType::COUNT; i++)
	{
		auto fdimButton = buttons[i];
		auto pin = pinMap[fdimButton.signalPin];
		// Make all pins 5V
		pinMode(pin, INPUT_PULLUP);

		Serial.print("Configure Pin ");
		Serial.print(InterconnectPinDisplayNameMap[fdimButton.signalPin]);
		Serial.print(" as connected to pin ");

		Serial.print(InterconnectPinDisplayNameMap[fdimButton.groundPin]);
		Serial.print(".\n");
	}


	pinMode(pinMap[encoder.signalPinA], INPUT);
	pinMode(pinMap[encoder.signalPinC], INPUT);

	digitalWrite(pinMap[encoder.signalPinA], HIGH);
	digitalWrite(pinMap[encoder.signalPinC], HIGH);


}
// globals
int state, prevState = 0, count = 0;
/* old state, new state, change (+ means clockwise)
 * 0 2 +
 * 1 0 +
 * 2 3 +
 * 3 1 +
 * 0 1 -
 * 1 3 -
 * 2 0 -
 * 3 2 -
 */
const int encoderStates[4][4] = {
 {  0, -1,  1,  0 }, 
 {  1,  0,  0, -1 }, 
 { -1,  0,  0,  1 }, 
 {  0,  1, -1,  0 }, 
};

void loop()
{
	const auto lowBitPin = pinMap[encoder.signalPinA];
	const auto highBitPin = pinMap[encoder.signalPinC];

	state = (digitalRead(highBitPin) << 1) | digitalRead(lowBitPin);

	count += encoderStates[prevState][state];
	if (state != prevState) 
	{
		Serial.print(state, DEC);
		Serial.print(' ');
		Serial.print(prevState, DEC);
		Serial.print(' ');
		Serial.println(count, DEC);
	}

	for (int i = 0; i < FdimButtonType::COUNT; i++)
	{
		const auto 
		auto pinA = allPins[i];
		pinMode(pinA, OUTPUT);
		digitalWrite(pinA, 0);
		for (int j = 0; j < allPinCount; j++)
		{
			auto pinB = allPins[j];
			if (pinA == pinB)
			{
				continue;
			}
			// if the output pin is not the same pin being read and there is a connection
			if (!digitalRead(pinB))
			{

				currentState[j][i] = PinStatus::ON;
			}
			else
			{
				currentState[j][i] = PinStatus::OFF;
			}
		}
		// set pin back to input before moving on to the next pin
		pinMode(pinA, INPUT_PULLUP);
	}

	auto hasChanges = false;

	for (int i = 0; i < allPinCount && !hasChanges; i++)
	{
		for (int j = 0; j < allPinCount; j++)
		{
			if (j == i)
			{
				continue;
			}
			auto lastValue = lastState[j][i];
			auto currentValue = currentState[j][i];

			if (lastValue != currentValue)
			{
				hasChanges = true;
		break;
			}
		}
	}

	if (hasChanges)
	{
		Serial.println();


//   for (int i = 0; i < allPinCount; i++)
//   {
// 	  Serial.print(i% 10);
//     for (int j = 0; j < allPinCount; j++)
//     {
// 	  Serial.print(j% 10);
//       if (j == i)
//       {
// 		  Serial.print(" ");
//         continue;
//       }
//       auto lastValue = lastState[j][i];
//       auto currentValue = currentState[j][i];

// 	  if (lastValue == currentValue)
// 	  {
// 		 Serial.print(" ");
// 		 continue;
// 	  }

// 	if (currentValue == PinStatus::ON ){
// 		  Serial.print("#");
// 	  }
// 	  else
// 	  {
// 		  Serial.print("-");

// 	  }
//     }
// 	Serial.println();
//   }

		memcpy(lastButtonState, currentButtonState, sizeof(lastState));
	}

	// for( unsigned groundPinIndex = 0; groundPinIndex < allPinCount && !hasChanges; groundPinIndex++ )
	// {
	// 	auto groundPin = allPins[groundPinIndex];

	// 	for ( auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++ )
	// 	{
	// 		auto lastValue = lastState[signalPinIndex][groundPinIndex];
	// 		auto currentValue = currentState[signalPinIndex][groundPinIndex];
	// 	}
	// }

	// Serial.print("   ");
	// for ( auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++ )
	// {
	// 	auto connectorPin = signalPinIndex + 5;
	// 	if(signalPinIndex < 10) {
	// 		Serial.print(" ");
	// 	}
	// 	Serial.print(connectorPin);
	// 	Serial.print(" ");

	// }
	// Serial.print("\n");

	// for( unsigned groundPinIndex = 0; groundPinIndex < allPinCount; groundPinIndex++ )
	// {

	// 	auto connectorPin = groundPinIndex + 5;
	// 	if(groundPinIndex < 10) {
	// 		Serial.print(" ");
	// 	}
	// 	Serial.print(connectorPin);
	// 	Serial.print(" ");

	// 	for ( auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++ )
	// 	{
	// 		auto lastValue = lastState[signalPinIndex][groundPinIndex];
	// 		auto currentValue = currentState[signalPinIndex][groundPinIndex];
	// 			Serial.print(" ");
	// 		if (currentValue == PinStatus::OFF) {
	// 			Serial.print("+");
	// 		}
	// 		 else if (currentValue == PinStatus::ON)
	// 		 {
	// 			Serial.print("-");
	// 		} else {
	// 			Serial.print(" ");
	// 		}
	// 			Serial.print(" ");
	// 	}
	// 	Serial.print("\n");
	// }

	// }
}
