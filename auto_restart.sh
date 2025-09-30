#!/bin/sh


#  This is shell script for auto-makeing dwm:

if [ -f config.h ]
then
	rm "config.h"
else
	echo "didin't recognize"
fi

make 
sudo make install
