#!/usr/bin/bash
shred -n 1 ~/.local/share/fish/fish_history 
>~/.local/share/fish/fish_history
shred -n 1 ~/.bash_history
>~/.bash_history
shred -n 1 ~/.zsh_history
