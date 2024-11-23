#include <FootKeyboardBuilder.h>

FootKeyboardBuilder::FootKeyboardBuilder(std::string deviceName , std::string deviceManufacturer , uint8_t batteryLevel ) :
    BleKeyboard(deviceName , deviceManufacturer , batteryLevel )
{
    SetKeyPerMinute(1000); //nghỉ 60ms giữa 2 lần gửi mã phím, để tránh tràn bộ đệm bàn phím
};


void FootKeyboardBuilder::SetKeyPerMinute(uint16_t kpm)
{
    keytokeytime = 60000 / kpm;  // = 60s / key per minute;
}