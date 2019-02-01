#!/usr/bin/sh
# This script generates standard tree of
# directories for projects

mkdir $1
cd $1
	mkdir src

	mkdir bin;
	cd bin
		mkdir dbg rls
	cd ..

	mkdir media
	cd media
		mkdir graphics audio
	cd ..
cd ..


