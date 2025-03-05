# Volkswagen Series CAN BUS Module and DVD Host Communication Protocol 1.4

## 1. Overview
This document describes the communication protocol between the DVD host system and the bus decoder, covering the physical layer, data link layer, and application layer protocols.

## 2. Physical Layer Description
- Standard UART communication interface
- Logic level: 5V TTL
- UART working mode: 8N1 (8 data bits, no parity, 1 stop bit)
- Baud rate: 38400bps

## 3. Conventions
- **HOST**: NAVI host
- **SLAVE**: Bus decoder

## 4. Data Frame Structure
| Order | Data Content | Description |
|---------|---------|------|
| 1 | Head Code | Fixed value `0x2E` |
| 2 | Data Type | Refer to DataType definitions |
| 3 | Length | Data length |
| 4 | Data0 | Data content |
| ... | ... | ... |
| N | Checksum | Checksum `SUM(DataType,Length,Data0…DataN) ^ 0xFF` |

## 5. ACK/NAK
### 5.1 Definitions
| Send/Receive Data | Content | Description |
|------------|------|------|
| ACK | `0xFF` | Acknowledgment |
| NACK | `0xF0` | Checksum error |

### 5.2 Rules
1. The receiver must return an ACK or NACK within 10ms after receiving a frame.
2. If no ACK is received within 100ms, the data frame must be resent.
3. If the frame is resent three times without success, transmission stops, and error handling is performed.

## 6. Data Type (DataType) Definitions
### 6.1 Slave → Host
| No. | Description | Code |
|-----|------|------|
| 1 | Backlight adjustment information | `0x14` |
| 2 | Vehicle speed | `0x16` |
| 3 | Steering wheel button | `0x20` |
| 4 | Air conditioning information | `0x21` |
| 5 | Rear radar information | `0x22` |
| 6 | Front radar information | `0x23` |
| 7 | Basic information | `0x24` |
| 8 | Parking assist status | `0x25` |
| 9 | Steering wheel angle | `0x26` |
| 10 | Amplifier status | `0x27` |
| 11 | Version information | `0x30` |
| 12 | Vehicle body information | `0x41` |

### 6.2 Host → Slave
| No. | Description | Code |
|-----|------|------|
| 1 | Start/End | `0x81` |
| 2 | Request control information | `0x90` |
| 3 | Amplifier control command | `0xA0` |
| 4 | Source | `0xC0` |
| 5 | ICON | `0xC1` |
| 6 | Radio information | `0xC2` |
| 7 | Media playback information | `0xC3` |
| 8 | Volume display control | `0xC4` |
| 9 | Radar volume control | `0xC6` |

## 7. Data Format Examples
### 7.1 Backlight Adjustment Information (`0x14`)
| Order | Data Content | Description |
|---------|---------|------|
| DataType | `0x14` | Data type |
| Length | `0x01` | Data length |
| Data0 | `0x00~0xFF` | Backlight adjustment (darkest~brightest) |

### 7.2 Vehicle Speed Information (`0x16`)
| Order | Data Content | Description |
|---------|---------|------|
| DataType | `0x16` | Data type |
| Length | `0x02` | Data length |
| Data0 | `LSB` | Vehicle speed (Km/h) = `X/16` |
| Data1 | `MSB` | - |

### 7.3 Steering Wheel Button Information (`0x20`)
| Order | Data Content | Description |
|---------|---------|------|
| DataType | `0x20` | Data type |
| Length | `0x02` | Data length |
| Data0 | `Key Code` | See table below |
| Data1 | `Key Status` | 0: Released, 1: Pressed, 2: Continuous press |

| Key Code | Button |
|---------|------|
| `0x00` | No button |
| `0x01` | VOL+ |
| `0x02` | VOL- |
| `0x03` | > /MENU UP |
| `0x04` | < /MENU DOWN |
| `0x05` | TEL |
| `0x06` | MUTE |
| `0x07` | SRC |
| `0x08` | MIC |

---
(More data formats can be added)

## 8. Conclusion
This protocol defines the UART communication between the CAN BUS module and the DVD host, covering the physical layer, data link layer, and application layer.



```cpp
#pragma once
#include <stdint.h>

// Base structure for a UART message
struct UARTMessage {
    uint8_t headCode;
    uint8_t dataType;
    uint8_t length;
    uint8_t data[8]; // Fixed-size array instead of vector
    uint8_t checksum;

    UARTMessage() : headCode(0x2E), length(0), checksum(0) {
        for (int i = 0; i < 8; i++) {
            data[i] = 0;
        }
    }

    // Calculate checksum
    uint8_t calculateChecksum() const {
        uint8_t sum = dataType + length;
        for (uint8_t i = 0; i < length; i++) {
            sum += data[i];
        }
        return sum ^ 0xFF;
    }
};

// Specific message structures

/**
 * Backlight Adjustment Message
 * - brightness: 0x00 (darkest) to 0xFF (brightest)
 */
struct BacklightAdjustment : public UARTMessage {
    BacklightAdjustment(uint8_t brightness) {
        dataType = 0x14;
        length = 1;
        data[0] = brightness;
        checksum = calculateChecksum();
    }
};

/**
 * Vehicle Speed Message
 * - speed: 0x0000 (0 km/h) to 0xFFFF (~4095.9375 km/h, using speed = X/16 formula)
 */
struct VehicleSpeed : public UARTMessage {
    VehicleSpeed(uint16_t speed) {
        dataType = 0x16;
        length = 2;
        data[0] = speed & 0xFF;  // LSB
        data[1] = (speed >> 8) & 0xFF;  // MSB
        checksum = calculateChecksum();
    }
};

/**
 * Steering Wheel Button Message
 * - keyCode: 0x00 (None) to 0x08 (MIC)
 * - keyStatus: 0 (Released), 1 (Pressed), 2 (Held)
 */
struct SteeringWheelButton : public UARTMessage {
    SteeringWheelButton(uint8_t keyCode, uint8_t keyStatus) {
        dataType = 0x20;
        length = 2;
        data[0] = keyCode;
        data[1] = keyStatus;
        checksum = calculateChecksum();
    }
};

/**
 * Air Conditioning Information Message
 */
struct AirConditioningInfo : public UARTMessage {
    AirConditioningInfo(uint8_t status, uint8_t fanSpeed, uint8_t driverTemp, uint8_t passengerTemp, uint8_t seatHeat) {
        dataType = 0x21;
        length = 5;
        data[0] = status;
        data[1] = fanSpeed;
        data[2] = driverTemp;
        data[3] = passengerTemp;
        data[4] = seatHeat;
        checksum = calculateChecksum();
    }
};

/**
 * Radar Information Message
 */
struct RadarInfo : public UARTMessage {
    RadarInfo(uint8_t frontLeft, uint8_t frontRight, uint8_t rearLeft, uint8_t rearRight) {
        dataType = 0x22;
        length = 4;
        data[0] = frontLeft;
        data[1] = frontRight;
        data[2] = rearLeft;
        data[3] = rearRight;
        checksum = calculateChecksum();
    }
};

/**
 * Parking Assist Message
 */
struct ParkingAssist : public UARTMessage {
    ParkingAssist(uint8_t status) {
        dataType = 0x25;
        length = 1;
        data[0] = status;
        checksum = calculateChecksum();
    }
};

/**
 * Steering Wheel Angle Message
 */
struct SteeringWheelAngle : public UARTMessage {
    SteeringWheelAngle(int16_t angle) {
        dataType = 0x26;
        length = 2;
        data[0] = angle & 0xFF;
        data[1] = (angle >> 8) & 0xFF;
        checksum = calculateChecksum();
    }
};

/**
 * Amplifier Status Message
 */
struct AmplifierStatus : public UARTMessage {
    AmplifierStatus(uint8_t volume, int8_t balance, int8_t fader, int8_t bass, int8_t midtone, int8_t treble) {
        dataType = 0x27;
        length = 6;
        data[0] = volume;
        data[1] = balance;
        data[2] = fader;
        data[3] = bass;
        data[4] = midtone;
        data[5] = treble;
        checksum = calculateChecksum();
    }
};

/**
 * Start/End Message
 */
struct StartEnd : public UARTMessage {
    StartEnd(uint8_t commandType) {
        dataType = 0x81;
        length = 1;
        data[0] = commandType;
        checksum = calculateChecksum();
    }
};

/**
 * Request Control Information Message
 */
struct RequestControlInfo : public UARTMessage {
    RequestControlInfo(uint8_t requestType) {
        dataType = 0x90;
        length = 1;
        data[0] = requestType;
        checksum = calculateChecksum();
    }
};

// More message structures can be added similarly

```
