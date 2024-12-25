#include <BoardConfiguration.h>

/**
 * Hàm chuyển chuỗi hex thành số uint8_t
 */
uint8_t hexStringToUint8(String hex) {
    if (hex.length() != 2) {
        Serial.println("Error: Chuỗi hex phải dài 2 ký tự.");
        return 0;
    }
    
    uint8_t highNibble = charToHexDigit(hex[0]); // Lấy phần cao của byte
    uint8_t lowNibble = charToHexDigit(hex[1]); // Lấy phần thấp của byte
    
    return (highNibble << 4) | lowNibble; // Ghép 2 nửa thành 1 byte
}

/**
 * Hàm chuyển một ký tự hex thành số nguyên 4-bit
 */
uint8_t charToHexDigit(char hex) {
    if (hex >= '0' && hex <= '9') return hex - '0'; // '0'-'9' thành 0-9
    if (hex >= 'A' && hex <= 'F') return hex - 'A' + 10; // 'A'-'F' thành 10-15
    if (hex >= 'a' && hex <= 'f') return hex - 'a' + 10; // 'a'-'f' thành 10-15
    
    Serial.print("Error: Invalid hex character: ");
    Serial.println(hex);
    return 0;
}