.section .text.init

.global _start
.global memset_zero

.equ UART_BASE, 0x10000000 
.equ UART_TX, 0x0
.equ UART_LSR, 0x5
.equ UART_LSR_TX_READY, 0x20

_start:
    la sp, stack_top

    li t1, 'A'
    call uart_putchar

    la a0, _bss_start
    la a1, _bss_end

    addi sp, sp, -4
    sw ra, 0(sp)
    call memset_zero

    lw ra, 0(sp)
    addi sp, sp, 4

    li t1, 'B'
    call uart_putchar

    li t1, 'X'
    call uart_putchar

    call kernel_main

    li t1, 'C'
    call uart_putchar

halt:
    wfi
    j halt

memset_zero:
    addi sp, sp, -4
    sw ra, 0(sp)
    
    beq a0, a1, memset_zero_done
    
memset_loop:
    sw zero, 0(a0)
    addi a0, a0, 4
    bne a0, a1, memset_loop

memset_zero_done:
    li t1, 'Z'
    call uart_putchar
    
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

uart_putchar:
    li a0, UART_BASE
wait_uart:
    lb t0, UART_LSR(a0)  
    andi t0, t0, UART_LSR_TX_READY
    beqz t0, wait_uart   
    sb t1, UART_TX(a0)  
    ret