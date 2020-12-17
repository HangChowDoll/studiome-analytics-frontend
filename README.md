
# NeoGeo Mini Bluetooth gamepad

Bluetooth conversion of the NeoGeo mini gamepad using an Esp32.

Uses [ESP32-BLE-Gamepad](https://github.com/lemmingDev/ESP32-BLE-Gamepad) to do Bluetooth things.

![photo](img/01-glam.jpg)

## Features

- Real analog joystick with [scaled radial deadzone](https://github.com/Minimuino/thumbstick-deadzones). Unlike the original controller the output is actually analog
- Optional selectable digital mode with [eight symmetric angular zones](https://gamingprojects.wordpress.com/2017/08/04/converting-analog-joystick-to-digital-joystick-signals/)
- Auto sleep
- Manual sleep
- Analog stick calibration

## Usage

- Wake from sleep: start button
- Force sleep: keep select pressed for 5 seconds
- Auto sleep: no inputs for 5 minutes
- Calibration mode: keep "C" pressed while it wakes from sleep
- Digital mode: keep "D" pressed while it wakes from sleep. This will send the analog stick data as a digital dpad. This setting is preserved in the eeprom
- Analog mode: keep "A" pressed while it wakes from sleep. This will send analog stick data as a left stick. This setting is preserved in the eeprom

## Calibration mode

- Press start to wake the controller from sleep, keeping "C" pressed for a few seconds
- Keep the analog stick in its center position, then press select
- Move the analog stick to its full range, then press select
- The Esp32 saves the calibration data to the internal eeprom then reboots

## Issues

- No external leds: I should add some to see what's going on (connected / disconnected / calibration mode, low battery, etc)
- The only battery that fits properly is only 350mah.

## Parts used

- Platformio: to build and flash the code
- Esp32 board: Lolin32 lite because it's cheap on aliexpress and has an integrated lipo charger
- Lipo battery: I used a 402535 (350mah) because it fits nicely
- USB C connector with breakout board: the shorter & narrower the better
- Stuff to trim the shell: craft files, flush cutters, (low) power tools
- A 3d printer to print the usb gasket
- Superglue to glue the USB connector to the gasket, and the gasket to the shell
- 30awg solid core wire, solder, flux