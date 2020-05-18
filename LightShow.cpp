#include "LightShow.hpp"

LightShow::LightShow(int led_count, int pin_led_strip, void (*onLightUpFinish)(void)) :
  _pixels(led_count, pin_led_strip, NEO_GRB + NEO_KHZ800),
  _onLightUpFinish(onLightUpFinish)
{
  this->_len = led_count;
  this->_isLit = false;
  this->_timeToSleep = 0;
}

void LightShow::init(void) {
  this->_pixels.begin();
  this->_pixels.clear();
  this->_pixels.setPixelColor(119, 0xFF0000);
  this->_pixels.show();
}

void LightShow::update(void) {
  static int i = -1;
  static int lap = -1;
  static const uint32_t colors[LAPS_MAX] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
  };

  if (this->_timeToSleep > 0) {
    long delta = millis() - this->_lastTick;
    this->_timeToSleep -= delta;
  } else {
    this->_pixels.clear();
    if (this->_isLit) {
      if (lap == LAPS_MAX - 1) {
        lap = -1;
        this->_isLit = false;
        if (this->_onLightUpFinish) {
          this->_onLightUpFinish();
        }
      } else {
        i++;
        if (i == this->_len) {
          lap++;
          i = -1;
        } else {
          this->_pixels.setPixelColor(i, colors[lap + 1]);
          this->_pixels.setPixelColor(i + 1, colors[lap + 1]);
          this->_pixels.setPixelColor(i + 2, colors[lap + 1]);
          this->_timeToSleep = LED_SLEEP_TIME;
        }
      }
    }
    this->_pixels.show();
  }
  this->_lastTick = millis();
}

void LightShow::lightUp(void) {
  this->_isLit = true;
}
