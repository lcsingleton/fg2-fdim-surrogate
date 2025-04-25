#ifndef MAIN_H
#define MAIN_H

// Reset and Clock Controls
#include <libopencm3/stm32/rcc.h>

//
#include <libopencm3/stm32/gpio.h>

// Timer Features
#include <libopencm3/cm3/systick.h>

// Interrupt RegisterControls
#include <libopencm3/cm3/nvic.h>

// CAN System
#include <libopencm3/stm32/can.h>

// Register definitions for the MCU
#include <Chip/Unknown/STMicro/STM32F41x/CAN1.hpp>

#include "Core/Timer.h"
#include "Core/Can.h"
#include "Acm/KeepAlive.h"
#include "Icc/KeepAlive.h"
#include "Keypad/HvacStatus.h"
#include "Keypad/KeypadStatus.h"

#endif //MAIN_H
