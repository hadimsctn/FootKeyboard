#include <FootKeyboardBuilder.h>

FootKeyboardBuilder::FootKeyboardBuilder(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel) : BleKeyboard(deviceName, deviceManufacturer, batteryLevel)
{
    SetKeyPerMinute(1000); // nghỉ 60ms giữa 2 lần gửi mã phím, để tránh tràn bộ đệm bàn phím
};

void FootKeyboardBuilder::SetKeyPerMinute(uint16_t kpm)
{
    keytokeytime = 60000 / kpm; // = 60s / key per minute;
}

void FootKeyboardBuilder::SendKeys(const ASCII_FORMAT *cmd)
{
    static unsigned char ch;
    static uint8_t i;

    i = 0;
    while (true)
    {
        ch = cmd[i];
        // đợi giữa 2 kí tự liên tiếp, tránh bị tràn bộ đêm bàn phím
        delay(keytokeytime);

        if (ch == 0)
        { // Nếu là kí tự kết thúc chuỗi thì nhả tất cả các phím và dừng lại
            releaseAll();
            return;
        }
        else if (ch < 0x80)
        { // Nếu là kí tự thường thì hiện thị
            press(ch);
            delay(keytokeytime); // Phải có khoảng trễ nhất định giữa press và release, nếu không sẽ bị mất phím
            release(ch);         // Phải có release. Nếu không có thì mặc dù biểu hiện không khác biệt, nhưng sẽ chỉ được 6 kí tự.
        }
        else
        {
            // Nếu là kí tự đặc biệt chính là vai trò của mã ASCII_FORMAT đây
            if (ch != ASCII_RELEASE_CODE)
            {
                press(ch);
            }
            else
            {
                i++;
                ch = cmd[i];
                release(ch);
            }
        }
        i++; // Chuyển sang kí tự tiếp theo
    };
}
uint16_t FootKeyboardBuilder::GetKeyPerMinute(uint16_t kpm)
{
    return 60000/keytokeytime;
}