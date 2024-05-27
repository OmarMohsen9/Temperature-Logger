#include "lcd_driver.h"
#include "adc.h"
#include "usart_driver.h"

#define temp_chng_Dir DDRC
#define temp_chng_Port PINC
#define temp_chng_Pin PC2
#define buzzer_dir DDRD
#define buzzer_port PORTD
#define buzzer_pin PD7
#define Send_Key '5'
#define threshold_temp 35

uint32_t temp_cels(uint32_t readings);
uint32_t temp_kelv(uint32_t readings);
uint32_t temp_fahr(uint32_t readings);

uint8_t cmmd=0;

int main(void)
{
    // ***** Devices INIT *****
    usart_init(9600);
    lcd_init();
    adc_init();
    temp_chng_Dir &=(~(1<<temp_chng_Pin));
    sei();
    buzzer_dir |= (1<<buzzer_pin);
    buzzer_port &= (~(1<<buzzer_pin));
    // ***** Variables *****
    uint8_t count =0;
    uint32_t temp=0;
    uint8_t symbol;
    uint32_t cels_temp=0;
    //***** Setup *****
    lcd_cleardisplay();
    lcd_displayString("Press to change!");
    while(1){

        lcd_movecursor(1,0);
        temp=adc_read(0);
        cels_temp = temp_cels(temp);
        Temp_threshold_check(cels_temp);
        lcd_displayString("Temp = ");
        lcd_movecursor(1,7);
        if(!(temp_chng_Port & (1<<temp_chng_Pin)))
        {
            _delay_ms(30);
            if(!(temp_chng_Port & (1<<temp_chng_Pin))){
                count++;
                PORTD ^=(1<<PD7);
            }else{}
        }
        if (count >= 3) count = 0; else if (count < 0) count = 2;
        switch(count){
        case 1:
            temp = temp_fahr(temp);
            lcd_inttostr(temp);
            lcd_displaychar(' ');
            lcd_displaychar(' ');
            lcd_movecursor(1,11);
            lcd_displaychar('F');
            symbol = 'F';
            break;
        case 2:
            temp = temp_kelv(temp);
            lcd_inttostr(temp);
            lcd_movecursor(1,11);
            lcd_displaychar('K');
            symbol = 'K';
            break;
        default:
            temp = temp_cels(temp);
            lcd_inttostr(temp);
            lcd_displaychar(' ');
            lcd_displaychar(' ');
            lcd_movecursor(1,11);
            lcd_displaychar('C');
            symbol = 'C';
            break;
        }
            if(cmmd == Send_Key){
                usart_inttostr(temp);
                cmmd =0;
                switch(symbol){
                case 'K':
                    usart_txchar('K');
                    break;
                case 'F':
                    usart_txchar('F');
                    break;
                default:
                    usart_txchar('C');
                    break;
                }

            }


    }
    return 0;
}

ISR(USART_RXC_vect)
{
	cmmd=UDR;
}

uint32_t temp_cels(uint32_t readings){
    readings = (readings*500)/(1023);
    return readings;
}

uint32_t temp_kelv(uint32_t readings){
    readings = (readings*500)/(1023);
    readings+=273.15;
    return readings;
}

uint32_t temp_fahr(uint32_t readings){
    readings = (readings*500)/(1023);
    readings=(readings*1.8)+32;
    return readings;
}

void Temp_threshold_check(uint32_t value){
    if(value >= threshold_temp){
        buzzer_port|= (1<<buzzer_pin);
    }else{
        buzzer_port &= (~(1<<buzzer_pin));
    }
}
