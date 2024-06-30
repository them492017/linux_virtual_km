CLIENT_TARGET = client
SERVER_TARGET = server
GUI_TARGET = test_gui

CC = gcc
# CFLAGS = -Wall -Werror -Wvla -lpthread
CFLAGS = -Wall -Wvla -lpthread
ASAN_FLAGS = -fsanitize=address -g
X11_FLAGS = -lX11 -lXi -DUSE_X11
GTK_FLAGS = $(shell pkg-config --cflags gtk4) $(shell pkg-config --libs gtk4)

LIBDIR := lib
SRCDIR := src
GUI_SRCDIR := gui
BUILDDIR := build
GUI_BUILDDIR := build_gui
BUILDDIR_NOX11 := build_nox11

SRCFILES := $(wildcard $(SRCDIR)/*.c)
GUI_SRCFILES := $(wildcard $(GUI_SRCDIR)/*.c)
GUI_OBJFILES := $(filter-out $(GUI_BUILDDIR)/server.o, $(patsubst $(GUI_SRCDIR)/%.c,$(GUI_BUILDDIR)/%.o, $(GUI_SRCFILES)))
CLIENT_OBJFILES := $(filter-out $(BUILDDIR)/server.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))
CLIENT_OBJFILES_NOX11 := $(filter-out $(BUILDDIR_NOX11)/server.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR_NOX11)/%.o, $(SRCFILES)))
SERVER_OBJFILES := $(filter-out $(BUILDDIR)/client.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))

ifneq ($(filter debug, $(MAKECMDGOALS)),)
	CFLAGS += -DDEBUG
endif

.PHONY: all clean nox11 debug

###############################################

all: $(SERVER_TARGET) $(CLIENT_TARGET) $(GUI_TARGET)

$(SERVER_TARGET): $(SERVER_OBJFILES)
	$(CC) $(CFLAGS) $(X11_FLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(CLIENT_TARGET): $(CLIENT_OBJFILES)
	$(CC) $(CFLAGS) $(X11_FLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(X11_FLAGS) $(ASAN_FLAGS) -I$(LIBDIR) $^ -c -o $@

###############################################

nox11: $(CLIENT_TARGET)_nox11

$(CLIENT_TARGET)_nox11: $(CLIENT_OBJFILES_NOX11)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(BUILDDIR_NOX11)/%.o : $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR_NOX11)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) $^ -c -o $@

###############################################

# gui only for server for now
gui: $(GUI_TARGET)

$(GUI_TARGET): $(GUI_OBJFILES)
	echo $(GTK_FLAGS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(GTK_FLAGS) -o $@ $^

$(GUI_BUILDDIR)/%.o : $(GUI_SRCDIR)/%.c
	mkdir -p $(GUI_BUILDDIR)
	$(CC) $(CFLAGS) $(GTK_FLAGS) $(ASAN_FLAGS) -I$(LIBDIR) $^ -c -o $@

debug:
	@:

# clean_binaries:
# 	rm $(CLIENT_TARGET) $(SERVER_TARGET)

clean:
	rm -rf $(BUILDDIR) $(BUILDDIR_NOX11) $(GUI_BUILDDIR) $(CLIENT_TARGET) $(SERVER_TARGET) \
		$(GUI_TARGET) $(CLIENT_TARGET)_nox11 $(SERVER_TARGET)_nox11
