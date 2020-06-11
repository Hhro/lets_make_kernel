#include <fried/stdio.h>
#include <shell.hpp>
#include <keyboard.hpp>
#include <fried/string.h>

#define INCLUDE_HEADERS
#define ADD_SHELL_BUILTIN(func, name, desc) extern void func(char *args);
#include <shell.inc>
#undef ADD_SHELL_BUILTIN
#undef INCLUDE_HEADERS

struct BUILTIN_CMDS {
    void (*function)(char *);
    const char *name;
    const char *desc;
};

#define BUILTIN_CMDS_COUNT  (sizeof(builtin_cmds) / sizeof(struct BUILTIN_CMDS))

void help(char *args);
void echo(char *args);
void banner(char *args);

struct BUILTIN_CMDS builtin_cmds[] = {
    #define ADD_SHELL_BUILTIN(_func, _name, _desc) {.function = _func, .name = _name, .desc = _desc},
    #include <shell.inc>
    #undef ADD_SHELL_BUILTIN
};

void help(char *args) {
    printf("List of cmds: \n");
    for(int i = 0; i < BUILTIN_CMDS_COUNT; i++) {
        printf("%s: %s\n", builtin_cmds[i].name, builtin_cmds[i].desc);
    }
}

void echo(char *args) {
    printf("%s\n", args);
}

void execute_command(char *command_buf) {
    size_t command_buf_len = strlen(command_buf);
    size_t command_len = command_buf_len;
    for (int i = 0; i < command_buf_len; i++) {
        if (command_buf[i] == ' ') {
            command_len = i;
            break;
        }
    }

    for(int i = 0; i < BUILTIN_CMDS_COUNT; i++) {
        size_t builtin_command_name_len = strlen(builtin_cmds[i].name);
        if (command_len == builtin_command_name_len && memcmp(command_buf, builtin_cmds[i].name, command_len) == 0) {
            builtin_cmds[i].function(command_buf + command_len + 1);
        } 
    }
}

void shell_main() {
    printf("> ");

    char command_buf[300];
    int command_buf_idx = 0;
    
    while(1) {
        char key = kGetch();

        if (key == KEY_BACKSPACE) {
            // TODO: backspace support
        }
        else if (key == KEY_ENTER) {
            printf("\n");
            if (command_buf_idx > 0) {
                command_buf[command_buf_idx] = '\x00';
                execute_command(command_buf);
            }
            printf("> ");
            memset(command_buf, 0, sizeof(command_buf));
            command_buf_idx = 0;
        }
        else {
            if (key == KEY_TAB) {
                key = ' ';
            }
            if (command_buf_idx +1< sizeof(command_buf)) {
                command_buf[command_buf_idx++] = key;
                printf("%c", key);
            }
        }
    }
}
