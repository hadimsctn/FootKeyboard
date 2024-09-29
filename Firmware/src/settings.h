#ifndef SETTINGS_H
#define SETTINGS_H

// Số lượng kí tự ban phím tối đa của một phím pedal
#define MAX_KEYCODE 100
// Số lượng pedal/nút bấm tối đa
#define MAX_BUTTONS 1
// Tên của thiết bị trên mạng
#define DEFAULT_BLENAME "Foot Keyboard"

// Default setting pedal
#define DEFAULT_PEDAL_01 "{PGDN}"

/// Chứa tên mạng BLE Bluetooth
#define MAX_BLE_NAME 32

// define the number of bytes you want to access. 32 kí tự chứa thông tin phần BLE Name
#define EEPROM_SIZE (MAX_KEYCODE * MAX_BUTTONS + MAX_BLE_NAME )

void GetSettings(char  *blename, void * button_sendkeys);
void SaveSettings(int key, char * value);
#endif