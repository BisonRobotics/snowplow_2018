#!/bin/bash
#printf "Polling single scan with bin\n"
echo -ne "\x02\x02\x02\x02\x00\x00\x00\x11sEN LMDscandata \x01\x33" | netcat 192.168.0.1 2111
#^^ sends binary equivalent of ascii command in singlePoll.sh
