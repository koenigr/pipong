
#!/bin/bash

#flags
FLAG="-Wunused-parameter -Wall"

if [ $# -gt 1 ]; then

	MAIN_CLASS=$1

	if [ $2 -eq 1 ]; then
		echo "Compiling $MAIN_CLASS"
                g++ $MAIN_CLASS.cpp \
                ../../mraa_libs/Canvas.cpp \
                ../../mraa_libs/Print.cpp \
                ../../mraa_libs/OLEDDisplay.cpp \
                $FLAG -lmraa -pthread -std=c++11 -o $MAIN_CLASS
	fi

	echo "Run $MAIN_CLASS"
	./$MAIN_CLASS
else

	echo "Usage: ./run.sh <class_name> <compile>"

fi
