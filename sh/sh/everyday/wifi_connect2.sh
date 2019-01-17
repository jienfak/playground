#!/bin/sh

dev=$1
echo Setting device \'$dev\' up...
sudo ip link set $dev up

echo Device status:
ip link show wlp1s0

sudo iw dev $dev scan | grep SSID

echo -n "Enter SSID you want to use:"
read ssid

echo -n "Enter password:"
read pass
sudo wpa_supplicant -i wlp1s0 -c <(wpa_passphrase $ssid $pass )

