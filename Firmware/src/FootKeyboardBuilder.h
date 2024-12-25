#include "BleKeyboard.h"
#include "BoardConfiguration.h"

class FootKeyboardBuilder : public BleKeyboard
{
#define ASCII_RELEASE_CODE 0xFF
private:
    uint16_t keytokeytime;

public:
    FootKeyboardBuilder(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
    void SetKeyPerMinute(uint16_t kpm);
    void SendKeys(const ASCII_FORMAT *cmd);
    uint16_t GetKeyPerMinute( uint16_t kpm);
};