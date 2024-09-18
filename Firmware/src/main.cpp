#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
#define PIN_PEDAL01 17 //Connect pedal1 to port D2
#define PEDAL_ACTIVE_LOGIC 0
#define PEDAL_DEACTIVE_LOGIC 1
enum KEYSTATUS
{
    KEYFREE = 0,    // phím không được bấm
    KEYDOWN = 1,    // phím vừa được bấm
    KEYPRESS = 2,   // phím bấm giữ
    KEYUP = 3,      // phím vừa được nhả 
};
const uint button_pins = PIN_PEDAL01;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  pinMode(button_pins, INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  uint8_t tmp;
  if(bleKeyboard.isConnected()) {
    tmp = digitalRead(button_pins);
    // Serial.println(tmp);
    if (tmp == KEYDOWN)
    {     
      //bleKeyboard.press(KEY_PAGE_UP);
    }
    // delay(1000);

    // Serial.println("Sending Enter key...");
    // bleKeyboard.write(KEY_RETURN);

    // delay(1000);

    // Serial.println("Sending Play/Pause media key...");
    // bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

    // delay(1000);

   //
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out.
    /*
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
  }
}