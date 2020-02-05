#!/bin/bash

cd $1

for img in frame*.exr
do 
	name=${img%%.exr}
	echo $name
	pfsin ${img} | pfsout ${name}.hdr
	pfsin ${name}.hdr | pfstmo_drago03 | pfsout ${name}.png
	rm ${name}.hdr
done

apngasm out.png frame*.png
apng2gif out.png


