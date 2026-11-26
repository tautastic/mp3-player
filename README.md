MP3 Player
==========

Firmware and desktop simulator for an MP3 player built on an ESP32-C3 Super
Mini. The device reads four buttons and sends one line per press over USB
serial. The simulator shows the menu in a 240x280 window and moves the
highlight with the arrow keys or with the buttons on the board.


Hardware
--------

ESP32-C3 Super Mini on native USB, seen as /dev/ttyACM0. Buttons connect a
GPIO to GND and use the internal pull-ups:

    GPIO 5     up
    GPIO 6     right
    GPIO 20    down
    GPIO 21    left

Each press sends UP, RIGHT, DOWN or LEFT and a newline at 115200 baud.


Layout
------

    platformio.ini     build environments: device and simulator
    unflags.py         applies build_unflags to the framework's flags
    flake.nix          development shell
    src/core/          button type, serial protocol, debouncer
    src/ui/            LVGL menu and keypad input
    src/device/        firmware
    src/simulator/     desktop program and serial port


Building
--------

Enter the development shell first:

    nix develop

Build and upload the firmware:

    pio run -e device -t upload

Build and run the simulator:

    pio run -e simulator -t exec

The simulator reads /dev/ttyACM0. Add -a and a path to use another port.
Without a port it runs with the keyboard only.
