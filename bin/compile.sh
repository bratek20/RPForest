#!/bin/bash

BUILD_FOLDER=build
CMAKE_FLAGS=""
if [ "$1" = "--debug" ] || [ "$1" = "-d" ] || [ "$2" = "--debug" ] || [ "$2" = "-d" ]; then
	BUILD_FOLDER=debug
	CMAKE_FLAGS=-DCMAKE_BUILD_TYPE=Debug
fi

cd ..
if [ "$1" = "--clean" ] || [ "$1" = "-c" ]; then
	rm -rf $BUILD_FOLDER
	mkdir $BUILD_FOLDER
	cd $BUILD_FOLDER
	cmake .. $CMAKE_FLAGS
else
	cd $BUILD_FOLDER
fi

make
cd ../bin
