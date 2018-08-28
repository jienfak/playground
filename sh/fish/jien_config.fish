# start X at login
if status --is-login
	if test -z "$DISPLAY" -a $XDG_VTNR -eq 1
		exec startx -- -keeptty
	end
end

echo Access granted.\n

# Vi editor mode.
echo Setting Vi key mode...
fish_vi_key_bindings 

echo Setting vars...
# Variables
	set MACHINE_NAME (uname -ormi)
	set ESC_COLOR_RED "\[\e[0;31;40m\]"
	set ESC_COLOR_GREEN "\[\e[0;32;40m\]"
	set ESC_COLOR_END "\[\e[00m\]"
	# Greeting.
	set SHELL_VERSION (fish -v)
	set fish_greeting " "

	# Fast using.
	set S $HOME/code/scripts

	# Editor for standard.
	which nvim > /dev/null 2>&1
	if test $status = 0
		export EDITOR=(which nvim)
		export PAGER="/usr/share/nvim/runtime/macros/less.sh"
	else
		which vim
		if test $status = 0
			export EDITOR=(which vim)
			export PAGER="/usr/share/vim/vim81/macros/less.sh"
		else
			export EDITOR=(which cat)
			export PAGER=(which less)
		end
	end

	# GUI editor.
	export VISUAL=(which gvim)

	# Pager.
	export PAGER=(which ccat)" | "(which less)" -R"
	export MANPAGER=(which less)" -R"
	# GCC variables.
	set C_USR_MODULES $HOME/code/scripts/c/modules/lib

# Aliases.
echo Setting aliases...
	alias ed $EDITOR
	alias edsu "sudo $EDITOR"
	alias service "sudo systemctl"
	alias pager "$PAGER"

# Functions-aliases.
function help -d 'Automaticaly gets help for a program'
	man $argv
	if test $status = 0
		return
	end

	info $argv
	if test $status = 0
		return
	end

	which $argv >/dev/null 2>&1
	if test $status != 0
		echo "help: Program '$argv' not found"
		return 
	end
	
	eval $argv -h > /dev/null 2>&1
	if test $status = 0
		eval $argv -h | pager 2>&1
		return
	end

	eval $argv --help > /dev/null 2>&1
	if test $status = 0
		eval $argv --help | pager 2>&1
		return
	end

	eval $argv -help > /dev/null 2>&1
	if test $status = 0
		eval $argv -help | pager 2>&1
		return
	end

	eval $argv help > /dev/null 2>&1
	if test $status = 0
		eval $argv help | pager 2>&1
		return
	end

	eval $argv > /dev/null 2>&1
	if test $status != 0
		eval $argv | pager 2>&1
		return
	end

	echo "help: Could not get any help!"
end

# Fish git prompt.
	set __fish_git_prompt_showdirtystate 'yes'
	set __fish_git_prompt_showstashstate 'yes'
	set __fish_git_prompt_showupstream 'yes'
	set __fish_git_prompt_color_branch yellow

	# Status Chars
	set __fish_git_prompt_char_dirtystate 'd'
	set __fish_git_prompt_char_stagedstate '→'
	set __fish_git_prompt_char_stashstate '↩'
	set __fish_git_prompt_char_upstream_ahead '↑'
	set __fish_git_prompt_char_upstream_behind '↓'
 
# My prompt.
function fish_prompt --description "Write out the prompt"
	set last_status $status
	set -l color_cwd
	set -l suffix

	# to get know is that a root
	switch "$USER"
		case root toor
			if set -q fish_color_cwd_root
				set color_cwd $fish_color_cwd_root
				set color_suffix white
			else
				set color_cwd $fish_color_cwd
			end
			set suffix '#'
		case '*'
			set color_cwd $fish_color_cwd
			set color_suffix white
			set suffix '$'
	end
	echo -n -s \[ (set_color blue) $SHLVL (set_color normal) \] \
	(set_color $color_cwd)"$USER"\
	(set_color normal) @ (set_color yellow)(uname -n)\
	(set_color normal)':' (set_color $color_cwd) (prompt_pwd) (set_color $color_suffix)\
	( printf '%s' (__fish_git_prompt) )\
	\( (set_color $color_cwd) $last_status (set_color normal) \)\
	"$suffix"\
	(set_color normal)
end


echo -n "Getting your permissions..."
set -l color_cwd
set -l suffix
# To get know is that a root
switch "$USER"
	case root toor
		if set -q fish_color_cwd_root
			set color_cwd $fish_color_cwd_root
		set color_suffix white	
		else
			set color_cwd $fish_color_cwd
		end
		set suffix '#'
		echo "root?!"
	case '*'
		set color_cwd $fish_color_cwd
		set color_suffix white
		set suffix '$'
		echo
end

echo -n "Setting 'Xresourses' via xrdb..."
which xrdb > /dev/null 2>&1
if test $status = 0
	xrdb -merge ~/.Xresources
	echo
else
	echo 'Nope.'
end


# Colors
	echo "Setting '$PAGER' colors..."
		# Less colors
		export LESS_TERMCAP_md=(perl -e "print \"\033[1;31m\"")
		export LESS_TERMCAP_me=(perl -e "print \"\033[0m\"")
			# Underlined
		export LESS_TERMCAP_us=(perl -e "print \"\033[1;32m\";")
		export LESS_TERMCAP_ue=(perl -e "print \"\033[0m\"; ")
			# Service info
		export LESS_TERMCAP_so=(perl -e "print \"\033[1;33m\";")
		export LESS_TERMCAP_se=(perl -e "print \"\033[0m\";")
			# Blinking color
		export LESS_TERMCAP_mb=(perl -e "print \"\033[1;32m\";")
		export LESS_TERMCAP_me=(perl -e "print \"\033[0m\";")

	echo "Setting fish colors..."
		# Fish colors
		set fish_color_comment		yellow
		set fish_color_error		grey
		set fish_color_operator		$color_cwd
		set fish_color_autosuggestion	"brgrey"

echo \
	# Start message
	\<---------------------------------------------\>\n\
	'   ' \<(set_color red)F(set_color green)A(set_color blue)K(set_color normal)-\>\
	(set_color red)Freedom(set_color normal)-\>\
	(set_color green)Anarchy(set_color normal)\<-\
	(set_color blue)Knowledge(set_color normal)\<-\
	(set_color red)F(set_color green)A(set_color blue)K(set_color normal)\>\n\
	\<---------------------------------------------\>\n\n\
	Welcome to the system, (set_color $color_cwd)$USER(set_color normal)!\n\
	You are on (set_color yellow)$MACHINE_NAME(set_color normal).\n\
	Now you are using (set_color green)$SHELL_VERSION(set_color normal).\n
