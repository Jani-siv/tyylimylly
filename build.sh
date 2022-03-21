#!/bin/bash
make CXX=arm-linux-gnueabihf-g++
if [ $? == 0 ]; then
	echo 'Compiling done'
else
	echo 'Error in compiling'
	exit -1
fi
echo 'sending file'
sshpass -f pass.txt scp ./out/tyylimylly pi@192.168.0.100:tyylimylly

if [ $? == 0 ]; then
	echo 'File send successfully'
else
	echo 'Error to connect raspberry'
	exit -1
fi

