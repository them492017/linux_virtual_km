TARGET = client

CC = gcc
CFLAGS = -Wall -Werror -Wvla
ASAN_FLAGS = -fsanitize=address -g

SRC = $(TARGET).c
OBJ = $(SRC:.c=.o)

LIBDIR := lib
SRCDIR := src
BUILDDIR := build

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o, $(SRCFILES))

.PHONY: all
.PHONY: clean

###############################################

all:$(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -I$(LIBDIR) $^ -c -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(GCOVDIR) $(TARGET) *.gcov *.gcda *.gcno
