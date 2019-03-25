#!/bin/sh

# Directories.
source $HOME/code/scripts/sh/sh/modules/dirs.sh
source $scripts/sh/sh/modules/ask.sh

if ask "Should I created directories in '\$HOME'\n\
 and change 'user-dirs.dirs' for my?[yn]:"; then
mkdir $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	$HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	mv $conf_dir/user-dirs.dirs                  $conf_dir/user-dirs.dirs.backup
	ln -s $scripts/other/opt/jien_user-dirs.dirs $conf_dir/user-dirs.dirs
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
	ln -s $HOME/code/scripts/other/opt/jien_Xmodmap    $HOME/.Xmodmap
	ln -s $HOME/code/scripts/other/opt/jien_Xresources $HOME/.Xresources
	# Xinit.
	ln -s $HOME/code/scripts/other/opt/jien_xinitrc $HOME/.xinitrc
fi

# Awesome!
if ask "Should I link your 'awesome' scripts and configs?(rc.lua etc)[yn]:"; then
	mkdir $conf_dir/awesome
	mv $conf_dir/awesome/rc.lua  $conf_dir/awesome/rc.lua.backup
	ln -s $HOME/code/scripts/other/opt/jien_awesome_rc.lua $conf_dir/awesome/rc.lua
fi

if ask "Should I link you 'profile' file?[yn]:"; then
	mv $HOME/.profile $HOME/.profile.backup
	ln -s $scripts/other/opt/jien_profile $HOME/.profile
fi

# Fish shell.
if ask "Should I link your 'fish' scripts and configs?(config.fish etc)[yn]:"; then
	mv $conf_dir/fish $conf_dir/fish.backup
	ln -s $HOME/code/scripts/sh/fish/ $conf_dir/fish
	# ln -s $HOME/code/scripts/sh/fish/jien_config.fish $conf_dir/fish/config.fish
fi

# Zsh shell.
if ask "Should I link your 'zsh' scripts and configs(zshrc etc)[yn]:"; then
	mv $HOME/.zshrc $HOME/.zshrc.backup
	ln -s $HOME/code/scripts/sh/zsh/jien_zshrc $HOME/.zshrc
fi

# sudo cp $HOME/code/scripts/sh/fish/completions/* /usr/share/fish/completions/



# Editor. Vim. Neovim.
if ask "Should I link your editor files?(vimrc, init.vim(neovim etc)[yn]:"; then
	# Vim.
	mv $HOME/.vimrc                                  $HOME/.vimrc.backup
	ln -s $HOME/code/scripts/vim/jien_vimrc          $HOME/.vimrc
	mv $HOME/.vim $HOME/.vim.backup
	ln -s $HOME/code/scripts/vim                     $HOME/.vim
	# Neovim.
	mv $conf_dir/nvim/ $conf_dir/nvim.backup
	ln -s $HOME/code/scripts/vim/                 $conf_dir/nvim
	ln -s $HOME/code/scripts/vim/jien_vimrc       $conf_dir/nvim/init.vim
fi

# Vifm.
if ask "Should I link you vifm file manager files?(~/.vifm)[yn]"; then
	mv $HOME/.vifm $HOME/.vifm.backup
	ln -s $scripts/vim $HOME/.vifm
fi

if ask "Should I link your uzbl config files?(config etc)[yn]:"; then
	mv $HOME
	ln -s  $scripts/other/opt/jien_uzbl_config $conf_dir/uzbl/config
fi

# Tmux.
if ask "Should I linke your tmux config files?(~/.tmux.conf)[yn]:"; then
	mv $HOME/.tmux.conf $HOME/.tmux.conf.backup
	ln -s $scripts/other/opt/jien_tmux.conf $HOME/.tmux.conf
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
