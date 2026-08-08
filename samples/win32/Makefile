# ========

# root directory of the makefile
MK_ROOT	= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

# compiler
CC = x86_64-w64-mingw32-gcc

# compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c99 -ggdb3

# linker files
LFLAGS = -lopengl32 -lgdi32

# linker directories
LDFLAGS = # ...

# include directories
IFLAGS = # ...

# preprocessor definitions
DFLAGS = -DWINDOW_BACKEND_WIN32 \
		 -DWINDOW_BACKEND_WGL

# ========

OBJS = $(SRCS:.c=.o)
SRCS = # ...

# ========

TARGET = $(SRCS:.c=.out) 

# ========

.PHONY : all

all : $(TARGET)

.PHONY : clean

clean :
	rm -f $(TARGET)
	rm -f $(OBJS)

# ========

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LFLAGS)

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAGS)

# ========

