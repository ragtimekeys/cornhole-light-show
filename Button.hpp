#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Arduino.h"

#define LONG_HOLD_TIME 1000

// See https://github.com/thomasfredericks/Bounce2
#define BOUNCE_LOCK_OUT
#include <Bounce2.h>

class Button {
  public:
    Button(int pin, void (*shortHoldCallback)(void), void (*longHoldCallback)(void));

    void        update(void);
  
  private:
    Bounce      _debouncer;
    int         _prevButtonState;
    uint32_t    _holdStart;
    bool        _isHeld;
    void        (*_shortHoldCallback)(void);
    void        (*_longHoldCallback)(void);

    void        _checkHold(bool isReleased);

};

#endif
