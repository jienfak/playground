
#for i in (string match(sctl list-unit-files | cat))
#	set description (string match -r '(\*)\s+(\w+).(\w+)\s+-(( \w+)*)' (sctl status $i))
#	complete -x -c sctl -d $description -a (echo $i| cut -d : -f 1)
#end
#$string match -r '(\w+\.\w+)\s+(\w+)' (sctl list-unit-files | cat)

complete -x -c sctl -d "Just checking" -a another_completion
