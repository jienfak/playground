#!/usr/bin/bash

# fish
shred -n 1 ~/.local/share/fish/fish_history 
>~/.local/share/fish/fish_history

# bash
shred -n 1 ~/.bash_history
>~/.bash_history

# zsh
shred -n 1 ~/.zsh_history
>~/.zsh_history
