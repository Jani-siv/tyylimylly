#!/bin/bash
make CXX=g++
if [ $? == 0 ]; then
	echo 'Compiling done'
else
	echo 'Error in compiling'
	exit -1
fi

