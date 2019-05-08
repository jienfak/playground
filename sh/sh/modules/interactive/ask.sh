
ask () {
	echo -n $1
	read answer
	if [ $answer = y ]; then return 0 ;fi
	if [ $answer = Y ]; then return 0 ;fi
	return 1
}
