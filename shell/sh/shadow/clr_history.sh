#!/usr/bin/bash
shred -n 5 ~/.local/share/fish/fish_history 
>~/.local/share/fish/fish_history
shred -n 5 ~/.bash_history
>~/.bash_history
shred -n 5 ~/.zsh_history
