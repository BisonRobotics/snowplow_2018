file is udev rule file for persistant naming of devices connnected.
udev creates symbolic names for devices based on aspects of devices
and assigns chosen symbolic name every time. actual name can change
every time, but the symbolic name will remain the same. current udev
file contains only the GPS. it will mount at /dev/ubloxGPS every
time GPS is plugged in. still need to modify GPS code to reflect
this

the file '99-usb-serial.rules' needs to go in /etc/udev/rules.d
this is a sudoer operation. the changes will go into effect the
next time the device is plugged in. no restarting needed!
