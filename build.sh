#!/bin/bash

clear

make

if [ $? -eq 0 ]; then
  ./PiPong $1 $2
fi
