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
 ln -s ~/code/scripts/sh/fish/jien_config.fish	~/.config/fish/config.fish

 #xinit
 ln -s ~/code/scripts/other/opt/jien_xinitrc	~/.xinitrc

 #editor
 ln -s ~/code/scripts/vim/jien_vimrc		~/.vimrc
 mkdir ~/.config/nvim
 ln -s ~/code/scripts/vim/jien_vimrc		~/.config/nvim/init.vim
