TARGET = device

CC = gcc
CFLAGS = -Wall -Werror -Wvla -std=c11 -lX11

ASAN_FLAGS = -fsanitize=address -g

.PHONY: all
.PHONY: clean

###############################################

all: $(TARGET)

$(TARGET): $(TARGET).h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(GCOV_FLAGS) $(TARGET).c -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(GCOVDIR) $(TARGET) *.gcov *.gcda *.gcno
