// #include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

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
	const char* displayName;
};


struct FdmRotaryEncoder
{
	InterconnectPin signalPinA;
	InterconnectPin signalPinC;
	InterconnectPin groundPinB;
	const char* displayName;
};

struct FdmTempSensor
{
	InterconnectPin sensePin;
	InterconnectPin groundPin;
	const char* displayName;
};

const char* InterconnectPinDisplayNameMap[InterconnectPin::IP_COUNT] = {

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


const FdmButton buttons[FdmButtonType::FBT_COUNT] = {
  { FdmButtonType::FBT_HVAC_OFF,    InterconnectPin::IP_ELEVEN,   InterconnectPin::IP_SIXTEEN, "Toggle HVAC"},
  { FdmButtonType::FBT_RECIRC,      InterconnectPin::IP_TWELVE,   InterconnectPin::IP_SIXTEEN, "Recirc/Fresh"},
  { FdmButtonType::FBT_AC,        InterconnectPin::IP_THIRTEEN,   InterconnectPin::IP_SIXTEEN, "Toggle Air Conditioning"},
  { FdmButtonType::FBT_AUTO,      InterconnectPin::IP_FOURTEEN,   InterconnectPin::IP_SIXTEEN, "Enable Climate Control"},

  { FdmButtonType::FBT_FAN_MINUS,     InterconnectPin::IP_ELEVEN,   InterconnectPin::IP_SEVENTEEN, "Reduce Fan Speed"},
  { FdmButtonType::FBT_FAN_PLUS,    InterconnectPin::IP_TWELVE,   InterconnectPin::IP_SEVENTEEN, "Increase Fan Speed"},

  // This is conjecture - I don't have a DZ Climate Control ICC
  { FdmButtonType::FBT_PASS_TEMP_PLUS,  InterconnectPin::IP_THIRTEEN,   InterconnectPin::IP_SEVENTEEN, "Increase Passenger Temp"},
  { FdmButtonType::FBT_PASS_TEMP_MINUS,   InterconnectPin::IP_FOURTEEN,   InterconnectPin::IP_SEVENTEEN, "Reduce Passenger Temp"},

  { FdmButtonType::FBT_VENTS,     InterconnectPin::IP_ELEVEN,   InterconnectPin::IP_EIGHTEEN , "Cycle Vents"},
  { FdmButtonType::FBT_FRONT_DEMIST,    InterconnectPin::IP_TWELVE,   InterconnectPin::IP_EIGHTEEN, "Toggle Windscreen Demister"},
  { FdmButtonType::FBT_DRIVER_TEMP_MINUS,InterconnectPin::IP_THIRTEEN,  InterconnectPin::IP_EIGHTEEN, "Reduce Temperature"},
  { FdmButtonType::FBT_DRIVER_TEMP_PLUS,  InterconnectPin::IP_FOURTEEN,   InterconnectPin::IP_EIGHTEEN, "Increase Temperature"},
  { FdmButtonType::FBT_REAR_DEMIST,   InterconnectPin::IP_FIFTEEN,  InterconnectPin::IP_EIGHTEEN, "Toggle Rear Demister"},

  { FdmButtonType::FBT_DSC,       InterconnectPin::IP_ELEVEN,   InterconnectPin::IP_NINETEEN, "Toggle Stability Control"},
  { FdmButtonType::FBT_SCN_AS,      InterconnectPin::IP_TWELVE,   InterconnectPin::IP_NINETEEN, "Scan Radio"},
  { FdmButtonType::FBT_SOURCE_MEDIA,    InterconnectPin::IP_THIRTEEN,   InterconnectPin::IP_NINETEEN, "Cycle Media Audio Sources"},
  { FdmButtonType::FBT_SOURCE_FM_AM,    InterconnectPin::IP_FOURTEEN,   InterconnectPin::IP_NINETEEN, "Cycle FM, AM Audio Sources"},
  { FdmButtonType::FBT_BACK,        InterconnectPin::IP_SIXTEEN,  InterconnectPin::IP_NINETEEN, "Back"},

  { FdmButtonType::FBT_SOURCE_CD,   InterconnectPin::IP_ELEVEN,   InterconnectPin::IP_TWENTY, "Select CD Audio Source"},
  { FdmButtonType::FBT_OK,        InterconnectPin::IP_TWELVE,   InterconnectPin::IP_TWENTY, "OK"},
  { FdmButtonType::FBT_MENU,        InterconnectPin::IP_THIRTEEN,   InterconnectPin::IP_TWENTY, "Menu"},
  { FdmButtonType::FBT_SEEK_LEFT,   InterconnectPin::IP_FOURTEEN,   InterconnectPin::IP_TWENTY, "Seek Lower"},
  { FdmButtonType::FBT_SEEK_RIGHT,    InterconnectPin::IP_FIFTEEN,  InterconnectPin::IP_TWENTY, "Seek Higher"},

  { FdmButtonType::FBT_HAZARD,        InterconnectPin::IP_FIVE,     InterconnectPin::IP_TWENTY_TWO, "Toggle Hazard Lights"},
  { FdmButtonType::FBT_AUDIO_POWER,   InterconnectPin::IP_SIX,    InterconnectPin::IP_TWENTY_TWO, "Toggle Audio Power"},
  { FdmButtonType::FBT_EJECT,         InterconnectPin::IP_SEVEN,  InterconnectPin::IP_TWENTY_TWO, "Eject CD"},
  { FdmButtonType::FBT_LOCK,          InterconnectPin::IP_EIGHT,  InterconnectPin::IP_TWENTY_TWO, "Lock Car Doors"},
  { FdmButtonType::FBT_UNLOCK,        InterconnectPin::IP_NINE,     InterconnectPin::IP_TWENTY_TWO, "Unlock Car Doors"},
  { FdmButtonType::FBT_INTERIOR_LIGHT,   InterconnectPin::IP_TEN,   InterconnectPin::IP_TWENTY_TWO, "Toggle Cabin Light"},
};


const FdmRotaryEncoder encoder = {
  InterconnectPin::IP_TWENTY_TWO,
  InterconnectPin::IP_TWENTY_THREE,
  InterconnectPin::IP_TWENTY_SIX,
  "Volume Control"
};

const FdmTempSensor tempSensor = {
  InterconnectPin::IP_TWENTY_FIVE,
  InterconnectPin::IP_TWENTY_FOUR,
  "Cabin Temp Sensor"
};


enum FdmButtonStatus
{
	UNKNOWN = 0,
	ON = 1,
	OFF = 2,
};

// ---------------------------------------
// Current System Status Variables
// ---------------------------------------
FdmButtonStatus lastButtonStatus[FdmButtonType::FBT_COUNT] = {};
FdmButtonStatus currentButtonStatus[FdmButtonType::FBT_COUNT] = {};

struct InterconnectPinMap
{
	InterconnectPin connectorPin;
	unsigned mcuPin;
};


const unsigned PIN_NOT_SET = 0XFF;

const InterconnectPinMap pinMap[InterconnectPin::IP_COUNT] = {
	// TODO: Fill this out when the header is completed
	{.connectorPin = InterconnectPin::IP_ONE, .mcuPin = PIN_NOT_SET },  // LED +
	{.connectorPin = InterconnectPin::IP_TWO, .mcuPin = PIN_NOT_SET },  // LED -
	{.connectorPin = InterconnectPin::IP_THREE, .mcuPin = PIN_NOT_SET },  // NC
	{.connectorPin = InterconnectPin::IP_FOUR, .mcuPin = PIN_NOT_SET },  // NC
	{.connectorPin = InterconnectPin::IP_FIVE, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_SIX, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_SEVEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_EIGHT, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_NINE, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_ELEVEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWELVE, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_THIRTEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_FOURTEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_FIFTEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_SIXTEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_SEVENTEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_EIGHTEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_NINETEEN, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY_ONE, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY_TWO, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY_THREE, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY_FOUR, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY_FIVE, .mcuPin = PIN_NOT_SET },
	{.connectorPin = InterconnectPin::IP_TWENTY_SIX, .mcuPin = PIN_NOT_SET },
};


bool withPin(const InterconnectPin iPin, void (*callback)(unsigned))
{
	if (!iPin || iPin >= InterconnectPin::IP_COUNT)
	{
		return false;
	}
	auto mcuPin = pinMap[iPin].mcuPin;
	if (mcuPin == PIN_NOT_SET)
	{
		return false;
	}
	callback(mcuPin);
}


void setupSensorPins()
{
  withPin(tempSensor.sensePin, [](unsigned mcuPin) { pinMode(mcuPin, OUTPUT); });

  auto setPinAsInput = [](unsigned mcuPin) { pinMode(mcuPin, INPUT); };

  withPin(encoder.signalPinA, setPinAsInput);
  withPin(encoder.signalPinC, setPinAsInput);

  auto writeHigh = [](unsigned mcuPin) { digitalWrite(mcuPin, HIGH); };

  withPin(encoder.signalPinA, writeHigh);
  withPin(encoder.signalPinC, writeHigh);
}

void setupKeypadPins()
{
  auto setPinAsInputPullup = [](unsigned mcuPin) { pinMode(mcuPin, INPUT_PULLUP); };

  for (unsigned i = 0; i < FdmButtonType::FBT_COUNT; i++)
  {
	auto fdmButton = buttons[i];

	withPin(fdmButton.signalPin, setPinAsInputPullup);
  }

}


MCP_CAN msCan(53);

void setupCanComms()
{

	if (msCan.begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK)
	{
		Serial.println("Start CAN succeeded Initialized Successfully!");
	}
	else {
		Serial.println("Starting CAN failed!");
		while (1);
	}
	msCan.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

void setup()
{

	// initialize serial to 38.4kbps - this is the speed that head units listen at
	Serial.begin(115200);

	// setupSensorPins();
	// setupKeypadPins();
	setupCanComms();

}


//
// Read the status of all the input pins and sensors, then update the stored status of the system
//
/*
void readInputState()
{

	for (int i = 0; i < FdmButtonType::FBT_COUNT; i++)
	{
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
		//    Serial.print(i% 10);
		//     for (int j = 0; j < allPinCount; j++)
		//     {
		//    Serial.print(j% 10);
		//       if (j == i)
		//       {
		//      Serial.print(" ");
		//         continue;
		//       }
		//       auto lastValue = lastState[j][i];
		//       auto currentValue = currentState[j][i];

		//    if (lastValue == currentValue)
		//    {
		//     Serial.print(" ");
		//     continue;
		//    }

		//  if (currentValue == PinStatus::ON ){
		//      Serial.print("#");
		//    }
		//    else
		//    {
		//      Serial.print("-");

		//    }
		//     }
		//  Serial.println();
		//   }

		memcpy(lastButtonState, currentButtonState, sizeof(lastState));
	}

	// for( unsigned groundPinIndex = 0; groundPinIndex < allPinCount && !hasChanges; groundPinIndex++ )
	// {
	//  auto groundPin = allPins[groundPinIndex];

	//  for ( auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++ )
	//  {
	//    auto lastValue = lastState[signalPinIndex][groundPinIndex];
	//    auto currentValue = currentState[signalPinIndex][groundPinIndex];
	//  }
	// }

	// Serial.print("   ");
	// for ( auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++ )
	// {
	//  auto connectorPin = signalPinIndex + 5;
	//  if(signalPinIndex < 10) {
	//    Serial.print(" ");
	//  }
	//  Serial.print(connectorPin);
	//  Serial.print(" ");

	// }
	// Serial.print("\n");

	// for( unsigned groundPinIndex = 0; groundPinIndex < allPinCount; groundPinIndex++ )
	// {

	//  auto connectorPin = groundPinIndex + 5;
	//  if(groundPinIndex < 10) {
	//    Serial.print(" ");
	//  }
	//  Serial.print(connectorPin);
	//  Serial.print(" ");

	for (auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++)
	{
		auto lastValue = lastState[signalPinIndex][groundPinIndex];
		auto currentValue = currentState[signalPinIndex][groundPinIndex];
		Serial.print(" ");
		if (currentValue == PinStatus::OFF) {
			Serial.print("+");
		}
		else if (currentValue == PinStatus::ON)
		{
			Serial.print("-");
		}
		else {
			Serial.print(" ");
		}
		Serial.print(" ");
	}
	Serial.print("\n");
	// }

	// }

}*/

const int encoderStates[4][4] = {
 {  0, -1,  1,  0 },
 {  1,  0,  0, -1 },
 { -1,  0,  0,  1 },
 {  0,  1, -1,  0 },
};

void readRotaryState()
{

	const auto lowBitPin = pinMap[encoder.signalPinA].mcuPin;
	const auto highBitPin = pinMap[encoder.signalPinC].mcuPin;

	auto state = (digitalRead(highBitPin) << 1) | digitalRead(lowBitPin);

	//count += encoderStates[prevState][state];
	//if (state != prevState)
	//{
	//	Serial.print(state, DEC);
	//	Serial.print(' ');
	//	Serial.print(prevState, DEC);
	//	Serial.print(' ');
	//	Serial.println(count, DEC);
	//}
}

const auto ntcValue = 10000u;
const auto scalar = 639.5, exponent = -0.1332, offset = -162.5;


void readTempState()
{
	withPin(tempSensor.sensePin, [](unsigned mcuPin) {

		auto ntcVoltage = (analogRead(mcuPin) * 5.0) / 1023.0;
		auto ntcResistance = ntcValue * ((5.0 / ntcVoltage) - 1);
		// auto tempKelvin = a * pow(ntcResistance, exponent) + offset;

		// TODO do something with the temp now that we've calculated it.

		});

}

struct TimerFlags
{
	short _25ms = 25;
	short _100ms = 100;
	short _125ms = 125;
	short _500ms = 500;
	short _10000ms = 10000;
	unsigned long lastMs = -1l;
};

TimerFlags tf;

unsigned long getTfDeltaMs(unsigned long currentMs)
{
	auto distanceToUnderflow = 1l - tf.lastMs;


	// Check if currentMs has overflowed since lastMs was set
	if (currentMs < tf.lastMs)
	{
		Serial.println("Overflow since last exection");
		// overflow has happened
		auto lastToOverflowMs = -1l - tf.lastMs;
		return lastToOverflowMs + currentMs;
	}

	auto diff = currentMs - tf.lastMs;
	return diff;
}

void tickTimerFlags()
{
	auto ms = millis();
	auto deltaMs = getTfDeltaMs(ms);

	tf._25ms -= deltaMs;
	tf._100ms -= deltaMs;
	tf._125ms -= deltaMs;
	tf._500ms -= deltaMs;
	tf._10000ms -= deltaMs;
	tf.lastMs = ms;
}

void outputHvacStatus()
{
	char buff[8];
	buff[0] = 0x00;
	buff[1] = 0x00;
	buff[2] = 0x00;
	buff[3] = 0x00;
	buff[4] = 0xFF;
	buff[5] = 0x00;
	buff[6] = 0x00;
	buff[7] = 0x00;

	auto result = msCan.sendMsgBuf(0x307, 1, 8, buff);
	Serial.print(result);
	if (result == CAN_OK)
	{
		Serial.println("Output HVAC Status");
	}
	else
	{
		Serial.println("HVAC Status Failed");
	}
}

void outputKeepAlive()
{
	char buff[8];
	buff[0] = 0xFE;
	buff[1] = 0x00;
	buff[2] = 0x00;
	buff[3] = 0x00;
	buff[4] = 0x00;
	buff[5] = 0x00;
	buff[6] = 0x00;
	buff[7] = 0x00;

	auto result = msCan.sendMsgBuf(0x425, 1, 8, buff);
	Serial.print(result);
	if (result == CAN_OK)
	{
		Serial.println("Output Keep Alive");
	}
	else
	{
		Serial.println("Keep Alive Failed");
	}
}

bool shouldExecute(short tfAttribute)
{
	return tfAttribute <= 0;
}

void resetTimerFlags()
{
	auto ms = millis();
	auto deltaMs = getTfDeltaMs(ms);

	if (shouldExecute(tf._25ms))
	{
		tf._25ms = 25 - deltaMs;
	}
	if (shouldExecute(tf._100ms))
	{
		tf._100ms = 100 - deltaMs;
	}
	if (shouldExecute(tf._125ms))
	{
		tf._125ms = 125 - deltaMs;
	}
	if (shouldExecute(tf._500ms))
	{
		tf._500ms = 500 - deltaMs;
	}
	if (shouldExecute(tf._10000ms))
	{
		tf._10000ms = 10000 - deltaMs;
	}
}

void loop()
{
	tickTimerFlags();
	// readRotaryState();

	if (shouldExecute(tf._25ms))
	{
		// readKeypadState();
	}

	if (shouldExecute(tf._100ms))
	{
		// 2FC
		// outputMediaControlState();
	}

	if (shouldExecute(tf._125ms))
	{
		// 425
		outputKeepAlive();
	}

	if (shouldExecute(tf._500ms))
	{
		// 307
		outputHvacStatus();
	}

	if (shouldExecute(tf._10000ms))
	{
		// readTempState();
	}

	resetTimerFlags();
}
