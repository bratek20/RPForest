#!/bin/bash

BUILD_FOLDER=build
if [ "$1" = "--debug" ] || [ "$1" = "-d" ]; then
	BUILD_FOLDER=debug
fi

cd ../$BUILD_FOLDER

if [ "$1" = "--clean" ] || [ "$1" = "-c" ]; then
	make clean
fi
make
cd ../bin
