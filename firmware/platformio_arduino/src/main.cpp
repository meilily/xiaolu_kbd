#include <Adafruit_Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Keyboard.h>
#include <Wire.h>

/// Row count of the key matrix
static const byte KEY_ROWS = 4;

/// Column count of the key matrix
static const byte KEY_COLS = 4;

/// Row pins (OUT) of the key matrix
static const byte KEY_ROWPINS[KEY_ROWS] = {
    // D1, D2, D3, D6
    27, 28, 29, 0};

/// Column pins (IN) of the key matrix
static const byte KEY_COLPINS[KEY_COLS] = {
    // D10, D9, D8, D7
    3, 4, 2, 1};

/// Definition of the symbol for each key
///
/// @attention
/// Xiaolu is different from the input/output pin layout assumed by
/// Adafruit_Keypad, so symbol is specified in an inverted matrix.
static const char KEY_SYMBOL[KEY_COLS][KEY_ROWS] = {{'7', '4', '1', '0'},
                                                    {'8', '5', '2', '.'},
                                                    {'9', '6', '3', '\n'},
                                                    {'/', '*', '-', '+'}};

/// Key matrix
Adafruit_Keypad keymatrix(makeKeymap(KEY_SYMBOL),
                          const_cast<byte *>(KEY_COLPINS),
                          const_cast<byte *>(KEY_ROWPINS), KEY_COLS, KEY_ROWS);

/// I2C address of M5Stack CardKB
static const uint8_t CARKB_ADDR = 0x5F;

/// Symbol Key Mapping for M5Stack CardKB
static const uint8_t CARKB_KEYMAP[][3] = {
    {0x08, KEY_BACKSPACE, 0},
    {0x09, KEY_TAB, 0},
    {0x0D, KEY_RETURN, 0},
    {0x1B, KEY_ESC, 0},
    {0xb5, KEY_UP_ARROW, 0},
    {0xb6, KEY_DOWN_ARROW, 0},
    {0xb4, KEY_LEFT_ARROW, 0},
    {0xb7, KEY_RIGHT_ARROW, 0},
    // Shift + Key combination
    {0x7f, KEY_DELETE, 0}, // Shift + Backspace
    // Fn + Key combination
    {0x81, KEY_F1, 0},           // Fn + 1
    {0x82, KEY_F2, 0},           // Fn + 2
    {0x83, KEY_F3, 0},           // Fn + 3
    {0x84, KEY_F4, 0},           // Fn + 4
    {0x85, KEY_F5, 0},           // Fn + 5
    {0x86, KEY_F6, 0},           // Fn + 6
    {0x87, KEY_F7, 0},           // Fn + 7
    {0x88, KEY_F8, 0},           // Fn + 8
    {0x89, KEY_F9, 0},           // Fn + 9
    {0x8a, KEY_F10, 0},          // Fn + 0
    {0x8b, KEY_F11, 0},          // Fn + Backspace
    {0x99, KEY_PAGE_UP, 0},      // Fn + Up
    {0xa4, KEY_PAGE_DOWN, 0},    // Fn + Down
    {0x98, KEY_HOME, 0},         // Fn + Left
    {0xa5, KEY_END, 0},          // Fn + Right
    {0x96, KEY_PRINT_SCREEN, 0}, // Fn + P
    {0xa6, 'z', KEY_LEFT_CTRL},  // Fn + Z
    {0xa7, 'x', KEY_LEFT_CTRL},  // Fn + X
    {0xa8, 'c', KEY_LEFT_CTRL},  // Fn + C
    {0xa9, 'v', KEY_LEFT_CTRL},  // Fn + V
    {0xaa, KEY_PAUSE, 0},        // Fn + B
    {0xab, KEY_NUM_LOCK, 0},     // Fn + N
    {0xac, KEY_MENU, 0},         // Fn + M
    {0xaf, ' ', KEY_LEFT_CTRL},  // Fn + SPACE
};

/// LED length of the NeoPixel LED
static const uint16_t NEO_NUMPIXELS = 1;

/// Power pin of NeoPixel LED
static const pin_size_t NEO_PWR = 11; // GPIO11

/// Pixel data pin of NeoPixel LED
static const pin_size_t NEO_PIX = 12; // GPIO12

/// NeoPixel LED
Adafruit_NeoPixel pixels(NEO_NUMPIXELS, NEO_PIX, NEO_GRB + NEO_KHZ800);

/// Arduino setup entry point (Core 0)
void setup() {
  pixels.begin();
  pinMode(NEO_PWR, OUTPUT);
  digitalWrite(NEO_PWR, HIGH);

  pixels.setBrightness(25);
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  pixels.show();

  Serial.begin(115200);
  // while (!Serial) { delay(1); }
  delay(100);
  Serial.println("Boot Xiaolu KBD Arduino FW ...");

  keymatrix.begin();

  Keyboard.begin();

  Wire.begin();

  delay(2000);

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();

  Serial.println("Ready.");
}

/// Arduino loop function (Core 0)
void loop() {
  uint8_t key_count = 0;

  keymatrix.tick();

  while (keymatrix.available()) {
    const keypadEvent e = keymatrix.read();
    const char key = (char)e.bit.KEY;

    Serial.print((key == '\n') ? "ENTER" : String(key));
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      Serial.println(" pressed.");
    } else if (e.bit.EVENT == KEY_JUST_RELEASED) {
      Serial.println(" released");
    }
    Serial.flush();

    uint8_t key_code = 0;
    if (key == '0') {
      key_code = KEY_KP_0;
    } else if (isDigit(key)) {
      key_code = KEY_KP_1 + (key - KEY_KP_1);
    } else if (key == '.') {
      key_code = KEY_KP_DOT;
    } else if (key == '/') {
      key_code = KEY_KP_SLASH;
    } else if (key == '*') {
      key_code = KEY_KP_ASTERISK;
    } else if (key == '-') {
      key_code = KEY_KP_MINUS;
    } else if (key == '+') {
      key_code = KEY_KP_PLUS;
    } else if (key == '\n') {
      key_code = KEY_KP_ENTER;
    }

    if ((key_code != 0) && (e.bit.EVENT == KEY_JUST_PRESSED)) {
      Keyboard.press(key_code);
    } else if ((key_code != 0) && (e.bit.EVENT == KEY_JUST_RELEASED)) {
      Keyboard.release(key_code);
    }
  }

  Wire.requestFrom(CARKB_ADDR, 1);
  while (Wire.available()) {
    const char c = Wire.read();
    if (c != 0) {
      if (isPrintable(c)) {
        Serial.printf("%02x \"%c\" received from CardKB\n", c, c);
        Keyboard.write(c);
      } else {
        Serial.printf("%02x received from CardKB\n", c);

        uint8_t key_code = 0;
        uint8_t modifier_key_code = 0;
        for (const auto keymap : CARKB_KEYMAP) {
          if (c == keymap[0]) {
            key_code = keymap[1];
            modifier_key_code = keymap[2];
            break;
          }
        }

        if (key_code != 0) {
          if (modifier_key_code != 0) {
            Keyboard.press(modifier_key_code);
            delay(10);
          }
          Keyboard.press(key_code);
          delay(10);
          Keyboard.releaseAll();
        }
      }
    }
  }

  delay(10);
}
