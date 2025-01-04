#include <Setting.h>
#include <EEPROM.h>

void GetSettings(char *blename,uint16_t * time_k2k, void *area)
{
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.readString(0, blename, MAX_BLE_NAME);
    EEPROM.readInt(MAX_BLE_NAME);
    EEPROM.readBytes(MAX_BLE_NAME+MAX_SCALAR, area, MAX_BUTTONS * MAX_KEY_CODE);
    EEPROM.end();
}

void SaveBleName(char *name)
{
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeString(0, name);
    EEPROM.commit();
    EEPROM.end();
}
void SaveSettings(int key, char *value)
{
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeBytes(key * MAX_KEY_CODE + MAX_BLE_NAME+MAX_SCALAR, value, strlen(value) + 1);
    EEPROM.commit();
    EEPROM.end();
}
void SaveScalarSettings(uint16_t time_k2k){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeInt(MAX_BLE_NAME, time_k2k);
    EEPROM.commit();
    EEPROM.end();
}
KEYSTATUS DetectKeyWordflow(uint8_t pre, uint8_t cur)
{
    if (pre == PEDAL_DEACTIVE_LOGIC && cur == PEDAL_ACTIVE_LOGIC)
        return KEYDOWN;
    else if (pre == PEDAL_ACTIVE_LOGIC && cur == PEDAL_ACTIVE_LOGIC)
        return KEYPRESS;
    else if (pre == PEDAL_ACTIVE_LOGIC && cur == PEDAL_DEACTIVE_LOGIC)
        return KEYUP;
    else
        return KEYFREE;
}
bool DetermineKeyValue(char *Command, char **key, char **value)
{
    char ch;
    uint8_t i;
    *key = Command;
    *value = NULL;

    /// Phân tích parsing
    i = 0;
    do
    {
        ch = Command[i];
        if (ch == '=')
        {
            Command[i] = 0; // Đánh dấu Zero kết thúc chuỗi
            *value = &Command[i + 1];
            break;
        }
        i++;
    } while (ch != 0);

    // Nếu không tìm thấy kí tự = không hợp lệ.
    if (ch == 0)
    {
        Serial.println("Error 01: delimiter = not found.");
        return false;
    };
    return true;
}