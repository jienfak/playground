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
# Variables.

	set MACHINE_NAME (uname -ormi)
	# Greeting.
	set SHELL_VERSION (fish -v)
	set fish_greeting " "

	# Fast using.
	set -g S $HOME/code/scripts

	# Editor for standard.
	which nvim > /dev/null 2>&1
	if test $status = 0 # Neovim is here.
		set -g EDITOR (which nvim)
		set -g PAGER /usr/share/nvim/runtime/macros/less.sh
	else
		which vim
		if test $status = 0 # Vim is here.
			set -g EDITOR (which vim)
			set -g PAGER /usr/share/vim/vim81/macros/less.sh
		else # Standard utils if found nothing.
			set -g EDITOR (which cat)
			set -g PAGER (which less)
		end
	end

	# GUI editor.
	set -g VISUAL (which gvim)

	# Manpager.
	# set -g PAGER (which less)" -R"
	set -g MANPAGER (which less)" -r"
	# Path.
	# set -g PATH $HOME/code/scripts/other/my_utils $PATH
	# GCC variables.
	set -g C_USR_MODULES "$HOME/code/scripts/c/modules/lib"

	# XDG.
	set -g XDG_CONFIG_HOME "$HOME/.config/"

	set last_status

# Aliases.
echo Setting aliases...
	alias ed $EDITOR # --description "Edit file."
	alias edsu "sudo $EDITOR" # --description "Edit file like root."
	alias edg $VISUAL # --description "Edit file with graphical text editor."
	alias edgsu "sudo $VISUAL" # --description "Edit file with graphical text editor like root."
	alias sctl "sudo systemctl" # --description "Alias for systemctl."
	alias pager "$PAGER" # --description "Standard pager."
	alias manpager "$MANPAGER"

	alias "ev" "eval" # --description "Evaluate text."
	alias "py"  (which "python") # --description "Python interpreter."
	alias "py2" (which "python2") # --description "Python interpreter version 2."
	alias "py3" (which "python3") # --description "Python interpreter version 3."
	alias "pl6" (which "perl6") # --description "Perl6 interpreter."
	alias "pl"  (which "perl") # --description "Perl5 interpreter."
	alias "rb"  (which "ruby") # --description "Ruby interpreter."
	alias "tcl" (which "tclsh") # --description "TCL interpreter."
	alias "lsp" (which "clisp") # --description "LISP interpreter."
	alias "f"   (which "gfortran") # --description "FORTRAN compiler."
	alias "c"   (which "cc")
	alias "cc"  (which "g++")

	alias "mnt"  "sudo mount"
	alias "umnt" "sudo umount"

	alias "sudo" 'sudo -p "\$->#_"'
	alias "info" 'info --vi-keys'
	alias "ipython"  "ipython --TerminalInteractiveShell.editing_mode=vi"
	alias "ipython2" "ipython2 --TerminalInteractiveShell.editing_mode=vi"
	alias "ipython3" "ipython3 --TerminalInteractiveShell.editing_mode=vi"


# Functions-aliases.
function helpa -d 'Automaticaly gets help for a program'
	# Check manual first.
	man $argv
	if test $status = 0
		return
	end

	# Check info.
	info --version
	if test $status = 0 
		info $argv
		if test $status = 0
			return
		end
	end
	
	# Check 'help' options.
	which $argv >/dev/null 2>&1
	if test $status != 0
		echo "help: Program '$argv' not found"
		return 
	end
	
	eval $argv -h > /dev/null 2>&1
	if test $status = 0
		eval $argv -h | manpager 2>&1
		return
	end

	eval $argv --help > /dev/null 2>&1
	if test $status = 0
		eval $argv --help | manpager 2>&1
		return
	end

	eval $argv -help > /dev/null 2>&1
	if test $status = 0
		eval $argv -help | manpager 2>&1
		return
	end

	eval $argv help > /dev/null 2>&1
	if test $status = 0
		eval $argv help | manpager 2>&1
		return
	end

	eval $argv > /dev/null 2>&1
	if test $status != 0
		eval $argv | manpager 2>&1
		return
	end

	echo "help: Could not get any help!"
end

function manual -d 'Get help about programing languages.'
		
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

# Right prompt.
function fish_right_prompt
	if test $last_status -ne 0
		echo -n (set_color red) =\( (set_color normal)
	end
	echo (set_color yellow)"["(set_color normal)(date +%R)(set_color yellow)"]" (set_color normal)
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
		set fish_color_comment           yellow
		set fish_color_error             grey
		set fish_color_operator          $color_cwd
		set fish_color_autosuggestion    "brgrey"
		set fish_color_command           "--bold"

echo \
	# Start message
\<-------------------------------------------------\>\n\
'|   ' \<(set_color red)F(set_color green)A(set_color blue)K(set_color normal)-\>\
"|"(set_color red)Freedom(set_color normal)-\>\
(set_color green)Anarchy(set_color normal)\<-\
(set_color blue)Knowledge(set_color normal)\<-"|"\
(set_color red)F(set_color green)A(set_color blue)K(set_color normal)\>"    |"\n\
\<-------------------------------------------------\>\n\n\
Welcome to the system, (set_color $color_cwd)$USER(set_color normal)!\n\
You are on (set_color yellow)$MACHINE_NAME(set_color normal).\n\
Now you are using (set_color green)$SHELL_VERSION(set_color normal).\n
