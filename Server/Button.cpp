/////////////////////////////////////////////////////////////////
/*
  Button.cpp - Arduino Library to simplify working with buttons.
  Created by Lennart Hennigs.
*/
/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "Button.h"

/////////////////////////////////////////////////////////////////

Button::Button(byte attachTo, byte buttonMode) {
  pin = attachTo;
  setDebounceTime(50);
  pinMode(attachTo, buttonMode);
  //if ((pin == 0) || (pin == 2) || (pin == 4) || (pin == 15) || (pin == 12) || (pin == 13) || (pin == 14) || (pin == 27) || (pin == 33) || (pin == 32)) {
  /*if ( (pin == 32)) {
    capa = touchRead(pin);
    state = capa <  CAPACITIVE_TOUCH_THRESHOLD ? LOW : HIGH;
    } else {
    state = digitalRead(pin);
    }/**/
  state = digitalRead(pin);
}

/////////////////////////////////////////////////////////////////

bool Button::operator==(Button &rhs) {
  return (this == &rhs);
}

/////////////////////////////////////////////////////////////////

void Button::setDebounceTime(unsigned int ms) {
  debounce_time_ms = ms;
}

/////////////////////////////////////////////////////////////////

void Button::setChangedHandler(CallbackFunction f) {
  change_cb = f;
}

/////////////////////////////////////////////////////////////////

void Button::setPressedHandler(CallbackFunction f) {
  pressed_cb = f;
}

/////////////////////////////////////////////////////////////////

void Button::setReleasedHandler(CallbackFunction f) {
  released_cb = f;
}

/////////////////////////////////////////////////////////////////

void Button::setClickHandler(CallbackFunction f) {
  click_cb = f;
}

/////////////////////////////////////////////////////////////////

void Button::setTapHandler(CallbackFunction f) {
  tap_cb = f;
}

/////////////////////////////////////////////////////////////////

void Button::setLongClickHandler(CallbackFunction f) {
  long_cb = f;
}

/////////////////////////////////////////////////////////////////

void Button::setDoubleClickHandler(CallbackFunction f) {
  double_cb = f;
}

/////////////////////////////////////////////////////////////////

unsigned int Button::wasPressedFor() const {
  return down_time_ms;
}

/////////////////////////////////////////////////////////////////

boolean Button::isPressed() const {
  return (state != pressed);
}

/////////////////////////////////////////////////////////////////

boolean Button::isPressedRaw() const {
  return (digitalRead(pin) == pressed);
}

/////////////////////////////////////////////////////////////////

byte Button::getNumberOfClicks() const {
  return click_count;
}

/////////////////////////////////////////////////////////////////

byte Button::getClickType() const {
  return last_click_type;
}
/////////////////////////////////////////////////////////////////

byte Button::getPin() const {
  return pin;
}

/////////////////////////////////////////////////////////////////

void Button::loop() {
  prev_state = state;
  //if (!capacitive) {
  //} else {
  //#if defined(ARDUINO_ARCH_ESP32)
  //if ((pin == 0) || (pin == 2) || (pin == 4) || (pin == 15) || (pin == 12) || (pin == 13) || (pin == 14) || (pin == 27) || (pin == 33) || (pin == 32)) {
  //if (pin == 32) {
  capa = digitalRead(pin);
  //capa = touchRead(pin);
  if (prev_state != (capa)) {
    if (down_ms == 0) {
      down_ms = millis();
    } else if (millis() - down_ms > 50) {
      down_ms = 0;
      state = capa ;
    }
  } else
    down_ms = 0;
  //} else {
  //  state = digitalRead(pin);
  //}/**/
  //state = digitalRead(pin);
  if (prev_state != state)
    if (state == pressed) {
      if (tap_cb != NULL) tap_cb (*this);
      //prev_click = millis();
      if (pressed_cb != NULL) pressed_cb (*this);
    } else {
      //down_time_ms = millis() - down_ms;
      if (tap_cb != NULL) tap_cb (*this);
      //down_ms = millis();
      //prev_click = millis();
    }
}

/////////////////////////////////////////////////////////////////

void Button::reset() {
  click_count = 0;
  last_click_type = 0;
  down_time_ms = 0;
  pressed_triggered = false;
  longclick_detected = false;

  pressed_cb = NULL;
  released_cb = NULL;
  change_cb = NULL;
  tap_cb = NULL;
  click_cb = NULL;
  long_cb = NULL;
  double_cb = NULL;
  triple_cb = NULL;
}

/////////////////////////////////////////////////////////////////
