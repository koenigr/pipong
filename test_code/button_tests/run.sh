
#!/bin/bash

#flags
FLAG="-Wunused-parameter -Wall"

if [ $# -gt 1 ]; then

	MAIN_CLASS=$1

	if [ $2 -eq 1 ]; then
		echo "Compiling $MAIN_CLASS"
		g++ $MAIN_CLASS.cpp ../../input/Canvas.cpp ../../input/Print.cpp ../../input/OLEDDisplay.cpp $FLAG -lmraa -pthread -std=c++11 -o $MAIN_CLASS
	fi

	echo "Run $MAIN_CLASS"
	./$MAIN_CLASS
else

	echo "Usage: ./run.sh <class_name> <compile>"

fi
