/*
  IdGuard.h - Library for guarding device id. Useful to avoid installing bad
  firmware on guarded device. On first start library writes device id to last
  byte of EEPROM memory and then with every start it check if it matches with
  given firmware id.

  Created by Vladislav Gingo Skoumal, February 25, 2017.
  All rights reserved.

  _____________________________________________________________________________

  Copyright 2018 by Vladislav Gingo Skoumal

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#pragma once

#include <EEPROM.h>

class IdGuardClass
{
public:
    uint8_t error_led_pin = -1;
    uint16_t offset = 0;

    uint8_t readId();
    void forceId(uint8_t myId);
    void writeIdAndRestartDevice(uint8_t myId);
private:
    void _resetDevice();
    void _ledBlink(bool dot);

};

void IdGuardClass::forceId(uint8_t myId) {
  uint8_t currentId = readId();

  if(currentId != myId) {
    _resetDevice();
  }

}

void IdGuardClass::writeIdAndRestartDevice(uint8_t myId) {
  uint8_t currentId = readId();

  if(currentId != myId) {
    EEPROM.write(EEPROM.length() - 1 - offset, myId);
  }

  _resetDevice();
}

uint8_t IdGuardClass::readId() {
  return EEPROM.read(EEPROM.length() - 1 - offset);
}

void IdGuardClass::_resetDevice() {

  if(error_led_pin >= 0) {
    pinMode(error_led_pin, OUTPUT);

    // I
    _ledBlink(true);
    _ledBlink(true);
    delay(1000);

    // D
    _ledBlink(false);
    _ledBlink(true);
    _ledBlink(true);
    delay(2000);
  }

  void(* resetFunc) (void) = 0;  // declare reset fuction at address 0
  resetFunc();
}

void IdGuardClass::_ledBlink(bool dot) {
  digitalWrite(error_led_pin, HIGH);
  delay(dot ? 300 : 1000);
  digitalWrite(error_led_pin, LOW);
  delay(300);
}

static IdGuardClass IdGuard;
