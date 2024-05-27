#include "usart_driver.h"

void usart_init(unsigned long baud){

unsigned short UBRR;
    UBRR = (F_CPU/(ASYNCHRONOUS_NORMAL*baud))-1;
    UBRRH = (unsigned char)(UBRR>>8);
    UBRRL = (unsigned char) (UBRR);

    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
    // enable transmit & recieve)
    //enable recieve interrupt
    UCSRB = (1<<TXEN)| (1<<RXEN) | (1<<RXCIE);
}

void usart_txchar(char data){

    while(!(UCSRA&(1<<UDRE)));
    UDR = data;
}

char usart_rx(void){

    while(!(UCSRA&(1<<RXC)));
    return UDR;
}

void usart_txsting(char * ptr){
    while(*ptr !=0){
        usart_txchar(*ptr);
        ptr++;
        _delay_ms(100);
        }
}

void usart_inttostr(int data){
    char buff[10];
    itoa(data,buff,10);
    usart_txsting(buff);
}

