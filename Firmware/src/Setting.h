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

#define DEFAUL_BLENAME "Foot Keyboard"

#define DEFAUL_FEATURE_PEDAL_00 "{PGDN}"
#define DEFAUL_FEATURE_PEDAL_01 "{PGUP}"
#define DEFAUL_FEATURE_PEDAL_02 "{ENTER}"
#define DEFAUL_FEATURE_PEDAL_03 "{CTRL}{F4}{~CTRL}"

#define MAX_BLE_NAME 32

#define EEPROM_SIZE (MAX_KEY_CODE * MAX_BUTTONS + MAX_BLE_NAME )

void GetSettings(char * blename, void * button_sendkeys);
void SaveSettings(int key, char * value);
