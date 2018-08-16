#!/usr/bin/env python3
"""Simple CLI for testing a stepper motor

author: Marion Anderson
date:   2018-08-09
file:   test_stepper.py
"""
from __future__ import absolute_import

import time

import click
import pigpio


@click.command()
@click.option('--step-pin', default=23,
              help='GPIO pin number connected to STEP on the driver')
@click.option('--dir-pin', default=22,
              help='GPIO pin number connected to DIRECTION on the driver')
@click.option('--step-angle', default=1.2,
              help='Angle per step on stepper motor')
@click.option('--start-angle', default=0,
              help='Current angular position of stepper')
def main(step_pin, dir_pin, step_angle, start_angle):
    """Continuous interface to move a stepper motor to angular positions."""
    # Setup 
    print('Starting cmd_stepper.py!')
    pi = pigpio.pi()
    pi.set_mode(step_pin, pigpio.OUTPUT)
    pi.set_mode(dir_pin, pigpio.OUTPUT)
    curpos = start_angle

    go = True
    while go:
        print('Current position: ', curpos)
        # Get desired position
        pos = input('Enter an angular position: ')
        if pos in ('q', 'quit', 'exit'):
            go = False
            break
        try:
            pos = int(pos)
        except ValueError as e:
            print('Bad position! Please enter an int or float')
            print(e)
            continue

        # Decide direction by minimizing angular distance
        pos %= 360  # wrap at 2pi
        posmirror = (pos + 180) % 360  # dividing angle b/t moving cw or ccw
        # Lots of if cases for figuring out what the right calculation is
        # basically figuring out which side of the line between pos and its
        # antipode you're on will tell
        if curpos < posmirror and curpos > pos:
            cw = True
            dist = curpos - pos
        elif pos > 180 and curpos > pos:
            cw = True
            dist = curpos - pos
        elif pos > 180 and curpos < posmirror:
            cw = True
            dist = 360 + curpos - pos
        elif curpos < pos and curpos > posmirror:
            cw = False
            dist = pos - curpos
        elif pos < 180 and curpos < pos:  # this and next account for wrapping
            cw = False
            dist = pos - curpos
        elif pos < 180 and curpos > posmirror:
            cw = False
            dist = 360 + pos - curpos
        else:  # default case: just go in some direction for the right distance
            dist = abs(curpos - pos)
            cw = True if curpos > pos else False
                
        # Step motor 
        if cw:
            pi.write(dir_pin, 1)
        else:
            pi.write(dir_pin, 0)
        time.sleep(0.005)  # setup time
        steps = int(dist / step_angle)
        for i in range(steps):
            pi.write(step_pin, 1)
            time.sleep(0.005)
            pi.write(step_pin, 0)
            time.sleep(0.005)
        curpos = pos

    # Shutdown
    pi.stop()

if __name__ == '__main__':
    main()
