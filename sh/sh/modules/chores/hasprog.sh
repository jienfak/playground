

source $HOME/.profile
hasprog(){
	if which $1 1>/dev/null 2>&1 ; then
		return 0
	else
		return 1
	fi
}
