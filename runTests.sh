#!/bin/bash

clear

echo "RUN MESSAGE TEST"
(cd test_code/message_protocol/; ./runMessageTest.sh)

echo "RUN PLAYER TEST"
(cd test_code/message_protocol/; ./runPlayerTest.sh)
