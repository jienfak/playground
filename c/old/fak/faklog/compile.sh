#/bin/sh

x86_64-w64-mingw32-g++  src/main.cpp -o bin/faklog.exe -lmsvcrt -static -Wl,--subsystem,windows
