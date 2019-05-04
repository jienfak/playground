#!/bin/sh
source $HOME/.profile
# Ask module.
source $S/sh/sh/modules/ask.sh
nil=/dev/null

backup(){
	mv $1 $1.backup 2>$nil
}



# Profile.
if ask "Should I link you profile files(~/.bash_profile, ~/.zprofile, ~/.profile etc)?[yn]:"; then
	backup $HOME/.profile
	ln -s $S/other/opt/jien_profile $HOME/.profile

	backup $HOME/.bash_profile
	ln -s $S/other/opt/jien_profile $HOME/.bash_profile

	backup $HOME/.zprofile
	ln -s $S/other/opt/jien_profile $HOME/.zprofile
	source $HOME/.profile
fi

if ask "Should I created directories in '\$HOME'\
 and change 'user-dirs.dirs' for my?[yn]:"; then
	mkdir $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	      $HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	backup $XDG_CONFIG_HOME/user-dirs.dirs
	ln -s $S/other/opt/jien_user-dirs.dirs $XDG_CONFIG_HOME/user-dirs.dirs        2>$nil
fi

# MEGA.
if ask "Should I link to MEGA disk?[yn]:"; then
	backup $HOME/imgs
	ln -s $HOME/MEGA/faksoc/imgs  $HOME/imgs
	backup $HOME/audio
	ln -s $HOME/MEGA/faksoc/audio $HOME/audio
fi

# X-es.
if ask "Should I link you X config files?(Xmodmap, Xresources etc)[yn]:"; then
	backup $HOME/.Xmodmap
	backup $HOME/.Xresources
	backup $XDG_CONFIG_HOME/awesome-mimeapps.list
	backup $XDG_CONFIG_HOME/mimeapps.list
	ln -s $S/other/opt/jien_Xmodmap          $HOME/.Xmodmap
	ln -s $S/other/opt/jien_Xresources       $HOME/.Xresources
	ln -s $S/other/opt/jien_awesome-mimeapps.list    $XDG_CONFIG_HOME/awesome-mimeapps.list
	ln -s $S/other/opt/jien_awesome-mimeapps.list    $XDG_CONFIG_HOME/mimeapps.list
	# Xinit.
	backup $HOME/.xinitrc
	ln -s $S/other/opt/jien_xinitrc          $HOME/.xinitrc
fi

# Awesome!
if ask "Should I link your 'awesome' and configs?(rc.lua etc)[yn]:"; then
	mkdir $XDG_CONFIG_HOME/awesome 2>$nil
	backup $XDG_CONFIG_HOME/awesome/rc.lua
	ln -s $S/other/opt/jien_awesome_rc.lua $XDG_CONFIG_HOME/awesome/rc.lua
fi


if ask "Should I link your mostrc file?(~/.mostc)[yn]"; then
	backup $HOME/.mostrc
	ln -s $S/other/opt/jien_mostrc $HOME/.mostrc
fi

# Fish shell.
if ask "Should I link your 'fish' and configs?(config.fish etc)[yn]:"; then
	backup $XDG_CONFIG_HOME/fish
	ln -s $S/sh/fish/ $XDG_CONFIG_HOME/fish
	# ln -s $HOME/code/S/sh/fish/jien_config.fish $XDG_CONFIG_HOME/fish/config.fish
fi

# Zsh shell.
if ask "Should I link your 'zsh' and configs(zshrc etc)[yn]:"; then
	backup $HOME/.zshrc
	ln -s $S/sh/zsh/jien_zshrc $HOME/.zshrc
fi

# sudo cp $HOME/code/S/sh/fish/completions/* /usr/share/fish/completions/



# Editor. Vim. Neovim.
if ask "Should I link your editor files?(vimrc, init.vim(neovim etc)[yn]:"; then
	# Vim.
	backup $HOME/.vimrc
	ln -s $S/vim/jien_vimrc          $HOME/.vimrc
	backup $HOME/.vim
	ln -s $S/vim                     $HOME/.vim
	# Neovim.
	backup $XDG_CONFIG_HOME/nvim
	ln -s $S/vim/                 $XDG_CONFIG_HOME/nvim
	ln -s $S/vim/jien_vimrc       $XDG_CONFIG_HOME/nvim/init.vim
fi

# Vifm.
if ask "Should I link you vifm(lf) file manager files?(~/.vifm)[yn]"; then
	backup $HOME/.vifm
	mkdir -p $XDG_CONFIG_HOME/lf
	backup $XDG_CONFIG_HOME/lf/lfrc
	ln -s $S/vim $HOME/.vifm
	ln -s $S/other/opt/jien_lfrc $XDG_CONFIG_HOME/lf/lfrc
fi

# Xfe.
if ask "Should I create your xfe rc(s)?[yn]"; then
	mkdir -p $XDG_CONFIG_HOME/xfe
	backup $XDG_CONFIG_HOME/xfe/xferc
	ln -s $S/other/opt/jien_xferc $XDG_CONFIG_HOME/xfe/xferc
fi

# Uzbl.
if ask "Should I link your uzbl config files?(config etc)[yn]:"; then
	backup $XDG_CONFIG_HOME/uzbl/config
	mkdir -p $XDG_CONFIG_HOME/uzbl
	ln -s  $S/other/opt/jien_uzbl_config $XDG_CONFIG_HOME/uzbl/config
fi

# Luakit.
if ask "Should I link you luakit config files?(userconf.lua etc)[yn]:"; then
	mkdir $XDG_CONFIG_HOME/luakit 2> $nil
	backup $XDG_CONFIG_HOME/luakit/userconf.lua
	ln -s $S/other/opt/jien_luakit_userconf.lua $XDG_CONFIG_HOME/luakit/userconf.lua
fi

# Tmux.
if ask "Should I link your tmux config files?(~/.tmux.conf)[yn]:"; then
	backup $HOME/.tmux.conf
	ln -s $S/other/opt/jien_tmux.conf $HOME/.tmux.conf
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
