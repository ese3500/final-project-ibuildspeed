/*
 * GccApplication1.c
 *
 * Created: 2/23/2024 2:21:11 PM
 * Author : atewfik1
 */

#define F_CPU          16000000UL
#define BAUD_RATE      9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>   // Include the math library for the exp() function
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "uart.h"

char String[25];

// keeps track of distance
int distance = 0;
volatile int discrete = 0;

// determines whether input has been received
volatile int duration = 0;
volatile int start = 0;
volatile int end = 0;
volatile int count = 0;

int speed = 0;   // neutral

int currADC = 0;
double duty = 0;

void
Initialize_PWM() {
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
Initialize_throttle() {
    cli();
    // input pins
    DDRC &= ~(1 << DDRC1);
    DDRC &= ~(1 << DDRC2);
    // 0V (min) to 5V (max)
    // 0 --> 1023
    sei();
}

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
Initialize_sensor() {
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

ISR(PCINT2_vect) {
    _delay_us(2);
    if (((PIND >> 0x7) && 0x1) == 1) {
        discrete ^= 1;
    }
    if (discrete == 0) {
        sprintf(String, "Continuous \n");
        UART_putstring(String);
    } else if (discrete == 1) {
        sprintf(String, "Discrete \n");
        UART_putstring(String);
    }
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

    // if(TCCR1B & (1<<ICES1)) {
    // TCNT1 = 0;
    // TCCR1B &= ~(1<<ICES1); //switches to falling edge detection
    // } else {
    // count = ICR1;
    // TCCR1B |= (1<<ICES1); //switches to rising edge
    // }
}

void
brake() {
    OCR0B = OCR0A * 6.1 / 100.0;
}

void
lowSpeed() {
    OCR0B = OCR0A * 10.1 / 100.0;
}

void
medSpeed() {
    OCR0B = OCR0A * 11.1 / 100.0;
}

void
highSpeed() {
    OCR0B = OCR0A * 12.1 / 100.0;
}

void
neutral() {
    OCR0B = OCR0A * 9.1 / 100.0;
}

double
set_brake(uint16_t brake_value) {
    // Constants for the formula
    const double L = 6.1;     // Lower asymptote
    const double U = 8.9;     // Upper asymptote
    const double k = 0.008;   // Decay rate
    const double x0 = 512;    // Midpoint

    // Logistic decay formula
    double result = L + (U - L) / (1 + exp(k * (brake_value - x0)));

    return (OCR0A * result / 100.0);
}

double
set_throttle(uint16_t acc_value) {
    // Define start and end points of input and output ranges
    const double start_x = 0;
    const double end_x = 1023;
    const double start_y = 9.1;
    const double end_y = 12.1;

    // Calculate slope (change in y / change in x)
    const double slope = (end_y - start_y) / (end_x - start_x);

    // Calculate and return the output value using the linear equation
    double result = start_y + slope * (acc_value - start_x);

    return (OCR0A * result / 100.0);
}
void
drive() {
    distance = (duration * 34000 * 256) / (16000000 * 2);
    // read the throttle value
    uint16_t acc_value = readADC(1);
    sprintf(String, "VROOOMM: %d \n", acc_value);
    UART_putstring(String);

    uint16_t brake_value = readADC(2);
    sprintf(String, "STOPPP: %d \n", brake_value);
    UART_putstring(String);

    if (brake_value > 0) {
        // both are being pressed --> we want to brake
        OCR0B = set_brake(brake_value);
    } else if (acc_value > 0) {
        OCR0B = set_throttle(acc_value);
    }
    // if (speed == 0) {
    //     neutral();
    // }

    // if (speed == 1) {                          // speed is low
    //     if (distance < 30 && distance > 0) {   // speed is low and distance to object is 30cm
    //         brake();
    //     } else {
    //         lowSpeed();
    //     }
    // }

    // if (speed == 2) {   // speed is medium
    //     if (distance < 40 && distance > 0) {
    //         brake();
    //     } else {
    //         medSpeed();
    //     }
    // }

    // if (speed == 3) {   // speed is high
    //     if (distance < 55 && distance > 0) {
    //         brake();
    //     } else {
    //         highSpeed();
    //     }
    // }
}

// 9.1 -> neutral
// 6.1 -> min
// 12.1 -> max

int
main(void) {

    UART_init(BAUD_PRESCALER);
    Initialize_sensor();
    Initialize_throttle();
    Initialize_PWM();
    Initialize_ADC();
    neutral();
    _delay_ms(10000);
    while (1) {
        lights();
        drive();
        _delay_ms(60);
        PORTB |= (1 << PORTB1);
        _delay_us(10);
        PORTB &= ~(1 << PORTB1);
        sprintf(String, "distance: %d \n", distance);
        UART_putstring(String);

        _delay_ms(100);
    }
}
