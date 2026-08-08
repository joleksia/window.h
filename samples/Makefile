# ========

# root directory of the makefile
MK_ROOT	= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

.PHONY : all

all :
	@# samples: X11
	-make -C $(MK_ROOT)/x11   all SRCS=01-basic.c
	-make -C $(MK_ROOT)/win32 all SRCS=01-basic.c
	
	@# samples: win32
	-make -C $(MK_ROOT)/x11   all SRCS=02-opengl.c
	-make -C $(MK_ROOT)/win32 all SRCS=02-opengl.c

.PHONY : clean

clean :
	@# samples: X11
	-make -C $(MK_ROOT)/x11   clean SRCS=01-basic.c
	-make -C $(MK_ROOT)/win32 clean SRCS=01-basic.c
	
	@# samples: win32
	-make -C $(MK_ROOT)/x11   clean SRCS=02-opengl.c
	-make -C $(MK_ROOT)/win32 clean SRCS=02-opengl.c

# ========
