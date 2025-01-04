#include "OledScreen.h"

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void showKeySetup(char* bleName)
{
    display.clearDisplay();
    display.setTextSize(1);                             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(0, 0);                            // Start at top-left corner
    display.print(F(" Foot "));
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.println(F(" keyboard"));
    display.setTextSize(1);
    display.setCursor(0, 12);
    display.print(F("NameBL: "));  
    display.println(F(bleName));
    display.setCursor(0, 24);
    display.print(F("Key press: "));
    display.display();
}

void setupOled(char* bleName)
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.display();
    delayMicroseconds(200 * 1000);
    showKeySetup(bleName);
    delayMicroseconds(200 * 1000);
}

void showKeyPress(unsigned char no)
{
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setCursor(75,24);
    display.print(" ");
    display.print(no);
    display.print(" ");
    display.display();
}