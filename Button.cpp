#include "Button.hpp"

Button::Button(
  int pin,
  void (*shortHoldCallback)(void),
  void (*longHoldCallback)(void)) :
  _shortHoldCallback(shortHoldCallback),
  _longHoldCallback(longHoldCallback)
{
  pinMode(pin, INPUT_PULLUP);
  this->_debouncer.attach(pin);
  this->_debouncer.interval(5); // 5 ms input delay
  this->_prevButtonState = HIGH;
  this->_isHeld = false;
}

void Button::update(void) {
  this->_debouncer.update();
  int buttonState = this->_debouncer.read();

  if (this->_prevButtonState != buttonState) {
    // on button press
    if (buttonState == LOW) {
      this->_isHeld = true;
      this->_holdStart = millis();
    }
    // on button release
    else {
      this->_checkHold(true);
    }
    this->_prevButtonState = buttonState;
  }
  this->_checkHold(false);
}

void Button::_checkHold(bool isReleased) {
  if (this->_isHeld) {
    uint32_t _holdTime = millis() - this->_holdStart;
    if (_holdTime >= LONG_HOLD_TIME) {
      Serial.print("LONG PRESS \n");
      if (this->_longHoldCallback) {
        this->_longHoldCallback();
      }
      this->_isHeld = false;
    }
    if (isReleased) {
      Serial.print("SHORT PRESS \n");
      if (this->_shortHoldCallback) {
        this->_shortHoldCallback();
      }
      this->_isHeld = false;
    }
  }
}
