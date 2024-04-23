
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

void
Initialize_light_PWM() {
    cli();

    // sets the ouptut pin
    DDRD |= (1 << DDD5);

    // prescale clock by 1024
    TCCR0B |= (1 << CS00);
    TCCR0B &= ~(1 << CS01);
    TCCR0B |= (1 << CS02);

    // sets the clock to PWM mode
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << WGM02);

    // clears input capture flag
    TIFR1 |= (1 << ICF1);

    // 	enables compare match
    TCCR0A &= ~(1 << COM0A1);
    TCCR0A |= (1 << COM0A0);

    TCCR0A |= (1 << COM0B1);
    OCR0A = 255;

    sei();
}

void
lights() {
    uint16_t currADC = readADC(0);
    sprintf(String, "light ADC: %d \n", currADC);
    UART_putstring(String);
    if (currADC < 300 && currADC > 200) {   // low brightness
        OCR2B = OCR2A * 1.0 / 3.0;
    } else if (currADC < 200 && currADC > 100) {   // medium brightness
        OCR2B = OCR2A * 2.0 / 3.0;
    } else if (currADC < 100) {   // high brightness
        OCR2B = OCR2A;
    } else {   // off
        OCR2B = 0;
    }
}