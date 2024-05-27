#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//operation modes
#define ASYNCHRONOUS_NORMAL 16
#define ASYNCHRONOUS_DOUBLE 8
#define SYNCHRONOUS 2
//functions
void usart_init(unsigned long baud);
void usart_txchar(char data);
char usart_rx(void);
void usart_txsting(char *ptr);
void usart_inttostr(int data);
#endif // USART_DRIVER_H
