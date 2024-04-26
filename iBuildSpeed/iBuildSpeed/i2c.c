/*
 * i2c.c
 *
 * Created: 4/25/2024 10:32:30 PM
 *  Author: Ahmed
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
char String[25];

void
startCondition_gas() {

    // I2C 0
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // wait for it to be transmitted
    while (!(TWCR0 & (1 << TWINT)))
        ;
}

void
startI2C_gas() {
    // configure output
    DDRC |= (1 << DDC4) | (1 << DDC5);
    PORTC |= (1 << PINC4) | (1 << PINC5);
    DDRC &= ~(1 << DDC4) | ~(1 << DDC5);
    TWBR0 = 50;   // set frequency
}

void
stop_gas() {
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void
setAddress_gas(uint8_t write_enable) {
    if (write_enable == 1) {
        TWDR0 = (0x28 << 1);
    } else {
        TWDR0 = (0x28 << 1) + 1;
    }
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)))
        ;
}

uint8_t
readByte_gas(uint8_t ack) {
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    while (!(TWCR0 & (1 << TWINT)))
        ;           // Wait for completion
    return TWDR0;   // Return received data
}

uint16_t
readGas() {
    startI2C_gas();
    startCondition_gas();
    setAddress_gas(0);
    uint16_t byte1 = readByte_gas(0) & (0x3F);
    uint8_t byte2 = readByte_gas(1);
    uint16_t combinedValue = (byte1 << 8) | byte2;   // Correct way to combine bytes
    // 	_delay_ms(1000);
    stop_gas();
    return combinedValue;
}

void
startCondition_brake() {

    // I2C 1
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // wait for it to be transmitted
    while (!(TWCR1 & (1 << TWINT)))
        ;
}

void
startI2C_brake() {
    // configure output
    DDRE |= (1 << DDE0) | (1 << DDE1);
    PORTE |= (1 << PINE0) | (1 << PINE1);
    DDRE &= ~(1 << DDE0) | ~(1 << DDE1);
    TWBR1 = 50;   // set frequency
}

void
stop_brake() {
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void
setAddress_brake(uint8_t write_enable) {
    if (write_enable == 1) {
        TWDR1 = (0x28 << 1);
    } else {
        TWDR1 = (0x28 << 1) + 1;
    }
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)))
        ;
}

uint8_t
readByte_brake(uint8_t ack) {
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    while (!(TWCR1 & (1 << TWINT)))
        ;           // Wait for completion
    return TWDR1;   // Return received data
}

uint16_t
readBrake() {
    startI2C_brake();
    startCondition_brake();
    setAddress_brake(0);
    uint16_t byte1 = readByte_brake(0) & (0x3F);
    uint8_t byte2 = readByte_brake(1);
    uint16_t combinedValue = (byte1 << 8) | byte2;   // Correct way to combine bytes
    // 	_delay_ms(1000);
    stop_brake();
    return combinedValue;
}