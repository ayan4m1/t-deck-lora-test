#include <Arduino.h>

#include <Keyboard.hpp>
#include <gfx.hpp>
#include <st7789.hpp>

#define LCD_ROTATION 1
#define LCD_WIDTH 320
#define LCD_HEIGHT 240
#define LCD_HOST HSPI
#define PIN_NUM_MISO 38
#define PIN_NUM_MOSI 41
#define PIN_NUM_CLK 40
#define PIN_NUM_CS 12
#define PIN_NUM_DC 11
#define PIN_NUM_RST -1
#define PIN_NUM_BCKL 42

#define PIN_NUM_ADC 4

using namespace arduino;
using namespace gfx;

using bus_type =
    tft_spi_ex<LCD_HOST, PIN_NUM_CS, PIN_NUM_MOSI, PIN_NUM_MISO, PIN_NUM_CLK,
               SPI_MODE0, LCD_WIDTH * LCD_HEIGHT * 2 + 8>;
using lcd_type = st7789<LCD_WIDTH, LCD_HEIGHT, PIN_NUM_DC, PIN_NUM_RST,
                        PIN_NUM_BCKL, bus_type, LCD_ROTATION, true, 400, 200>;
using lcd_color = color<typename lcd_type::pixel_type>;

lcd_type lcd;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Connected!");

  lcd.initialize();

  Keyboard::begin();
}

void loop() {
  lcd.fill(lcd.bounds(), lcd_color::alice_blue);

  Keyboard::loop();

  KeyEvent event = KeyEvent();
  if (Keyboard::get(&event)) {
    Serial.print("Code: ");
    Serial.println(event.code);
    Serial.print("Text: ");
    Serial.println(event.text);
  }
}
