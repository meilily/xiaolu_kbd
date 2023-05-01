#include <Adafruit_Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Keyboard.h>

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

    uint8_t key_code = 0xFF;
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

    if ((key_code != 0xFF) && (e.bit.EVENT == KEY_JUST_PRESSED)) {
      Keyboard.press(key_code);
    } else if ((key_code != 0xFF) && (e.bit.EVENT == KEY_JUST_RELEASED)) {
      Keyboard.release(key_code);
    }
  }

  delay(10);
}
