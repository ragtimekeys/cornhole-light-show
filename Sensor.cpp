#include "Sensor.hpp"

Sensor::Sensor(int pin_echo, int pin_trig, void (*onDrop)(void)) :
  _sr04(pin_echo, pin_trig),
  _onDrop(onDrop)
{
  this->_timeToSleep = 0;
  this->_lastTick = millis();
  this->_isPolling = true;
}

void Sensor::init(void) {
  this->_defaultDistance = this->_sr04.Distance();
  Serial.print("defaultDistance: ");
  Serial.println(this->_defaultDistance);
}

void Sensor::update(void) {
  if (!this->_isPolling) {
    return;
  }
  if (this->_timeToSleep > 0) {
    long delta = millis() - this->_lastTick;
    this->_timeToSleep -= delta;
  } else {
    long dist = this->_sr04.Distance();
    Serial.print(dist);
    Serial.println("cm");

    if (!(this->_defaultDistance - DIST_TOLERANCE <= dist &&
          dist <= this->_defaultDistance + DIST_TOLERANCE)) {
      Serial.println("SOMETHING DROPPED!!");
      if (this->_onDrop) {
        this->_onDrop();
        this->_isPolling = false;
      }
      this->_timeToSleep = TIME_TO_SLEEP;
    }
  }
  this->_lastTick = millis();
}

void Sensor::resumePolling(void) {
  this->_isPolling = true;  
}
