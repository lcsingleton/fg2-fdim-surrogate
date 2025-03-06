## onReceiveData Method Data Shape

The `onReceiveData` method in the `RZC_GMSeriesManager` class processes incoming data based on the command (`cmd`) and parameters (`param`). Below is the structure of the data:

### Parameters

- `cmd` (int): The command identifier.
- `param` (int[]): An array of integers representing the parameters associated with the command.

### Command Definitions

The `cmd` parameter can take the following values, each corresponding to a specific command:

- `0x01` - Steering Wheel Key
- `0x02` - Panel Key
- `0x03` - Air Conditioning Info
- `0x04` - Illumination Info
- `0x05` - Air Condition Control Info
- `0x06` - Vehicle Setting Info
- `0x07` - Parking Radar Switch Info
- `0x08` - OnStar Phone Info
- `0x09` - OnStar Status Info
- `0x0A` - Vehicle Setting Info 2
- `0x0B` - Vehicle Speed Signal
- `0x0C` - Vehicle Language
- `0x0D` - Alarm Volume
- `0x22` - Rear Radar Info
- `0x23` - Front Radar Info
- `0x24` - Base Info
- `0x26` - Steering Wheel Angle
- `0x30` - Protocol Version Info
- `0x41` - OnStar Wireless Access Point
- `0x42` - OnStar Wireless Password
- `0x43` - External Vehicle Setting Info

### Parameter Structure

The structure of the `param` array depends on the `cmd` value. Here are some examples:

- **Steering Wheel Key (`0x01`)**:
  - `param[0]`: Key code
  - `param[1]`: Key status (0: released, 1: pressed, 2: held)

- **Air Conditioning Info (`0x03`)**:
  - `param[0]`: AC status and mode
  - `param[1]`: Fan direction and speed
  - `param[2]`: Left temperature
  - `param[3]`: Right temperature
  - `param[4]`: Seat heating status
  - `param[5]`: Exterior temperature
  - `param[6]`: Additional status flags

- **Base Info (`0x24`)**:
  - `param[0]`: Door and trunk status
  - `param[1]`: Additional status flags

### Example

For a command `0x03` (Air Conditioning Info) with parameters `[0x80, 0x1F, 0x1A, 0x1A, 0x00, 0x10, 0x01]`, the data represents:
- AC is on
- Fan direction is auto
- Left and right temperatures are 26°C
- No seat heating
- Exterior temperature is 16°C
- Additional status flags indicate auto mode

This documentation provides an overview of the data structure for the `onReceiveData` method, detailing the command identifiers and the expected parameter formats.
