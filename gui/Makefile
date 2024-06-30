TARGET := main

CC := g++
C++_FLAGS := -std=c++17 -Wall
GTK_FLAGS := $(shell pkg-config --cflags --libs gtkmm-4.0)

LIBDIR := lib
SRCDIR := src
BUILDDIR := build

SRCFILES := $(wildcard $(SRCDIR)/*.cc)
OBJFILES := $(patsubst $(SRCDIR)/%.cc,$(BUILDDIR)/%.o, $(SRCFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(C++_FLAGS) $(GTK_FLAGS) -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.cc
	mkdir -p $(BUILDDIR)
	$(CC) $(C++_FLAGS) $(GTK_FLAGS) -I$(LIBDIR) $^ -c -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
