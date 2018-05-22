#/usr/sbin/bash
sudo umount /mnt/backup2
sudo cryptsetup luksClose backup2
sudo cryptsetup -v status backup2

