#!/usr/bin/env bash
#
# This file runs hamlib on the receiving side.
#
# author: Marion Anderson
# date:   2018-08-11
# file:   hamlib_dump.sh

set -o errexit
set -o pipefail
echo "Running hamlib_dump.sh"; echo

# stitch cust serial ports together
if [ $(ps aux | grep socat | wc --lines) -gt 1 ]
then
  echo "socat already running!"
else
  sudo socat PTY,link="$HOME/opt/hamlibT",user="$USER"\
             PTY,link="$HOME/opt/hamlibR",user="$USER" &
  echo "socat started in $HOME/opt/!"
fi

# use EasyComm I protocol
if [ $(ps aux | grep rotctld | wc --lines) -gt 1 ]
then
  echo "rotctld already running! Kill that process before running this script."
else
  sudo rotctld -m 201 -T "raspberrypi.local" -vvvvv -r "$HOME/opt/hamlibT" &> "$HOME/rotlog.log" &
  echo "rotctld activated using EasyComm I protocol!"; echo
  echo "See $HOME/rotlog.log for debug output."
  echo "run \'cat $HOME/opt/hamlibR\' to see serial dump."
fi

echo
echo "Resources successfully stitched!"
exit 0
