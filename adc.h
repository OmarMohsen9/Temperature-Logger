#ifndef adc_h
#define adc_h

#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t channel_number);

#endif // adc_h
