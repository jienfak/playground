#!/usr/bin/sh


helpa(){
	helppager(){
		less -R
	}
	# Check manual first.
	man $argv >/dev/null 2>&1
	if [ $status = 0 ] ; then
		man $argv
		echo "Got manual, for $argv."
		return
	fi

	# Check info.
	info --version
	if [ $status = 0 ]  ; then
		echo "Got info page for $argv."
		info $argv	
		if [ $status = 0 ] ; then
			return
		fi
	fi
	
	# Check 'help' options.
	which $argv > /dev/null 2>&1
	if [ $status != 0 ] ; then
		echo "helpa: Program '$argv' not found."
		return 
	fi
	
	eval $argv -h > /dev/null 2>&1
	if [ $status = 0 ] ; then 
		echo "helpa: Worked with '-h' option."
		eval $argv -h | helppager 2>&1
		return
	fi

	eval $argv --help > /dev/null 2>&1
	if [ $status = 0 ] ; then
		echo "helpa: Worked with '--help' option."
		eval $argv --help | helppager 2>&1
		return
	fi

	eval $argv -help > /dev/null 2>&1
	if [ $status = 0 ] ; then
		echo "helpa: Worked with '-help' option"
		eval $argv -help | helppager 2>&1
		return
	fi

	eval $argv help > /dev/null 2>&1
	if [ $status = 0 ] ; then
		echo "helpa: Worked with 'help' option."
		eval $argv help | helppager 2>&1
		return
	fi

	eval $argv > /dev/null 2>&1
	if [ $status = 0 ] ; then
		echo "helpa: Worked without any options."
		eval $argv | helppager 2>&1
		return
	fi

	echo "helpa: Could not get any help!"
}
