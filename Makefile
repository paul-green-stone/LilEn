OBJDIR		:= objects
OBJS 		:= $(addprefix $(OBJDIR)/, Window.o Core.o Timer.o Text.o Texture.o)
COREOBJS	:= $(addprefix $(OBJDIR)/, core.o cJSON.o error.o file.o)

INCLUDE		:= source/LilEn.h

# ================================================================ #
# Window module 
WINDOW		:= $(addprefix source/Window/, window.c window.h)

# ================================================================ #
# Timer module 
TIMER		:= $(addprefix source/Timer/, timer.c timer.h)

# ================================================================ #
# Text module
TEXT		:= $(addprefix source/Text/, text.c text.h)

# ================================================================ #
# Texture module
TEXTURE		:= $(addprefix source/Texture/, texture.c texture.h)

# ================================================================ #
# Core module 
CORE		:= $(addprefix source/Core/, core.c core.h)
CJSON		:= $(addprefix source/Core/cJSON/, cJSON.c cJSON.h)
ERROR		:= $(addprefix source/Core/Error/, error.c error.h)
FILE		:= $(addprefix source/Core/File/, file.c file.h)

STATIC 		:= liblilen.a
SHARED		:= liblilen.so

AR 			:= ar
ARFLAGS 	:= -r -c

LD			:= ld
LDFLAGS 	:= `pkg-config --cflags --libs sdl2` `pkg-config --cflags --libs SDL2_image` `pkg-config --cflags --libs SDL2_ttf` `pkg-config --cflags --libs SDL2_mixer` -lm

CC			:= gcc
CFLAGS 		:= -g -c `pkg-config --cflags --libs sdl2` `pkg-config --cflags --libs SDL2_image` `pkg-config --cflags --libs SDL2_ttf` `pkg-config --cflags --libs SDL2_mixer` -lm

ALL_CFLAGS 	:= -Wall -Wextra -pedantic-errors -fPIC -O2

# ================================================================ #

all: $(STATIC)

$(STATIC): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# ================================================================ #
# Window module
$(OBJDIR)/Window.o: $(WINDOW) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

# ================================================================ #
# Timer module 
$(OBJDIR)/Timer.o: $(TIMER) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

# ================================================================ #
# Text module 
$(OBJDIR)/Text.o: $(TEXT) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

# ================================================================ #
# Core module 
$(OBJDIR)/Core.o: $(COREOBJS)
	$(LD) -r -o $@ $^
	rm $(COREOBJS)

# ================================================================ #
# Texture module
$(OBJDIR)/Texture.o: $(TEXTURE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/core.o: $(CORE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/file.o: $(FILE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/error.o: $(ERROR) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/cJSON.o: $(CJSON) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

# ================================================================ #

$(shell mkdir -p $(OBJDIR))

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(STATIC) $(SHARED)