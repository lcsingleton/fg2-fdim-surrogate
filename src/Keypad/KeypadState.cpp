#include "KeypadState.h"

#include "Buttons.h"

using namespace Keypad::KeypadState;


struct KeypadState
{
	//--------------------//
	// HIWORD             //
	//--------------------//
	Button<1> back;
	// Button<> cd
	Button<15> eject;
	Button<22> leftSeek;
	Button<23> rightSeek;
	// Button<> media;
	// Button<> menu;
	// Button<> ok;
	// Button<> power;
	// Button<> scan;
	Button<31> fmAm;

	//--------------------//
	// LOWORD             //
	//--------------------//
	Button<22> rotaryClockwise;
	Button<23> rotaryCounterClockwise;

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

//------------------------------------------------------------------------------------------------//
// Read the status of all the input pins and sensors, then update the stored status of the system //
//------------------------------------------------------------------------------------------------//
void UpdateKeypadState()
	//	{
	//for( int i = 0; i < FdmButtonType::FBT_COUNT; i++ )
	//{
	//	auto pinA = allPins[ i ];
	//	pinMode( pinA, OUTPUT );
	//	digitalWrite( pinA, 0 );
	//	for( int j = 0; j < allPinCount; j++ )
	//	{
	//		auto pinB = allPins[ j ];
	//		if( pinA == pinB )
	//		{
	//			continue;
	//		}
	//		// if the output pin is not the same pin being read and there is a connection
	//		if( !digitalRead( pinB ) )
	//		{

	//			currentState[ j ][ i ] = PinStatus::ON;
	//		} else
	//		{
	//			currentState[ j ][ i ] = PinStatus::OFF;
	//		}
	//	}
	//	// set pin back to input before moving on to the next pin
	//	pinMode( pinA, INPUT_PULLUP );
	//}

	//auto hasChanges = false;

	//for( int i = 0; i < allPinCount && !hasChanges; i++ )
	//{
	//	for( int j = 0; j < allPinCount; j++ )
	//	{
	//		if( j == i )
	//		{
	//			continue;
	//		}
	//		auto lastValue = lastState[ j ][ i ];
	//		auto currentValue = currentState[ j ][ i ];

	//		if( lastValue != currentValue )
	//		{
	//			hasChanges = true;
	//			break;
	//		}
	//	}
	//}

	//if( hasChanges )
	//{
	//	Serial.println();


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

//		memcpy( lastButtonState, currentButtonState, sizeof( lastState ) );
	//}

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

	f/*or( auto signalPinIndex = 0; signalPinIndex < allPinCount; signalPinIndex++ )
	{
		auto lastValue = lastState[ signalPinIndex ][ groundPinIndex ];
		auto currentValue = currentState[ signalPinIndex ][ groundPinIndex ];
		Serial.print( " " );
		if( currentValue == PinStatus::OFF )
		{
			Serial.print( "+" );
		} else if( currentValue == PinStatus::ON )
		{
			Serial.print( "-" );
		} else
		{
			Serial.print( " " );
		}
		Serial.print( " " );
	}
	Serial.print( "\n" );*/
	// }

	// }
}

