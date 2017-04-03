#!/bin/bash
printf "Logging in as Service\n"
echo -ne "\x02sMN SetAccessMode 04 81BE23AA\x03" | netcat 192.168.0.1 2111

