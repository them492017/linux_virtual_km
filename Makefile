CLIENT_TARGET = client
SERVER_TARGET = server

CC = gcc
CFLAGS = -Wall -Werror -Wvla
ASAN_FLAGS = -fsanitize=address -g
X11_FLAGS = -lX11 -lXi -lpthread -DUSE_X11

LIBDIR := lib
SRCDIR := src
BUILDDIR := build
BUILDDIR_NOX11 := build_nox11

SRCFILES := $(wildcard $(SRCDIR)/*.c)
CLIENT_OBJFILES := $(filter-out $(BUILDDIR)/server.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))
CLIENT_OBJFILES_NOX11 := $(filter-out $(BUILDDIR_NOX11)/server.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR_NOX11)/%.o, $(SRCFILES)))
SERVER_OBJFILES := $(filter-out $(BUILDDIR)/client.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))

.PHONY: all clean nox11 clean_binaries

###############################################

all: $(SERVER_TARGET) $(CLIENT_TARGET)

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

# clean_binaries:
# 	rm $(CLIENT_TARGET) $(SERVER_TARGET)

clean:
	rm -rf $(BUILDDIR) $(BUILDDIR_NOX11) $(CLIENT_TARGET) $(SERVER_TARGET) \
		$(CLIENT_TARGET)_nox11 $(SERVER_TARGET)_nox11
