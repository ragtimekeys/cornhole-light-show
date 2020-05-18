#include "Button.hpp"
#include "Sensor.hpp"
#include "LightShow.hpp"

#define BAUD            115200

#define PIN_BUTTON      2

#define PIN_ECHO        11
#define PIN_TRIG        12

#define PIN_LED_STRIP   6
#define LED_COUNT       120

void onLightUpFinish();

LightShow lightShow(LED_COUNT, PIN_LED_STRIP, onLightUpFinish);

void onDropCallback() {
  lightShow.lightUp();
}

Sensor sensor(PIN_ECHO, PIN_TRIG, onDropCallback);

void onLightUpFinish() {
  sensor.resumePolling();
}

void shortHoldCallback() {
  lightShow.lightUp();
}

Button button(PIN_BUTTON, shortHoldCallback, nullptr);

void setup() {
  Serial.begin(BAUD);
  while (!Serial) {}

  sensor.init();
  lightShow.init();
}

void loop() {
  button.update();
  sensor.update();
  lightShow.update();
}
