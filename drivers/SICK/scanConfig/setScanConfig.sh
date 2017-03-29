#!/bin/bash
#printf "\nSetting frequency and angular resolution:\n"
#printf "\tFrequency: 25Hz, Angular Resolution: .5 Degrees\n"
echo -ne "\x02sMN mLMPsetscancfg +5000 +1 +5000 -450000 2250000\x03" | netcat 192.168.0.1 2111
#cat setScanConfiguration.txt | netcat 192.168.0.1 2111

