
source $HOME/.profile

srconeof(){
	for src in $@ ; do
		if [ -f $src ] ; then
			source $src
			echo $src
			return 0
		fi
	done
	echo "nop"
	return 1
}

