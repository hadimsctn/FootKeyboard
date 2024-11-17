#include "SerialConfiguration.h"
     

bool DetermineKeyValue(char * Command, char ** key, char ** value) {
    char ch;
    uint8_t i;
    *key = Command;
    *value = NULL;
    
    /// Phân tích parsing
    i = 0;
    do {
        ch = Command[i];
        if (ch == '=') {
            Command[i]=0; // Đánh dấu Zero kết thúc chuỗi
            *value = & Command[i+1];
            break;
        }
        i++;
    } while (ch != 0);
    
    // Nếu không tìm thấy kí tự = không hợp lệ.
    if (ch == 0) {
        Serial.println("Error 01: delimiter = not found.");
        return false;
    };
    return true;
}

/**
 * @brief Cấu hình chức năng các phím/pedal qua Serial
 *
 */
void SerialConfiguration()
{
    uint8_t i, j;
    int16_t res;
    /// Nếu không có kết nối serial thì kết thúc luôn
    if (Serial.available() <= 0)
    {
        return;
    }
    
    /// Đọc lệnh từ Serial
    int rlen = Serial.readBytesUntil('\n',SerialCommand, SERIAL_BUFFER_SIZE);
    SerialCommand[rlen] = 0; // đánh dấu kết thúc chuỗi, nếu không sẽ dính với phần còn lại của lệnh trước.
    
    // Phân tích thành cặp key=value. Không phù hợp thì dừng luôn
    if (!DetermineKeyValue(SerialCommand, & cmdkey, & cmdvalue)) return;

#pragma region ASSIGN_COMMAND
    /// Gán lệnh cho các nút bấm/pedal tương ứng
    if (strcasecmp(cmdkey, KEY01) == 0) {
        i = 0;
    } else if (strcasecmp(cmdkey, KEY02) == 0) {
        i = 1;
    } else if (strcasecmp(cmdkey, KEY03) == 0) {
        i = 2;
    } else if (strcasecmp(cmdkey, KEY04) == 0) {
        i = 3;
    } else {
        // mã phím bấm không phù hợp, kết thúc luôn
        Serial.println("Error 02: button key is invalid.");
        return;
    }
    // Debug
    Serial.print("Info: Button="); Serial.print(i);
    Serial.print(", UserFormat="); Serial.println(cmdvalue);

    // Chuyển đổi từ USER_FORMAT về thành ASCII_FORMAT. Tận dụng lại mảng SerialComamnd để tiết kiệm bộ nhớ, vì cmdValue chắc chắn chứa các cụm từ mô tả dài hơn.
    res = FootKeyboardBuilder::ConvertFormat(cmdvalue, SerialCommand);
    if (res < 0) {
        Serial.println("Error: UserFormat wrong at the character "); Serial.print(-res);
        return;
    } else {
        Serial.print("cmd ");
        Serial.print(res);
        Serial.print(" chars: ");
        Serial.println(SerialCommand);
    }
    // Áp dụng thành các phím kí tự của phím pedal
    for (j = 0; j <= res ; j++) {   // <=res để copy cả kí tự 0
        button_sendkeys[i][j] = SerialCommand[j];    
    }
    Serial.print("Infor: ap dung ");
    Serial.println(button_sendkeys[i]);    
    // Debug
    Serial.print("Info: OK");
    // Lưu cấu hình
    SaveSettings(i , button_sendkeys[i]);
#pragma endregion ASSIGN_COMMAND
}


