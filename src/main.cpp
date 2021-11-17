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
const byte BUTTON_C_PIN = 18; // errnoeously marked "A"
const byte BUTTON_D_PIN = 5;  // errnoeously marked "C"

const byte BUTTON_START_PIN = 15;
const byte BUTTON_SELECT_PIN = 13;

const byte LED_PIN = 22;

/* end config */

BluJoy joy("Neogeo Mini Gamepad", "SNK", DEADZONE);
TaskHandle_t core0_handle;

bool IS_BLE_CONNECTED = false;
bool IS_CLASSIC_CONNECTED = false;

byte LED_STATE = HIGH;

bool CALIBRATION_MODE = false;
bool DIGITAL_MODE = false;

void report ();
void report_calibrate ();
void toggle_led ();
void deep_sleep ();
void ble_conn_check ();
void poll ();

#ifdef JOY_DEBUG
void debug_common ();
TickTwo debug_interval(debug_common, 1000, 0); // 1 second
#endif

TickTwo report_interval(report, REPORT_RATE, 0, MICROS_MICROS);
TickTwo poll_interval(poll, POLL_RATE, 0, MICROS_MICROS);
TickTwo ble_conn_check_interval(ble_conn_check, 1000, 0); // 1 second
TickTwo calibrate_interval(report_calibrate, REPORT_RATE, 0, MICROS_MICROS);
TickTwo nc_led_interval(toggle_led, 1000, 0); // 1 second
TickTwo sleep_timeout(deep_sleep, SLEEP_TIMEOUT * 60000, 0);
TickTwo button_sleep_timeout(deep_sleep, SLEEP_BUTTON_TIMEOUT * 1000, 1);

void stop_all_timers () {
  poll_interval.stop();
  report_interval.stop();
  ble_conn_check_interval.stop();
  calibrate_interval.stop();
  nc_led_interval.stop();
  sleep_timeout.stop();
  button_sleep_timeout.stop();
}

void update_core1_timers () {
  report_interval.update();
  ble_conn_check_interval.update();
  calibrate_interval.update();
  nc_led_interval.update();
  sleep_timeout.update();
  button_sleep_timeout.update();

  #ifdef JOY_DEBUG
  debug_interval.update();
  #endif
}

void update_core0_timers () {
  poll_interval.update();
}

float map_axis_value (uint16_t axis_state_raw) {
  return BluJoy::map_range(axis_state_raw, 0.0, 4095.0, -1.0, 1.0);
}

void read_dpad () {
  joy.set_dpad_analog_state(
    BluJoy::AXIS_LX, BluJoy::AXIS_LY,
    map_axis_value(analogRead(AXIS_X_PIN)), map_axis_value(analogRead(AXIS_Y_PIN))
  );
}

void read_buttons () {
  joy.set_button_state(BluJoy::BUTTON_A, digitalRead(BUTTON_A_PIN));
  joy.set_button_state(BluJoy::BUTTON_B, digitalRead(BUTTON_B_PIN));
  joy.set_button_state(BluJoy::BUTTON_X, digitalRead(BUTTON_C_PIN));
  joy.set_button_state(BluJoy::BUTTON_Y, digitalRead(BUTTON_D_PIN));

  joy.set_button_state(BluJoy::BUTTON_START, digitalRead(BUTTON_START_PIN));
  joy.set_button_state(BluJoy::BUTTON_SELECT, digitalRead(BUTTON_SELECT_PIN));
}

void read_axes () {
  joy.set_axis_state(BluJoy::AXIS_LX, map_axis_value(analogRead(AXIS_X_PIN)));
  joy.set_axis_state(BluJoy::AXIS_LY, map_axis_value(analogRead(AXIS_Y_PIN)));
}

#ifdef JOY_DEBUG
uint32_t report_runs = 0;
uint32_t poll_runs = 0;
#endif

void loop () {
  update_core1_timers();
}

void core0_loop (void *p) {
  for(;;) {
    up