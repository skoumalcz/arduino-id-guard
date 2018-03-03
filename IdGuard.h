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

class IdGuard
{
  public:
    IdGuard(uint8_t myId, uint8_t ledPin = -1, bool overrideCurrent = false, uint8_t offset = 0);
    uint8_t getId();

  private:
    uint8_t _offset = 0;
    void _resetDevice(uint8_t ledPin);
    void _ledBlink(uint8_t ledPin, bool dot);

};

IdGuard::IdGuard(uint8_t myId, uint8_t ledPin, bool overrideCurrent, uint8_t offset) {

  _offset = offset;

  uint8_t currentId = getId();

  if(currentId != myId) {

    if(overrideCurrent) {
      EEPROM.write(EEPROM.length() - 1 - offset, myId);
    }

  }

  // restart arduino in error situation
  if(currentId != myId || overrideCurrent) {
    _resetDevice(ledPin);
  }
}

void IdGuard::_resetDevice(uint8_t ledPin = -1) {

  if(ledPin >= 0) {
    pinMode(ledPin, OUTPUT);

    // I
    _ledBlink(ledPin, true);
    _ledBlink(ledPin, true);
    delay(1000);

    // D
    _ledBlink(ledPin, false);
    _ledBlink(ledPin, true);
    _ledBlink(ledPin, true);
    delay(2000);
  }

  void(* resetFunc) (void) = 0;  // declare reset fuction at address 0
  resetFunc();
}

uint8_t IdGuard::getId() {
  return EEPROM.read(EEPROM.length() - 1 - _offset);
}

void IdGuard::_ledBlink(uint8_t ledPin, bool dot) {
  digitalWrite(ledPin, HIGH);
  delay(dot ? 300 : 1000);
  digitalWrite(ledPin, LOW);
  delay(300);
}
