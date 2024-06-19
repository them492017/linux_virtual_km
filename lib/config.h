#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_LEN 512

#define EXIT_KEY_STR "exit_key"
#define EXIT_KEY_LEN 9

#define META_STR "Meta"
#define META_LEN 5
#define SUPER_STR "Super"
#define SUPER_LEN 6
#define CONTROL_STR "Control"
#define CONTROL_LEN 8
#define ALT_STR "Alt"
#define ALT_LEN 4
#define SHIFT_STR "Shift"
#define SHIFT_LEN 6

#define DEFAULT_EXIT_KEY (struct keybind) {.control=true, .shift=true, .key='K'}

struct keybind {
    bool meta;
    bool control;
    bool alt;
    bool shift;
    char key;
};

struct linuxkm_config {
    struct keybind exit_key;
};

int parse_config(struct linuxkm_config* config);

#endif /* ifndef CONFIG_H */
