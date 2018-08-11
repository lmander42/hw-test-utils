#!/usr/bin/env python3
"""Simple CLI for stepping a stepper motor

STEP PIN: 17
DIR PIN:  18

author: Marion Anderson
date:   2018-08-09
file:   test_stepper.py
"""
from __future__ import absolute_import

import time

import click
import pigpio


@click.command()
def main():
    """Steps a stepper motor and can change the direction.
    \b
    Direction Pin: GP17
    Stepper Pin: GP18
    """
    print('Starting test_stepper!')

    # Setup
    dir_pin = 17
    step_pin = 18
    pi = pigpio.pi()
    pi.set_mode(step_pin, pigpio.OUTPUT)
    pi.set_mode(dir_pin, pigpio.OUTPUT)
    pi.write(dir_pin, 1)

    # Control
    state = 1
    go = True
    while go:
        cmd = input('Press enter to step or \'-\' to switch direction: ')
        # change direction
        if cmd == '-':
            if state == 1:
                pi.write(dir_pin, 0)
                state = 0
            else:
                pi.write(dir_pin, 1)
                state = 1
            time.sleep((0.0000003))  # 200ns setup time

        # exit
        elif cmd == 'q' or cmd == 'quit' or cmd == 'exit':
            go = False

        # step motor
        pi.write(step_pin, 1)
        time.sleep(0.0001)  # 1us minimum pulse width
        pi.write(step_pin, 0)
        time.sleep(0.0001)

    # Shutdown
    pi.stop()
