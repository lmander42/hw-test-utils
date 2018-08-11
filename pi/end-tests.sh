#!/usr/bin/env bash
#
# This script kills ALL the background processes that the test scripts
# collectively use.
#
# author: Marion Anderson
# date:   2018-08-11
# file:   end-tests.sh

set -o errexit -o pipefail

# Helper function to get pid of satcomm BASH commands
# takes one arg, the input string
# usage: `get_pid "input str"``
get_pid() {
  str=$(ps aux | grep "$1" | head --lines=1)
  str=$(tr --squeeze-repeats " " <<< "$str")
  pid=$(cut --delimiter=' ' --fields=2 <<< "$str")
}

# Loop through process names
declare -a proc_names=("pigpiod" "socat" "rotctld")  # from stack overflow
for name in "${proc_names[@]}"; do

  # check if actually running
  if ! [ $(ps aux | grep "$name" | wc --lines) -gt 1 ]; then
    echo "$name isn't running?"

  # killing process
  else
    get_pid "$name"
    sudo kill $pid
    if [ $? ]; then
      echo "$name killed!"
    else
      echo "Failed to kill $name !"
    fi
  fi
done

exit 0
