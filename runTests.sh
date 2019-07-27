#!/bin/bash

clear

echo "RUN MESSAGE TEST"
(cd test_code/message_protocol/; ./runMessageTest.sh)

echo "RUN PLAYER TEST"
(cd test_code/message_protocol/; ./runPlayerTest.sh)

echo "RUN SYNC TEST"
(cd test_code/message_protocol/; ./runSyncTest.sh)

echo "RUN PART TEST"
(cd test_code/address_manager/; ./runParticipantsTest.sh)
