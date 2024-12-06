#include <Arduino.h>
#include <BleKeyboard.h>
#include <Setting.h>

const uint button_pins[MAX_BUTTONS] = {PIN_PEDAL01, PIN_PEDAL02, PIN_PEDAL03, PIN_PEDAL04};
uint button_prevalues[MAX_BUTTONS];   /// Giá trị trước đó, ở dạng digital 0/1 của nút bấm
uint button_curvalues[MAX_BUTTONS];   /// Giá trị hiện thời, ở dạng digital 0/1 của nút bấm
KEYSTATUS button_status[MAX_BUTTONS]; /// Trạng thái hiện thời của các nút bấm

/// @brief Thời điểm của lần lặp trước đó
unsigned long TimeOfPreLoop;

FootKeyboardBuilder footKeyboardBuilder(DEFAUL_BLENAME, "NDT Device Manufacturer", 100);

void connectBleBluetooth()
{
  uint8_t led_blink = HIGH;

  // Nếu đã kết nối rồi thì hủy kết nối
  if (footKeyboardBuilder.isConnected())
  {
    footKeyboardBuilder.end();
  }

  // Bắt đầu phiên
  footKeyboardBuilder.begin();
  // Led nháy báo hiệu đang tìm thiết bị kết nôi
  while (!footKeyboardBuilder.isConnected())
  {
    led_blink = !led_blink;
    digitalWrite(LED_BUILTIN, led_blink);
    delay(100);
  }
  if (footKeyboardBuilder.isConnected())
    digitalWrite(LED_BUILTIN, HIGH);
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
}

void loop()
{
  if (footKeyboardBuilder.isConnected())
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    // footKeyboardBuilder.write(0x62);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
  }
  else
  {
    connectBleBluetooth();
  }
}