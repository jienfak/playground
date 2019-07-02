# ex version
VERSION = 0.1

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib


INCS = -I${X11INC} -I/usr/include
LIBS = -L${X11LIB} -lX11 -L/usr/lib -lc

# flags
CFLAGS   = -Os -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS} -DVERSION=\"${VERSION}\" -static
#CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# Solaris
#CFLAGS = -fast ${INCS} -DVERSION=\"${VERSION}\"
#LDFLAGS = ${LIBS}

# compiler and linker
CC = tcc
LD = $(CC)
