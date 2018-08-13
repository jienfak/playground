#!/bin/sh

 # directories
 mkdir ~/video ~/audio ~/docs ~/temps ~/imgs ~/shared
 rm -f ~/.config/user-dir.dirs
 ln -s ~/code/scripts/other/opt/jien_user-dir.dirs ~/.config/user-dir.dirs
 mkdir ~/code/ ~/progs ~/torrent

 #X-es
 ln -s ~/code/scripts/other/opt/jien_Xmodmap	~/.Xmodmap
 ln -s ~/code/scripts/other/opt/jien_Xresources	~/.Xresources

 #fish
 sudo mv /etc/fish/config.fish /etc/fish/config.fish.backup
 sudo ln -s ~/code/scripts/sh/fish/jien_config.fish	/etc/fish/config.fish

 #xinit
 ln -s ~/code/scripts/other/opt/jien_xinitrc	~/.xinitrc

 #editor

 sudo mv /etc/vimrc /etc/vimrc.backup
 sudo ln -s ~/code/scripts/vim/jien_vimrc		/etc/vimrc
 sudo mv /usr/share/nvim/sysinit.vim			/usr/share/nvim/sysinit.vim.backup
 sudo ln -s ~/code/scripts/vim/jien_vimrc		/usr/share/nvim/sysinit.vim
 mkdir ~/.config/nvim
 ln -s ~/code/scripts/vim/jien_vimrc		~/.config/nvim/init.vim
