#!/bin/bash

echo -ne "\x02sRN\x20LMDscandata\x03" | netcat 192.168.0.1 2111 > /tmp/feedback.hex

#single poll of buffered data from distance sensor
