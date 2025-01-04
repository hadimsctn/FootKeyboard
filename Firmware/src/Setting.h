#pragma once

#include "FootKeyboardBuilder.h"

enum KEYSTATUS
{
    KEYFREE = 0,    // phím không được bấm
    KEYDOWN = 1,    // phím vừa được bấm
    KEYPRESS = 2,   // phím bấm giữ
    KEYUP = 3,      // phím vừa được nhả 
};
#define PERIOD_OF_BUTTON_SCAN_LOOP  15
/// Số lượng kí tự bàn phím tối đa của một phím pedal
#define MAX_KEY_CODE 100

/// Số lượng pedal/nút bấm tối đa
#define MAX_BUTTONS 4 

#define DEFAUL_BLENAME "Foot Keyboard"

#define DEFAUL_FEATURE_PEDAL_00 0x8f
#define DEFAUL_FEATURE_PEDAL_01 "{PGUP}"
#define DEFAUL_FEATURE_PEDAL_02 "{ENTER}"
#define DEFAUL_FEATURE_PEDAL_03 "{CTRL}{F4}{~CTRL}"

#define MAX_BLE_NAME 32
#define MAX_SCALAR 16
#define EEPROM_SIZE (MAX_KEY_CODE * MAX_BUTTONS + MAX_SCALAR + MAX_BLE_NAME )

void GetSettings(char * blename, uint16_t * time_k2k, void * button_sendkeys);
void SaveSettings(int key, char * value);
void SaveBleName(char * name);
void SaveScalarSettings(uint16_t time_k2k);
KEYSTATUS DetectKeyWordflow(uint8_t pre, uint8_t cur);
bool DetermineKeyValue(char * Command, char ** key, char ** value);