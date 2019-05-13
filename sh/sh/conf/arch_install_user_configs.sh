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



# Profile.
if ask "Should I link you profile files(~/.bash_profile, ~/.zprofile, ~/.profile etc)?[yn]:"; then
	backup $HOME/.profile
	lns $S/other/opt/jien_profile $HOME/.profile

	backup $HOME/.bash_profile
	lns $S/other/opt/jien_profile $HOME/.bash_profile

	backup $HOME/.zprofile
	lns $S/other/opt/jien_profile $HOME/.zprofile
	source $HOME/.profile
fi

if ask "Should I created directories in '\$HOME'\
 and change 'user-dirs.dirs' for my?[yn]:"; then
	mkdir -p $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	         $HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	backup $XDG_CONFIG_HOME/user-dirs.dirs
	lns $S/other/opt/jien_user-dirs.dirs $XDG_CONFIG_HOME/user-dirs.dirs
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
	backup $HOME/.Xmodmap
	backup $HOME/.Xresources
	backup $HOME/.Xdefaults
	backup $XDG_CONFIG_HOME/awesome-mimeapps.list
	backup $XDG_CONFIG_HOME/mimeapps.list
	lns $S/other/opt/jien_Xmodmap                  $HOME/.Xmodmap
	lns $S/other/opt/jien_Xresources               $HOME/.Xresources
	lns $S/other/opt/jien_Xresources               $HOME/.Xdefaults
	lns $S/other/opt/jien_awesome-mimeapps.list    $XDG_CONFIG_HOME/awesome-mimeapps.list
	lns $S/other/opt/jien_awesome-mimeapps.list    $XDG_CONFIG_HOME/mimeapps.list
	# Xinit.
	backup $HOME/.xinitrc
	lns $S/other/opt/jien_xinitrc          $HOME/.xinitrc
fi

# Awesome!
if ask "Should I link your 'awesome' and configs?(rc.lua etc)[yn]:"; then
	mkdir -p $XDG_CONFIG_HOME/awesome
	backup   $XDG_CONFIG_HOME/awesome/rc.lua
	lns $S/other/opt/jien_awesome_rc.lua $XDG_CONFIG_HOME/awesome/rc.lua
fi

if ask "Should I link your 'Eterm' files?(~/.Eterm)[yn]:" ; then
	backup $HOME/.Eterm
	lns /home/jien/code/scripts/other/opt/jien_Eterm $HOME/.Eterm
fi


if ask "Should I link your mostrc file?(~/.mostc)[yn]"; then
	backup $HOME/.mostrc
	lns $S/other/opt/jien_mostrc $HOME/.mostrc
fi

# Fish shell.
if ask "Should I link your 'fish' and configs?(config.fish etc)[yn]:"; then
	backup $XDG_CONFIG_HOME/fish
	lns $S/sh/fish/ $XDG_CONFIG_HOME/fish
	# ln -s $HOME/code/S/sh/fish/jien_config.fish $XDG_CONFIG_HOME/fish/config.fish
fi

# Zsh shell.
if ask "Should I link your 'zsh' and configs(zshrc etc)[yn]:"; then
	backup $HOME/.zshrc
	lns $S/sh/zsh/jien_zshrc $HOME/.zshrc
fi

# sudo cp $HOME/code/S/sh/fish/completions/* /usr/share/fish/completions/



# Editor. Vim. Neovim.
if ask "Should I link your editor files?(vimrc, init.vim(neovim etc)[yn]:"; then
	# Vim.
	backup $HOME/.vimrc
	lns $S/vim/jien_vimrc          $HOME/.vimrc
	backup $HOME/.vim
	lns $S/vim                     $HOME/.vim
	# Neovim.
	backup $XDG_CONFIG_HOME/nvim
	lns $S/vim/                 $XDG_CONFIG_HOME/nvim
	lns $S/vim/jien_vimrc       $XDG_CONFIG_HOME/nvim/init.vim
fi

# Vifm.
if ask "Should I link you vifm(lf) file manager files?(~/.vifm)[yn]"; then
	backup $HOME/.vifm
	mkdir -p $XDG_CONFIG_HOME/lf
	backup $XDG_CONFIG_HOME/lf/lfrc
	lns $S/vim $HOME/.vifm
	lns $S/other/opt/jien_lfrc $XDG_CONFIG_HOME/lf/lfrc
fi

# Xfe.
if ask "Should I create your xfe rc(s)?[yn]"; then
	mkdir -p $XDG_CONFIG_HOME/xfe
	backup $XDG_CONFIG_HOME/xfe/xferc
	lns $S/other/opt/jien_xferc $XDG_CONFIG_HOME/xfe/xferc
fi

# Uzbl.
if ask "Should I link your uzbl config files?(config etc)[yn]:"; then
	backup $XDG_CONFIG_HOME/uzbl/config
	mkdir -p $XDG_CONFIG_HOME/uzbl
	lns  $S/other/opt/jien_uzbl_config $XDG_CONFIG_HOME/uzbl/config
fi

# Luakit.
if ask "Should I link you luakit config files?(userconf.lua etc)[yn]:"; then
	mkdir -p $XDG_CONFIG_HOME/luakit
	backup   $XDG_CONFIG_HOME/luakit/userconf.lua
	lns $S/other/opt/jien_luakit_userconf.lua $XDG_CONFIG_HOME/luakit/userconf.lua
fi

# Tmux.
if ask "Should I link your 'tmux' and 'screen' config files?(~/.tmux.conf and ~/.screenrc)[yn]:"; then
	backup $HOME/.tmux.conf
	backup $HOME/.screenrc
	lns $S/other/opt/jien_tmux.conf $HOME/.tmux.conf
	lns $S/other/opt/jien_screenrc  $HOME/.screenrc
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
