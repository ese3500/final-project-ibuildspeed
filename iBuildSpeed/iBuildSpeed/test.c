/*
 * GccApplication1.c
 *
 * Created: 2/23/2024 2:21:11 PM
 * Author : atewfik1
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

char String[25];

	//keeps track of distance
	int distance = 0;
	volatile int discrete = 0;

	//determines whether input has been received
	volatile int duration = 0;
	volatile int start = 0;
	volatile int end = 0;
	volatile int count = 0;
	
	int speed = 0;
	
	int currADC = 0;
	double duty = 0;
	
void Initialize_PWM() {
		cli();
		
		//sets the ouptut pin
		DDRD |= (1<<DDD5);
		
		//sets the input pin
		DDRD &= ~(1<<DDD7);
		
		//enables pull up resistor
		PORTD |= (1<<PORTD7);
		
		//enable pin change interrupt
		PCICR |= (1<<PCIE2);
		
		//enable trigger for PCINT21
		PCMSK2 |= (1<<PCINT23);
		
		//prescale clock by 256
		TCCR0B &= ~(1<<CS00);
		TCCR0B &= ~(1<<CS01);
		TCCR0B |= (1<<CS02);
		
		//sets the clock to PWM mode
		TCCR0A |= (1<< WGM00);
		TCCR0A |= (1<< WGM01);
		TCCR0B |= (1<< WGM02);
		
		//clears input capture flag
		TIFR1 |= (1<<ICF1);
		
		// 	enables compare match
		TCCR0A &= ~(1<<COM0A1);
		TCCR0A |= (1<<COM0A0);
		
		TCCR0A |= (1<<COM0B1);
		
		sei();
}

void Initialize_sensor() {
	cli();
	
	//sets the ouptut pin
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	
	//initialize PB1 as LOW
	PORTB &= ~(1<<PORTB1);
	PORTB &= ~(1<<PORTB2);
	PORTB &= ~(1<<PORTB3);
	
	//sets the input pin - echo
	DDRB &= ~(1<<DDB0);
	
	//prescale clock by 256
	TCCR1B &= ~(1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	
	//sets the clock to fast PWM
		TCCR1A |= (1<< WGM10);
		TCCR1A |= (1<< WGM11);
		TCCR1B |= (1<< WGM12);
		TCCR1B |= (1<< WGM13);
		
	//enables compare match
	TCCR1A |= (1<<COM1A0);
	TCCR1A &= ~(1<<COM1A1);
	
	TCCR1A |= (1<<COM1B1);
	
	//clears input capture flag
	TIFR1 |= (1<<ICF1);
	
	//enables input capture
	TIMSK1 |= (1<<ICIE1);
	
	OCR1A = 200;
	
	sei();
}
void changeADC_MUX(int adc_mode) {
	ADMUX = adc_mode;
}
void Initialize_ADC() {
	cli();
	//clear power reduction for ADC
	PRR0 &= ~(1<<PRADC);
	
	//select vref = AVcc
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	//set ADC clock to have prescale of 128
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
	
	//select channel 0
	ADMUX &= ~(1<<MUX0);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX3);
	
	//autotrigger
	ADCSRA |= (1<<ADATE);
	
	//free running
	ADCSRB &= ~(1<<ADTS0);
	ADCSRB &= ~(1<<ADTS1);
	ADCSRB &= ~(1<<ADTS2);
	
	//disable digital input buffer
	DIDR0 |= (ADC0D);
	
	//enable ADC
	ADCSRA |= (1<<ADEN);
	
	//start conversion
	ADCSRA |= (1<<ADSC);
	sei();
}

ISR(PCINT2_vect) {
	_delay_us(2);
	if (((PIND >> 0x7) && 0x1) == 1){
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

void dutyCycle(void) {
	
	currADC = ADC;
	
		if (currADC < 129 && currADC > 30) {
		duty = 5.0;
		} else if (currADC < 228 && currADC > 129) {
		duty = 10.0;
		} else if (currADC < 327 && currADC > 228) {
		duty = 15.0;
		} else if (currADC < 426 && currADC > 327) {
		duty = 20.0;
		} else if (currADC < 525 && currADC > 426) {
		duty = 25.0;
		} else if (currADC < 624 && currADC > 525) {
		duty = 30.0;
		} else if (currADC < 723 && currADC > 624) {
		duty = 35.0;
		} else if (currADC < 822 && currADC > 723) {
		duty = 40.0;
		} else if (currADC < 921 && currADC > 822) {
		duty = 45.0;
		} else if (currADC < 921) {
		duty = 50.0;
	}
	
	ADCSRA |= (1<<ADSC);
	
}



void lights() {
	
	currADC = ADC;
	if(currADC < 300 && currADC > 200) { //low brightness
		OCR1B = OCR1A * 1.0 / 3.0;
		
	} else if (currADC < 200 && currADC > 100) { //medium brightness
		 OCR1B = OCR1A * 2.0 / 3.0;
		 
	} else if (currADC < 100) { //high brightness
		OCR1B = OCR1A;
		
	} else { //off
		OCR1B = 0;
		
	}
	ADCSRA |= (1<<ADSC);
	
}


void emergencyBrake() {
	duty = 19;
	OCR0A = duty;
}

void lowSpeed() {
	duty = 11;
	OCR0A = duty;
}

void medSpeed() {
	duty = 10;
	OCR0A = duty;
}

void highSpeed() {
	duty = 9;
	OCR0A = duty;
}

void neutral() {
	duty = 12;
	OCR0A = duty;
}

void drive() {
	
	distance = (duration * 34000 * 256) / (16000000 * 2);
	sprintf(String, "distance: %d \n", distance);
	UART_putstring(String);
	
	if(speed == 0) {
		neutral();
	}
	
	if(speed == 1) { //speed is low
		if(distance < 30 && distance > 0) { //speed is low and distance to object is 30cm
			emergencyBrake();
		} else {
			lowSpeed();
		}
	}
	
	if(speed == 2) { //speed is medium
		if(distance < 40 && distance > 0) {
			emergencyBrake();
		} else {
			medSpeed();
		}
	}
	
	if(speed == 3) { //speed is high
		if(distance < 55 && distance > 0) {
			emergencyBrake();
		} else {
			highSpeed();
		}
	}
}

int main(void)
{
	
	UART_init(BAUD_PRESCALER);
   Initialize_sensor();
   Initialize_PWM();
   Initialize_ADC();
	  
    while (1) 
    {	
		lights();
		drive();
		_delay_ms(60);
		PORTB |= (1<<PORTB3);
		_delay_us(10);
		PORTB &= ~(1<<PORTB3);
	
	_delay_ms(100);
}
	
}