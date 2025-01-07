#include <Arduino.h>
#include <BleKeyboard.h>
#include <Setting.h>
#include <OledScreen.h>

const uint button_pins[MAX_BUTTONS] = {PIN_PEDAL01, PIN_PEDAL02, PIN_PEDAL03, PIN_PEDAL04};
uint button_prevalues[MAX_BUTTONS];   /// Giá trị trước đó, ở dạng digital 0/1 của nút bấm
uint button_curvalues[MAX_BUTTONS];   /// Giá trị hiện thời, ở dạng digital 0/1 của nút bấm
KEYSTATUS button_status[MAX_BUTTONS]; /// Trạng thái hiện thời của các nút bấm
char BleName[MAX_BLE_NAME];
/// @brief Thời điểm của lần lặp trước đó
unsigned long TimeOfPreLoop;

FootKeyboardBuilder footKeyboardBuilder(DEFAUL_BLENAME, "NDT Device Manufacturer", 100);

#define SERIAL_BUFFER_SIZE MAX_KEY_CODE + 3
char SerialCommand[SERIAL_BUFFER_SIZE];
char *cmdkey = SerialCommand;
const char KEY00[] = "01";
const char KEY01[] = "02";
const char KEY02[] = "03";
const char KEY03[] = "04";
const char KEYNAME[] = "NAME";
const char TimeKeyToKey[] = "TK";
const char GetAll[] = "ALL";
USER_FORMAT *cmdvalue = NULL;
ASCII_FORMAT button_sendkeys[MAX_BUTTONS][MAX_KEY_CODE];

void SerialConfiguration(char *SerialCommand)
{
  /// Phân tách mỗi dòng lệnh điều khiển thành 2 vùng. key=value.
  /// Key ở điểm bắt đầu của commandline, nên luôn trùng với điểm đầu của lệnh
  char *cmdkey = SerialCommand;

  uint8_t i, j;
  uint16_t res;
  unsigned char ch;

  // Phân tích thành cặp key=value. Không phù hợp thì dừng luôn
  if (!DetermineKeyValue(SerialCommand, &cmdkey, &cmdvalue))
    return;

#pragma region ASSIGN_COMMAND
  /// Gán lệnh cho các nút bấm/pedal tương ứng
  if (strcasecmp(cmdkey, KEY00) == 0)
  {
    i = 0;
  }
  else if (strcasecmp(cmdkey, KEY01) == 0)
  {
    i = 1;
  }
  else if (strcasecmp(cmdkey, KEY02) == 0)
  {
    i = 2;
  }
  else if (strcasecmp(cmdkey, KEY03) == 0)
  {
    i = 3;
  }
  else if (strcasecmp(cmdkey, TimeKeyToKey) == 0)
  {
    // Thiết lập tốc độ gửi phím
    res = atoi(cmdvalue);
    if (res == 0)
    {
      Serial.println("Error: toc do do phim phai la so nguyen duong.");
    }
    footKeyboardBuilder.SetKeyPerMinute(res);
    SaveScalarSettings(res);
    Serial.print("Info: thiet lap toc do go phim ");
    Serial.print(res);
    Serial.println(" key/phut.");
    Serial.print("Info: OK");
    return;
  }
  else if (strcasecmp(cmdkey, GetAll) == 0)
  {
    /// Hiện ra các thông số cấu hình
    ///  1. Hiển thị tốc độ gửi phím
    res = footKeyboardBuilder.GetKeyPerMinute();
    Serial.print("Info: ");
    Serial.println(res);
    Serial.print("NameBLE: ");
    Serial.println(BleName);
    ///  2. Hiển thị thông tin phím
    for (i = 0; i < MAX_BUTTONS; i++)
    {
      Serial.print("Button ");
      Serial.print(i+1);
      Serial.print(": ");
      res = FootKeyboardBuilder::RevertFormat(button_sendkeys[i], SerialCommand);
      Serial.println(SerialCommand);
    }
    return;
  }
  else if (strcasecmp(cmdkey, KEYNAME) == 0)
  {
    Serial.print("Info: Name Device=");
    Serial.println(cmdvalue);
    SaveBleName(cmdvalue);
    ESP.restart();
  }
  else
  {
    // mã phím bấm không phù hợp, kết thúc luôn
    Serial.println("Error 02: button key is invalid.");
    return;
  }
  // Chuyển đổi từ USER_FORMAT về thành ASCII_FORMAT. Tận dụng lại mảng SerialComamnd để tiết kiệm bộ nhớ, vì cmdValue chắc chắn chứa các cụm từ mô tả dài hơn.
  res = FootKeyboardBuilder::ConvertFormat(cmdvalue, SerialCommand);
  if (res < 0)
  {
    Serial.println("Error: UserFormat wrong at the character ");
    Serial.print(-res);
    return;
  }
  // Áp dụng thành các phím kí tự của phím pedal
  for (j = 0; j <= res; j++)
  { // <=res để copy cả kí tự 0
    button_sendkeys[i][j] = SerialCommand[j];
  }
  SaveSettings(i, button_sendkeys[i]);
  Serial.println("Update Data successfully");
#pragma endregion ASSIGN_COMMAND
}

void connectBleBluetooth()
{
  uint8_t led_blink = HIGH;

  // Nếu đã kết nối rồi thì hủy kết nối
  if (footKeyboardBuilder.isConnected())
  {
    footKeyboardBuilder.end();
    delay(1000);
  }
  // Bắt đầu phiên
  footKeyboardBuilder.begin();
  // Led nháy báo hiệu đang tìm thiết bị kết nôi
  while (!footKeyboardBuilder.isConnected())
  {
    led_blink = !led_blink;
    digitalWrite(LED_BUILTIN, led_blink);
    delay(100);
    if (Serial.available() > 0)
    {
      /// Đọc lệnh từ Serial
      int tmp = Serial.readBytesUntil('\n', SerialCommand, SERIAL_BUFFER_SIZE);
      SerialCommand[tmp] = 0; // đánh dấu kết thúc chuỗi, nếu không sẽ dính với phần còn lại của lệnh trước.
      SerialConfiguration(SerialCommand);
    }
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
  /// Thời gian trễ giữa 2 lần gửi phím 
  uint16_t k2k;
  GetSettings(BleName, &k2k, (void *)button_sendkeys);
  footKeyboardBuilder.setName(BleName);
  setupOled(BleName);
  connectBleBluetooth();
  TimeOfPreLoop = millis();
}

void loop()
{
  if (Serial.available() > 0)
  {
    /// Đọc lệnh từ Serial
    int tmp = Serial.readBytesUntil('\n', SerialCommand, SERIAL_BUFFER_SIZE);
    SerialCommand[tmp] = 0; // đánh dấu kết thúc chuỗi, nếu không sẽ dính với phần còn lại của lệnh trước.
    SerialConfiguration(SerialCommand);
  }
  if (footKeyboardBuilder.isConnected())
  {
    static uint8_t isDown;
    static uint8_t tmp;
    unsigned long currentMillis = millis();
    if ((isDown && (currentMillis - TimeOfPreLoop < 180))                             // Nếu có phím bấm thì phải 180ms mới chạy lại.
        || (!isDown && (currentMillis - TimeOfPreLoop < PERIOD_OF_BUTTON_SCAN_LOOP))) // Nếu không bấm phím thì cứ 15ms lại kiểm tra lại
    {
      return;
    }
    TimeOfPreLoop = currentMillis;
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
      tmp = digitalRead(button_pins[i]);
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
    for (int i = 0; i < MAX_BUTTONS; i++)
    {            
      if (button_status[i] == KEYDOWN)
      {

        footKeyboardBuilder.SendKeys(button_sendkeys[i]); // bleKeyboardBuilder.write(KEY_PAGE_DOWN);
        isDown = true;
        showKeyPress(i+1);
      }
    }
    if (isDown)
    {
      digitalWrite(LED_BUILTIN, LOW);     
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  else
  {
    ESP.restart();
  }
}