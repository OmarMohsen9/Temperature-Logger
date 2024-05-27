#ifndef lcd_driver_h
#define lcd_driver_h


#include <avr/io.h>
#include<util/delay.h>

#define LCD_CTR_DIR DDRB
#define LCD_CTR_PORT PORTB
#define LCD_DATA_DIR DDRC
#define LCD_DATA_PORT PORTC

#define RS PB1
#define RW PB2
#define E PB3

#define CLR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define CURSOR_1ST 0x80
#define CURSOR_2ND 0xC0
#define TWO_LINE_8BIT 0x38
#define TWO_LINE_4BIT 0x28
#define CURSOR_RIGHT 0x06
#define CURSOR_BLINK 0x0F

//functions prototypes

void lcd_cmd(uint8_t cmd);
void lcd_init(void);
void lcd_displaychar(uint8_t data);
void lcd_displayString(const char *Str);
void lcd_cleardisplay(void);
void lcd_movecursor(uint8_t row,uint8_t col);
void lcd_inttostr(int data);
void lcd_cuschar (unsigned char loc, unsigned char *msg);

#endif // lcd_driver_h
