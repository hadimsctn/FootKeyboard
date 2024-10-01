#include <Arduino.h>
#include <BleKeyboard.h>
#include "FootKeyboardBuilder.h"
#include "settings.h"

#define PIN_PEDAL01 15 //Connect pedal1 to port D15
#define PEDAL_ACTIVE_LOGIC 0
#define PEDAL_DEACTIVE_LOGIC 1
enum KEYSTATUS
{
    KEYFREE = 1,    // phím không được bấm
    KEYDOWN = 0,    // phím được bấm
    KEYPRESS = 2,   // phím bấm giữ
    KEYUP = 3,      // phím vừa được nhả 
};
const uint button_pins = PIN_PEDAL01;
uint button_prevalues;
uint button_curvalues;
KEYSTATUS button_status;


FootKeyboardBuilder footKeyboardBuilder = FootKeyboardBuilder(DEFAULT_BLENAME);

void connectBleBluetooth(){
  uint8_t led_blink = HIGH;
  
  if(footKeyboardBuilder.isConnected()){
    footKeyboardBuilder.end();
  }
  footKeyboardBuilder.begin();
  while(!footKeyboardBuilder.isConnected()){
    led_blink = !led_blink;
    digitalWrite(LED_BUILTIN, led_blink);
    delay(100);
  }
  if(footKeyboardBuilder.isConnected())digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(button_pins, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  connectBleBluetooth();
}

void loop() {
  uint8_t tmp;
  if(footKeyboardBuilder.isConnected()) {
    tmp = digitalRead(button_pins);
    if (tmp == KEYDOWN)
    {    
      Serial.println(tmp);
      footKeyboardBuilder.press(0x80);
      footKeyboardBuilder.press(0x81);
      footKeyboardBuilder.print("n");
      footKeyboardBuilder.releaseAll(); 
    }
  }
  else{
    connectBleBluetooth();
  }
}