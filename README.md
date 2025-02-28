# Connectors


## Mobile Communications Network (MCN) to Audio Control Module (ACM)

**Socket/Header:** Custom Moulding

This is a custom connector used in the BA, BF, FG, and FG Mk II Falcons.

I suspect some form of custom moulded TE Multilock connector with 51 pins

| Layout | Positions | Contact Width | Pitch       |
|--------|-----------|---------------|-------------|
| 4 x 3  | 12        | 2.2mm         | 3mm x 5mm   |
| 5 x 3	 | 15        | 1.0mm         | 2.2mm x 5mm |
| 8 x 3	 | 24        | 1.0mm         | 2.2mm x 5mm |

## Antenna to ACM

**Socket:** Hirose GTS13-1S-HU

**Header:** Hirose GT13SHA-1PP-DS

Single position 2 wire shielded coax

## MCN to Front Display Module (FDM)

**Socket:** MX84B024SF1

**Header:** MX84B024NF1

2x12 24 Position JAE connector

| Layout | Positions | Contact Width | Pitch |
|--------|-----------|---------------|-------|
| 12 x 2 | 24        | 1.0mm         | 2.2mm |


Runs the (MS) CAN to the ACM. The ACM internally bridges the CAN H and CAN L wires into the Mobile Communication Network (MCN) through the body loom.

2 pins unpopulated, wires are connected in like-for-like wiring and header ends. They are not wired straight through.

## FDM to internal daughterboard:

**Receptacle/Connector:** Molex 716617050

50 Position Molex Connector


## FDM internal daughterboard to Interior Comand Center (ICC) keypad:

**Socket:** Hi-Rose DF11-26DS-2C

**Header:** Hi-Rose DF11-26P-2DSA

2x13 26 position Hi-Rose connector


| Layout | Positions | Contact Width | Pitch |
|--------|-----------|---------------|-------|
| 13 x 2 | 26        |               | 2.0mm |

**Rotary Encoder:**

Alpine EC21A or EC35A

**Cabin Temp Sensor:**

EBM PABST S2000 with external surface mount 10K NTC


# MS CAN PIDs Required by Instrument Cluster


# Features

## Safety

- Hazzard Lights
- Front Demister
- Rear Demist
- Central Locking
- Unlock
- Interior Lighting (including dimming)
- DSC

## Comfort and Convenience - Single Zone (SZ)

- Internal Temp
- HVAC Off
- Temp
- A/C
- Fan Speed
- Recirculate/Fresh
- Vents
- Reverse Camera
- Reverse Sensors (including trailer attachment detection)

## Entertainment
- External Temp
- Bluetooth Audio
- Aux In
- USB
- DAB+
- RDS
- AM Radio
- FM Radio
- CD (No longer usable)
- Volume Dial
- Bluetooth Phone

## Operational
- OEM Menu
	- Follow me home lighting
- GPS Navigation
- Steerting Wheel Controls
	- Mode
	- Vol Up
	- Vol Down
	- Phone

- Dash Controls
	- Menu
	- Back

# MS Can Messages Decodes

## Speed
0x330 ((D6 * 2) + (D7 / 255))

## RPM
0x330 (D1 * 100) + D2

## Boost
0x120, D7

## Internal Temp

## ICC Key Status

## Reverse Sensors

## Lateral and Longitudinal G forces
0x397, (D5 * x + D6 ) Long or lat
0x397, (D7 * x + D8 ) Long or lat


## Engine Water Temp
0x44D, (D7 - 40) (seems to be in °C)

## Battery Voltage
0x307, D5 Maybe???? 

Others?
0x128 D5 is some kind of timer? possible speed related timer? i.e. trip computer, distance traveled or something?
