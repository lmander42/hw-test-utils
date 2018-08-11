# hw-test-utils/pi
Test utilities for Raspberry Pi. Covers PWM control, some network communication, serial ports (by way of [miniterm](https://pyserial.readthedocs.io/en/latest/tools.html#miniterm)),  and a **_very_** hardcoded stepper motor test script.

## Installation
run `./installer/installer.sh` to create a virtual environment and install all dependencies. To uninstall, just run `rm -rf "$HOME/.hwtest/"`.

## Usage
The test scripts make use of a virtual envrionment at `$HOME/.hwtest/bin/activate`. Source it in your terminal, and then run any of the scripts in this directory.

`end-tests.sh` is an end-of-testing cleanup script. It kills all the background processes the test scripts use.
