#!/bin/sh 

 # Fish shell.
 sudo mv /etc/fish/config.fish /etc/fish/config.fish.backup
 sudo ln -s ~/code/scripts/sh/fish/jien_config.fish	/etc/fish/config.fish

 # Editor.

 sudo mv /etc/vimrc /etc/vimrc.backup
 sudo ln -s ~/code/scripts/vim/jien_vimrc		/etc/vimrc
 sudo mv /usr/share/nvim/sysinit.vim			/usr/share/nvim/sysinit.vim.backup
 sudo ln -s ~/code/scripts/vim/jien_vimrc		/usr/share/nvim/sysinit.vim
