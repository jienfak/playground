if [ $PROFILE_IS_SOURCED != 0 ] ; then
	source $HOME/.profile
fi
source $SHMODS/chores/hasprog.sh

alifhas(){
	if hasprog $2 ; then
		alias $1=$2
	fi
}
