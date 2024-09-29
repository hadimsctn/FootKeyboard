#include "settings.h"
#include <EEPROM.h>

void GetSettings(char * bleName, void * area){
    uint8_t i;
    EEPROM.begin(EEPROM_SIZE);
    // Read Name BLE Device
    EEPROM.readString(0,bleName,MAX_BLE_NAME);
    // Read data of all button
    EEPROM.readBytes(i * MAX_KEYCODE + MAX_BLE_NAME, area , MAX_BUTTONS * MAX_KEYCODE);
    EEPROM.end();  
}
void SaveSettings(int key, char * value){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeBytes(key*MAX_KEYCODE + MAX_BLE_NAME, value, strlen(value)+1);
    EEPROM.end();
}