#include "lcd_driver.h"

void lcd_cmd(uint8_t cmd){
    LCD_CTR_PORT&=(~(1<<RS));
    LCD_CTR_PORT&=(~(1<<RW));
    _delay_ms(1);
    LCD_CTR_PORT|=(1<<E);
    _delay_ms(1);
    LCD_DATA_PORT = (cmd&0xf0);
    _delay_ms(1);
    LCD_CTR_PORT&=(~(1<<E));
    _delay_ms(1);
    LCD_CTR_PORT|=(1<<E);
    _delay_ms(1);
    LCD_DATA_PORT = (cmd<<4)&0xf0;
    _delay_ms(1);
    LCD_CTR_PORT&=(~(1<<E));
    _delay_ms(1);
}
void lcd_init(void){
    LCD_CTR_DIR|=(1<<RS)|(1<<RW)|(1<<E);
    LCD_DATA_DIR=0xf0;
    lcd_cmd(RETURN_HOME);
    //LCD_CTR_PORT&=(~(1<<RW));
    _delay_ms(1);
    lcd_cmd(TWO_LINE_4BIT);
    lcd_cmd(CURSOR_OFF);
    lcd_cmd(CLR_DISPLAY);
    lcd_cmd(CURSOR_RIGHT);
}

void lcd_displaychar(uint8_t data){
    LCD_CTR_PORT|=(1<<RS);
    LCD_CTR_PORT&=(~(1<<RW));
    _delay_ms(1);
    LCD_CTR_PORT|=(1<<E);
    _delay_ms(1);
    LCD_DATA_PORT = (data&0xf0);
    _delay_ms(1);
    LCD_CTR_PORT&=(~(1<<E));
    _delay_ms(1);
    LCD_CTR_PORT|=(1<<E);
    _delay_ms(1);
    LCD_DATA_PORT = (data<<4)&0xf0;
    _delay_ms(1);
    LCD_CTR_PORT&=(~(1<<E));
    _delay_ms(1);

}

void lcd_displayString(const char *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		lcd_displaychar(Str[i]);
		i++;
	}
}
void lcd_cleardisplay(void){
    lcd_cmd(CLR_DISPLAY);
}
void lcd_movecursor(uint8_t row,uint8_t col)
{
uint8_t address ;
switch(row){
    case 0:
        address = CURSOR_1ST+col;
        break;
    case 1:
        address = CURSOR_2ND+col;
        break;
}
lcd_cmd(address);
}
void lcd_inttostr(int data){
    char buff[16];
    itoa(data,buff,10);
    lcd_displayString(buff);
}
void lcd_cuschar (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		lcd_cmd (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		lcd_displaychar(msg[i]);
	}
}
