#pragma once

#include "FootKeyboardBuilder.h"

enum KEYSTATUS
{
    KEYFREE = 0,    // phím không được bấm
    KEYDOWN = 1,    // phím vừa được bấm
    KEYPRESS = 2,   // phím bấm giữ
    KEYUP = 3,      // phím vừa được nhả 
};

/// Số lượng kí tự bàn phím tối đa của một phím pedal
#define MAX_KEY_CODE 100

/// Số lượng pedal/nút bấm tối đa
#define MAX_BUTTONS 4 

const uint button_pins[MAX_BUTTONS] = {PIN_PEDAL01, PIN_PEDAL02, PIN_PEDAL03, PIN_PEDAL04};
#define uint button_prevalues[MAX_BUTTONS];   /// Giá trị trước đó, ở dạng digital 0/1 của nút bấm
#define uint button_curvalues[MAX_BUTTONS];   /// Giá trị hiện thời, ở dạng digital 0/1 của nút bấm
#define KEYSTATUS button_status[MAX_BUTTONS]; /// Trạng thái hiện thời của các nút bấm

/// @brief Thời điểm của lần lặp trước đó
#define unsigned long TimeOfPreLoop;
