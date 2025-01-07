#include <FootKeyboardBuilder.h>

FootKeyboardBuilder::FootKeyboardBuilder(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel) : BleKeyboard(deviceName, deviceManufacturer, batteryLevel)
{
    SetKeyPerMinute(1000); // nghỉ 60ms giữa 2 lần gửi mã phím, để tránh tràn bộ đệm bàn phím
    SetPressTime(60);
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
uint16_t FootKeyboardBuilder::GetKeyPerMinute()
{
    return 60000 / keytokeytime;
}
/**
 * @brief Thiết lập độ trễ giữa 2 trạng thái nhấn-nhả. Đơn vị ms. Mặc định 60ms.
 */
void FootKeyboardBuilder::SetPressTime(uint16_t ms)
{
    timePressToRelease = ms;
}
typedef struct
{
    String userFormat;
    uint8_t code;
} TableCode;

TableCode tableCode[] = {
    {"CTRL", KEY_LEFT_CTRL},
    {"~CTRL", KEY_LEFT_CTRL},
    {"SHIFT", KEY_LEFT_SHIFT},
    {"~SHIFT", KEY_LEFT_SHIFT},
    {"ALT", KEY_LEFT_ALT},
    {"~ALT", KEY_LEFT_ALT},
    {"WINDOWS", KEY_LEFT_GUI},
    {"UP_ARROW", KEY_UP_ARROW},
    {"DOWN_ARROW", KEY_DOWN_ARROW},
    {"LEFT_ARROW", KEY_LEFT_ARROW},
    {"RIGHT_ARROW", KEY_RIGHT_ARROW},
    {"BACKSPACE", KEY_BACKSPACE},
    {"TAB", KEY_TAB},
    {"RETURN", KEY_RETURN},
    {"ESC", KEY_ESC},
    {"INSERT", KEY_INSERT},
    {"PRTSC", KEY_PRTSC},
    {"DELETE", KEY_DELETE},
    {"PGUP", KEY_PAGE_UP},
    {"PGDN", KEY_PAGE_DOWN},
    {"HOME", KEY_HOME},
    {"END", KEY_END},
    {"CPLK", KEY_CAPS_LOCK},
    {"F1", KEY_F1},
    {"F2", KEY_F2},
    {"F3", KEY_F3},
    {"F4", KEY_F4},
    {"F5", KEY_F5},
    {"F6", KEY_F6},
    {"F7", KEY_F7},
    {"F8", KEY_F8},
    {"F9", KEY_F9},
    {"F10", KEY_F10},
    {"F11", KEY_F11},
    {"F12", KEY_F12},
    {"ENTER", KEY_NUM_ENTER}};
int FootKeyboardBuilder::ConvertFormat(const USER_FORMAT *request, ASCII_FORMAT *command)
{
    uint8_t i, oi;
    uint16_t start_brace_i;
    char ch;

    i = 0;
    oi = 0;
    start_brace_i = 0; // 0 tức là chưa tìm thấy kí tự {

    if (request == NULL)
    {
        Serial.println("Debug: USER_FORMAT is null!");
        return 0;
    }

    while (true)
    {
        // Lấy ra kí tự
        ch = request[i];
        if (ch == 0)
        {
            command[oi] = 0; // Đánh dấu điểm cuối cùng
            break;
        }
        else if (ch == '{')
        {
            /// Đã tìm thấy điểm bắt đầu ngoặc
            /// Tìm điểm cuối của ngoặc
            i = i + 1;
            // Tính checksum là tổng mã ascii của tất cả các kí tự x vị trí, áp dụng dể tìm chuỗi cho nhanh. bản chất là đánh indexing chuỗi
            String specialKey;
            while (request[i] != '}' and (request[i] != 0))
            {
                specialKey += request[i];
                i++;
            }
            // Nếu không tìm thấy dấu đóng }, tức là lỗi cú pháp rồi, loại.
            if (request[i] == 0)
            {
                oi =start_brace_i;
                Serial.print("Debug: } not found.");
                break;
            }
            if (specialKey[0] == '~')
            {
                command[oi] = ASCII_RELEASE_CODE;
                oi++;
                start_brace_i = 1; // Shift, Ctrl, Alt
            }
            // Lúc này command[start_brace_i:i] chứa chuỗi như {ENTER},  {PGUP}
            // Xác định mã của các phím đặc biệt và gán vào command.
            for (int j = 0; j < sizeof(tableCode); j++)
            {
                if (tableCode[j].userFormat == specialKey)
                {
                    // Đã tìm thấy mã của điều khiển
                    command[oi] = tableCode[j].code;
                    oi++;
                    // Đánh dấu đã xử lý xong ngoặc
                    start_brace_i = 1; // Shift, Ctrl, Alt
                    break;
                }
            }
            // Nếu không tìm thấy cụm từ khóa, tức là lỗi cú pháp rồi, loại.
            if (start_brace_i == 0)
            {
                oi = start_brace_i; // Lỗi ở vị trí dấu ngoặc
                Serial.print("Debug: code not found");
                break;
            }
        }
        else
        {
            command[oi] = request[i];
            oi++;
        }
        i++; // CHuyển sang kí tự tiếp theo
    }
    return oi;
}
int FootKeyboardBuilder::RevertFormat(const ASCII_FORMAT *sascii, char *suser)
{
    uint8_t i, oi, j;
    int16_t start_brace_i;
    char ch;

    i = 0;
    oi = 0;
    do
    {
        ch = sascii[i];
        if (ch == 0)
        {
            break;
        }
        else if (ch < 0x80)
        {
            suser[oi] = ch;
            oi++;
        }
        else
        { // Bảng đặc biệt: luôn có dạng 3 kí tự {...} hoặc 4 kí tự {~...}
            suser[oi] = '{';
            oi++;
            if (ch == ASCII_RELEASE_CODE)
            {
                // ghi nhận kí tự điều khiển release ~.
                suser[oi] = '~';
                oi++;
                // phân tích luôn kí tự tiếp theo
                i++;
                ch = sascii[i]; //
            }
            for (j = 0; j < sizeof(tableCode); j++)
            {
                if (tableCode[j].code == ch)
                {
                    const char *userFormat = tableCode[j].userFormat.c_str();
                    for (size_t k = 0; k < strlen(userFormat); k++)
                    {
                        suser[oi] = userFormat[k];
                        oi++;
                    }
                    break;
                }
            }
            suser[oi] = '}';
            oi++;
        }
        i++; // Chuyển sang kí tự ascii tiếp theo
    } while (ch != 0);

    /// Thêm kí tự \0 đánh dấu kết thúc chuỗi
    suser[oi] = 0;
    oi++;
    return oi;
}