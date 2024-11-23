#include "BleKeyboard.h"
#include "BoardConfiguration.h"

class FootKeyboardBuilder : public BleKeyboard
{
private:
    uint16_t keytokeytime;
public:
    FootKeyboardBuilder(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
    void SetKeyPerMinute( uint16_t kpm); 
};