#include <Arduino.h>
#include <BleKeyboard.h>
#include "FootKeyboardBuilder.h"
#include "settings.h"
#include <SerialConfiguration.h>

#define PIN_PEDAL01 15 // Connect pedal1 to port D15
#define PIN_PEDAL02 16 // Connect pedal1 to port D15
#define PIN_PEDAL03 17 // Connect pedal1 to port D15
#define PIN_PEDAL04 18 // Connect pedal1 to port D15

const uint button_pins[MAX_BUTTONS] = {PIN_PEDAL01, PIN_PEDAL02, PIN_PEDAL03, PIN_PEDAL04};
uint button_prevalues[MAX_BUTTONS];   /// Giá trị trước đó, ở dạng digital 0/1 của nút bấm
uint button_curvalues[MAX_BUTTONS];   /// Giá trị hiện thời, ở dạng digital 0/1 của nút bấm
KEYSTATUS button_status[MAX_BUTTONS]; /// Trạng thái hiện thời của các nút bấm
unsigned long TimeOfPreLoop;
FootKeyboardBuilder footKeyboardBuilder = FootKeyboardBuilder(DEFAULT_BLENAME);

void connectBleBluetooth()
{
  uint8_t led_blink = HIGH;

  if (footKeyboardBuilder.isConnected())
  {
    footKeyboardBuilder.end();
  }
  footKeyboardBuilder.begin();
  while (!footKeyboardBuilder.isConnected())
  {
    led_blink = !led_blink;
    digitalWrite(LED_BUILTIN, led_blink);
    delay(100);
  }
  if (footKeyboardBuilder.isConnected())
    digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < MAX_BUTTONS; i++)
  {
    pinMode(button_pins[i], INPUT_PULLUP);
    button_status[i] = KEYFREE;
  }
  connectBleBluetooth();
  TimeOfPreLoop = millis();
}

void loop()
{
  static uint8_t tmp;
  static uint8_t isDown;
  if (footKeyboardBuilder.isConnected())
  {
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        // Lấy giá trị phím bấm mới
        tmp = digitalRead(button_pins[i]);
        // Nếu 3 lần đọc liên tiếp có dạng 010 hoặc 101 thì chuyển về 000 hoặc 111 tương ứng
        if ((tmp == button_prevalues[i]) && (tmp != button_curvalues[i]))
        {
            button_curvalues[i] = tmp;
        };
        // Lưu lại lịch sử, chóng nhảy phím
        button_prevalues[i] = button_curvalues[i];
        button_curvalues[i] = tmp;

        // Xác định trạng thái phím
        button_status[i] = DetectKeyWordflow(button_prevalues[i], button_curvalues[i]);
    }
    isDown = false;
    // đọc trạng thái của cả 4 nút
    for (int i = 0; i < MAX_BUTTONS; i++)
    {    
        if (button_status[i] == KEYDOWN)
        {
            
            footKeyboardBuilder.SendKeys(button_sendkeys[i]);       //bleKeyboardBuilder.write(KEY_PAGE_DOWN);
            isDown = true;
        }
    }
    if (isDown)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
  }
  else
  {
    connectBleBluetooth();
  }
  SerialConfiguration();
}