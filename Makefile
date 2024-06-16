CLIENT_TARGET = client
SERVER_TARGET = server

CC = gcc
CFLAGS = -Wall -Werror -Wvla
ASAN_FLAGS = -fsanitize=address -g

# Check for X11 using pkg-config
X11_LIBS := $(shell pkg-config --libs x11)

ifeq ($(strip $(X11_LIBS)),)
else
	CFLAGS += -lX11 -DUSE_X11
endif

LIBDIR := lib
SRCDIR := src
BUILDDIR := build

SRCFILES := $(wildcard $(SRCDIR)/*.c)
CLIENT_OBJFILES := $(filter-out $(BUILDDIR)/server.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))
SERVER_OBJFILES := $(filter-out $(BUILDDIR)/client.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))

.PHONY: all
.PHONY: clean

###############################################

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_OBJFILES)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(CLIENT_TARGET): $(CLIENT_OBJFILES)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) $^ -c -o $@

clean:
	rm -rf $(BUILDDIR) $(CLIENT_TARGET) $(SERVER_TARGET)
