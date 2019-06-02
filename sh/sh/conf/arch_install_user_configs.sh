#!/bin/sh
source $HOME/.profile
# Ask module.
source $SHMODS/interactive/ask.sh
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
if ask "Should I link you profile files(~/.bash_profile, ~/.zprofile, ~/.profile etc)?[yn]:"; then

	backup $HOME/.bash_profile
	lns $MYOPT/profile $HOME/.bash_profile

	backup $HOME/.zprofile
	lns $MYOPT/profile $HOME/.zprofile
fi

if ask "Should I created directories in '\$HOME'\
 and change 'user-dirs.dirs' for my?[yn]:"; then
	mkdir -p $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	         $HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	conflikeln user-dirs.dirs
fi

# MEGA.
if ask "Should I link to MEGA disk?[yn]:"; then
	backup $HOME/imgs
	lns $HOME/MEGA/faksoc/imgs  $HOME/imgs
	backup $HOME/audio
	lns $HOME/MEGA/faksoc/audio $HOME/audio
fi

# X-es.
if ask "Should I link you X config files?(Xmodmap, Xresources etc)[yn]:"; then
	rclikeln Xmodmap Xresources xinitrc
	conflikeln awesome-mimeapps.list mimeapps.list
fi

# Awesome!
if ask "Should I link your 'awesome' and configs?(rc.lua etc)[yn]:"; then
	conflikeln awesome
fi

if ask "Should I link your 'Eterm' files?(~/.Eterm)[yn]:" ; then
	rclikeln Eterm
fi


if ask "Should I link your mostrc file?(~/.mostrc)[yn]:"; then
	rclikeln mostrc
fi

# Fish shell.
if ask "Should I link your 'fish' and configs?(config.fish etc)[yn]:"; then
	backup $XDG_CONFIG_HOME/fish
	lns $S/sh/fish/ $XDG_CONFIG_HOME/fish
	# ln -s $HOME/code/S/sh/fish/config.fish $XDG_CONFIG_HOME/fish/config.fish
fi

# Zsh shell.
if ask "Should I link your 'zsh' and configs(zshrc etc)[yn]:"; then
	backup $HOME/.zshrc
	lns $S/sh/zsh/zshrc $HOME/.zshrc
fi

# sudo cp $HOME/code/S/sh/fish/completions/* /usr/share/fish/completions/



# Editor. Vim. Neovim.
if ask "Should I link your editor files?(vim and Neovim)[yn]:"; then
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
if ask "Should I link you vifm(lf) file manager files?(~/.vifm)[yn]"; then
	# vifm.
	backup $HOME/.vifm
	lns $S/vim $HOME/.vifm

	conflikeln lf
fi

# Xfe.
if ask "Should I create your xfe rc(s)?[yn]"; then
	conflikeln xfe
fi

# Uzbl.
if ask "Should I link your uzbl config files?(config etc)[yn]:"; then
	conflikeln uzbl
fi

# Luakit.
if ask "Should I link you luakit config files?(userconf.lua etc)[yn]:"; then
	conflikeln luakit
fi

if ask "Should I link you vimb config files?(config etc)[yn]:" ; then
	conflikeln vimb
fi

# Tmux.
if ask "Should I link your 'tmux' and 'screen' config files?(~/.tmux.conf and ~/.screenrc)[yn]:"; then
	rclikeln screenrc
	rclikeln tmux.conf
fi

# Git.
if ask "Should I configure git as you want?[yn]:" ; then
	if ask "\tMaybe I can use protonmail and your OS-username that for?[yn]:"; then
		git config --global  user.email $(whoami)@protonmail.com
		git config --global user.name $(whoami)
	fi
	echo "Hm... nice, then enter your:";
	echo "Username:"; read name
	echo "E-mail:"; read email
	git config --global user.name $name
	git config --global user.email $email
fi
