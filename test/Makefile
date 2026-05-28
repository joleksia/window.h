# ========

# root directory of the makefile
MK_ROOT	= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

# compiler
CC = cc

# compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c99 -ggdb3

# ========

.PHONY : all

all :
	-$(CC) $(CFLAGS) -o $(MK_ROOT)00-compile.out $(MK_ROOT)00-compile.c -lX11
	-$(CC) $(CFLAGS) -o $(MK_ROOT)01-basic.out 	 $(MK_ROOT)01-basic.c	-lX11
	-$(CC) $(CFLAGS) -o $(MK_ROOT)02-no-api.out  $(MK_ROOT)02-no-api.c	-lX11
	-$(CC) $(CFLAGS) -o $(MK_ROOT)03-egl.out 	 $(MK_ROOT)03-egl.c		-lX11 -lEGL -lGL

.PHONY : clean

clean :
	rm -f $(MK_ROOT)00-compile.out
	rm -f $(MK_ROOT)01-basic.out
	rm -f $(MK_ROOT)02-no-api.out
	rm -f $(MK_ROOT)03-egl.out

# ========
