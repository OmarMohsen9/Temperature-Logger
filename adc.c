#include "adc.h"

void adc_init(void){
    /*REFS0:1 = 1,0 -> AVCC+CAP AT AREFF
        MUX4:0 = 00000 -> DEFAULT ADC0 SELECTED
        ADLAR = 0 -> RIGHT ADJUSTED*/
    ADMUX=(1<<REFS0);
    /*ADEN=1 ->ENABLE ADC
        ADPS0:2=011->8
        PRESCALLER // F_CLOCK = 1M/8 = 125KHZ ADC OPERATION RANGE FROM 50~200KHZ*/
    ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);
}

uint16_t adc_read(uint8_t channel_number){
    channel_number&=0x07;
    ADMUX&=0xe0;
    ADMUX |= channel_number;
    ADCSRA |= (1<<ADSC);
    while(!(ADCSRA&(1<<ADSC)));
    ADCSRA|=(1<<ADIF);
    return ADC;
}
