#!/bin/bash
cd ../build
if [ "$1" = "--clean" ] || [ "$1" = "-c" ]; then
	make clean
fi
make
cd ../bin
