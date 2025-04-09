#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_BASE        0x10000000UL

#define UART_THR         (*(volatile uint8_t *)(UART_BASE + 0x00))
#define UART_RBR         (*(volatile uint8_t *)(UART_BASE + 0x00))
#define UART_IER         (*(volatile uint8_t *)(UART_BASE + 0x01))
#define UART_LCR         (*(volatile uint8_t *)(UART_BASE + 0x03))
#define UART_MCR         (*(volatile uint8_t *)(UART_BASE + 0x04))
#define UART_LSR         (*(volatile uint8_t *)(UART_BASE + 0x05))

#define UART_LSR_TX_READY 0x20
#define UART_LSR_RX_READY 0x01

#endif
