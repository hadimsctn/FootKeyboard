#include <Setting.h>
#include <EEPROM.h>

void GetSettings(char * blename, void * area){

}

void SaveBleName(char * name){
    
}
void SaveSettings(int key, char * value){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeBytes(key*MAX_KEY_CODE + MAX_BLE_NAME,value,strlen(value)+1);
    EEPROM.commit();
    EEPROM.end();
}