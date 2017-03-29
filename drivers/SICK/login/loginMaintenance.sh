#!/bin/bash
printf "Logging in as maintenance\n"
echo -ne "\x02sMN SetAccessMode 03 B21ACE26\x03" | netcat 192.168.0.1 2111
