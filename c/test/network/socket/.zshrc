autoload -U compinit promptinit]
compinit
#prompt
promptinit
prompt walters

setopt HIST_IGNORE_DUPS
ttyctl -f

export EDITOR=/usr/bin/vim
