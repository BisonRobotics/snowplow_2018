#!/bin/bash
#printf "Polling single data with ascii\n"
COMMAND=0
while [ $COMMAND -lt 1 ]; do
	echo -ne "\x02sRN\x20LMDscandata\x03" | netcat 192.168.0.1 2111
	sleep 3
	let COMMAND=COMMAND+1
done

