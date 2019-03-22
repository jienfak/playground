#!/bin/sh

# Directories.
scripts="$HOME/code/scripts"
ask () {
	echo -n $1
	read answer
	if [ $answer = y ]; then return 0 ;fi
	if [ $answer = Y ]; then return 0 ;fi
	return 1
}
if ask "Should I created directories in '\$HOME'\n\
 and change 'user-dirs.dirs' for my?[yn]:"; then
mkdir $HOME/video $HOME/docs $HOME/temps $HOME/shared \
	$HOME/code/ $HOME/progs $HOME/torrent $HOME/bluetooth
	mv $HOME/.config/user-dirs.dirs                  $HOME/.config/user-dirs.dirs.backup
	ln -s $scripts/other/opt/jien_user-dirs.dirs $HOME/.config/user-dirs.dirs
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
	mkdir $HOME/.config/awesome
	mv $HOME/.config/awesome/rc.lua  $HOME/.config/awesome/rc.lua.backup
	ln -s $HOME/code/scripts/other/opt/jien_awesome_rc.lua $HOME/.config/awesome/rc.lua
fi

# Fish shell.
if ask "Should I link your 'fish' scripts and configs?(config.fish etc)[yn]:"; then
	mv $HOME/.config/fish $HOME/.config/fish.backup
	ln -s $HOME/code/scripts/sh/fish/ $HOME/.config/fish
	# ln -s $HOME/code/scripts/sh/fish/jien_config.fish $HOME/.config/fish/config.fish
fi

# Zsh shell.
if ask "Should I link your 'zsh' scripts and configs(zshrc etc)[yn]:"; then
	mv $HOME/.zshrc $HOME/.zshrc.backup
	ln -s $HOME/code/scripts/sh/zsh/jien_zshrc $HOME/.zshrc
fi

# sudo cp $HOME/code/scripts/sh/fish/completions/* /usr/share/fish/completions/



# Editor.
if ask "Should I link your editor files?(vimrc, init.vim(neovim etc)[yn]:"; then
	# Vim.
	mv $HOME/.vimrc                                  $HOME/.vimrc.backup
	ln -s $HOME/code/scripts/vim/jien_vimrc          $HOME/.vimrc
	mv $HOME/.vim $HOME/.vim.backup
	ln -s $HOME/code/scripts/vim                     $HOME/.vim
	# Neovim.
	mv $HOME/.config/nvim/ $HOME/.config/nvim.backup
	ln -s $HOME/code/scripts/vim/                 $HOME/.config/nvim
	ln -s $HOME/code/scripts/vim/jien_vimrc       $HOME/.config/nvim/init.vim
fi

if ask "Should I link your uzbl config files?(config etc):"; then
	ln -s  $scripts/other/opt/jien_uzbl_config ~/.config/uzbl/config
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
