#pragma once

#define LOW               0x0
#define HIGH              0x1
// Số lượng kí tự ban phím tối đa của một phím pedal
#define MAX_KEYCODE 100
// Số lượng pedal/nút bấm tối đa
#define MAX_BUTTONS 4
// Tên của thiết bị trên mạng
#define DEFAULT_BLENAME "Foot Keyboard"

// Default setting pedal
#define DEFAULT_PEDAL_01 "{PGDN}"
#define DEFAUL_FEATURE_PEDAL_01 "{PGUP}"
#define DEFAUL_FEATURE_PEDAL_02 "{ENTER}"
#define DEFAUL_FEATURE_PEDAL_03 "{CTRL}{F4}{~CTRL}"
/// Chứa tên mạng BLE Bluetooth
#define MAX_BLE_NAME 32
#define PEDAL_ACTIVE_LOGIC 0
#define PEDAL_DEACTIVE_LOGIC 1
enum KEYSTATUS
{
  KEYFREE = 1,  // phím không được bấm
  KEYDOWN = 0,  // phím được bấm
  KEYPRESS = 2, // phím bấm giữ
  KEYUP = 3,    // phím vừa được nhả
};
// define the number of bytes you want to access. 32 kí tự chứa thông tin phần BLE Name
#define EEPROM_SIZE (MAX_KEYCODE * MAX_BUTTONS + MAX_BLE_NAME )
void GetSettings(char  *blename, void * button_sendkeys);
void SaveSettings(int key, char * value);
KEYSTATUS DetectKeyWordflow(uint8_t pre, uint8_t cur);