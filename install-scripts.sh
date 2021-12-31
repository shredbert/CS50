#!/usr/bin/bash

# lib50
curl -s https://packagecloud.io/install/repositories/cs50/repo/script.deb.sh | sudo bash
sudo apt install libcs50

# style50
sudo pip install style50
# Artistic Style 3.0 (style50 dependency)
sudo add-apt-repository ppa:cs50/ppa
sudo apt-get update
sudo apt-get install astyle

# check50
sudo pip install check50
