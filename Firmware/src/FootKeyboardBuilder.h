#pragma once

#include "BleKeyboard.h"

#ifndef ESP32_BLE_SENDKEYS_H
#define ESP32_BLE_KEYBOARD_H

typedef char USER_FORMAT;
typedef char ASCII_FORMAT; 
class FootKeyboardBuilder : public BleKeyboard{
private:
    uint16_t keytokeytime;
public:
    FootKeyboardBuilder(std::string deviceName,std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
    void SendKeys(const ASCII_FORMAT);
    static int ConvertFormat(const char * USER_FORMAT, char * ASCII_FORMAT);
    void SetKeyPerMinute( uint16_t kpm);  
    uint16_t GetKeyPerMinute( uint16_t kpm);
};
#endif