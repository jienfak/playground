#!/usr/bin/sh
# This script generates standard tree of
# directories for projects

mkdir $1
cd $1
	mkdir include
	mkdir src
	cd src
		mkdir lib modules
	cd ..

	mkdir bin;
	cd bin
		mkdir dbg rls lib obj
	cd ..

	mkdir media
	cd media
		mkdir graphics audio
	cd ..

cd ..


