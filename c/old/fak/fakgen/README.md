
fakgen - program generating individual dictionary of passwords for researching by it.
Program generates all combinations of words you specified.
For example:
```sh
> fakgen password 123 login root -n 2 -m
password
123
login
root
123password
loginpassword
rootpassword
password123
login123
root123
passwordlogin
123login
rootlogin
passwordroot
123root
loginroot
```
---
Installing:
```sh
git clone https://github.com/jienfak/fakgen
cd fakgen
make all
make clean
make install
```
---
Uninstalling:
```sh
cd fakgen
make uninstall
```
---
To get help enter 'fakgen -h' or 'fakgen --help'.

**Enjoy.**
