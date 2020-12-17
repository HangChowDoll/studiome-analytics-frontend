
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