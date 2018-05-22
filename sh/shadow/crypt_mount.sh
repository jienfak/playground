#/usr/sbin/bash
sudo cryptsetup luksOpen /dev/sdb backup2
sudo cryptsetup -v status backup2
sudo mount /dev/mapper/backup2 /mnt/backup2

