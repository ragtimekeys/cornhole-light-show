#ifndef LIGHT_SHOW_HPP
#define LIGHT_SHOW_HPP

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#define LED_SLEEP_TIME  3
#define LAPS_MAX        3

class LightShow {
  public:
    LightShow(int led_count, int pin_led_strip, void (*onLightUpFinish)(void));

    void              init(void);
    void              update(void);

    void              lightUp(void);
  
  private:
    Adafruit_NeoPixel _pixels;
    int               _len;
    bool              _isLit;
    void              (*_onLightUpFinish)(void);

    long              _timeToSleep;
    unsigned long     _lastTick;
};

#endif