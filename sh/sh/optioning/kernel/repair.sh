#!/usr/bin/sh

#try
sudo pacman-mirrors -g
sudo pacman -Syyu
sudo mkinitcpio -P

#or
mount /dev/sda3 /mnt
cd /mnt
mount -t proc proc /mnt/proc
mount -t sysfs sys /mnt/sys
mount -o bind /dev /mnt/dev
mount -t devpts pts /mnt/dev/pts/
chroot /mnt
#where "/dev/sda" is a directory with linux
