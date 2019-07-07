# Variable to lose the output.

loseall(){
	eval "$@" 1>/dev/null 2>&1
}
