
#include <avr/interrupt.h>
#include <avr/io.h>
uint16_t
readADC(uint8_t ADCchannel) {
    // select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    // single conversion mode
    ADCSRA |= (1 << ADSC);
    // wait until ADC conversion is complete
    while (ADCSRA & (1 << ADSC)) {
    }
    return ADC;
}

void
Initialize_ADC() {
    cli();
    // clear power reduction for ADC
    PRR0 &= ~(1 << PRADC);

    // select vref = AVcc
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // set ADC clock to have prescale of 128
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS2);

    // autotrigger off
    ADCSRA &= ~(1 << ADATE);

    // disable digital input buffer
    DIDR0 |= (ADC0D);

    // enable ADC
    ADCSRA |= (1 << ADEN);
    sei();
}