#!/bin/sh
source $HOME/.profile # It's for '$G'(My git directory).

# It's simple script to recompile and reinstall programs from suckless.

progs="dwm surf tabbd dmenu"
gitdir=$G

for prog in $progs ; do
	cd "$gitdir/$prog"
	make
	sudo make install
done

# surft
sudo cp -f $S/sl/surf/surft.sh /bin/surft
sudo chmod 755 /bin/surft
