#!/bin/bash

./singlePoll.sh > feedback.hex
./getData < feedback.hex > final_data/c_prog_output_4.hex

