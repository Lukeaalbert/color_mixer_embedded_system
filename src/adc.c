#include <avr/io.h>

#include "adc.h"


void adc_init(void)
{
    // Initialize the ADC

    // REFS0 set to a 1 and REFS1 set to 0 so that the analog range is between
    // 0v-5v.
    // ADLAR set to 1 so that we use 8-bit conversion results (not 10-bits).
    ADMUX |= ((1 << REFS0) | (1 << ADLAR));
    ADMUX &= ~(1 << REFS1);

    // All 3 ADPS bits set to 1 to choose a prescalar of 128 for the
    // Arduino's 16Mhz clock (16Mhz/128 = 125 KHz).
    // ADEN set to 1 to enable the ADC module.
    ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN));
    ADCSRA &= ~((1 << ADATE) | (1 << ADIF) | (1 << ADIE));
}

uint8_t adc_sample(uint8_t channel)
{
    // Set ADC input mux bits to 'channel' value
    uint8_t MASKBITS = 0x07; // = 0000 0111
    ADMUX &= ~MASKBITS;
    ADMUX |= (channel & MASKBITS);

    // Take a sample
    // Start the conversion process.
    ADCSRA |= (1 << ADSC);
    // Wait for sample to be taken
    while ((ADCSRA & (1 << ADSC)) != 0) {}
    return ADCH;
}
