#include <Arduino.h>
#include <Wire.h>

#define KB_I2C_ADDR 0x55
#define KB_POWER_PIN 10
#define KB_I2C_SDA_PIN 18
#define KB_I2C_SCL_PIN 8

enum KeyState { PRESSED, HELD_DOWN, RELEASED };

struct KeyEvent {
  KeyState state;
  char text;
  uint8_t code;
};

class Keyboard {
  static uint8_t lastCode;

 public:
  static void begin();
  static void loop();
  static bool get(KeyEvent* event);
  static void end();
};