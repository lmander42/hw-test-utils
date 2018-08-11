#!/usr/bin/env bash
# Install script for hardware test utils on Raspberry Pi

# Script Setup
# ============
set -o errexit -o pipefail

# Script Execution
# ================
echo "Running cmd-n-ctl install.sh"
script_path=$(dirname "$0")  # for copying files

# Install python3
echo
echo "Checking for python3..."
sudo apt install python3
# Install pip3
echo
echo "Checking for pip3..."
sudo apt install python3-pip
# Install  hamlib
echo
echo "Checking for hamlib..."
sudo apt install libhamlib-doc libhamlib-dev libhamlib-utils
# Install socat
echo
echo "Checking for socat..."
sudo apt install socat
# Install pigpio daemon
echo
echo "Checking for pigpio daemon..."
sudo apt install pigpio

# Install & activate virtualenv
# -----------------------------
echo
echo "Checking for virtualenv..."
sudo pip3 install virtualenv

# activating virtualenv
if ! [ -e "$HOME/.satcomm/bin/activate" ]; then
  echo; echo "Creating virtual environment..."
  python3 -m venv "$HOME/.hwtest/"
fi
source "$HOME/.hwtest/bin/activate"
echo "Virtual environment activated!"
echo; echo "Installing python packages..."

# install python packages
echo; echo "Installing pyserial..."
pip3 install pyserial --no-cache-dir
echo; echo "Installing click..."
pip3 install click --no-cache-dir

# Cleanup
# =======
deactivate
echo
echo "Installation Complete!"
echo "Virtual environment stored in $HOME/.hwtest/bin/activate"
echo; echo "To uninstall, run \'rm -rf $HOME/.hwtest\'"

exit 0
