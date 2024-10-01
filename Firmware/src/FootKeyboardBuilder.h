#pragma once

#include "BleKeyboard.h"

typedef char USER_FORMAT;
typedef char ASCII_FORMAT; 
class FootKeyboardBuilder : public BleKeyboard{
private:
    uint16_t keytokeytime;
public:
    FootKeyboardBuilder(std::string deviceName="Foot Keyboard",std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
    void SendKeys(const ASCII_FORMAT * cmd);
    //static int ConvertFormat(const char * USER_FORMAT, char * ASCII_FORMAT);
    void SetKeyPerMinute( uint16_t kpm);  
    //uint16_t GetKeyPerMinute( uint16_t kpm);
};