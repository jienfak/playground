#!/bin/sh

 # Directories.
 mkdir ~/video ~/audio ~/docs ~/temps ~/imgs ~/shared
 mv ~/.config/user-dir.dirs ~/.config/user-dir.dirs.backup
 ln -s ~/code/scripts/other/opt/jien_user-dir.dirs ~/.config/user-dir.dirs
 mkdir ~/code/ ~/progs ~/torrent ~/bluetooth

 # X-es.
 ln -s ~/code/scripts/other/opt/jien_Xmodmap	~/.Xmodmap
 ln -s ~/code/scripts/other/opt/jien_Xresources	~/.Xresources

 # Fish shell. 
 ln -s ~/code/scripts/sh/fish/jien_config.fish ~/.config/fish/config.fish

# sudo cp ~/code/scripts/sh/fish/completions/* /usr/share/fish/completions/

 # Xinit.
 ln -s ~/code/scripts/other/opt/jien_xinitrc ~/.xinitrc

 # Editor.

 # Vim.
mv ~/.vimrc ~/.vimrc.backup
	ln -s ~/code/scripts/vim/jien_vimrc          ~/.vimrc
mv /usr/share/nvim/sysinit.vim               /usr/share/nvim/sysinit.vim.backup
	ln -s ~/code/scripts/vim/jien_vimrc          /usr/share/nvim/sysinit.vim

 # Neovim.
	 mkdir ~/.config/nvim
	 ln -s ~/code/scripts/vim/jien_vimrc       ~/.config/nvim/init.vim
