#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <SR04.h>

#define DIST_TOLERANCE  10
#define TIME_TO_SLEEP   500

class Sensor {
  public:
    Sensor(int pin_echo, int pin_tri, void (*onDrop)(void));

    void          init(void);
    void          update(void);

    void          resumePolling(void);

  private:
    SR04          _sr04;
    long          _defaultDistance;
    long          _timeToSleep;
    unsigned long _lastTick;
    bool          _isPolling;

    void          (*_onDrop)(void);
  
};

#endif
