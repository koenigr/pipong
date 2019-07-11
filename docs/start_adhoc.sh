#!/bin/sh

sudo iwconfig wlan0 mode ad-hoc channel 11 essid "PiAdHocNetwork"
sudo ip addr add 192.168.1.11 dev wlan0
