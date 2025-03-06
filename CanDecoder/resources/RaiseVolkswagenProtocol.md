# Volkswagen Series CAN BUS Module and DVD Host Communication Protocol 1.4

## 1. Overview
This document describes the communication protocol between the DVD host system and the bus decoder, covering the physical layer, data link layer, and application layer protocols.

## 2. Physical Layer Description
- Standard UART communication interface
- Logic level: 5V TTL
- UART working mode: 8N1 (8 data bits, no parity, 1 stop bit)
- Baud rate: 38400bps

## 3. Conventions
- **HOST**: Head Unit
- **SLAVE**: Can Bus decoder

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
| Data0 | `0x00~0xFF` | Backlight adjustment (darkest~brightest) |

### 7.2 Vehicle Speed Information (`0x16`)
| Order | Data Content | Description |
|---------|---------|------|
| Data0 | `LSB` | Vehicle speed (Km/h) = `X/16` |
| Data1 | `MSB` | - |

### 7.3 Steering Wheel Button Information (`0x20`)
| Order | Data Content | Description |
|---------|---------|------|
| Data0 | `Key Code` | See Key Code table |
| Data1 | `Key Status` | 0: Released, 1: Pressed, 2: Continuous press |

#### Key Code
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

### 7.4 Start/End (`0x81`)
| Order | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Command Type | `0x01`: Start (system start), `0x00`: End (system shutdown) |

### 7.5 Request Control Information (`0x90`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Request Type | See Request Type table |
| Data1    | Command Value | Used only for `0x41` vehicle body information |

#### Request Type
| Request Type | Description |
|--------------|-------------|
| `0x14`       | Backlight information |
| `0x16`       | Vehicle speed information |
| `0x21`       | Air conditioning information |
| `0x24`       | Basic information |
| `0x25`       | Parking assist status information |
| `0x26`       | Steering wheel angle |
| `0x30`       | Version information |
| `0x41`       | Vehicle body information |

### 7.6 Amplifier Control Command (`0xA0`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Command      | See Command table |
| Data1    | Parameter    | See Command Parameter table |

#### Command
| Command | Description |
|---------|-------------|
| `0x00`  | Volume |
| `0x01`  | Balance |
| `0x02`  | Fader |
| `0x03`  | Bass |
| `0x04`  | Midtone |
| `0x05`  | Treble |
| `0x06`  | Volume with vehicle speed |

#### Command Parameter Table
| Command | Parameter | Default Value |
|---------|-----------|---------------|
| Volume  | `0~30` (unsigned char) | `28` |
| Balance | `-9~+9` (signed char) | `0` |
| Fader   | `-9~+9` (signed char) | `0` |
| Bass    | `-9~+9` (signed char) | `0` |
| Midtone | `-9~+9` (signed char) | `0` |
| Treble  | `-9~+9` (signed char) | `0` |
| Volume with vehicle speed | `0~7` (unsigned char) | `0` |

### 7.7 Source (`0xC0`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Source       | See Source table |
| Data1    | Media Type   | See Media Type table |

#### Source
| Source | Description |
|--------|-------------|
| `0x00` | OFF |
| `0x01` | Tuner |
| `0x02` | Disc (CD, DVD) |
| `0x03` | TV (Analog) |
| `0x04` | NAVI |
| `0x05` | Phone |
| `0x06` | iPod |
| `0x07` | Aux |
| `0x08` | USB |
| `0x09` | SD |
| `0x0A` | DVB-T |
| `0x0B` | Phone A2DP |
| `0x0C` | Other |
| `0x0D` | CDC v1.02 |

#### Media Type
| Media Type | Description |
|------------|-------------|
| `0x01`     | Tuner |
| `0x10`     | Simple Audio Media |
| `0x11`     | Enhanced Audio Media |
| `0x12`     | iPod |
| `0x20`     | File based Video |
| `0x21`     | DVD Video |
| `0x22`     | Other Video |
| `0x30`     | Aux, other |
| `0x40`     | Phone |

### 7.8 ICON (`0xC1`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Source       | Bit7~Bit3: Reserved, Bit1~Bit2: Play mode V1.02 (`0x00`: Normal, `0x01`: Scan (CD/DVD/TUNER), `0x02`: Mix (CD/DVD Only), `0x03`: Repeat (CD/DVD Only)), Bit0: Reserved |

### 7.9 Radio Information (`0xC2`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Radio Band   | See Radio Band table |
| Data1    | Current Frequency (LSB) | FM: Freq = `X/100` (MHz), AM: Freq = `X` (kHz) |
| Data2    | Current Frequency (MSB) | - |
| Data3    | Preset Station Number | `0~6`, `0` indicates the current station is not a preset station |

#### Radio Band
| Radio Band | Description |
|------------|-------------|
| `0x00`     | FM |
| `0x01`     | FM1 |
| `0x02`     | FM2 |
| `0x03`     | FM3 |
| `0x10`     | AM |
| `0x11`     | AM1 |
| `0x12`     | AM2 |
| `0x13`     | AM3 |

### 7.10 Media Playback Information (`0xC3`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Info1        | See Media Type Descriptions table |
| Data1    | Info2        | - |
| Data2    | Info3        | - |
| Data3    | Info4        | - |
| Data4    | Info5        | - |
| Data5    | Info6        | - |

#### Media Type Descriptions
| Media Type | Description | Info1 | Info2 | Info3 | Info4 | Info5 | Info6 |
|------------|-------------|-------|-------|-------|-------|-------|-------|
| `0x01`     | Tuner       | Unused | Unused | Unused | Unused | Unused | Unused |
| `0x10`     | Simple Audio Media | Disc Number (`0x00`: No disc) | Track Number (`0x01-0xFF`) | Unused | Unused | Minute | Second |
| `0x11`     | Enhanced Audio Media | Folder Number (Low byte) | Folder Number (High byte) | File Number (Low byte) | File Number (High byte) | Minute | Second |
| `0x12`     | iPod        | Current Song Number | Current Song Number | Total Song Number | Total Song Number | Unused | Unused |
| `0x20`     | File Based Video | Folder Number (Low byte) | Folder Number (High byte) | File Number (Low byte) | File Number (High byte) | Unused | Unused |
| `0x21`     | DVD Video   | Current Chapter | Total Chapter | - | - | - | - |
| `0x22`     | Other Video | Unused | Unused | Unused | Minute | Second | Unused |
| `0x30`     | Aux, other  | Unused | Unused | Unused | Unused | Unused | Unused |
| `0x40`     | Phone       | Unused | Unused | Unused | Unused | Unused | Unused |

### 7.11 Volume Display Control (`0xC4`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Volume Display | Bit7: Mute Control (`1`: Mute, `0`: Unmute), Bit6~Bit0: Volume Level (`0~127`) |

### 7.12 Radar Volume Control (`0xC6`)
| Order    | Data Content | Description |
|----------|--------------|-------------|
| Data0    | Command      | See Command table |
| Data1    | Parameter    | See Command table |

#### Command Table
| Command | Parameter | Description |
|---------|-----------|-------------|
| `0x00`  | `0x00`    | Turn off radar sound |
| `0x00`  | `0x01`    | Turn on radar sound |
| `0x02`  | `0x00`    | Parking mode 1 (standard) |
| `0x02`  | `0x01`    | Parking mode 2 (parallel parking) |

## 8. Conclusion
This protocol defines the UART communication between the CAN BUS module and the DVD host, covering the physical layer, data link layer, and application layer.

```cpp
#pragma once
#include <stdint.h>

// Base structure for a UART message
struct UARTMessage {
    const uint8_t headCode;
    const uint8_t dataType;
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

/**
 * Version Information Message
 */
struct VersionInfo : public UARTMessage {
    VersionInfo(uint8_t majorVersion, uint8_t minorVersion) {
        dataType = 0x30;
        length = 2;
        data[0] = majorVersion;
        data[1] = minorVersion;
        checksum = calculateChecksum();
    }
};

/**
 * Vehicle Body Information Message
 */
struct VehicleBodyInfo : public UARTMessage {
    VehicleBodyInfo(uint8_t doorStatus, uint8_t trunkStatus, uint8_t hoodStatus) {
        dataType = 0x41;
        length = 3;
        data[0] = doorStatus;
        data[1] = trunkStatus;
        data[2] = hoodStatus;
        checksum = calculateChecksum();
    }
};

/**
 * Amplifier Control Command Message
 */
struct AmplifierControlCommand : public UARTMessage {
    AmplifierControlCommand(uint8_t command) {
        dataType = 0xA0;
        length = 1;
        data[0] = command;
        checksum = calculateChecksum();
    }
};

/**
 * Source Message
 */
struct Source : public UARTMessage {
    Source(uint8_t sourceType) {
        dataType = 0xC0;
        length = 1;
        data[0] = sourceType;
        checksum = calculateChecksum();
    }
};

/**
 * ICON Message
 */
struct ICON : public UARTMessage {
    ICON(uint8_t iconType) {
        dataType = 0xC1;
        length = 1;
        data[0] = iconType;
        checksum = calculateChecksum();
    }
};

/**
 * Radio Information Message
 */
struct RadioInfo : public UARTMessage {
    RadioInfo(uint8_t frequency, uint8_t band) {
        dataType = 0xC2;
        length = 2;
        data[0] = frequency;
        data[1] = band;
        checksum = calculateChecksum();
    }
};

/**
 * Media Playback Information Message
 */
struct MediaPlaybackInfo : public UARTMessage {
    MediaPlaybackInfo(uint8_t trackNumber, uint8_t playbackStatus) {
        dataType = 0xC3;
        length = 2;
        data[0] = trackNumber;
        data[1] = playbackStatus;
        checksum = calculateChecksum();
    }
};

/**
 * Volume Display Control Message
 */
struct VolumeDisplayControl : public UARTMessage {
    VolumeDisplayControl(uint8_t volumeLevel) {
        dataType = 0xC4;
        length = 1;
        data[0] = volumeLevel;
        checksum = calculateChecksum();
    }
};

/**
 * Radar Volume Control Message
 */
struct RadarVolumeControl : public UARTMessage {
    RadarVolumeControl(uint8_t volumeLevel) {
        dataType = 0xC6;
        length = 1;
        data[0] = volumeLevel;
        checksum = calculateChecksum();
    }
};
```
