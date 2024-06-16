TARGET1 = client
TARGET2 = server

CC = gcc
CFLAGS = -Wall -Werror -Wvla -lX11
ASAN_FLAGS = -fsanitize=address -g

LIBDIR := lib
SRCDIR := src
BUILDDIR := build

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES1 := $(filter-out $(BUILDDIR)/server.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))
OBJFILES2 := $(filter-out $(BUILDDIR)/client.o, $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES)))

.PHONY: all
.PHONY: clean

###############################################

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJFILES1)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(TARGET2): $(OBJFILES2)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) $^ -c -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET1) $(TARGET2)
