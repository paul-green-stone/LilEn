OBJDIR		:= objects
OBJS 		:= $(addprefix $(OBJDIR)/, Window.o)

INCLUDE		:= source/include.h
WINDOW		:= $(addprefix source/Window/, window.c window.h)

LIBRARY 	:= liblilen.a

AR 			:= ar
ARFLAGS 	:= -r -c

LD			:= ld
LDFLAGS 	:= -lSDL2 -lSDL2_image -lm

CC			:= gcc
CFLAGS 		:= -g -c
ALL_CFLAGS 	:= -Wall -Wextra -pedantic-errors -fPIC -O2

# ================================================================ #

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/Window.o: $(WINDOW) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(shell mkdir -p $(OBJDIR))

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(LIBRARY)