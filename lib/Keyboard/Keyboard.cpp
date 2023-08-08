#include "Keyboard.hpp"

uint8_t Keyboard::lastCode = 0;

void Keyboard::begin() {
  pinMode(KB_POWER_PIN, OUTPUT);
  digitalWrite(KB_POWER_PIN, HIGH);
  delay(500);
  Wire.begin(KB_I2C_SDA_PIN, KB_I2C_SCL_PIN);
}

void Keyboard::loop() {
  char keyValue = 0;
  Wire.requestFrom(KB_I2C_ADDR, 1);
  while (Wire.available() > 0) {
    lastCode = Wire.read();
  }
}

bool Keyboard::get(KeyEvent* event) {
  if (lastCode != (char)0x00) {
    event->code = lastCode;
    if (lastCode >= (char)0x20 && lastCode <= (char)0x7f) {
      event->text = (char)lastCode;
    }
    event->state = KeyState::PRESSED;

    return true;
  } else {
    return false;
  }
}

void Keyboard::end() { digitalWrite(KB_POWER_PIN, LOW); }