# IdGuard - Arduino hardare ID

Tiny library to avoid deploying your sketch to wrong device.
Writes device ID in EEPROM memory and verifies if it matches id
hardcoded in you sketch.

## Write ID in EEPROM

```cpp
#include "IdGuard.h"

#define DEVICE_ID 2

int ledPin = 13;

void setup() {

  // Next line does:
  // Writes DEVICE_ID to last byte in EEPROM memory.
  // LED devined by ledPin blinks I and D in morse code "..|-.."
  // Restarts device.
  IdGuard idGuard(DEVICE_ID, ledPin, true);

  // The same as above but with offset 3 to write ID in 4th byte in EEPROM.
  //IdGuard idGuard(DEVICE_ID, ledPin, true, 3);

  // nothing after IdGuard will be executed
}

void loop()
{
  // main loop will be never called
}
```

# Check device ID on every startup

To check device if device ID in EEPROM matches the on we expect in our sketch,
we only need to switch 3rd parameter in IdGuard constructor from true to false.

When id matches, sketch continues normally. In case of id mismatch device is
restarted immediately and led blinks I and D in morse code "..|-..".

```cpp
#include "IdGuard.h"

#define DEVICE_ID 2

int ledPin = 13;

void setup() {

  // Next line does:
  // Checks DEVICE_ID against last byte in EEPROM memory.
  // Blinks I and D in morse code "..|-.."and restarts device in case of mismatch.
  IdGuard idGuard(DEVICE_ID, ledPin, false);

  // The same as above but with offset 3 to write ID in 4th byte in EEPROM.
  //IdGuard idGuard(DEVICE_ID, ledPin, false, 3);

  // nothing after IdGuard will be executed in case of id mismatch
}

void loop()
{
  // main loop will be never called in case of id mismatch
}
```
