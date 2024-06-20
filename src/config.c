#include "config.h"

int parse_config(struct linuxkm_config* config) {
    /* 
        Assume config file is of the form
            key1=value1
            key2=value2
            key3=value3
        and the values are of the form
            [Meta]+[Control]+[Alt]+[Shift]+Key
    */
    FILE* file = fopen("/home/martin/.config/linuxkm.conf", "r");
    int line_no = 0;
    char buf[BUF_LEN];

    if (file == NULL) {
        config->exit_key = DEFAULT_EXIT_KEY;
        return 0;
    }

    while (fgets(buf, BUF_LEN, file) != NULL) {
        buf[strcspn(buf, "\n")] = 0; // TODO: handle case where no '\n' is read
        char* key = strtok(buf, "=");

        if (key == NULL) {
            line_no++;
            continue;
        } else if (strncmp(key, EXIT_KEY_STR, EXIT_KEY_LEN) == 0) {
            char* val;

            while (1) {
                val = strtok(NULL, "+");

                // TODO: make this case insensitive
                if (val == NULL) {
                    break;
                } else if (strncmp(val, META_STR, META_LEN) == 0) {
                    config->exit_key.meta = true;
                } else if (strncmp(val, SUPER_STR, SUPER_LEN) == 0) {
                    config->exit_key.meta = true;
                } else if (strncmp(val, CONTROL_STR, CONTROL_LEN) == 0) {
                    config->exit_key.control = true;
                } else if (strncmp(val, ALT_STR, ALT_LEN) == 0) {
                    config->exit_key.alt = true;
                } else if (strncmp(val, SHIFT_STR, SHIFT_LEN) == 0) {
                    config->exit_key.shift = true;
                } else if (strlen(val) == 1) {
                    config->exit_key.key = val[0];
                } else {
                    fprintf(stderr, "Unknown keybind argument in config in %d\n", line_no);
                    return 1;
                }
            }
        } else {
            fprintf(stderr, "Unknown config key: %s\n", key);
            return 1;
        }

        line_no++;
    }

    return 0;
}

/* void print_keybind(struct keybind keybind) {
    if (keybind.meta) {
        printf("Meta+");
    }
    if (keybind.control) {
        printf("Control+");
    }
    if (keybind.alt) {
        printf("Alt+");
    }
    if (keybind.shift) {
        printf("Shift+");
    }
    printf("%c\n", keybind.key);
}

void print_config(struct linuxkm_config* config) {
    printf("Exit_key: ");
    print_keybind(config->exit_key);
} */
