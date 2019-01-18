#!/bin/sh

# Directories.
mkdir ~/video ~/docs ~/temps ~/shared
ln -s ~/MEGA/faksoc/imgs ~/
ln -s ~/MEGA/audio ~/audio
mv ~/.config/user-dirs.dirs ~/.config/user-dirs.dirs.backup
ln -s ~/code/scripts/other/opt/jien_user-dirs.dirs ~/.config/user-dirs.dirs
mkdir ~/code/ ~/progs ~/torrent ~/bluetooth

# X-es.
ln -s ~/code/scripts/other/opt/jien_Xmodmap	~/.Xmodmap
ln -s ~/code/scripts/other/opt/jien_Xresources	~/.Xresources

# Fish shell. 
mv ~/.config/fish ~/.config/fish.backup
ln -s ~/code/scripts/sh/fish/ ~/.config/fish
# ln -s ~/code/scripts/sh/fish/jien_config.fish ~/.config/fish/config.fish

# sudo cp ~/code/scripts/sh/fish/completions/* /usr/share/fish/completions/

# Xinit.
ln -s ~/code/scripts/other/opt/jien_xinitrc ~/.xinitrc

# Editor.

# Vim.
mv ~/.vimrc                                  ~/.vimrc.backup
ln -s ~/code/scripts/vim/jien_vimrc          ~/.vimrc
mv ~/.vim ~/.vim.backup
ln -s ~/code/scripts/vim                     ~/.vim

# Neovim.
mv ~/.config/nvim/ ~/.config/nvim.backup
ln -s ~/code/scripts/vim/                 ~/.config/nvim
ln -s ~/code/scripts/vim/jien_vimrc       ~/.config/nvim/init.vim

