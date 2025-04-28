#include "Main.h"

using Core::Timer;


const auto allTimers[ 5 ] = {
	// Update the internal state of the Keypad every 25 milliseconds
	Timer<25>{ []() { Keypad::UpdateKeypadState(); } },

	// Output the CAN with the new state of the Media Key States every 100ms
	Timer<100>{ []() { Keypad::MediaControlState::OutputMediaControlState(); } },

	// Output the CAN with the new state of the Media Key States every 1250ms
	Timer<125>{ []() { Icc::KeepAlive::OutputKeepAlive(); } },

	
	// Output the CAN with the new state of the ACM Keepalive every 100ms
	Timer<125>{ []() { Acm::KeepAlive::OutputKeepAlive(); } },


	// Output the CAN with the new state of the Media Key States every 500ms
	Timer<500>{ []() { Keypad::HvacControlState::OutputHvacControlState(); } },

	// Update the internal state of the Cabin Temp Sensor every 10 seconds
	Timer<10000>{ []() { Keypad::CabinTempSensor::UpdateCabinTempSensor } },
	
};

void InitGpio () {  }
void InitGpio () {  }
void InitUsart (){ 
	// initialize serial to 38.4kbps - this is the speed that head units listen at
	// Serial.begin( 115200 );
}

void Setup()
{
	Core::Timer::InitTimerSystem();
	// Core::InitGpio();
	// Core::InitUsart();
	Core::Can::InitCanSystem();

	Keypad::RotaryDial::InitRotaryDialSystem();

	/*	
	usart_setup();
	clock_setup();
	gpio_setup();
	can_setup();
	*/



}


void Loop()
{
	for( auto timer: allTimers )
	{
		timer.Tick( Timer::GetSysUptimeMs() );
	}
}


void main()
{
	Setup();

	Loop();
}


/*
ADC_HandleTypeDef hadc1;

CAN_HandleTypeDef hcan1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

int main( void )
{


	// Reset of all peripherals, Initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	// Initialize all configured peripherals
	MX_GPIO_Init();
	MX_ADC1_Init();
	MX_CAN1_Init();
	MX_USART1_UART_Init();
	MX_TIM2_Init();
	while( 1 )
	{
	}
}

//  System Clock Configuration
void SystemClock_Config( void )
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

// Configure the main internal regulator output voltage
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );

	// Initializes the RCC Oscillators according to the specified parameters
	// in the RCC_OscInitTypeDef structure.
	//
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
	{
		Error_Handler();
	}

	// Initializes the CPU, AHB and APB buses clocks
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_0 ) != HAL_OK )
	{
		Error_Handler();
	}
}

// ADC1 Initialization Function
static void MX_ADC1_Init( void )
{

	ADC_ChannelConfTypeDef sConfig = { 0 };

	// Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if( HAL_ADC_Init( &hadc1 ) != HAL_OK )
	{
		Error_Handler();
	}

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if( HAL_ADC_ConfigChannel( &hadc1, &sConfig ) != HAL_OK )
	{
		Error_Handler();
	}
}

// CAN1 Initialization Function
static void MX_CAN1_Init( void )
{
	hcan1.Instance = CAN1;
	hcan1.Init.Prescaler = 80;
	hcan1.Init.Mode = CAN_MODE_NORMAL;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_10TQ;
	hcan1.Init.TimeSeg2 = CAN_BS2_5TQ;
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.AutoBusOff = ENABLE;
	hcan1.Init.AutoWakeUp = ENABLE;
	hcan1.Init.AutoRetransmission = ENABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;
	if( HAL_CAN_Init( &hcan1 ) != HAL_OK )
	{
		Error_Handler();
	}
}

 // TIM2 Initialization Function
static void MX_TIM2_Init( void )
{


	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 4294967295;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if( HAL_TIM_Base_Init( &htim2 ) != HAL_OK )
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if( HAL_TIM_ConfigClockSource( &htim2, &sClockSourceConfig ) != HAL_OK )
	{
		Error_Handler();
	}
	if( HAL_TIM_PWM_Init( &htim2 ) != HAL_OK )
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if( HAL_TIMEx_MasterConfigSynchronization( &htim2, &sMasterConfig ) != HAL_OK )
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if( HAL_TIM_PWM_ConfigChannel( &htim2, &sConfigOC, TIM_CHANNEL_1 ) != HAL_OK )
	{
		Error_Handler();
	}

	HAL_TIM_MspPostInit( &htim2 );
}

 // USART1 Initialization Function
static void MX_USART1_UART_Init( void )
{

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if( HAL_UART_Init( &huart1 ) != HAL_OK )
	{
		Error_Handler();
	}

}

// GPIO Initialization Function
static void MX_GPIO_Init( void )
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Configure GPIO pin Output Level
	HAL_GPIO_WritePin( ROTARY_C_GPIO_Port, ROTARY_C_Pin, GPIO_PIN_RESET );

	// Configure GPIO pins : PA6 ROTARY_BY_Pin
	GPIO_InitStruct.Pin = GPIO_PIN_6 | ROTARY_BY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

	// Configure GPIO pin : ROTARY_C_Pin
	GPIO_InitStruct.Pin = ROTARY_C_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init( ROTARY_C_GPIO_Port, &GPIO_InitStruct );

}
//  This function is executed in case of error occurrence.
void Error_Handler( void )
{
	__disable_irq();
	while( 1 )
	{
	}
}

*/
