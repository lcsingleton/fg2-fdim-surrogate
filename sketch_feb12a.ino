

enum FdimButtonType
{
  UNKNOWN_FDIM_BUTTON,
  HVAC_OFF,
  RECIRC,
  AC,
  AUTO,
  HAZARD,
  FRONT_DEMIST,
  VENTS,
  REAR_DEMIST,
  PASSENGER_TEMP_MINUS,
  PASSENGER_TEMP_PLUS,
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
};

char *FdimButtonNameMap[] =
    {
        "UNKNOWN",
        "HVAC_OFF",
        "RECIRC",
        "AC",
        "AUTO",
        "HAZARD",
        "FRONT_DEMIST",
        "VENTS",
        "REAR_DEMIST",
        "PASSENGER_TEMP_MINUS",
        "PASSENGER_TEMP_PLUS",
        "FAN_MINUS",
        "FAN_PLUS",
        "TEMP_MINUS",
        "TEMP_PLUS",
        "EJECT",
        "SOURCE_CD",
        "SCN_AS",
        "SOURCE_MEDIA",
        "SOURCE_FM_AM",
        "BACK",
        "OK",
        "MENU",
        "AUDIO_POWER",
        "SEEK_LEFT",
        "SEEK_RIGHT",
        "LOCK",
        "UNLOCK",
        "DSC",
        "INTERIOR_LIGHT"};

struct FdimButton
{
  FdimButtonType buttonType;
  unsigned signalPin;
  unsigned groundPin;
  const char *displayName;
};

FdimButton buttons[] = {
    {FdimButtonType::HVAC_OFF, 11, 16, "Toggle HVAC"},
	{FdimButtonType::RECIRC, 12, 16, "Recirc/Fresh"},
	{FdimButtonType::AC, 13, 16, "Toggle Air Conditioning"},
	{FdimButtonType::AUTO, 14, 16, "Enable Climate Control"},

	{FdimButtonType::FAN_MINUS, 11, 17, "Reduce Fan Speed"},
	{FdimButtonType::FAN_PLUS, 12, 17, "Increase Fan Speed"},

	{FdimButtonType::VENTS, 11, 18 , "Cycle Vents"},
	{FdimButtonType::FRONT_DEMIST, 12, 18, "Toggle Windscreen Demister"},
	{FdimButtonType::DRIVER_TEMP_MINUS, 13, 18, "Reduce Temperature"},
	{FdimButtonType::DRIVER_TEMP_PLUS, 14, 18, "Increase Temperature"},
	{FdimButtonType::REAR_DEMIST, 15, 18, "Toggle Rear Demister"},

	{FdimButtonType::DSC, 11, 19, "Toggle Stability Control"},
	{FdimButtonType::SCN_AS, 12, 19, "Scan Radio"},
	{FdimButtonType::SOURCE_MEDIA, 13, 19, "Cycle Media Audio Sources"},
	{FdimButtonType::SOURCE_FM_AM, 14, 19, "Cycle FM, AM Audio Sources"},
	{FdimButtonType::BACK, 16, 19, "Back"},

	{FdimButtonType::SOURCE_CD, 11, 20, "Select CD Audio Source"},
	{FdimButtonType::OK, 12, 20, "OK"},
	{FdimButtonType::MENU, 13, 20, "Menu"},
	{FdimButtonType::SEEK_LEFT, 14, 20, "Seek Lower"},
	{FdimButtonType::SEEK_RIGHT, 15, 20, "Seek Higher"},

	{FdimButtonType::HAZARD, 5, 22, "Toggle Hazard Lights"},
	{FdimButtonType::AUDIO_POWER, 6, 22, "Toggle Audio Power"},
	{FdimButtonType::EJECT, 7, 22, "Eject CD"},
	{FdimButtonType::LOCK, 9, 22, "Lock Car Doors"},
	{FdimButtonType::UNLOCK, 9, 22, "Unlock Car Doors"},
	{FdimButtonType::INTERIOR_LIGHT, 12, 22, "Toggle Cabin Light"},
};

enum ConnectorPinMapIndex
{
  // ONE, LED +
  // TWO, LED -
  // THREE, NC
  // FOUR, NC
  FIVE = 21,
  SIX = 20,
  SEVEN = 23,
  EIGHT = 22,
  NINE = 25,
  TEN = 24,
  ELEVEN = 27,
  TWELVE = 26,
  THIRTEEN = 29,
  FOURTEEN = 28,
  FIFTEEN = 31,
  SIXTEEN = 30,
  SEVENTEEN = 33,
  EIGHTEEN = 32,
  NINETEEN = 35,
  TWENTY = 34,
  TWENTY_ONE = 37,
  TWENTY_TWO = 36,
  TWENTY_THREE = 39,
  TWENTY_FOUR = 38,
  TWENTY_FIVE = 41,
  TWENTY_SIX = 40,
};

unsigned allPins[] =
    {
        // ConnectorPinMapIndex::FIVE,
        // ConnectorPinMapIndex::SIX,
        // ConnectorPinMapIndex::SEVEN,
        // ConnectorPinMapIndex::EIGHT,
        // ConnectorPinMapIndex::NINE,
        // ConnectorPinMapIndex::TEN,
        // ConnectorPinMapIndex::ELEVEN,
        // ConnectorPinMapIndex::TWELVE,
        // ConnectorPinMapIndex::THIRTEEN,
        // ConnectorPinMapIndex::FOURTEEN,
        // ConnectorPinMapIndex::FIFTEEN,
        // ConnectorPinMapIndex::SIXTEEN,
        // ConnectorPinMapIndex::SEVENTEEN,
        // ConnectorPinMapIndex::EIGHTEEN,
        // ConnectorPinMapIndex::NINETEEN,
        ConnectorPinMapIndex::TWENTY,
        ConnectorPinMapIndex::TWENTY_ONE,
       ConnectorPinMapIndex::TWENTY_TWO,
      ConnectorPinMapIndex::TWENTY_THREE,
       ConnectorPinMapIndex::TWENTY_FOUR,
        ConnectorPinMapIndex::TWENTY_FIVE,
        ConnectorPinMapIndex::TWENTY_SIX,
};

const unsigned allPinCount = sizeof(allPins) / sizeof(unsigned);

const char *pinNames[] =
    {
        // "FIVE",
        // "SIX",
        // "SEVEN",
        // "EIGHT",
        // "NINE",
        // "TEN",
        // "ELEVEN",
        // "TWELVE",
        // "THIRTEEN",
        // "FOURTEEN",
        // "FIFTEEN",
        // "SIXTEEN",
        // "SEVENTEEN",
        // "EIGHTEEN",
        // "NINETEEN",
        "TWENTY",
        "TWENTY_ONE",
        "TWENTY_TWO",
       "TWENTY_THREE",
       "TWENTY_FOUR",
        "TWENTY_FIVE",
        "TWENTY_SIX",
};

enum PinStatus
{
  UNKNOWN = 0,
  ON = 1,
  OFF = 2,
};

PinStatus lastState[allPinCount][allPinCount] = {};
PinStatus currentState[allPinCount][allPinCount] = {};

int currentPinIndex = 0;


#define PIN_HIGHBIT ConnectorPinMapIndex::TWENTY_THREE
#define PIN_LOWBIT ConnectorPinMapIndex::TWENTY_TWO

void setup()
{

  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  for (unsigned i = 0; i < allPinCount; i++)
  {
    auto pin = allPins[i];
    // Make all pins 5V
    pinMode(pin, INPUT_PULLUP);

    Serial.print("Configure Pin ");
    Serial.print(pin);
    Serial.print(" as connected to pin ");

    Serial.print(pinNames[i]);
    Serial.print(".\n");
  }


  pinMode(PIN_HIGHBIT, INPUT);
  pinMode(PIN_LOWBIT, INPUT);
  digitalWrite(PIN_LOWBIT, HIGH);
  digitalWrite(PIN_HIGHBIT, HIGH);


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
int encoderStates[4][4] = {
 {  0, -1,  1,  0 }, 
 {  1,  0,  0, -1 }, 
 { -1,  0,  0,  1 }, 
 {  0,  1, -1,  0 }, 
};

void loop()
{
  state = (digitalRead(PIN_HIGHBIT) << 1) | digitalRead(PIN_LOWBIT);
  count += encoderStates[prevState][state];
    if (state != prevState) {
    Serial.print(state, DEC);
    Serial.print(' ');
    Serial.print(prevState, DEC);
    Serial.print(' ');
    Serial.println(count, DEC);
  }

  for (int i = 0; i < allPinCount; i++)
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

    memcpy(lastState, currentState, sizeof(lastState));
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
