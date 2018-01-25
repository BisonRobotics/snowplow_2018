#!/bin/bash
printf "Logging in as client\n"
echo -ne "\x02sMN SetAccessMode 03 F4724744\x03" | netcat 192.168.0.1 2111
#client password: F4724744, client mode: 03
