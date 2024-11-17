#include "FootKeyboardBuilder.h"
#include "settings.h"
#include <Arduino.h>

#define SERIAL_BUFFER_SIZE MAX_KEYCODE + 3
// Lệnh điều khiển nhận được từ Serial, có dạng userformat
char SerialCommand[SERIAL_BUFFER_SIZE];
/// Phân tách mỗi dòng lệnh điều khiển thành 2 vùng. key=value.
/// Key ở điểm bắt đầu của commandline, nên luôn trùng với điểm đầu của lệnh
char *cmdkey = SerialCommand;
const char KEY01[] = "01"; // mã cấu hình tương ứng với chân PIN_PEDAL01
const char KEY02[] = "02"; // mã cấu hình tương ứng với chân PIN_PEDAL02
const char KEY03[] = "03"; // mã cấu hình tương ứng với chân PIN_PEDAL03
const char KEY04[] = "04"; // mã cấu hình tương ứng với chân PIN_PEDAL04

// Phân tách mỗi dòng lệnh điều khiển thành 2 vùng. key=value
USER_FORMAT *cmdvalue = NULL;
/// Chuỗi các kí tự cần gửi, ứng với mỗi pedal. Cú pháp đơn kí tự, là bộ mã ASCII nhưng tận dụng mã ascii điều khiển để thành mã phím bấm điều khiển
ASCII_FORMAT button_sendkeys[MAX_BUTTONS][MAX_KEYCODE];

bool DetermineKeyValue(char * Command, char ** key, char ** value);
void SerialConfiguration();