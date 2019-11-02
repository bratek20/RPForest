#!/bin/bash

BUILD_FOLDER=build
if [ "$1" = "--debug" ] || [ "$1" = "-d" ]; then
	BUILD_FOLDER=debug
fi

cd ..
if [ "$1" = "--clean" ] || [ "$1" = "-c" ]; then
	rm -rf $BUILD_FOLDER
	mkdir $BUILD_FOLDER
	cd $BUILD_FOLDER
	cmake ..
else
	cd $BUILD_FOLDER
fi

make
cd ../bin
