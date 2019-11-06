# IdGuard - Arduino hardware ID

Tiny library to avoid deploying your sketch to wrong device or to identify
device by its ID. Writes device ID in [EEPROM](https://en.wikipedia.org/wiki/EEPROM)
memory and verifies if it matches ID hardcoded in your sketch.

## Usage

```cpp
#include "IdGuard.h"

#define DEVICE_ID 2

int ledPin = 13;

void setup() {

  // Optional offset to write ID in 4th byte from the end in EEPROM.
  // Defaults to 0, which means ID is stored in last byte in EEPROM.
  IdGuard.offset = 3;

  // Recommended, but optional led for error signalization.
  IdGuard.error_led_pin = ledPin;

  // Writes DEVICE_ID to EEPROM memory.
  // LED defined by error_led_pin blinks I and D letters in Morse code "..|-..".
  // Restarts device to prevent execution of any following code.
  // Comment out this line after ID is successfully stored in EEPROM.
  IdGuard.writeIdAndRestartDevice(DEVICE_ID);

  // Checks DEVICE_ID against last byte in EEPROM memory.
  // Blinks I and D in morse code "..|-.."and restarts device in case of
  // mismatch to prevent execution of any following code.
  IdGuard.forceId(DEVICE_ID);

  // Only reads ID from EEPROM.
  uint8_t device_id = IdGuard.readId();

}

void loop()
{
  // main loop will be never called in case of ID mismatch thanks to IdGuard
}
```

## Credits

[Jakub Dolejsek](https://github.com/x0nix)  
[David Vadura](https://www.linkedin.com/in/david-va%C4%8Fura-b1a8b3124/)
