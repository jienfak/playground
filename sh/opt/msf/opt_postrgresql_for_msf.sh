#!/bin/sh

#main optioning
sudo chown -R postgres:postgres /var/lib/postgres/
sudo -i -u postgres
initdb --locale $LANG -E UTF8 -D '/var/lib/postgres/data'
CTRL+D
sudo systemctl start postgresql.service

sudo -u postgres createuser user

sudo -u postrgres createdb -O user msf3


