#ifndef ICCKEYPADSTATUS_H 
#define ICCKEYPADSTATUS_H

enum MsCanId
{
	RDS_MESSAGE = 0x2F5,
	ICC_BUTTONS = 0x2FC,
	ICC = 0x307,
	INTACTTEMP = 0x313,
	MENU_OPTIONS_ICC = 0x315,

	// NFI??
	PCM_CRS_ECON = 0x425,

	FDM_KEEPALIVE = 0x55C,

	// WTF??
	MSG2 = 0x6f8
};

enum FdmId
{
	
};

struct FdmKeyStatus
{

};


struct CanMessage
{
	MsCanId id;
	union CanData
	{
		unsigned[4] _unsigned;
		char[8] _char;

	} canData;
};



struct 
{
	unsigned padding1: 16;
	unsigned padding2: 16;
	bool isTempActive: 1;
	unsigned temp: 7
	char b5: 8;
	unsigned padding3: 16;
};





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

#endif