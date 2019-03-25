#!/bin/sh
source $HOME/.profile
# Ask module.
source $S/sh/sh/modules/ask.sh

if ask "Should I created directories in '\$HOME'\
 and change 'user-dirs.dirs' for my?[yn]:"; then
	mkdir $HOME/video $HOME/docs $HOME/temps $HOME/shared \
		$HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	mv $XDG_CONF_HOME/user-dirs.dirs $XDG_CONF_HOME/user-dirs.dirs.backup
	ln -s $S/other/opt/jien_user-dirs.dirs $XDG_CONF_HOME/user-dirs.dirs
fi

# MEGA.
if ask "Should I link to MEGA disk?[yn]:"; then
	ln -s $HOME/MEGA/faksoc/imgs $HOME/
	ln -s $HOME/MEGA/faksoc/audio $HOME/audio
fi

# X-es.
if ask "Should I link you X config files?(Xmodmap, Xresources etc)[yn]:"; then
	mv    $HOME/.Xmodmap                               $HOME/.Xmodmap.backup
	mv    $HOME/.Xresources                            $HOME/.Xresources.backup
	ln -s $HOME/code/S/other/opt/jien_Xmodmap    $HOME/.Xmodmap
	ln -s $HOME/code/S/other/opt/jien_Xresources $HOME/.Xresources
	# Xinit.
	ln -s $HOME/code/S/other/opt/jien_xinitrc $HOME/.xinitrc
fi

# Awesome!
if ask "Should I link your 'awesome' S and configs?(rc.lua etc)[yn]:"; then
	mkdir $XDG_CONF_HOME/awesome
	mv $XDG_CONF_HOME/awesome/rc.lua  $XDG_CONF_HOME/awesome/rc.lua.backup
	ln -s $HOME/code/S/other/opt/jien_awesome_rc.lua $XDG_CONF_HOME/awesome/rc.lua
fi

# Profile.
if ask "Should I link you profile files(~/.bash_profile, ~/.zprofile, ~/.profile etc)?[yn]:"; then
	mv $HOME/.profile $HOME/.profile.backup
	ln -s $S/other/opt/jien_profile $HOME/.profile

	mv $HOME/.bash_profile $HOME/.profile.backup
	ln -s $S/other/opt/jien_profile $HOME/.bash_profile

	mv $HOME/.zprofile $HOME/.profile.backup
	ln -s $S/other/opt/jien_profile $HOME/.zprofile
fi

if ask "Should I link your mostrc file?(~/.mostc)[yn]"; then
	mv $HOME/.mostrc $HOME/.mostrc.backup
	ln -s $S/other/opt/jien_mostrc $HOME/.mostrc
fi

# Fish shell.
if ask "Should I link your 'fish' S and configs?(config.fish etc)[yn]:"; then
	mv $XDG_CONF_HOME/fish $XDG_CONF_HOME/fish.backup
	ln -s $HOME/code/S/sh/fish/ $XDG_CONF_HOME/fish
	# ln -s $HOME/code/S/sh/fish/jien_config.fish $XDG_CONF_HOME/fish/config.fish
fi

# Zsh shell.
if ask "Should I link your 'zsh' S and configs(zshrc etc)[yn]:"; then
	mv $HOME/.zshrc $HOME/.zshrc.backup
	ln -s $HOME/code/S/sh/zsh/jien_zshrc $HOME/.zshrc
fi

# sudo cp $HOME/code/S/sh/fish/completions/* /usr/share/fish/completions/



# Editor. Vim. Neovim.
if ask "Should I link your editor files?(vimrc, init.vim(neovim etc)[yn]:"; then
	# Vim.
	mv $HOME/.vimrc                                  $HOME/.vimrc.backup
	ln -s $HOME/code/S/vim/jien_vimrc          $HOME/.vimrc
	mv $HOME/.vim $HOME/.vim.backup
	ln -s $HOME/code/S/vim                     $HOME/.vim
	# Neovim.
	mv $XDG_CONF_HOME/nvim/ $XDG_CONF_HOME/nvim.backup
	ln -s $HOME/code/S/vim/                 $XDG_CONF_HOME/nvim
	ln -s $HOME/code/S/vim/jien_vimrc       $XDG_CONF_HOME/nvim/init.vim
fi

# Vifm.
if ask "Should I link you vifm file manager files?(~/.vifm)[yn]"; then
	mv $HOME/.vifm $HOME/.vifm.backup
	ln -s $S/vim $HOME/.vifm
fi

if ask "Should I link your uzbl config files?(config etc)[yn]:"; then
	mv $HOME
	ln -s  $S/other/opt/jien_uzbl_config $XDG_CONF_HOME/uzbl/config
fi

# Tmux.
if ask "Should I linke your tmux config files?(~/.tmux.conf)[yn]:"; then
	mv $HOME/.tmux.conf $HOME/.tmux.conf.backup
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
