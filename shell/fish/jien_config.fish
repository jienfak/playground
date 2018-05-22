# start X at login
if status --is-login
	if test -z "$DISPLAY" -a $XDG_VTNR -eq 1
		exec startx -- -keeptty
	end
end

#vi editor mode
fish_vi_key_bindings 

#vars
set fish_greeting "FAK:Freedom Anarchy Knowledge"
set EDITOR /usr/bin/vim

# fish git prompt
set __fish_git_prompt_showdirtystate 'yes'
set __fish_git_prompt_showstashstate 'yes'
set __fish_git_prompt_showupstream 'yes'
set __fish_git_prompt_color_branch yellow

# Status Chars
set __fish_git_prompt_char_dirtystate '⚡'
set __fish_git_prompt_char_stagedstate '→'
set __fish_git_prompt_char_stashstate '↩'
set __fish_git_prompt_char_upstream_ahead '↑'
set __fish_git_prompt_char_upstream_behind '↓'
 
#my prompt
function fish_prompt --description "Write out the prompt"
    set last_status $status
    set -l color_cwd
    set -l suffix
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

	echo -n -s (set_color $color_cwd)"$USER"\
	(set_color normal) @ (set_color yellow)(prompt_hostname)\
	' ' (set_color $color_cwd) (prompt_pwd) (set_color $color_suffix)\
	( printf '%s ' (__fish_git_prompt) ) " $suffix" (set_color normal)
end
