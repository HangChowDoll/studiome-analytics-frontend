#include <Arduino.h>
#include <TickTwo.h>

#include <BluJoy.h>

/* config */

// #define JOY_DEBUG 1

const uint REPORT_RATE = 1000; // micros, 1ms
const uint POLL_RATE = 1000; // micros

const float DEADZONE = 0.20;

const uint SLEEP_TIMEOUT = 5; // minutes
const uint SLEEP_BUTTON_TIMEOUT = 5; // seconds

// pins

const byte AXIS_X_PIN = 34;
const byte AXIS_Y_PIN = 35;

const byte BUTTON_A_PIN = 19; // errnoeously marked "B" in the mini controller
const byte BUTTON_B_PIN = 23; // errnoeously marked "D"
const b