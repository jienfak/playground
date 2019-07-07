#!/bin/sh

# Show where your home 'code' directory is.
C="$(cat $HOME/.codepath)"
source $C/opt/rc/profile
# Ask module.
source $SHMODS/interactive/iaskyn.sh
source $SHMODS/chores/loseall.sh


backup(){
	loseall mv "$1" "$1.backup"
}

lns(){
	for i in ${@:2} ; do
		ln -s $1 $i
	done
}

rclikeln(){
	for i in $@ ; do
		backup $HOME/.$i
		lns $MYOPT/$i $HOME/.$i
	done
}

conflikeln(){
	for i in $@ ; do
		backup $XDG_CONFIG_HOME/$i
		lns $MYOPT/$i $XDG_CONFIG_HOME/$i
	done
}
if [ -z $@ ] ; then
	echo usage: $0 [targets]
	return
fi
if [ "$@" == "all" ] ; then
	deps="config rc zsh bash nvim git dir mega dict"
else
	deps="$@"
fi

for i in $deps ; do
	case "$i" in
		"config")
			cd "$OPT/config"
			for i in * ; do
				backup "$XDG_CONFIG_HOME/$i"
				lns "$i" "$XDG_CONFIG_HOME/$i"
			done
			cd -
		;;
		"rc")
			cd "$OPT/rc"
			for i in * ; do
				backup "$HOME/.$i"
				lns "$i" "$HOME/.$i"
			done
			cd -
		;;
		"zsh")
			backup "$HOME/.zprofile"
			lns "$HOME/.profile" "$HOME/.zprofile"
		;;
		"bash")
			backup "$HOME/.bash_profile"
			lns "$HOME/.profile" "$HOME/.bash_profile"
		;;
		"nvim")
			lns "$HOME/.vim" "$XDG_CONFIG_HOME/nvim"
			lns "$HOME/.vimrc" "$XDG_CONFIG_HOME/nvim/init.vim"
		;;
		"git")
			if iaskyn "Should I configure git as you want?:" ; then
				if iaskyn "\tMaybe I can use protonmail and your OS-username that for?"; then
					git config --global  user.email $(whoami)@protonmail.com
					git config --global user.name $(whoami)
				fi
				echo "Nice, then enter your:";
				echo "Username:"; read name
				echo "E-mail:"; read email
				git config --global user.name $name
				git config --global user.email $email
			fi
		;;
		"dir")
			mkdir -p $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	         	 	 $HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
		;;
		"mega")
			backup $HOME/imgs
			lns "$HOME/MEGA/neij/imgs"  "$HOME/imgs"
			backup "$HOME/audio"
			lns "$HOME/MEGA/neij/audio" "$HOME/audio"
		;;
		dict)
			lns "$OPT/dict" "$OPT/.dict"
		;;
	esac
done
