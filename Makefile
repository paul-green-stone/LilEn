OBJDIR		:= objects
OBJS 		:= $(addprefix $(OBJDIR)/, Window.o Core.o)
COREOBJS	:= $(addprefix $(OBJDIR)/, core.o cJSON.o)

INCLUDE		:= source/include.h
WINDOW		:= $(addprefix source/Window/, window.c window.h)
CORE		:= $(addprefix source/core/, core.c core.h)
CJSON		:= $(addprefix source/core/, cJSON.c cJSON.h)

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

$(OBJDIR)/Core.o: $(COREOBJS)
	$(LD) -r -o $@ $^
	rm $(COREOBJS)

$(OBJDIR)/core.o: $(CORE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/cJSON.o: $(CJSON) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(shell mkdir -p $(OBJDIR))

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(LIBRARY)