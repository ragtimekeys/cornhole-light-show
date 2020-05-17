#include "Button.hpp"

#define BAUD        115200

#define PIN_BUTTON  2

Button button(PIN_BUTTON);

void setup() {
  Serial.begin(BAUD);
  while (!Serial) {}
}

void loop() {
  button.update();
}
