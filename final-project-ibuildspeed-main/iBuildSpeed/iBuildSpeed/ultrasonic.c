
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
// #define F_CPU  16000000UL

volatile int duration = 0;
// determines whether input has been received
// volatile int duration = 0;
volatile int start = 0;
volatile int end = 0;

void
Initialize_ultrasonic() {
    cli();

    // sets the ouptut pin
    DDRB |= (1 << DDB1);

    // initialize PB1 as LOW
    PORTB &= ~(1 << PORTB1);

    // sets output to  lights
    DDRB |= (1 << DDB2);
    PORTB &= ~(1 << PORTB2);

    DDRB |= (1 << DDRB3);
    DDRD |= (1 << DDD3);
    PORTD &= ~(1 << PORTD7);

    // sets the input pin - echo
    DDRB &= ~(1 << DDB0);

    // prescale clock by 256
    TCCR1B &= ~(1 << CS10);
    TCCR1B &= ~(1 << CS11);
    TCCR1B |= (1 << CS12);

    // sets the clock to normal mode
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B &= ~(1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    // rising edge detection
    TCCR1B |= (1 << ICES1);

    // clears input capture flag
    TIFR1 |= (1 << ICF1);

    // enables input capture
    TIMSK1 |= (1 << ICIE1);

    // sets timer2 to fast pwm
    TCCR2A |= (1 << WGM20);
    TCCR2A |= (1 << WGM21);
    TCCR2B &= ~(1 << WGM22);

    // prescale timer2 by 256
    TCCR2B &= ~(1 << CS20);
    TCCR2B |= (1 << CS21);
    TCCR2B |= (1 << CS22);

    TCCR2A &= ~(1 << COM2A1);
    TCCR2A |= (1 << COM2A0);

    TCCR2A |= (1 << COM2B1);

    OCR2A = 200;

    sei();
}
void
send_trigger() {
    _delay_ms(60);
    PORTB |= (1 << PORTB1);
    _delay_us(10);
    PORTB &= ~(1 << PORTB1);
}

uint16_t
get_distance() {
    return abs((duration * 34000 * 256) / (16000000 * 2));
}

ISR(TIMER1_CAPT_vect) {

    if (TCCR1B & (1 << ICES1)) {   // if rising edge is detected
        TCNT1 = 0;
        start = TCNT1;
    } else {
        end = TCNT1;
        if (end >= start) {
            duration = end - start;
        } else {
            duration = end - start + 65535;   // 2^16 = 65536 = no. of ticks before overflow
        }
    }

    TIFR1 |= (1 << ICF1);     // Clear input capture flag
    TCCR1B ^= (1 << ICES1);   // Toggle trigger
}
