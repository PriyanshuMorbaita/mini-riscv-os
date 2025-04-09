#include "../main.h"
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

void putchar(char c) {
    volatile uint8_t *uart = (uint8_t *)0x10000000;
    while (!(uart[5] & (1 << 5)));  
    uart[0] = c;
}


char getchar() {
    while (!(UART_LSR & UART_LSR_RX_READY)); 
    return UART_RBR;
}

void puts(const char *s) {
    while (*s) {
        putchar(*s++);
    }
}

void gets(char *buffer, size_t size) {
    size_t i = 0;
    char c;

    while (i < size - 1) {
        c = getchar();

        if (c == 127 || c == 8) { 
            if (i > 0) {
                putchar(8);
                putchar(' ');
                putchar(8);
                i--;
            }
            continue;
        }

        if (c == '\r' || c == '\n') {
            putchar('\n');
            break;
        }

        putchar(c); 
        buffer[i++] = c;
    }

    buffer[i] = '\0';
}

void io_init(void) {
    volatile uint8_t *uart = (volatile uint8_t *)UART_BASE;

    uart[1] = 0x00; 
    uart[3] = 0x80; 
    uart[0] = 0x03; 
    uart[1] = 0x00; 
    uart[3] = 0x03;
    uart[4] = 0x00; 

    puts("UART initialized\n");
}


void printf(const char *fmt, ...) {
    char c;
    va_list args;
    va_start(args, fmt);

    while ((c = *fmt++)) {
        if (c != '%') {
            putchar(c);
            continue;
        }

        c = *fmt++;
        switch (c) {
            case 'd': {
                int val = va_arg(args, int);
                char buf[16];
                int i = 0;
                if (val < 0) {
                    putchar('-');
                    val = -val;
                }
                do {
                    buf[i++] = '0' + val % 10;
                    val /= 10;
                } while (val > 0);
                while (i--) putchar(buf[i]);
                break;
            }
            case 'x': {
                unsigned int val = va_arg(args, unsigned int);
                char hex[] = "0123456789ABCDEF";
                for (int i = 28; i >= 0; i -= 4) {
                    putchar(hex[(val >> i) & 0xF]);
                }
                break;
            }
            case 's': {
                char *str = va_arg(args, char *);
                puts(str);
                break;
            }
            case '%': {
                putchar('%');
                break;
            }
            default: {
                putchar('?');
                break;
            }
        }
    }

    va_end(args);
}

void print_dec(size_t num) {
    char buf[20];
    int i = 0;

    if (num == 0) {
        putchar('0');
        return;
    }

    while (num > 0) {
        buf[i++] = '0' + (num % 10);
        num /= 10;
    }

    while (i--) {
        putchar(buf[i]);
    }
}
