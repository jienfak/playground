#!/bin/sh
source $HOME/.profile
# Ask module.
source $SHMODS/interactive/iaskyn.sh
source $SHMODS/chores/loseall.sh

backup(){
	loseall mv "$1" "$1.backup"
}

lns(){
	ln -sf $1 $2
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



# Profile.
if iaskyn "Should I link you profile files[but before you have to link your '~/.profile' to get env. variables]\
	(~/.bash_profile, ~/.zprofile, etc)?";
		then
	backup $HOME/.bash_profile
	lns $MYOPT/profile $HOME/.bash_profile

	backup $HOME/.zprofile
	lns $MYOPT/profile $HOME/.zprofile
fi

if iaskyn "Should I created directories in '\$HOME'\
 and change 'user-dirs.dirs' for my?"; then
	mkdir -p $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	         $HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	conflikeln user-dirs.dirs
fi

if iaskyn "Should I link you dictionary directory? " ; then
	rclikeln "dict"
fi
##
# MEGA.
if iaskyn "Should I link to MEGA disk?"; then
	backup $HOME/imgs
	lns $HOME/MEGA/neij/imgs  $HOME/imgs
	backup $HOME/audio
	lns $HOME/MEGA/neij/audio $HOME/audio
fi

# X.
if iaskyn "Should I link you X config files?(Xmodmap, Xresources etc)"; then
	rclikeln Xmodmap Xresources xinitrc
	conflikeln awesome-mimeapps.list mimeapps.list
	ln -sf /etc/X11/xinit/xserverrc ~/.xserverrc
fi

# Awesome!
if iaskyn "Should I link your 'awesome' and configs?(rc.lua etc)"; then
	conflikeln awesome
fi

if iaskyn "Should I link your 'Eterm' files?(~/.Eterm)" ; then
	rclikeln Eterm
fi


if iaskyn "Should I link your mostrc file?(~/.mostrc)"; then
	rclikeln mostrc
fi

# Fish shell.
if iaskyn "Should I link your 'fish' and configs?(config.fish etc)"; then
	backup $XDG_CONFIG_HOME/fish
	lns $S/sh/fish/ $XDG_CONFIG_HOME/fish
	# ln -s $HOME/code/S/sh/fish/config.fish $XDG_CONFIG_HOME/fish/config.fish
fi

# Zsh shell.
if iaskyn "Should I link your 'zsh' and configs(zshrc etc)"; then
	backup $HOME/.zshrc
	lns $S/sh/zsh/zshrc $HOME/.zshrc

	backup $HOME/.zlogin
	lns $S/sh/zsh/zlogin $HOME/.zlogin
fi

# sudo cp $HOME/code/S/sh/fish/completions/* /usr/share/fish/completions/



# Editor. Vim. Neovim.
if iaskyn "Should I link your editor files?(vim and Neovim)"; then
	# Vim.
	backup $HOME/.vimrc
	lns $S/vim/vimrc          $HOME/.vimrc
	backup $HOME/.vim
	lns $S/vim                $HOME/.vim
	# Neovim.
	backup $XDG_CONFIG_HOME/nvim
	lns $S/vim             $XDG_CONFIG_HOME/nvim
	lns $S/vim/vimrc       $XDG_CONFIG_HOME/nvim/init.vim
fi

# vifm and lf.
if iaskyn "Should I link you vifm(lf) file manager files?(~/.vifm)"; then
	# vifm.
	backup $HOME/.vifm
	lns $S/vim $HOME/.vifm

	conflikeln lf
fi

# Xfe.
if iaskyn "Should I create your xfe rc(s)?"; then
	conflikeln xfe
fi

# Uzbl.
if iaskyn "Should I link your uzbl config files?(config etc)"; then
	conflikeln uzbl
fi

# Luakit.
if iaskyn "Should I link you luakit config files?(userconf.lua etc)"; then
	conflikeln luakit
fi

if iaskyn "Should I link you vimb config files?(config etc)" ; then
	conflikeln vimb
fi

# Tmux.
if iaskyn "Should I link your 'tmux' and 'screen' config files?(~/.tmux.conf and ~/.screenrc)"; then
	rclikeln screenrc
	rclikeln tmux.conf
fi

if iaskyn "Should I link your 'termite' config files?(config etc)" ; then
	conflikeln termite
fi

# Git.
if iaskyn "Should I configure git as you want?:" ; then
	if iaskyn "\tMaybe I can use protonmail and your OS-username that for?"; then
		git config --global  user.email $(whoami)@protonmail.com
		git config --global user.name $(whoami)
	fi
	echo "Hm... nice, then enter your:";
	echo "Username:"; read name
	echo "E-mail:"; read email
	git config --global user.name $name
	git config --global user.email $email
fi
