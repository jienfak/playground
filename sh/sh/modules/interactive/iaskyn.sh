source $HOME/.profile
source $SHMODS/interactive/iask.sh

iaskyn(){
	while true ; do
		echo -n "$1"
		ans=$(iask)
		[ "$ans" == "y" ] && return 0
		[ "$ans" == "Y" ] && return 0
		[ "$ans" == "n" ] && return 1
		[ "$ans" == "N" ] && return 1
	done
}
