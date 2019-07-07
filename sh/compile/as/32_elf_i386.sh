#!/usr/bin/bash
as --32 file.s -o file.o
ld -melf_i386 -s file.o -o file
