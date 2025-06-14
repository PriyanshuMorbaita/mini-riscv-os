#include "../main.h"

#define MAX_CMD_LEN 64
#define MAX_ARGS 8

typedef struct {
    const char *name;
    const char *help;
    cmd_func_t func;
} command_t;

static int cmd_help(int argc, char **argv);
static int cmd_echo(int argc, char **argv);
static int cmd_clear(int argc, char **argv);
static int cmd_mem(int argc, char **argv);
static int cmd_testmalloc(int argc, char **argv);
static void print_memory_stats(memory_info_t *info);

static command_t commands[] = {
    {"help", "Display available commands", cmd_help},
    {"echo", "Echo arguments", cmd_echo},
    {"clear", "Clear the screen", cmd_clear},
    {"mem", "Show memory usage", cmd_mem},
    {"testmalloc", "Test malloc and free", cmd_testmalloc},
    {NULL, NULL, NULL}
};

void shell_init(void) {
    puts("Shell initialized\n");
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}


int strcmp(const char *s1, const char *s2) {
    return my_strcmp(s1, s2);
}

char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    while ((*dest++ = *src++));
    return original_dest;
}

size_t strlen(const char *s) {
    size_t len = 0;
    while (*s++) len++;
    return len;
}

void shell_run(void) {
    char cmd_buf[MAX_CMD_LEN];

    puts("Entering shell_run()...\n");

    while (1) {
        puts("$ ");
        int i = 0;
        while (i < MAX_CMD_LEN - 1) {
            char c = getchar();
            if (c == '\n' || c == '\r') break;
            cmd_buf[i++] = c;
            putchar(c);
        }
        cmd_buf[i] = '\0';

        puts("\nReceived command: ");
        puts(cmd_buf);
        putchar('\n');

        char *argv[MAX_ARGS];
        int argc = 0;
        char *token = cmd_buf;
        char *next_token = NULL;

        while (token && argc < MAX_ARGS) {
            while (*token == ' ') token++;
            if (*token == '\0') break;

            next_token = token;
            while (*next_token && *next_token != ' ') next_token++;

            if (*next_token) {
                *next_token = '\0';
                next_token++;
            } else {
                next_token = NULL;
            }

            argv[argc++] = token;
            token = next_token;
        }

        if (argc == 0) continue;

        bool found = false;
        for (int i = 0; commands[i].name; i++) {
            if (my_strcmp(argv[0], commands[i].name) == 0) {
                puts("Executing command...\n");
                commands[i].func(argc, argv);
                found = true;
                break;
            }
        }

        if (!found) {
            puts("Unknown command: ");
            puts(argv[0]);
            putchar('\n');
        }
    }
}

static int cmd_help(int argc, char **argv) {
    puts("Available commands:\n");
    for (int i = 0; commands[i].name; i++) {
        puts("  ");
        puts(commands[i].name);
        puts(" - ");
        puts(commands[i].help);
        putchar('\n');
    }
    return 0;
}

static int cmd_echo(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        puts(argv[i]);
        if (i < argc - 1) putchar(' ');
    }
    putchar('\n');
    return 0;
}

static int cmd_clear(int argc, char **argv) {
    puts("\033[2J\033[H"); 
    return 0;
}

static int cmd_mem(int argc, char **argv) {
    memory_info_t info;
    memory_stats(&info);

    puts("Memory Usage:\n");

    puts("  Total: ");
    print_dec(info.total);
    puts(" bytes\n");

    puts("  Used: ");
    print_dec(info.used);
    puts(" bytes\n");

    puts("  Free: ");
    print_dec(info.free);
    puts(" bytes\n");

    puts("  Blocks - Total: ");
    print_dec(info.total_blocks);
    puts(", Used: ");
    print_dec(info.used_blocks);
    puts(", Free: ");
    print_dec(info.free_blocks);
    puts("\n");

    return 0;
}

static int cmd_testmalloc(int argc, char **argv) {
    puts("=== Testing malloc() and free() ===\n");

    memory_info_t info;

    memory_stats(&info);
    puts("Before malloc:\n");
    print_memory_stats(&info);

    void *ptr = malloc(256);
    if (!ptr) {
        puts("malloc failed!\n");
        return -1;
    }

    memory_stats(&info);
    puts("\nAfter malloc(256):\n");
    print_memory_stats(&info);

    free(ptr);

    memory_stats(&info);
    puts("\nAfter free():\n");
    print_memory_stats(&info);

    return 0;
}
static void print_memory_stats(memory_info_t *info) {
    printf("Memory Usage:\n");
    printf("  Total: ");  print_dec(info->total);  printf(" bytes\n");
    printf("  Used:  ");  print_dec(info->used);   printf(" bytes\n");
    printf("  Free:  ");  print_dec(info->free);   printf(" bytes\n");

    printf("  Blocks - Total: ");
    print_dec(info->total_blocks);
    printf(", Used: ");
    print_dec(info->used_blocks);
    printf(", Free: ");
    print_dec(info->free_blocks);
    printf("\n");
}